
#include "TriggerSimple.h"

// Most of this code is to create the Trigger graphics, but there
// is also stuff that works out how the triggers recharge. 

TriggerSimple :: TriggerSimple (ParticleSystemManager& psm, float triggerRadius ) : TriggerBase(psm, triggerRadius){
	
	typeLabel = "TriggerSimple";
	// the power level for the trigger
	unitPower =1;
	// the amount typename = "TriggerRocket"; of power a rocket takes away
	triggerPower = 0.2;
	elapsedTime = 0;
	lastTriggerTime = 0;
	minTriggerInterval = 0.3;
	
	elapsedTime = 0;
	
	type = TRIGGER_TYPE_FIRE_ON_MOTION;
	
	restoreSpeed = 0.2;
	triggerLevel = 0.5;
	stopping = false;
	active = false;
	scale = 0;
	
	motionSensitivity = 0;
	
	motionDecay = 20;
	
	
	motionValueCount = 20; 
	
	// these values are to create the Trigger swirly circle animation
	rot1 = ofRandom(360);
	rot2 = ofRandom(360);
	rot3 = ofRandom(360);
	vel1 = ofRandom(400,440);
	vel2 = ofRandom(320,380);
	vel3 = ofRandom(280,320);
	
	hue = 0;
	saturation = 0; 
	
	
}

void TriggerSimple :: start() {
	
	stopping = false;
	//if(!)scale = 0;
	
	if(!active) {
		rot1 = ofRandom(360);
		rot2 = ofRandom(360);
		rot3 = ofRandom(360);
		vel1 = ofRandom(400,440);
		vel2 = ofRandom(320,380);
		vel3 = ofRandom(280,320);
	}
	
	active = true;
	motionLevel = 0;
	
	if(type == TRIGGER_TYPE_FIRE_ON_CHARGE) {
		unitPower = 0;
	} else if(type == TRIGGER_TYPE_FIRE_ON_MOTION) {
		unitPower = 1;
	}
	
	
	

}

void TriggerSimple :: stop() {
	
	stopping = true;
	
}

bool TriggerSimple::update(float deltaTime) {

	if(!active) return false;

	elapsedTime+=deltaTime;
	
	// scale up / down on start stop
	if(stopping) {
		scale-=deltaTime*3;
		if(scale<=0.0) {
			scale = 0;
			active = false;
			return false;
		}
	} else {
		scale+= (1-scale)*0.1;
	}
	
	
	if(type == TRIGGER_TYPE_FIRE_ON_MOTION) {
		unitPower+=restoreSpeed * deltaTime;
		if(unitPower>1) unitPower = 1;
		
		
		// we need to have sensed motion,
		// AND we need to have enough unitPower to trigger
		if( (!stopping) &&
		    //(scale>0.99) &&
		    (motionLevel >= triggerLevel) &&
		    (unitPower>=triggerPower) &&
		    (elapsedTime - lastTriggerTime > minTriggerInterval) ) {
			
			if(doTrigger()) {
				motionLevel = 0;
				unitPower-=triggerPower;
				lastTriggerTime = elapsedTime;
				
				if(restoreSpeed==0) {
					// this trigger is a one shot so stop it
					stop();
					
				}
			}
		}
		
		motionLevel -= motionDecay*deltaTime;
		if(motionLevel<0) motionLevel = 0;
		
	}
	
	
	//	else if(type == TRIGGER_TYPE_FIRE_ON_CHARGE) {
	//		unitPower+=(motionLevel*deltaTime*motionSensitivity);
	//		motionLevel = 0;
	//		if(unitPower>=triggerLevel) {
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
	
	
	float speed = 1.5;
	if(unitPower<triggerPower ) speed = ofMap(unitPower, 0, triggerPower, 0, 0.5, true);
	rot1+= vel1 * deltaTime * speed;
	rot2+= vel2 * deltaTime * speed;
	rot3+= vel3 * deltaTime * speed;
	
	
	if(showDebugData) {
		
		if((elapsedTime-lastUpdate>0.032)||(motionValues.size()==0)) {
			
			motionValues.push_back(motionLevel);
			lastUpdate = elapsedTime;
			
		} else {
			
			float lastlevel = 0;
			
			
			lastlevel = motionValues[motionValues.size()-1];
			
			motionValues[motionValues.size()-1] = (motionLevel>lastlevel) ? motionLevel : lastlevel;
		}
		
		//if(motionLevel>0) cout <<motionLevel << endl;
		if(motionValues.size()>motionValueCount) {
			motionValues.pop_front();
		}
	}
	

	
	
	return active;
}

