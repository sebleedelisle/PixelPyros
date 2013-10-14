
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
	

	/*
	
	// these values are to create the Trigger swirly circle animation
	rot1 = ofRandom(360);
	rot2 = ofRandom(360);
	rot3 = ofRandom(360);
	vel1 = ofRandom(400,440);
	vel2 = ofRandom(320,380);
	vel3 = ofRandom(280,320);
	*/
	
	
		
	
}

void Trigger :: start() {
	
	stopping = false;
	//if(!)scale = 0;
	//cout << "START TRIGGER ----------------------";
	/*
	if(!active) {
		rot1 = ofRandom(360);
		rot2 = ofRandom(360);
		rot3 = ofRandom(360);
		vel1 = ofRandom(400,440);
		vel2 = ofRandom(320,380);
		vel3 = ofRandom(280,320);
	}*/
	
	active = true;
	motionLevel = 0;
	
	//if(type == TRIGGER_TYPE_FIRE_ON_CHARGE) {
	//	unitPower = 0;
	//} else if(type == TRIGGER_TYPE_FIRE_ON_MOTION) {
	
	if(settings->startEmpty)
		unitPower = 0;
	else
		unitPower = 1;
	//}
	
}

void Trigger :: stop() {
	
	stopping = true;
	
}

bool Trigger::update(float deltaTime, ofRectangle& triggerArea) {

	this->deltaTime = deltaTime;
	//if((!stopping) && (scale<1)) scale+=0.1;

	elapsedTime+=deltaTime;
	
	
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
	
	
	//angle++;
	
	
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
		
	//if(type == TRIGGER_TYPE_FIRE_ON_MOTION) {
	
	if(showDebugData) {
		
		 if((elapsedTime-lastUpdate>0.032)||(motionValues.size()==0)) {
		 
		 motionValues.push_back(motionLevel);
		 lastUpdate = elapsedTime;
		 
		 } else {
		 
		 float lastlevel = 0;
		 
		 lastlevel = motionValues[motionValues.size()-1];
		 
		 motionValues[motionValues.size()-1] = (motionLevel>lastlevel) ? motionLevel : lastlevel;
		 }
		//motionValues.push_back(motionLevel);
		//if(motionLevel>0) cout <<motionLevel << endl;
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
			/*
			if(restoreSpeed==0) {
				// this trigger is a one shot so stop it
				stop();
				
			}*/
		}
	}
	
	motionLevel -= rechargeSettings->motionDecay*deltaTime;
	if(motionLevel<0) motionLevel = 0;
	
	//	else if(type == TRIGGER_TYPE_FIRE_ON_CHARGE) {
	//		unitPower+=(motionLevel*deltaTime*motionSensitivity);
	//		motionLevel = 0;
	//		if(unitPower>=motionTriggerLevel) {
	//			if(doTrigger()) {
	//				unitPower = 0;
	//
	//			}
	//
	//		}
	//
	//
	//	}
	//
	
	
	
	return active;
}

void Trigger :: draw() {
	
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
        //ofScale(1, scale);
		ofTranslate(0, motionValueCount*-2);
		ofSetColor(ofColor::red);
		ofFill();
		//ofRect(0,0,200,200);
        
        for(float i = -0.5; i<=0.5 ; i++){
                  
            ofPushMatrix();
            
            ofBeginShape();
            
            ofScale(i,1);
            
            ofVertex(-1,0);
            float lastvalue = -1;
            
            for(int i = 0; i<motionValues.size(); i++) {
				
                float value = ofClamp(motionValues[i]*20, 0, 50);
                if(value!=lastvalue) {
                    //ofLine(0,i,motionValues[i]*20,i);
                    ofVertex(lastvalue,(i*2)-1);
                    ofVertex(value,i*2);
                    ofVertex(value,(i*2)+1);
                }
                lastvalue = value;
                //cout << motionValues[i] << " " << i << endl;
            }
            ofVertex(0,motionValues.size()*2);
            ofVertex(-1,motionValues.size()*2);
            ofEndShape();
            
            ofPopMatrix();
        }
		
		ofPopMatrix();
		ofPopStyle();

		
	}
	
}


void Trigger :: registerMotion(float unitValue) {
	
	if(!active) return;
	// TODO Add motion sensitivity here? 
	motionLevel+=unitValue;
	
	if(motionLevel>1) motionLevel = 1; 
	//unitPower += unitValue*motionSensitivity;
	
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

