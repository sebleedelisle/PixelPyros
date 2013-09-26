//
//  SceneSpace.h
//  ArchitectureCamera
//
//  Created by Seb Lee-Delisle on 14/08/2012.
//  Copyright (c) 2012 seb.ly. All rights reserved.
//
#pragma once

#include "Scene.h"
#include "RocketBasic.h"
#include "RocketThinFountain.h"
#include "ParticleRendererStar.h"
#include "ParticleRendererBitmap.h"
#include "ParticleRendererCircle.h"
#include "ParticleRendererSquare.h"
#include "RocketFountain.h"

#include "LetterWritingPatternMaker.h"

#include "Starfield.h"
#include "FireworkFactory.h"

class SceneSpace : public Scene {
	
	public : 
	
	SceneSpace(string scenename) ;
	
	bool update(float deltaTime);
	bool draw();
	
	
	TriggerSettingsRocket* getStarryRocket();
	TriggerSettingsRocket* getPlanetRocket();
	
	TriggerSettingsRocket* getFlowerRocket(float hue = 20, float hueChange = -5);
	TriggerSettingsRocket* getSphereFlowerRocket(float hue = 20, float hueChange = -5);
	
	ParticleSystemSettings getFlowerTrailParticles(float hue = 20, float hueChange = -5);
	ParticleSystemSettings getFlowerExplosionParticles(float hue = 20, float hueChange = -5);
	ParticleSystemSettings getLineExplosionParticles(float hue = 20, float hueChange = -5);
	
	
	ofImage softWhiteImage;

	
	
	
	ParticleRendererShape* renderer;
	
	Starfield starfield; 
	
};