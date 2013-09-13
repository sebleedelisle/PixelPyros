//
//  FireworkFactory.cpp
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 09/09/2013.
//
//

#include "FireworkFactory.h"


FireworkFactory* FireworkFactory::factory = NULL;

FireworkFactory* FireworkFactory::instance() {
	
	if (factory == NULL) {
		factory = new FireworkFactory();
	}
	return factory;
	
}

FireworkFactory :: FireworkFactory() {
		
	softWhiteImage.loadImage("img/ParticleWhite.png");
	bangerFlashImage.loadImage("img/ParticleBangerFlash.png");

	
}


TriggerSettingsRocket* FireworkFactory::getBasicRocket(float hue , float hueChange ){
	
	ParticleSystemManager& particleSystemManager = *ParticleSystemManager::instance();
	
	RocketSettings& rocketSettings = *new RocketSettings();
	
	rocketSettings.startSpeedMin = 600;
	rocketSettings.startSpeedMax = 800;
	rocketSettings.direction = -90;
	rocketSettings.directionVar = 4;
	rocketSettings.gravity.y = 400;
	
	//rocketSettings.drag = 0.95;
	
	ParticleSystemSettings trails = getFlowerTrailParticles(hue, hueChange);
	ParticleSystemSettings explosion = getFlowerExplosionParticles(hue, hueChange);
	//ParticleSystemSettings explosionLines = getLineExplosionParticles(150, hueChange);
	
	trails.timeSpeed = explosion.timeSpeed = rocketSettings.timeSpeed = 0.7;
	
	explosion.emitDelay = trails.emitLifeTime = 2;
	
	rocketSettings.addParticleSystemSetting(trails);
	rocketSettings.addParticleSystemSetting(explosion);
	//rocketSettings.addParticleSystemSetting(explosionLines);
	
	
	TriggerSettingsRocket* ts = new TriggerSettingsRocket();
	ts->rocketSettings = &rocketSettings;
	ts->rechargeSettings = TriggerRechargeSettings::medium; 
	
	return ts;
	

	
	
}


ParticleSystemSettings FireworkFactory :: getFlowerTrailParticles(float hue, float hueChange ){
	
	
	ParticleSystemSettings trails;
	trails.renderer = new ParticleRendererShape();
	
	
	trails.speedMin = 20;
	trails.speedMax = 50;
	trails.directionZ = 0;
	trails.directionZVar = 90;
	trails.directionYVar = 180;
	trails.drag = 0.90;
	trails.gravity.set(0,30);
	
	
	
	trails.sizeStartMin = 4;
	trails.sizeStartMax = 6;
	trails.sizeChangeRatio = 1;
	
	trails.hueStartMin = hue;
	trails.hueStartMax = hue;
	trails.hueChange = hueChange;
	trails.saturationMin = trails.saturationMax = 0;
	trails.saturationEnd = 300;
	trails.brightnessStartMin = 150;
	trails.brightnessStartMax = 255;
	trails.brightnessEnd = 0;
	
	trails.emitInheritVelocity = -0.5;
	trails.emitCount = 1000;
	
	
	//trails.shimmerMin = 0;
	trails.lifeMin = 0.5;
	trails.lifeMax = 0.8;
	trails.startSound = "LaunchRocketSharp";
	
	return trails;
	
	
};
ParticleSystemSettings FireworkFactory :: getFlowerExplosionParticles(float hue, float hueChange){
	
	
	
	ParticleSystemSettings explosion;
	explosion.renderer = new ParticleRendererBitmap(&softWhiteImage);
	
	//pss.directionZVar = 20;
	explosion.speedMin = 650;
	explosion.speedMax = 700;
	explosion.drag = 0.9;
	explosion.gravity.y = 30;
	explosion.directionZ = 0;
	explosion.directionZVar = 90;
	explosion.directionYVar = 180;
	
	
	
	explosion.sizeStartMin = 15;
	explosion.sizeStartMax = 25;
	explosion.sizeChangeRatio = 0;
	explosion.hueStartMin = hue;
	explosion.hueStartMax = hue + 5;
	explosion.hueChange = -20;
	explosion.saturationMin = 50;
	explosion.saturationMax = 100;
	explosion.saturationEnd = 500;
	explosion.brightnessStartMin =
	explosion.brightnessStartMin = 155;
	explosion.brightnessEnd = 100;
	
	explosion.shimmerMin = 0.1;
	explosion.lifeMin = 0.5;
	explosion.lifeMax = 0.8;
	
	//explosion.emitMode = PARTICLE_EMIT_BURST;
	explosion.emitLifeTime = 0.1;
	explosion.emitCount = 10000;
	
	explosion.startSound = "SoftExplosion";
	
	
	return explosion;
	
	
}

