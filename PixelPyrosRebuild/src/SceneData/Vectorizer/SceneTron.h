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
#include "TriggerRocket.h"
#include "StretchyNet.h"
#include "ParticleRendererSquare.h"
#include "RocketFountain.h"
#include "TriggerRotator.h"


class SceneTron : public Scene {
	
	public : 
	
	SceneTron (string scenename, ParticleSystemManager& psm, ofRectangle triggerarea) ;
	
	
	RocketSettings getCircleFountain(float hue = 120);

	
	bool update(float deltaTime) ;
	
	bool draw();
	
   
	StretchyNet stretchyNet; 
	ParticleRendererSquare renderer;
	
};