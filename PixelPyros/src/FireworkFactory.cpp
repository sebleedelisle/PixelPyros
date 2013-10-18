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



TriggerSettingsRocket* FireworkFactory::getSimpleRocket(float speed, float hue , float saturation,  float speedVar, float directionVar ){
	
	ParticleSystemManager& particleSystemManager = *ParticleSystemManager::instance();
	
	RocketSettings& rocketSettings = *new RocketSettings();
	
	rocketSettings.startSpeedMin = speed *(1-speedVar);
	rocketSettings.startSpeedMax = speed;
	rocketSettings.direction = -90;
	rocketSettings.directionVar = directionVar;
	rocketSettings.gravity.y = 300;
	
	//rocketSettings.drag = 0.95;
	
	ParticleSystemSettings rocketParticles;
	rocketParticles.speedMin = 0;
	rocketParticles.speedMax = 0;
	rocketParticles.drag = 0.9;
	rocketParticles.gravity.y = 30;
	rocketParticles.directionZ = 0;
	rocketParticles.directionZVar = 90;
	rocketParticles.directionYVar = 180;
	
	rocketParticles.sizeStartMin = 2.5;
	rocketParticles.sizeStartMax = 7.5;
	rocketParticles.sizeChangeRatio = 0;
	rocketParticles.hueStartMin = hue;
	rocketParticles.hueStartMax = hue + 5;
	rocketParticles.hueChange = 0;
	rocketParticles.saturationMin = saturation/5;
	rocketParticles.saturationMax = saturation/2;
	rocketParticles.saturationEnd = saturation;
	rocketParticles.brightnessStartMin =
	rocketParticles.brightnessStartMin = 200;
	rocketParticles.brightnessEnd = 100;
	
	rocketParticles.shimmerMin = 0.1;
	rocketParticles.lifeMin = 0.1;
	rocketParticles.lifeMax = 0.5;
	
	//explosion.emitMode = PARTICLE_EMIT_BURST;
	rocketParticles.emitLifeTime = 2;
	rocketParticles.emitCount = 300;
	rocketParticles.startSound = "LaunchRocketSharp";
	
	
	// = getFlowerTrailParticles(hue, hueChange);
	//ParticleSystemSettings explosion = getFlowerExplosionParticles(hue, hueChange);
	//ParticleSystemSettings explosionLines = getLineExplosionParticles(150, hueChange);
	
	//trails.timeSpeed = explosion.timeSpeed = rocketSettings.timeSpeed = 0.7;
	
	//explosion.emitDelay = trails.emitLifeTime = 2;
	
	//rocketSettings.addParticleSystemSetting(trails);
	rocketSettings.addParticleSystemSetting(rocketParticles);
	//rocketSettings.addParticleSystemSetting(explosionLines);
	
	
	TriggerSettingsRocketOrb* ts = new TriggerSettingsRocketOrb();
	ts->radius = 7;
	ts->hue = hue;
	ts->saturation = saturation * 0.7;
	ts->addRocketSettings(&rocketSettings);
	ts->rechargeSettings = TriggerRechargeSettings::superFastMultiples;
	
	return ts;
	
	
}


// TODO is this really a rotating rocket or is it a fluffy rocket? CONFUSED

