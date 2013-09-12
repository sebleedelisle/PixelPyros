//
//  NadiaScene.cpp
//  PixelPyrosNew
//
//  Created by Seb Lee-Delisle on 11/09/2013.
//
//

#include "SceneNadia.h"


SceneNadia :: SceneNadia  (string scenename) : Scene(scenename){
	
	TriggerPattern empty;
	addTriggerPattern(empty);
	
	TriggerPattern pattern1;
	TriggerSettings* laserRocket = getLaserRocket();
	pattern1.addTriggerSettings(laserRocket);
	pattern1.addTriggerSettings();
	
	addTriggerPattern(pattern1);
	
}



TriggerSettingsRocket* SceneNadia::getLaserRocket(float hue, float hueChange) {
	
	TriggerSettingsRocket& ts = *new TriggerSettingsRocket();
	
	RocketSettings& rocketSettings = *new RocketSettings();
	
	rocketSettings.startSpeedMin = 800;
	rocketSettings.startSpeedMax = 900;
	rocketSettings.drag = 1;
	rocketSettings.gravity.y = 800;
	
	ParticleSystemSettings trails = getLaserParticles(hue, hueChange);
	ParticleSystemSettings explosion = getTrailParticles(hue, hueChange);
	
	//explosion.emitDelay = trails.emitLifeTime;
	
	rocketSettings.addParticleSystemSetting(trails);
	rocketSettings.addParticleSystemSetting(explosion);
	
	ts.rocketSettings = &rocketSettings;
	
	ts.rechargeSettings = TriggerRechargeSettings::medium;
	
	return &ts;
	
}


ParticleSystemSettings SceneNadia::  getLaserParticles(float hue, float hueChange){
	
	ParticleSystemSettings laserParticles;
	laserParticles.renderer = new ParticleRendererLaser();
	
	laserParticles.speedMin = 0;
	laserParticles.speedMax = 0;
	laserParticles.sizeStartMin = laserParticles.sizeStartMax = 10;
	laserParticles.sizeChangeRatio = 0.2;
	laserParticles.hueStartMin = laserParticles.hueStartMax = hue;
	laserParticles.hueChange = hueChange;
	laserParticles.saturationMin = laserParticles.saturationMax = 0;
	laserParticles.saturationEnd = 500;
	laserParticles.brightnessStartMin = laserParticles.brightnessStartMin = laserParticles.brightnessEnd = 255;
	
	laserParticles.emitCount = 20; 
	laserParticles.emitInheritVelocity = 1;
	laserParticles.shimmerMin = 0;
	laserParticles.lifeMin = laserParticles.lifeMax = 0.1; 
	laserParticles.startSound = "RetroLaunch";
	
	return laserParticles;
	
};



ParticleSystemSettings SceneNadia::  getTrailParticles(float hue, float hueChange){
	
	ParticleSystemSettings trails;
	trails.renderer = new ParticleRendererShape();
	//pss.directionZVar = 20;
	trails.speedMin = 10;
	trails.speedMax = 10;
	trails.sizeStartMin = trails.sizeStartMax = 10;
	trails.hueStartMin = trails.hueStartMax = hue;
	trails.hueChange = hueChange;
	trails.saturationMin = trails.saturationMax = 0;
	trails.saturationEnd = 500;
	trails.brightnessStartMin = trails.brightnessStartMin = trails.brightnessEnd = 255;
	
	trails.shimmerMin = 0;
	trails.lifeMin = trails.lifeMax = 0.5;
	trails.startSound = "RetroLaunch";
	
	return trails;
	
};