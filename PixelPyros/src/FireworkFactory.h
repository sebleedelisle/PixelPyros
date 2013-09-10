//
//  FireworkFactory.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 09/09/2013.
//
//

#pragma once

#include "ofMain.h"
#include "TriggerSettings.h"
#include "TriggerableRocket.h"
#include "ParticleSystemSettings.h"
#include "ParticleRendererBitmap.h"


class FireworkFactory {
	
	
	public:

	static FireworkFactory* instance();
	static FireworkFactory* factory;

	FireworkFactory();

	
	RocketSettings getBasicRocket(float hue = 20, float hueChange = -5);
	RocketSettings getFountain(float hueStartOffset = 150, float hueChange = 0);


	ParticleSystemSettings getFlowerTrailParticles(float hue = 20, float hueChange = -5);
	ParticleSystemSettings getFlowerExplosionParticles(float hue = 20, float hueChange = -5);


	ofImage softWhiteImage;
	ofImage bangerFlashImage;



};