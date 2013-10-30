
#pragma once

#include "Scene.h"
#include "ParticleRendererShape.h"
#include "ParticleRendererLowRes.h"
#include "RocketSettings.h"
#include "ParticleSystemSettings.h"


class SceneRetro : public Scene {

	public :

	SceneRetro (string scenename) ;

	bool draw();
	bool update(float deltaTime); 
	
	TriggerSettingsRocket* getRetroRocket(float hue = -30, float hueChange = 40);
	TriggerSettingsRocket* getRetroFountain(float hueOffset = 0, float hueChange = -128, float minSpeed = 600, float maxSpeed = 900);
	TriggerSettingsRocket* getRetroSpinner(float hueOffset = 0, float hueChange = -128);
	
	
	ParticleSystemSettings getPixelTrailParticles(float hue = -30, float hueChange = 40);
	ParticleSystemSettings getPixelExplosionParticles(float hue = -30, float hueChange = 40);

	
	TriggerSettingsRocket* getPixelRocket(float hue = 0);
    
		
	unsigned int pixelSize;
	ofMesh pixelMesh; 
    
   
};