TriggerSettingsRocket* FireworkFactory::getRotatingRocket(float speed, float hue , float saturation, float speedVar, float directionVar ){
	
	ParticleSystemManager& particleSystemManager = *ParticleSystemManager::instance();
	
	RocketSettings& rocketSettings = *new RocketSettings();
	
	rocketSettings.startSpeedMin = speed *(1-speedVar);
	rocketSettings.startSpeedMax = speed;
	rocketSettings.direction = -90;
	rocketSettings.directionVar = directionVar;
	rocketSettings.gravity.y = 300;
	
	//rocketSettings.drag = 0.95;
	
	ParticleSystemSettings rocketParticles;
	rocketParticles.speedMin = 0;
	rocketParticles.speedMax = 0;
	rocketParticles.drag = 0.9;
	rocketParticles.gravity.y = 30;
	rocketParticles.directionZ = 0;
	rocketParticles.directionZVar = 90;
	rocketParticles.directionYVar = 180;
	
	rocketParticles.sizeStartMin = 2.5;
	rocketParticles.sizeStartMax = 7.5;
	rocketParticles.sizeChangeRatio = 0;
	rocketParticles.hueStartMin = hue;
	rocketParticles.hueStartMax = hue + 5;
	rocketParticles.hueChange = 0;
	rocketParticles.saturationMin = saturation/5;
	rocketParticles.saturationMax = saturation/2;
	rocketParticles.saturationEnd = saturation;
	rocketParticles.brightnessStartMin =
	rocketParticles.brightnessStartMin = 200;
	rocketParticles.brightnessEnd = 100;
	
	rocketParticles.shimmerMin = 0.1;
	rocketParticles.lifeMin = 0.1;
	rocketParticles.lifeMax = 0.5;
	
	//explosion.emitMode = PARTICLE_EMIT_BURST;
	rocketParticles.emitLifeTime = 2;
	rocketParticles.emitCount = 300;
	rocketParticles.startSound = "LaunchRocketSharp";
	
	
	// = getFlowerTrailParticles(hue, hueChange);
	//ParticleSystemSettings explosion = getFlowerExplosionParticles(hue, hueChange);
	//ParticleSystemSettings explosionLines = getLineExplosionParticles(150, hueChange);
	
	//trails.timeSpeed = explosion.timeSpeed = rocketSettings.timeSpeed = 0.7;
	
	//explosion.emitDelay = trails.emitLifeTime = 2;
	
	//rocketSettings.addParticleSystemSetting(trails);
	rocketSettings.addParticleSystemSetting(rocketParticles);
	//rocketSettings.addParticleSystemSetting(explosionLines);
	
	
	TriggerSettingsRocket* ts = new TriggerSettingsRocketOrb();
	ts->radius = 7;
	ts->hue = hue;
	ts->saturation = saturation * 0.7;
	ts->addRocketSettings(&rocketSettings);
	ts->rechargeSettings = TriggerRechargeSettings::fast;
	ts->rotateOnFire = true;
	
	return ts;
	
	
}




TriggerSettingsRocket* FireworkFactory::getBasicRocket(float hue , float hueChange, float flightTime){
	
	ParticleSystemManager& particleSystemManager = *ParticleSystemManager::instance();
	
	RocketSettings& rocketSettings = *new RocketSettings();
	
	rocketSettings.startSpeedMin = 600;
	rocketSettings.startSpeedMax = 800;
	rocketSettings.direction = -90;
	rocketSettings.directionVar = 2;
	rocketSettings.gravity.y = 400;
	
	//rocketSettings.drag = 0.95;
	
	ParticleSystemSettings trails = getFlowerTrailParticles(hue, hueChange);
	ParticleSystemSettings explosion = getFlowerExplosionParticles(hue, hueChange);
	//ParticleSystemSettings explosionLines = getLineExplosionParticles(150, hueChange);
	
	ParticleSystemSettings laserFlashParticles = getLaserFlashParticles(hue, 200);

	
	// the time would usually be 2/0.7 so we need to divide that by the flightTime
	// to change time to match the flight time. Confused? Me too! 
	trails.timeSpeed = explosion.timeSpeed = laserFlashParticles.timeSpeed = rocketSettings.timeSpeed = 0.7 * ((2/0.7) / flightTime);
	
	
	laserFlashParticles.emitDelay = explosion.emitDelay = trails.emitLifeTime = 2;
	
	//cout << "EXPECTED TIME : " << explosion.emitDelay * explosion.timeSpeed << endl;

	
	rocketSettings.addParticleSystemSetting(trails);
	rocketSettings.addParticleSystemSetting(explosion);
	rocketSettings.addParticleSystemSetting(laserFlashParticles);
	
	
	TriggerSettingsRocket* ts = new TriggerSettingsRocketOrb();
	ts->addRocketSettings(&rocketSettings);
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
	//explosion.renderer = new ParticleRendererBitmap(&softWhiteImage);
	explosion.renderer = new ParticleRendererShape();
	
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
	
	explosion.emitMode = PARTICLE_EMIT_BURST;
	explosion.emitShape = new ofMesh(ofMesh::icosphere(1,2));
	explosion.emitLifeTime = 0.1;
	explosion.directionYVar = explosion.directionZVar = 0;
	explosion.emitCount = explosion.emitShape->getNumVertices()/explosion.emitLifeTime;

	explosion.startSound = "SoftExplosion";
	
	
	return explosion;
	
	
}

