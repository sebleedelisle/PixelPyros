//
//  SceneSpace.h
//  ArchitectureCamera
//
//  Created by Seb Lee-Delisle on 14/08/2012.
//  Copyright (c) 2012 seb.ly. All rights reserved.
//
#pragma once

#include "Scene.h"
#include "RocketTron.h"

#include "RocketTronFountain.h"
#include "TriggerSettingsRocket.h"
#include "StretchyNet.h"
#include "ParticleRendererSquare.h"
#include "ParticleRendererGlitchLineLaser.h"

class SceneVectorizer : public Scene {
	
	public : 
	
	SceneVectorizer (string scenename) ;
	
	
	TriggerSettingsRocketOrb* getCircleFountain(float hue = 120);

	
	bool update(float deltaTime) ;
	
	bool draw();
	
	TriggerSettingsRocketOrb* getRocketTronFountain(float hueStartOffset = 0, float hueChange = 0, float speedMultiplier = 1, bool useLaser = false);
	TriggerSettingsRocketOrb* getGlitchRocket();
	
   
	StretchyNet stretchyNet;
	
	ParticleRendererSquare renderer;
	
	ParticleSystemManager& particleSystemManager;

};