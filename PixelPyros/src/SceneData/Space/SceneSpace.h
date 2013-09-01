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
#include "TriggerRocket.h"
#include "RocketThinFountain.h"
#include "ParticleRendererStar.h"
#include "ParticleRendererBitmap.h"
#include "ParticleRendererCircle.h"
#include "RocketFountain.h"

#include "LetterWritingPatternMaker.h"

#include "Starfield.h"

class SceneSpace : public Scene {
	
	public : 
	
	SceneSpace(string scenename, ParticleSystemManager& psm) ;
	
	bool update(float deltaTime);
	bool draw();
	
	RocketSettings getPlanetRocket();
	
	RocketSettings getStarryRocket();

	RocketSettings getFlowerRocket(float hue = 20, float hueChange = -5);
	RocketSettings getSphereFlowerRocket(float hue = 20, float hueChange = -5);
	ParticleSystemSettings getFlowerTrailParticles(float hue = 20, float hueChange = -5);
	ParticleSystemSettings getFlowerExplosionParticles(float hue = 20, float hueChange = -5);
	ParticleSystemSettings getLineExplosionParticles(float hue = 20, float hueChange = -5);
	
	RocketSettings getFountain(float hueStartOffset = 150, float hueChange = 0);
	
	RocketSettings getFluffyRocket();
	
	
	RocketSettings  getBangerRocket();
	ParticleSystemSettings getBangerTrails();
	ParticleSystemSettings getBangerBang();
	ParticleSystemSettings  getBangerCrackles();
	
	ParticleSystemSettings getSmoke();
	
	ofImage softWhiteImage;
	ofImage bangerFlashImage;

	
	
	
	ParticleRendererShape* renderer;
	
	Starfield starfield; 
	
};