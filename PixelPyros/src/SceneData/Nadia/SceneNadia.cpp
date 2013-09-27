//
//  NadiaScene.cpp
//  PixelPyrosNew
//
//  Created by Seb Lee-Delisle on 11/09/2013.
//
//

#include "SceneNadia.h"


SceneNadia :: SceneNadia  (string scenename) : Scene(scenename){
	
	loadMusicFile("06 Nadia.aif");
	
	TriggerPattern empty;
	addTriggerPattern(empty);
	
	TriggerPattern soft1;
	soft1.addTriggerSettings();
	soft1.addTriggerSettings();
	soft1.addTriggerSettings();
	soft1.addTriggerSettings(getLaserSlowRocket(10,0));
	
	addTriggerPattern(soft1);

	
	
	TriggerPattern pattern1;
	TriggerSettings* laserRocket = getLaserRocket();
	pattern1.addTriggerSettings(laserRocket);
	pattern1.addTriggerSettings();
	
	addTriggerPattern(pattern1);
	
}





TriggerSettingsRocket* SceneNadia::getLaserSlowRocket(float hue, float hueChange) {
	
	TriggerSettingsRocket& ts = *new TriggerSettingsRocket();
	
	RocketSettings& rocketSettings = *new RocketSettings();
	
	rocketSettings.startSpeedMin = 40;
	rocketSettings.startSpeedMax = 60;
	rocketSettings.drag = 1;
	rocketSettings.gravity.y = 0;
	
	ParticleSystemSettings ps;
	
	ps.emitLifeTime = 14;
	ps.renderer = new ParticleRendererCircle(11, false, 2);
	ps.hueStartMin = hue;
	ps.hueStartMax = hue;
	ps.hueChange = hueChange;
	ps.brightnessEnd = 0;
	ps.saturationEnd = 500;
	ps.emitCount = 10;
	ps.speedMin = 0;
	ps.speedMax = 0;
	ps.lifeMin = 0.5;
	ps.lifeMax = 1;
	ps.drag = 0.4;
	ps.emitSpeedModifier = 0.5;
	
	ps.sizeStartMin = 5;
	ps.sizeStartMax = 20;
	ps.sizeChangeRatio = 0;
	
	ps.emitInheritVelocity = 1;
	
	ParticleSystemSettings laser = getLaserParticles(hue, hueChange);
	laser.emitCount = 3;
	laser.lifeMin = 0.2;
	laser.lifeMax = 4;
	//laser.gravity.y = 100;
	laser.startSound = ""; 
	laser.emitStartSizeModifier = 0.1;
	
	laser.sizeStartMin = 20;
	laser.sizeStartMax = 40;
	laser.sizeChangeRatio = 0.1;
	laser.shimmerMin = 1; 
	
	laser.emitLifeTime = 14;
	laser.emitInheritVelocity =1;
	laser.drag = 0.97;
	laser.saturationMin = laser.saturationMax = 0;
	laser.gravity.y = 20; 
	
	ParticleSystemSettings smoke = FireworkFactory::instance()->getSmoke();
	smoke.emitCount = 100;
	smoke.emitLifeTime = 14;
	smoke.lifeMin = 1;
	smoke.lifeMax = 3;
	smoke.brightnessStartMax *=0.5;
	smoke.brightnessStartMin *=0.5;
	

	rocketSettings.addParticleSystemSetting(ps);
	rocketSettings.addParticleSystemSetting(laser);
	rocketSettings.addParticleSystemSetting(smoke);
	
	
	ts.rocketSettings = &rocketSettings;
	
	ts.rechargeSettings = TriggerRechargeSettings::slow;
	
	return &ts;
	
}




TriggerSettingsRocket* SceneNadia::getLaserRocket(float hue, float hueChange) {
	
	TriggerSettingsRocket& ts = *new TriggerSettingsRocket();
	
	RocketSettings& rocketSettings = *new RocketSettings();
	
	rocketSettings.startSpeedMin = 800;
	rocketSettings.startSpeedMax = 900;
	rocketSettings.drag = 0.96;
	rocketSettings.gravity.y = 100;
	rocketSettings.lifeTime = 1.7;
	
	ParticleSystemSettings laserTrails = getLaserParticles(hue, hueChange);
	ParticleSystemSettings trails = getTrailParticles(hue, hueChange);
	
	laserTrails.sizeStartMin = 8;
	laserTrails.sizeStartMax = 10;
	laserTrails.sizeChangeRatio = 0; 
	laserTrails.shimmerMin = 1;
	laserTrails.emitInheritVelocity = 1;
	laserTrails.drag = rocketSettings.drag;
	laserTrails.gravity = rocketSettings.gravity;
	
	laserTrails.lifeMin = laserTrails.lifeMax = rocketSettings.lifeTime;
	
	laserTrails.emitCount = 1;
	laserTrails.emitMode = PARTICLE_EMIT_BURST;
	trails.emitLifeTime = rocketSettings.lifeTime;
	
	ParticleSystemSettings explosion(laserTrails);
	explosion.emitDelay = rocketSettings.lifeTime;
	explosion.emitCount = 15;
	explosion.speedMax = 500;
	explosion.speedMin = 800;
	explosion.directionZVar = 180;
	explosion.sizeStartMin = 1;
	explosion.sizeStartMax = 1;
	explosion.lifeMin = 0.3;
	explosion.lifeMin = 0.5;
	explosion.drag = 0.9;
	explosion.hueChange = 0;
	explosion.brightnessEnd = 0; 
	
	
	
	//explosion.emitDelay = trails.emitLifeTime;
	
	rocketSettings.addParticleSystemSetting(laserTrails);
	rocketSettings.addParticleSystemSetting(trails);
	rocketSettings.addParticleSystemSetting(explosion);
	
	ts.rocketSettings = &rocketSettings;
	
	ts.rechargeSettings = TriggerRechargeSettings::fastMultiples;
	
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
	
	laserParticles.emitCount = 50;
	laserParticles.emitInheritVelocity = 1;
	laserParticles.shimmerMin = 0;
	laserParticles.lifeMin = 0.1;
	laserParticles.lifeMax = 0.1;
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




