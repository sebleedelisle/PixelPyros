//
//  TriggerBase.h
//  ParticlePlay4
//
//  Created by Seb Lee-Delisle on 02/08/2012.
//  Copyright (c) 2012 seb.ly. All rights reserved.
//

#pragma once 

#include "ParticleSystem.h"
#include "PhysicsObject.h"
#include "RocketSettings.h"
#include "ParticleSystemManager.h"

#include "TriggerSimple.h"

//template <typename Derived>
class TriggerRocket : public TriggerSimple{

	public : 
	
	TriggerRocket(ParticleSystemManager & psm, float triggerRadius = 5);
	//virtual bool update(float deltaTime);
	virtual void draw(); 
	
	//virtual void start();
	//virtual void stop();
	
	//virtual void registerMotion(float unitValue);
	virtual void addRocketSettings(RocketSettings rocket);
	
	virtual bool doTrigger();
	
	
	virtual TriggerRocket* clone() const{
		//cout << "clone TriggerRocket"<< endl;
		return new TriggerRocket( *this );
	}
	
	int currentRocketIndex;
	bool useAllPower;
	
	vector <RocketSettings> rocketSettings;
	PhysicsObject* makeNewRocket(); 
	
	
};