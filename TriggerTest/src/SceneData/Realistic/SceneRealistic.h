
#pragma once

#include "Scene.h"
#include "ParticleRendererShape.h"
#include "ParticleRendererLowRes.h"
#include "ParticleRendererBitmap.h"
#include "ParticleRendererStar.h"
#include "ParticleRendererLine.h"
#include "ParticleRendererCircle.h"
#include "RocketSettings.h"
#include "ParticleSystemSettings.h"
#include "FireworkFactory.h"


class SceneRealistic : public Scene {

	public :
		
	SceneRealistic (string scenename) ;
	
	TriggerSettingsRocket*  getFountain(float hueStartOffset = 150, float hueChange = 0);
	TriggerSettingsRocket*  getFlowerRocket(float hue = 20, float hueChange = -5);
	TriggerSettingsRocket* getSphereFlowerRocket(float hue = 20, float hueChange = -5);
	
	ParticleSystemSettings getFlowerTrailParticles(float hue = 20, float hueChange = -5);
	ParticleSystemSettings getFlowerExplosionParticles(float hue = 20, float hueChange = -5);
	ParticleSystemSettings getLineExplosionParticles(float hue = 20, float hueChange = -5);
	
		



	ofImage softWhiteImage; 
	
    
};