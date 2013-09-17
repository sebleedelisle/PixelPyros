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
#include "TriggerSettingsRocket.h"
#include "ParticleSystemSettings.h"
#include "ParticleRendererBitmap.h"


class FireworkFactory {
	
	
	public:

	static FireworkFactory* instance();
	static FireworkFactory* factory;

	FireworkFactory();

	TriggerSettingsRocket* getSimpleRocket(float speed = 500, float hue = 20, float saturation = 255, float speedVar = 0.2, float directionVar = 4 );
	TriggerSettingsRocket* getBasicRocket(float hue = 20, float hueChange = -5);
	TriggerSettingsRocket* getFountain(float hueStartOffset = 150, float hueChange = 0);

	ParticleSystemSettings getFlowerTrailParticles(float hue = 20, float hueChange = -5);
	ParticleSystemSettings getFlowerExplosionParticles(float hue = 20, float hueChange = -5);

	ofImage softWhiteImage;
	ofImage bangerFlashImage;



};