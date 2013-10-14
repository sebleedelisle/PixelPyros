//
//  TriggerableRocket.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 01/09/2013.
//
//

#pragma once

#include "TriggerSettings.h"
#include "ParticleSystemManager.h"


class TriggerSettingsRocket : public TriggerSettings {


	public :
	
	TriggerSettingsRocket(); 

	virtual void doTrigger(ofVec3f& pos, float power, float direction, map<string, float>& values);

	virtual void draw(float elapsedtime, ofVec3f pos, float unitPower, bool active, float scale, float angle);
	
	virtual ofColor getColour();
	
	virtual void addRocketSettings(RocketSettings* rs); 
	virtual void setProbabilities(vector<float> probs);
	virtual RocketSettings* getRocketSettings(int index = 0);
	
	ofPath path;

	ParticleSystemManager & particleSystemManager;
	
	//void addRocketSettings(RocketSettings* rs);
	
	
		
	private :
	
	//RocketSettings* rocketSettings;
	vector<RocketSettings*> multiRocketSettings;
	vector<float> multiRocketProbabilities;

	
	//float rot1, rot2, rot3, vel1, vel2, vel3;

};