TriggerSettingsRocket* FireworkFactory :: getSimpleFountain(float hueStartOffset , float hueChange){
	
	
	
	ParticleRendererBase* renderer = new ParticleRendererShape();
	
	ParticleSystemSettings ps, ps2;
	
	
	// SPARKLES **************************
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
	
	
	// SMOKE ***************************************
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
	ps2.emitCount = 200;
	
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
	rocketSettings.setLifeTime(1);
	ps.timeSpeed = ps2.timeSpeed = rocketSettings.timeSpeed = 0.5;
	
	
	rocketSettings.addParticleSystemSetting(ps);
	rocketSettings.addParticleSystemSetting(ps2);
	
	TriggerSettingsRocket* ts = new TriggerSettingsRocketOrb();
	ts->addRocketSettings(&rocketSettings);
	
	ts->rechargeSettings = TriggerRechargeSettings::fast;
	ts->radius = 5; 
	return ts;
	
	
	
}


TriggerSettingsRocket* FireworkFactory :: getFountain(float hueStartOffset , float hueChange){
	return new TriggerSettingsFountain(hueStartOffset, hueChange);
	
}


TriggerSettingsRocket* FireworkFactory :: getFluffyRocket(){
	
	RocketSettings& rocketSettings = *new RocketSettings();
	ParticleSystemSettings pss;
	pss.renderer = new ParticleRendererBitmap(&softWhiteImage);
	
	pss.gravity.y = 100;
	pss.speedMin = 00;
	pss.speedMax = 20;
	pss.drag = 0.93;
	
	pss.sizeStartMin = 8;
	pss.sizeStartMax = 15;
	pss.sizeChangeRatio = 0.9;
	pss.shimmerMin = 1;
	
	pss.emitCount = 500;
	pss.emitStartSizeModifier = 0.2;
	
	pss.brightnessStartMin = 10;
	pss.brightnessStartMax = 255;
	pss.brightnessEnd = 0;
	
	pss.lifeMin = 0.5;
	pss.lifeMax = 0.8;
	
	
	pss.startSound = "RocketFountain";
	
	
	rocketSettings.startSpeedMin = 800;
	rocketSettings.startSpeedMax = 1000	;
	rocketSettings.gravity.y = 1200;
	rocketSettings.timeSpeed = pss.timeSpeed = 0.7;
	
	
	
	rocketSettings.addParticleSystemSetting(pss);
	//rocketSettings.addParticleSystemSetting(getSmoke());
	TriggerSettingsRocket* ts = new TriggerSettingsRocketOrb();
	ts->addRocketSettings(&rocketSettings);
	ts->rechargeSettings = TriggerRechargeSettings::fast;
	
	return ts;
	
}




