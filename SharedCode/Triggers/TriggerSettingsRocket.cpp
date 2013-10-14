//
//  TriggerableRocket.cpp
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 01/09/2013.
//
//

#include "TriggerSettingsRocket.h"

TriggerSettingsRocket :: TriggerSettingsRocket() : particleSystemManager(*ParticleSystemManager::instance()) {
	
	//rocketSettings = NULL;
	
	rotationExtent = 0;
	rotationSpeed = 0;
	rotateOnFire = false;
	enabled = true;
	
//	rot1 = ofRandom(360);
//	rot2 = ofRandom(360);
//	rot3 = ofRandom(360);
//	vel1 = ofRandom(400,440);
//	vel2 = ofRandom(320,380);
//	vel3 = ofRandom(280,320);
}



void TriggerSettingsRocket ::doTrigger(ofVec3f& pos, float power, float direction, map<string, float>& values){
	
	PhysicsObject* rocket = NULL;
	
	RocketSettings* rs = NULL;
	float* currentMultiRocket = NULL; 
	
	if(multiRocketSettings.size()>0) {
		
		if(multiRocketProbabilities.size() == multiRocketSettings.size()) {
			float random = ofRandom(1);
			int i;
			for(i = 0; i<=multiRocketSettings.size(); i++) {
				if(random<multiRocketProbabilities[i]) break;
			}
			// shouldn't need this
			if(i>=multiRocketSettings.size()) i =multiRocketSettings.size()-1;
			rs = multiRocketSettings[i];
			
		} else {
			
			if(values.find("currentmultirocket")==values.end()) {
				values["currentmultirocket"] = 0;
			}
			currentMultiRocket = &values["currentmultirocket"];
			   
			rs = multiRocketSettings[*currentMultiRocket];
			(*currentMultiRocket)++;
			if(*currentMultiRocket>=multiRocketSettings.size()) (*currentMultiRocket) =0;
		}
	}
	if(rs!=NULL) {
		rocket = particleSystemManager.addRocket(*rs, pos);
		rocket->vel.rotate(0,0, direction );
	}

}



void TriggerSettingsRocket::draw(float elapsedtime, ofVec3f pos, float unitPower, bool active, float scale, float angle) {
	
	//elapsedTime+=deltaTime;
	
	ofColor colour = getColour(); 
	
	ofPushMatrix();
	ofPushStyle();
	ofDisableBlendMode();
	
	ofTranslate(pos);
	ofScale(scale, scale);
	
	ofFill();
	ofSetColor(0);
	ofCircle(0,0, radius);
	
	
	ofNoFill();
	ofSetLineWidth(1);
	
	ofSetColor(colour);
	if(!active) ofSetColor(ofColor::gray);
	
	
	ofCircle(0,0, radius);
	
	
	//ofCircle(pos, radius*unitPower);
	
	path.clear();
	path.setFillColor(colour);
	path.setCircleResolution(12);
	
	
	float size;
	
	if(rechargeSettings->triggerPower ==1 ) {
		size = unitPower;
	} else if(unitPower >= rechargeSettings->triggerPower ) {
		size = ofMap(unitPower, rechargeSettings->triggerPower, 1,0.8,1); 
	} else {
		size = ofMap(unitPower, 0, rechargeSettings->triggerPower, 0, 0.8);
	}
	
	bool triggerable = (unitPower>=rechargeSettings->triggerPower);
	
	//float modlevel = 0.3f;
	if(triggerable){
		path.arc(0,0, (radius-2)*size, (radius-2)*size, -90, -90 + size*360);
		
	} else if (int(elapsedtime*1000) % 200 >100) {
		path.setFillColor(colour * ofMap(unitPower, 0, rechargeSettings->triggerPower, 0.4,1));
		path.arc(0,0, (radius-2)*size, (radius-2)*size, -90, -90 + size*360);

	}

	
	
	path.draw();
	
	
	if((rotateOnFire) || (rotationSpeed!=0)) {
		ofRotate(angle);
		ofLine(0,0,0,-20);
	}
	
	ofPopStyle();
	ofPopMatrix();
}

ofColor TriggerSettingsRocket::getColour() {
	ofColor c = ofColor::white;
	c.setSaturation(saturation);

	c.setHue(hue);
	return c; 

}

void TriggerSettingsRocket::addRocketSettings(RocketSettings* rs){
	multiRocketSettings.push_back(rs);
}

void TriggerSettingsRocket::setProbabilities(vector<float> probs){
	
	multiRocketProbabilities.clear();
	
	float total = 0;
	
	for(int i = 0;i<multiRocketSettings.size();i++) {
		if(i>=probs.size()) {
			cout << "ERROR"<< endl;
			
		} else {
			total+=probs[i];
		}
		
	}
	float currentprob = 0;
	for(int i = 0;i<probs.size();i++) {
		currentprob+=(probs[i]/total);
		multiRocketProbabilities.push_back(currentprob); 
	}
	
	
}

RocketSettings* TriggerSettingsRocket::getRocketSettings(int index) {
	if(index>=multiRocketSettings.size()) return NULL; 
	return multiRocketSettings[index];
	
}

