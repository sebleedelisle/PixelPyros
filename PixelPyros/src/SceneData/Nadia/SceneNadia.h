//
//  NadiaScene.h
//  PixelPyrosNew
//
//  Created by Seb Lee-Delisle on 11/09/2013.
//
//

#pragma once 
#include "Scene.h"
#include "TriggerSettingsRocket.h"
#include "ParticleRendererShape.h"
#include "ParticleRendererLaser.h"

#include "ParticleRendererLine.h"
#include "FireworkFactory.h"

class SceneNadia : public Scene {

	public :
	
	SceneNadia(string scenename);
	
	TriggerSettingsRocket* getLaserRocket(float hue = -30, float hueChange = 40);
	TriggerSettingsRocket* getLaserSlowRocket(float hue = -30, float hueChange = 40);
	ParticleSystemSettings getTrailParticles(float hue, float hueChange);
	ParticleSystemSettings getLaserParticles(float hue, float hueChange);
	
}; 