TriggerSettingsRocket* FireworkFactory:: getBangerRocket() {
	
	RocketSettings& rocketSettings = *new RocketSettings();
	
	rocketSettings.startSpeedMin = 1000;
	rocketSettings.startSpeedMax = 1200;
	rocketSettings.directionVar = 4;
	rocketSettings.gravity.y = 200;
	rocketSettings.drag = 0.95;
	
	ParticleSystemSettings trails = getBangerTrails();
	ParticleSystemSettings bang = getBangerBang();
	ParticleSystemSettings bangCrackles = getBangerCrackles();
	ParticleSystemSettings smoke1 = getSmoke();
	ParticleSystemSettings smoke2 = getSmoke();
	
	smoke2.emitMode = PARTICLE_EMIT_CONTINUOUS;
	smoke2.emitCount = 200;
	smoke2.emitLifeTime = 0.2;
	smoke2.sizeStartMax = 30;
	smoke2.speedMax = 100;
	smoke2.brightnessStartMin = 10;
	smoke2.brightnessStartMax = 30;
	
	
	bang.emitDelay = bangCrackles.emitDelay = trails.emitLifeTime = smoke1.emitLifeTime =smoke2.emitDelay = 2;
	
	rocketSettings.addParticleSystemSetting(trails);
	//rocketSettings.addParticleSystemSetting(smoke1);
	rocketSettings.addParticleSystemSetting(smoke2);
	rocketSettings.addParticleSystemSetting(bang);
	rocketSettings.addParticleSystemSetting(bangCrackles);
	
	TriggerSettingsRocket* ts = new TriggerSettingsRocketOrb();
	
	ts->addRocketSettings(&rocketSettings);
	ts->rechargeSettings = TriggerRechargeSettings::slow;
	ts->radius *=1.3;
	
	return ts;
	
	
}




ParticleSystemSettings FireworkFactory :: getBangerTrails() {
	
	ParticleSystemSettings trails;
	trails.renderer = new ParticleRendererLine(1, true);
	trails.directionZVar = 20;
	trails.speedMin = 5;
	trails.speedMax = 60;
	trails.sizeStartMin = trails.sizeStartMax = 3;
	trails.hueStartMin = trails.hueStartMax = 30;
	trails.hueChange = -10;
	trails.saturationMin = trails.saturationMax = 0;
	trails.saturationEnd = 0;
	trails.brightnessStartMin = trails.brightnessStartMin = trails.brightnessEnd = 255;
	
	trails.emitInheritVelocity = -0.1;
	trails.emitStartSizeModifier = 0;
	trails.emitSpeedModifier = 0;
	
	trails.emitCount = 100;
	
	
	trails.shimmerMin = 0;
	trails.lifeMin = 0.1;
	trails.lifeMax = 0.3;
	trails.startSound = "Launch";
	
	return trails;
	
	
}


ParticleSystemSettings FireworkFactory:: getBangerBang() {
	
	ParticleSystemSettings explosion;
	//explosion.renderer = new ParticleRendererCircle(24);
	explosion.renderer = new ParticleRendererBitmap(&bangerFlashImage);
	
	//pss.directionZVar = 20;
	explosion.speedMin = 0;
	explosion.speedMax = 0;
	explosion.drag = 0.90;
	
	explosion.sizeStartMin = 600;
	explosion.sizeStartMax = 900;
	explosion.sizeChangeRatio = 0;
	explosion.hueStartMin = explosion.hueStartMax = 0;
	explosion.hueChange = 0;
	explosion.saturationMin = explosion.saturationMax = 0;
	explosion.saturationEnd = 0;
	explosion.brightnessStartMin = explosion.brightnessStartMin = 255;
	explosion.brightnessEnd = 0;
	
	explosion.shimmerMin = 1;
	explosion.lifeMin = 0.1;
	explosion.lifeMax = 0.1;
	
	explosion.emitMode = PARTICLE_EMIT_BURST;
	explosion.emitLifeTime = 0.1;
	explosion.emitCount = 1;
	
	
	
	explosion.startSound = "Banger";
	
	
	return explosion;
	
	
	return ParticleSystemSettings();
	
}



ParticleSystemSettings FireworkFactory:: getBangerCrackles() {
	
	ParticleSystemSettings explosion;
	//explosion.renderer = new ParticleRendererCircle();
	explosion.renderer = new ParticleRendererLaser();
	
	
	explosion.directionYVar= 90;
	explosion.speedMin = 300;
	explosion.speedMax = 400;
	explosion.drag = 0.93;
	
	explosion.sizeStartMin = 5;
	explosion.sizeStartMax = 8;
	explosion.hueStartMin = explosion.hueStartMax = 0;
	explosion.hueChange = 0;
	explosion.saturationMin = explosion.saturationMax = 0;
	explosion.saturationEnd = 0;
	explosion.brightnessStartMin = explosion.brightnessStartMax = 255;
	explosion.brightnessEnd = 0;
	
	explosion.shimmerMin = 0.0;
	explosion.lifeMin = 0.1;
	explosion.lifeMax = 0.2;
	
	explosion.emitMode = PARTICLE_EMIT_BURST;
	//explosion.emitLifeTime = 0.1;
	explosion.emitCount = 200;
	
	explosion.renderDelayMin = 0.5;
	explosion.renderDelayMax = 3;
	
	
	explosion.startSound = "Crackle";
	
	
	return explosion;
	
	
}


