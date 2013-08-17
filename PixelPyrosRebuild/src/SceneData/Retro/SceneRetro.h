
#pragma once

#include "Scene.h"
#include "ParticleRendererShape.h"
#include "ParticleRendererLowRes.h"
#include "RocketSettings.h"
#include "ParticleSystemSettings.h"


class SceneRetro : public Scene {

	public :

	SceneRetro (string scenename, ParticleSystemManager& psm, ofRectangle triggerarea) ;

	bool draw();
	
	RocketSettings getRetroRocket(float hue = -30, float hueChange = 40);
	ParticleSystemSettings getPixelTrailParticles(float hue = -30, float hueChange = 40);
	ParticleSystemSettings getPixelExplosionParticles(float hue = -30, float hueChange = 40);

	RocketSettings getRetroFountain(float hueOffset = 0, float hueChange = -128);
	
	RocketSettings getFatRocket(float hue = 0);
    
	unsigned int pixelSize;
    
   
};