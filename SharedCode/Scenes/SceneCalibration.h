
#pragma once

#include "Scene.h"
#include "Trigger.h"
#include "RocketBasic.h"

#include "ofMain.h"

class SceneCalibration : public Scene {
	
	public : 
	
	SceneCalibration(string scenename, ParticleSystemManager& psm) : Scene(scenename, psm){
		RocketBasic rocketSettings(100,10, 120);
		
		TriggerSettings trigger;
		
		//trigger.addRocketSettings(rocketSettings);
		//addTriggers(trigger, 50, 0, ofGetHeight()*0.85, ofGetWidth());
		
		//Trigger trigger2(psm);
		TriggerPattern pattern;
		
		pattern.addTriggerSettings(trigger);
		//pattern.addTrigger(trigger2);
		
		addTriggerPattern(pattern);
		
		
	}
	
	virtual bool draw() {
		
		
		if((!active) || stopping) return false;
		
		ofPushStyle();
		ofEnableBlendMode(OF_BLENDMODE_ADD);
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
		
		ofSetLineWidth(1);
		
		ofPopStyle(); 
	}
	
	
	
	
	
};