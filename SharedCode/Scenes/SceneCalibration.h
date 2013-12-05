
#pragma once

#include "Scene.h"
#include "Trigger.h"
#include "RocketBasic.h"
#include "LaserManager.h"

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
		
		addEmptyTriggerPattern("laser lines");
		addEmptyTriggerPattern("laser circles");
		addEmptyTriggerPattern("laser spirals");
		addEmptyTriggerPattern("laser dots");
		
		
	}
	
	
	
	virtual bool draw() {
		
		
		if(!active) return false;
		
		LaserManager& lm = *LaserManager :: instance();
		
		
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
		} else if(currentTriggerPatternIndex == 3) {
			//LASER LINES
			
			for(int i = 0; i<=12; i++) {
				
				ofColor c;
				c.setSaturation(255);
				c.setBrightness(255);
				c.setHue(ofMap(i, 0, 12,0,255));
				
				float x = ofMap(i,0,12,APP_WIDTH *0.2, APP_WIDTH*0.8);
				
				lm.addLaserLineEased(ofPoint(x,100), ofPoint(x,200), c);
				
				c.setSaturation(128);
				lm.addLaserLineEased(ofPoint(x,250), ofPoint(x,350), c);
				
				lm.addLaserLineEased(ofPoint(x,400), ofPoint(x,500), ofColor(ofMap(i, 0, 12, 0,255)));
				
			}
			
		} else if(currentTriggerPatternIndex == 4) {
			//LASER CIRCLES
			
			for(int i = 0; i<=5; i++) {
				
				ofColor c;
				c.setSaturation(255);
				c.setBrightness(255);
				c.setHue(ofMap(i, 0, 5,0,255));
				
				float x = ofMap(i,0,5,APP_WIDTH *0.2, APP_WIDTH*0.8);
				
				float scale = ofMap(sin(ofGetElapsedTimef() + i), -1, 1, 0.2,1);
				
				
				lm.addLaserCircle(ofPoint(x,150), c, 30*scale);
				
				lm.addLaserDot(ofPoint(x,450), c);
				
				c.setSaturation(128);
				lm.addLaserCircle(ofPoint(x,250), c, 30);
				
				
				scale = ofMap(sin(ofGetElapsedTimef() + i), -1, 1, 2,20);
				lm.addLaserCircle(ofPoint(x,350), ofColor(255), scale);
				
				
			}
			
		} else if(currentTriggerPatternIndex == 5) {
			//LASER SPIRALS
			
			for(int i = 0; i<=5; i++) {
				
				ofColor c;
				c.setSaturation(255);
				c.setBrightness(255);
				c.setHue(ofMap(i, 0, 5,0,255));
				
				float scale = ofMap(sin(ofGetElapsedTimef() + i), -1, 1, 0.2,1);
				
				
				float x = ofMap(i,0,5,APP_WIDTH *0.2, APP_WIDTH*0.8);
				lm.addLaserSpiral(ofPoint(x,300), ofColor(255), ofMap(i,0,5,0,20)*scale, ofMap(i,0,5,10,50) *scale);
				
				
			}
			
		}
	}
	
	
	
	
	
};