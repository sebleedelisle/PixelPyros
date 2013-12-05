
#include "Trigger.h"


//TriggerRendererBase * Trigger::defaultRenderer = new TriggerRendererBase();
// Most of this code is to create the Trigger graphics, but there
// is also stuff that works out how the triggers recharge. 

Trigger :: Trigger(){
	
	flashImage.loadImage("img/TriggerFlash.png");
	
	// the amount typename = "TriggerRocket"; of power a rocket takes away
	elapsedTime = 0;
	lastTriggerTime = 0;
	
	elapsedTime = 0;
	
	//type = TRIGGER_TYPE_FIRE_ON_MOTION;
	
	stopping = false;
	active = false;
	scale = 0;
	lastScale = 0; 
	
	// the power level for the trigger
	unitPower =1;
	
	// passed in by manager
	triggerSampleSize = 0;
	multiSampleSize = 0; 
	
	// SETTINGS :
	
	lastSettings = NULL;
	settings = NULL;
	// get defaults from the default TriggerSettings object
	copySettings(TriggerSettings::blank);
	
	//rechargeSettings = TriggerRechargeSettings::defaultSettings;
	
	motionValueCount = 20;
	showDebugData = true;
	
	angle = 0;
	triggerCount = 0;
	
	sampleBrightness = 1;
	
	
		
	
}

void Trigger :: start() {
	
	stopping = false;
		
	active = true;
	motionLevel = 0;
	
	if(!settings) return;
	
	if(settings->startEmpty)
		unitPower = 0;
	else
		unitPower = 1;
		
}

void Trigger :: stop() {
	
	stopping = true;
	
}

bool Trigger::update(float deltaTime, ofRectangle& triggerArea) {

	this->deltaTime = deltaTime;
	
	elapsedTime+=deltaTime;
	
	if((moving) || ( (elapsedTime-lastTriggerTime > 4) && (rechargeSettings->restoreSpeed>0) && !disabled && (unitPower>=rechargeSettings->triggerPower) )) {
		sampleBrightness += deltaTime;
		
	} else {
		sampleBrightness-=deltaTime*2;
	}
	sampleBrightness = ofClamp(sampleBrightness, 0, 1);
	
	moving = false;
	
	if(lastSettings!=NULL) {
		lastScale-=deltaTime*5;
		if(lastScale<=0.0) {
			lastScale = 0;
			lastSettings  = NULL;
		}
		
	}
	
	// scale up / down on start stop
	if(stopping) {
		scale-=deltaTime*5;
		if(scale<=0.0) {
			scale = 0;
			active = false;
			return false;
		}
		return active;
	} else if(scale<1){
		scale+= deltaTime*5; // (1-scale)*0.2;
		if(scale>1) scale = 1; 
	}
	
	
	
	
	if((settings!=NULL) &&(!settings->rotateOnFire)) {
		
		angle = 0;
	
		if(settings->rotationSpeed>0) {
			
			float sinoffset = settings->rotateOscillationOffset * ofMap(pos.x, triggerArea.getLeft(), triggerArea.getRight(), -1, 1);
			angle = (sin((elapsedTime + sinoffset)*settings->rotationSpeed )*settings->rotationExtent);
			
		}
		
		if(settings->rotateMirrorOffset!=0) {
			angle+= ofMap(pos.x, triggerArea.getLeft(), triggerArea.getRight(), 1, -1) * settings->rotateMirrorOffset;
			
		}
		
	}
		
	
	if(showDebugData) {
		
		 if((elapsedTime-lastUpdate>0.032)||(motionValues.size()==0)) {
		 
		 motionValues.push_back(motionLevel);
		 lastUpdate = elapsedTime;
		 
		 } else {
		 
		 float lastlevel = 0;
		 
		 lastlevel = motionValues[motionValues.size()-1];
		 
		 motionValues[motionValues.size()-1] = (motionLevel>lastlevel) ? motionLevel : lastlevel;
		 }
	
		if(motionValues.size()>motionValueCount) {
			motionValues.pop_front();
		}
	}

	
	unitPower+=rechargeSettings->restoreSpeed * deltaTime;
	if(unitPower>1) unitPower = 1;
	
	if((rechargeSettings->restoreSpeed==0) && (unitPower<=0)) {
		stopping = true; 
	
	}
	
	
	// we need to have sensed motion,
	// AND we need to have enough unitPower to trigger
	if( (!disabled) && (!stopping) &&
		(scale>0.95) &&
		(motionLevel >= rechargeSettings->motionTriggerLevel) &&
		(unitPower>=rechargeSettings->triggerPower) &&
		(elapsedTime - lastTriggerTime > rechargeSettings->minTriggerInterval) ) {
		
		if(doTrigger()) {
			motionLevel = 0;
			unitPower-=rechargeSettings->triggerPower;
			lastTriggerTime = elapsedTime;
			
		}
	}
	
	motionLevel -= rechargeSettings->motionDecay*deltaTime;
	if(motionLevel<0) motionLevel = 0;
		
	
	
	return active;
}

