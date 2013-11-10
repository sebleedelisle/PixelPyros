
#pragma once

#include "Scene.h"
#include "Trigger.h"
#include "RocketBasic.h"

#include "ofMain.h"

class SceneCalibration : public Scene {
	
	public : 
	
	SceneCalibration(string scenename) : Scene(scenename){
		RocketBasic rocketSettings(100,10, 120);
		
		//TriggerSettings trigger;
		
		//trigger.addRocketSettings(rocketSettings);
		//addTriggers(trigger, 50, 0, ofGetHeight()*0.85, ofGetWidth());
		
		//Trigger trigger2(psm);
		//TriggerPattern pattern;
		
		//pattern.addTriggerSettings(TriggerSettings::blank);
		//pattern.addTrigger(trigger2);
		TriggerPattern pattern;
		addTriggerPattern(pattern, "Projector calibrate");
		pattern.addTriggerSettings(new TriggerSettings());
		addTriggerPattern(pattern, "Trigger position");
		TriggerPattern pattern2;
		pattern2.addTriggerSettings(new TriggerSettingsRocket());
		addTriggerPattern(pattern2, "Trigger test");
		
		
	}
	
	virtual bool draw() {
		
		
		if(!active) return false;
		
		if(currentTriggerPatternIndex == 0) {
			ofPushStyle();
			//ofEnableBlendMode(OF_BLENDMODE_ADD);
			ofSetColor(255,0,0);
			ofFill();
			//ofRect(0,0,(APP_WIDTH/2), APP_HEIGHT);
			ofSetColor(0,255,0);
			//ofRect(APP_WIDTH/2,0,APP_WIDTH/2, APP_HEIGHT);
			
			int numCols = APP_WIDTH/128;
			int numRows = APP_HEIGHT/128;
			ofDisableBlendMode();
			ofEnableAlphaBlending();
			ofSetColor(0,0,0,100);
			for(int x = 0; x<numCols; x++) {
				for(int y = 0; y<numRows; y++) {
					int xpos = x + round((float)x/(float)numCols);
					if((xpos+y)%2==0)
						ofNoFill();
						ofSetColor(255);
					ofSetLineWidth(10);
						ofRect(x*128, y*128, 128, 128);
				
				
				}
				
			}
			

			ofPopStyle(); 

		} else if (currentTriggerPatternIndex == 1) {
			if(triggerManager != NULL) {
				TriggerManager & tm = *triggerManager;
				vector <Trigger*>& triggers = tm.triggers;
				
				ofPushStyle();
				ofSetLineWidth(4);
				ofSetColor(ofColor::magenta);
				
				for(int i = 0; i<triggers.size(); i++) {
					Trigger& trigger = *triggers[i];
					if(!trigger.active) continue;
					
					ofLine(trigger.pos.x - 4, tm.triggerArea.getTop(),trigger.pos.x + 4 , tm.triggerArea.getTop());
					ofLine(trigger.pos.x, tm.triggerArea.getTop(), trigger.pos.x, tm.triggerArea.getBottom());
					ofLine(trigger.pos.x - 4, tm.triggerArea.getBottom(),trigger.pos.x + 4 , tm.triggerArea.getBottom());

				
				}
				
				ofPopStyle(); 
			
			}
		}
	}
	
	
	
	
	
};