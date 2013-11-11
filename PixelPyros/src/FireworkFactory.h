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
#include "TriggerSettingsRocketOrb.h"
#include "ParticleSystemSettings.h"
#include "ParticleRendererBitmap.h"
#include "ParticleRendererLine.h"
#include "ParticleRendererLaserLine.h"
#include "ParticleRendererCircle.h"
#include "ParticleRendererLaser.h"
#include "ParticleRendererLaserFlash.h"
#include "TriggerSettingsFountain.h"


class FireworkFactory {
	
	
	public:

	static FireworkFactory* instance();
	static FireworkFactory* factory;

	FireworkFactory();

	TriggerSettingsRocket* getSimpleRocket(float speed = 500, float hue = 20, float saturation = 255, float speedVar = 0.2, float directionVar = 4 );
	TriggerSettingsRocket* getSimpleLaserRocket(float speed = 500, float hue = 20, float saturation = 255, float speedVar = 0.2, float directionVar = 4 );
	TriggerSettingsRocket* getRotatingRocket(float speed = 500, float hue = 20, float saturation = 255, float speedVar = 0.2, float directionVar = 4 );
	TriggerSettingsRocket* getBasicRocket(float hue = 20, float hueChange = -5, float flightTime = 2);
	TriggerSettingsRocket* getSimpleFountain(float hueStartOffset = 150, float hueChange = 0);
	TriggerSettingsRocket* getFountain(float hueStartOffset = 150, float hueChange = 0);

	ParticleSystemSettings getFlowerTrailParticles(float hue = 20, float hueChange = -5);
	ParticleSystemSettings getFlowerExplosionParticles(float hue = 20, float hueChange = -5);

	ParticleSystemSettings getLaserExplosionParticles(float hue, float hueChange);

	
	TriggerSettingsRocket* getFluffyRocket();
	
	TriggerSettingsRocket* getBangerRocket();
	ParticleSystemSettings getBangerTrails();
	ParticleSystemSettings getBangerBang();
	ParticleSystemSettings getBangerLaserBang();
	ParticleSystemSettings getBangerCrackles();
	ParticleSystemSettings getSmoke();
	ParticleSystemSettings getLaserFlashParticles(float hue = 0, float saturation = 0);
	
	TriggerSettingsRocket* getWigglyRocket();
	
	ParticleSystemSettings getLaserParticles(float hue, float hueChange);
	TriggerSettingsRocket* getLaserRocket(float hue, float hueChange);

	
	ofImage softWhiteImage;
	ofImage bangerFlashImage;



};