TriggerSettingsRocket* FireworkFactory :: getFountain(float hueStartOffset , float hueChange){
	
	
	
	ParticleRendererBase* renderer = new ParticleRendererShape();
	
	ParticleSystemSettings ps, ps2;
	
	// ParticleData
	// size range
	// size modifier
	// velocity range
	// life range
	// drag
	// gravity
	// colour
	// colour modifier
	// renderer
	
	// EmmisionData
	// Frequency
	// Burst/continuous
	// range of start sizes for particles
	// range of colours for particles
	
	// optional colour modifier
	// PHYSICS
	ps.speedMin = 0;
	ps.speedMax = 20;
	ps.directionZ = 0;
	ps.directionZVar = 90;
	ps.directionYVar = 180;
	ps.drag = 0.90;
	ps.gravity.set(0,30);
	
	//LIFE
	ps.lifeMin = 0.5;
	ps.lifeMax = 2;
	
	//APPEARANCE
	
	ps.sizeStartMin = 10;
	ps.sizeStartMax = 15;
	ps.sizeChangeRatio = 0;
	
	ps.hueStartMin = hueStartOffset;
	ps.hueStartMax = hueStartOffset+10;
	ps.hueChange = hueChange;
	
	ps.brightnessStartMin = 255;
	ps.brightnessStartMax = 255;
	ps.brightnessEnd = 255;
	
	ps.saturationMin = 0;
	ps.saturationMax = 0;
	ps.saturationEnd = 500;
	
	ps.shimmerMin = 0.1;
	
	// but also :
	// lifeExpectancy
	// delay
	
	ps.emitMode = PARTICLE_EMIT_CONTINUOUS;
	ps.emitCount = 200;
	
	ps.emitDelay = 0;
	ps.emitLifeTime= 0.6;
	
	ps.emitStartSizeModifier = 0;
	ps.emitSpeedModifier = 1;
	ps.emitHueModifierOffset = 0;
	
	//ps.emitAttachedPhysicsObject = &rocket;
	ps.emitInheritVelocity = 0.3;
	ps.startSound = "RocketFountain";
	
	//psystem.init(ps);
	
	// optional colour modifier
	
	
	// PHYSICS
	ps2.speedMin = 15;
	ps2.speedMax = 20;
	ps2.directionZ = 0;
	ps2.directionZVar = 90;
	ps2.directionYVar = 180;
	ps2.drag = 0.90;
	ps2.gravity.set(0,-30);
	
	//LIFE
	ps2.lifeMin = 1;
	ps2.lifeMax = 1.5;
	
	//APPEARANCE
	
	ps2.sizeStartMin = 2;
	ps2.sizeStartMax = 5;
	ps2.sizeChangeRatio = 5;
	
	ps2.hueStartMin = 0+hueStartOffset;
	ps2.hueStartMax = 0+hueStartOffset;
	ps2.hueChange = 0;
	
	ps2.brightnessStartMin = 20;
	ps2.brightnessStartMax = 70;
	ps2.brightnessEnd = 0;
	
	ps2.saturationMin = 100;
	ps2.saturationMax = 250;
	ps2.saturationEnd = 100;
	
	//ps.shimmerMin = 0.1;
	
	// but also :
	// lifeExpectancy
	// delay
	
	ps2.emitStartSizeModifier = 0;
	//ps2.emitSpeedModifier = 0;
	
	
	ps2.emitMode = PARTICLE_EMIT_CONTINUOUS;
	ps2.emitCount = 500;
	
	ps2.emitDelay = 0;
	ps2.emitLifeTime= 0.5;
	
	ps2.renderer = ps.renderer = renderer;
	//ps2.velocityModifierSettings = new VelocityModifierSettings(200,300);
	
	
	RocketSettings& rocketSettings = *new RocketSettings();
	rocketSettings.startSpeedMin = 1000;
	rocketSettings.startSpeedMax = 1500;
	rocketSettings.direction = -90;
	rocketSettings.directionVar = 5;
	rocketSettings.gravity.y = 300;
	rocketSettings.drag = 0.9;
	rocketSettings.lifeTime = 1;
	ps.timeSpeed = ps2.timeSpeed = rocketSettings.timeSpeed = 0.5;
	
	
	rocketSettings.addParticleSystemSetting(ps);
	rocketSettings.addParticleSystemSetting(ps2);
	
	TriggerSettingsRocket* ts = new TriggerSettingsRocket();
	ts->rocketSettings = &rocketSettings;
	
	ts->rechargeSettings = TriggerRechargeSettings::fast;
	ts->radius = 5; 
	return ts;
	
	
	
}