void Trigger :: draw(ofRectangle area, int motionTargetThreshold) {
	
	if(settings!=NULL) {
		settings->update(deltaTime, values);
		settings->draw(elapsedTime, pos,  unitPower, active, scale, angle);
		
		if(elapsedTime-lastTriggerTime<0.15) {
			ofPushMatrix();
			ofPushStyle();
			ofTranslate(pos.x, pos.y);
			float size = ofMap(elapsedTime - lastTriggerTime, 0, 0.15, 1, 0);
			size*=size;
			size*=settings->radius*5;
			ofScale(size, size);
			ofSetColor(settings->getColour());
			flashImage.draw(-0.5, -0.5, 1,1);
			ofScale(0.5,0.5);
			flashImage.draw(-0.5, -0.5, 1,1);
			
			ofPopStyle(); 
			ofPopMatrix();
		}
	}
	
	if(lastSettings!=NULL) {
		lastSettings->update(deltaTime, values);
		lastSettings->draw(elapsedTime, pos,  unitPower, active, lastScale, angle);
	}
	if(!active) return;


	
	if(showDebugData) {
		
		ofPushMatrix();
		ofPushStyle();
		ofTranslate(pos);
      
		ofSetColor(100,0,0);
		ofNoFill();
		ofRect(-triggerSampleSize/2, -triggerSampleSize/2, triggerSampleSize, triggerSampleSize);
		ofTranslate(0, motionValueCount*-2);
		
		ofFill();
		 
        for(float i = -0.5; i<=0.5 ; i++){
                  
            ofPushMatrix();
            
            ofBeginShape();
            
            ofScale(i,1);
            
            ofVertex(-1,0);
            float lastvalue = -1;
            
            for(int i = 0; i<motionValues.size(); i++) {
				
                float value = ofClamp(motionValues[i]*20, 0, 50);
                if(value!=lastvalue) {
                    ofVertex(lastvalue,(i*2)-1);
                    ofVertex(value,i*2);
                    ofVertex(value,(i*2)+1);
                }
                lastvalue = value;
             }
            ofVertex(0,motionValues.size()*2);
            ofVertex(-1,motionValues.size()*2);
            ofEndShape();
            
            ofPopMatrix();
        }
		
		ofPopMatrix();
		
		
		for(int i = 0; i<vertMotionSamples.size(); i++) {
			float sample = vertMotionSamples[i];
			ofSetColor(ofMap(sample, 0, 255,0,255,true));
			if(sample<motionTargetThreshold) ofSetColor(50,0,0);
			ofNoFill();
			float ypos = ofMap(i, 0, vertMotionSamples.size(), area.getTop(), area.getBottom());
			ofCircle(pos.x, ypos, 3);
			ofRect(pos.x - (multiSampleSize/2), ypos-(multiSampleSize/2), multiSampleSize, multiSampleSize);
			
		}
		
		
		
		ofPopStyle();

		
	} else if(sampleBrightness>0) {
	
		ofPushStyle();
		
		for(int i = 0; i<vertMotionSamples.size(); i++) {
			//			ofSetColor(ofMap(sample, 0, 255,0,255,true));
			//if(sample<motionTargetThreshold) ofSetColor(50,0,0);
			ofNoFill();
			float ypos = ofMap(i, 0, vertMotionSamples.size(), area.getTop(), area.getBottom());
			if(ypos > pos.y) {
				float sample = vertMotionSamples[i];
				ofSetColor(sampleBrightness * 100 );
				ofSetLineWidth(1* scale);
				ofCircle(pos.x, ypos, 3* scale);
				if(i<vertMotionSamples.size()-1) {
					
					ofLine(pos.x, ypos+(3* scale), pos.x, ofMap(i+1, 0, vertMotionSamples.size(), area.getTop(), area.getBottom())-(3* scale));
				}
				
				ofSetColor(ofMap(sample, 0, 255,0,80,true) * sampleBrightness);
				ofFill();
				ofCircle(pos.x, ypos, 2* scale);
				
			}
		}
		
		ofPopStyle();
	}
}


void Trigger :: registerMotion(float unitValue) {
	
	if(!active) return;
	motionLevel+=(unitValue);
	
	if(motionLevel>1) motionLevel = 1; 
	
}

bool Trigger::doTrigger() {
	

	if(settings!=NULL) {
		settings->doTrigger(pos,1,angle, values);
		lastTriggerTime = ofGetElapsedTimef(); 
		triggerCount++;
		if(settings->rotateOnFire) {
			angle += settings->rotationSpeed * rotateDirection;
			if(angle >= settings->rotationExtent) {
				angle = settings->rotationExtent;
				rotateDirection = -1;
			} else if (angle <= -settings->rotationExtent) {
				angle = -settings->rotationExtent;
				rotateDirection = 1;
			}
		}

	}
	return true;//!disabled;
}


void Trigger::copySettings(TriggerSettings* newsettings) {
	lastSettings = settings;
	lastScale = scale;

	settings = newsettings;
	if(settings!=NULL){
		rechargeSettings = settings->rechargeSettings;
		disabled = (!settings->enabled);
	} else {
		stop();
	}

	scale = 0;
	angle = 0;
	rotateDirection = 1;
	values.clear();
	
	

	
};

