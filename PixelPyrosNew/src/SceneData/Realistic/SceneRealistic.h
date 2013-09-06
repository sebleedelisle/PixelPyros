
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



class SceneRealistic : public Scene {

	public :
		
	SceneRealistic (string scenename, ParticleSystemManager& psm) ;
	
	//bool draw();
	
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
    
};