ParticleSystemSettings FireworkFactory:: getSmoke() {
	
	float hueStartOffset = 200;
	float saturation = 0;
	ParticleSystemSettings ps2;
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
	
	ps2.saturationMin = saturation;
	ps2.saturationMax = saturation;
	ps2.saturationEnd = saturation;
	
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
	
	ps2.renderer = new ParticleRendererBitmap(&softWhiteImage);
	
	
	return ps2;
	
	
}

ParticleSystemSettings FireworkFactory :: getLaserExplosionParticles(float hue, float hueChange){
	
	ParticleSystemSettings explosion;
	explosion.renderer = new ParticleRendererLaser();
	
	//pss.directionZVar = 20;
	explosion.speedMin = 0;
	explosion.speedMax = 0;
	explosion.drag = 0;
	explosion.gravity.y = 0;
	explosion.directionZ = 0;
	explosion.directionZVar = 0;
	explosion.directionYVar = 0;
	
	explosion.sizeStartMin = 0.1;
	explosion.sizeStartMax = 4;
	explosion.sizeChangeRatio = 30;
	explosion.hueStartMin = hue;
	explosion.hueStartMax = hue + 5;
	explosion.hueChange = -20;
	explosion.saturationMin = 0;
	explosion.saturationMax = 0;
	explosion.saturationEnd = 0;
	explosion.brightnessStartMin =
	explosion.brightnessStartMax = 255;
	explosion.brightnessEnd = 0;
	
	explosion.shimmerMin = 1;
	explosion.lifeMin = 0.2;
	explosion.lifeMax = 0.2;
	
	explosion.emitMode = PARTICLE_EMIT_BURST;
	explosion.emitLifeTime = 0.1;
	explosion.emitCount = 10;
	
	explosion.startSound = "SoftExplosion";
	
	
	return explosion;
	
	
}

TriggerSettingsRocket* FireworkFactory :: getWigglyRocket(){
	
	RocketSettings& rocketSettings = *new RocketSettings();
	
	rocketSettings.startSpeedMin = 100;
	rocketSettings.startSpeedMax = 120;
	rocketSettings.directionVar = 4;
	rocketSettings.gravity.y = 0;
	rocketSettings.drag = 0.999;
	rocketSettings.addParticleSystemSetting(getBangerTrails());
	
	rocketSettings.setLifeTime(12);
	rocketSettings.addParticleRenderer(new ParticleRendererShape());
	
	
	

	
	TriggerSettingsRocket* ts = new TriggerSettingsRocketOrb();
	
	ts->addRocketSettings(&rocketSettings);
	ts->rechargeSettings = TriggerRechargeSettings::slow;
	ts->radius *=1.3;
	
	return ts;
	
}

ParticleSystemSettings FireworkFactory:: getLaserFlashParticles(float hue, float saturation) {
	
	ParticleSystemSettings pss;
	
	pss.renderer = new ParticleRendererLaserFlash(20);
	pss.emitCount =1;
	pss.emitMode = PARTICLE_EMIT_BURST;
	
	pss.sizeStartMin = pss.sizeStartMax = 1;
	pss.sizeChangeRatio = 30;
	pss.saturationMin = pss.saturationMax = 0;
	pss.saturationEnd = saturation;
	pss.lifeMin = pss.lifeMax = 0.2;
	pss.brightnessEnd = 0;
	pss.brightnessStartMin = pss.brightnessStartMax = 500;
	
	return pss;
}


