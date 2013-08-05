//
//  TriggerTest.h
//  openFrameworksLib
//
//  Created by Seb Lee-Delisle on 16/08/2012.
//  Copyright (c) 2012 seb.ly. All rights reserved.
//

#pragma once

#include "TriggerSimple.h"

class TriggerTest : public TriggerSimple {
	
	public : 
	
	TriggerTest(ParticleSystemManager& psm): TriggerSimple (psm, 5) {
		typeLabel = "TriggerTest"; 
		motionDecay = 100;
		type = TRIGGER_TYPE_FIRE_ON_MOTION; 
		//triggerLevel = 0.01;
		motionValueCount = 20;
		lastUpdate = 0; 
	};
	
	TriggerTest* clone() const{
		//cout << "clone TriggerTest"<< endl;
		
		return new TriggerTest( *this );
	}
	
	bool update(float deltaTime) { 
		// update bitmap
		
				
		if (TriggerSimple :: update(deltaTime)){
			return true;
		} else { 
			return false; 
		}
		
		
	};
	
	virtual void draw() {
		if(!active || !showDebugData) return;

		//cout << "trigger test draw" << endl;
		
		// draw trigger and motion bitmap 
        // disabling super draw as this is now being extended byTtriggerRocket, which overrides the draw of simple
		 
        
		
		
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
            
                float value = motionValues[i]*20; 
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
		
		TriggerSimple::draw();
		
		
	};
	
    deque <float> motionValues; 
	int motionValueCount; 
	float lastUpdate; 

};