void TriggerSimple :: draw() {

	if(!active) return;

	
	ofPushStyle();
	ofPushMatrix();
    
	ofTranslate(pos);
	ofScale(scale, scale);
	float activeScale = ofMap(unitPower, 0, triggerPower, 0.5, 1, true);
	ofScale(activeScale, activeScale);
	ofEnableSmoothing();
	
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	
	ofColor dimColour = ofColor::white;
	//dimColour.setHue(hue);
	//dimColour.setSaturation(saturation);
	
  	
	if((triggerPower<=unitPower) || (fmodf(elapsedTime,0.16) < 0.08) || (restoreSpeed==0) || (type == TRIGGER_TYPE_FIRE_ON_CHARGE)) {
		
		//ofCircle(0, 0, radius*0.5);
		//ofNoFill();
		
		dimColour.setHsb(hue, saturation, ofMap(unitPower, 0, triggerLevel, 10,150, true));
		
		ofSetColor(dimColour);
		ofCircle(0, 0, radius*unitPower*0.5);
		
		ofSetColor(ofMap(unitPower, 0, triggerLevel, 10,255, true));
		ofCircle(0, 0, radius*unitPower*0.3);
		
		dimColour.setHsb(hue, saturation, ofMap(unitPower, 0, triggerLevel, 10,200, true));
		
		//ofSetColor(200);
		
	} else {
		
		dimColour.setHsb(hue, saturation, 50);
								
		
	}
	
	ofSetColor(dimColour);
	//ofCircle(0, 0, radius);
	
	
	
	//ofPushMatrix();
	//ofTranslate(pos);
	//orbSize = 0.5;
	
	//cout << orbSize << "\n";
	
	//ofScale(orbSize,orbSize,orbSize);
	
	
	
	//ofEnableSmoothing();
	//ofSetColor(255,50);
	//ofFill();
	//ofCircle(0,0,22);
	
	
	ofSetLineWidth(1);
	
	ofPushMatrix();
	ofRotateY(30);
	ofRotateX(rot1);
	ofNoFill();
	ofCircle(0, 0, radius/2, radius);
	ofPopMatrix();
	
	ofPushMatrix();
	ofRotateZ(120);
	ofRotateX(rot2);
	ofNoFill();
	ofCircle(0, 0, radius/2, radius);
	ofPopMatrix();
	
	ofPushMatrix();
	ofRotateZ(240);
	ofRotateX(rot3);
	ofNoFill();
	ofCircle(0, 0, radius/2, radius);
	ofPopMatrix();
	
	
	//ofPopMatrix();
	
	if(disabled) {
		ofDisableBlendMode();
		ofDisableSmoothing();
		ofSetLineWidth(3);
		ofSetColor(140,0,0);
		
		//ofSetColor(colour);
		
		ofLine(-radius,-radius,radius,radius);
		ofLine(radius,-radius,-radius,radius);
		ofEnableBlendMode(OF_BLENDMODE_ADD);
		
	}
	
	ofPopStyle();
	ofPopMatrix();
	
	
	if(showDebugData) {
		
		ofPushMatrix();
		ofPushStyle();
		ofTranslate(pos);
        ofScale(1, scale);
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


void TriggerSimple :: registerMotion(float unitValue) {
	
	if(!active) return;

	motionLevel+=unitValue;
	unitPower += unitValue*motionSensitivity;
	
}

bool TriggerSimple::doTrigger() {
	return !disabled;
}
