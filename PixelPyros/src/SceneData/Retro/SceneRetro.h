
#pragma once

#include "Scene.h"
#include "ParticleRendererShape.h"
#include "ParticleRendererLowRes.h"
#include "RocketSettings.h"
#include "TriggerableRocket.h"
#include "ParticleSystemSettings.h"


class SceneRetro : public Scene {

	public :

	SceneRetro (string scenename) ;

	bool draw();
	
	TriggerSettings* getRetroRocket(float hue = -30, float hueChange = 40);
	ParticleSystemSettings getPixelTrailParticles(float hue = -30, float hueChange = 40);
	ParticleSystemSettings getPixelExplosionParticles(float hue = -30, float hueChange = 40);

	TriggerSettings* getRetroFountain(float hueOffset = 0, float hueChange = -128, float minSpeed = 700, float maxSpeed = 1200);
	
	TriggerSettings* getFatRocket(float hue = 0);
    
	unsigned int pixelSize;
    
   
};