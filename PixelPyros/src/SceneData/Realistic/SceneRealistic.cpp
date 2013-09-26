//
//  SceneRealistic .cpp
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 27/08/2012.
//
//

#include "SceneRealistic.h"

SceneRealistic :: SceneRealistic(string scenename) : Scene(scenename) {

	FireworkFactory& fireworkFactory = *FireworkFactory::instance();
	
	loadMusicFile("LightsEllie.aif");
	softWhiteImage.loadImage("img/ParticleWhite.png");
	//bangerFlashImage.loadImage("img/ParticleBangerFlash.png");
	
	TriggerPattern blank;
	addTriggerPattern(blank);
	
	TriggerSettingsRocket* triggerFluffy = fireworkFactory.getFluffyRocket();
	TriggerSettingsRocket* triggerFountain = getFountain(); 

	TriggerSettingsRocket* triggerFlower = getFlowerRocket(20);
	triggerFlower->hue = 20;
	triggerFlower->saturation = 100;
		

	TriggerSettingsRocket* triggerBanger = fireworkFactory.getBangerRocket();

	
	TriggerPattern patternFluffy;
	
	patternFluffy.addTriggerSettings(triggerFluffy);
	patternFluffy.addTriggerSettings();
	patternFluffy.addTriggerSettings(triggerFountain);
	patternFluffy.addTriggerSettings();
	addTriggerPattern(patternFluffy); 
	
	// fluffy with added flowers
	patternFluffy.addTriggerSettings(triggerFlower);
	patternFluffy.addTriggerSettings();

	addTriggerPattern(patternFluffy);
	
	
	
	// another fountain and banger
	patternFluffy.addTriggerSettings(triggerFountain);
	patternFluffy.addTriggerSettings();
	patternFluffy.addTriggerSettings(triggerBanger);
	patternFluffy.addTriggerSettings();
	addTriggerPattern(patternFluffy);
	
	
	TriggerSettingsRocket*  triggerFlowerPurple = getFlowerRocket(220);
	triggerFlowerPurple->hue = 255-20;
	triggerFlowerPurple->saturation = 200;
	

	
	TriggerPattern multiColourFountains;
	
	float colours [4] = {170, 0, 220, 0};
	
	for(int i = 0; i<4; i++) {
		TriggerSettingsRocket* triggerRocketFountain = getFountain(colours[i]);
		
	
		//fountain.startSpeedMax *=2;
		
		triggerRocketFountain->hue = colours[i];
		triggerRocketFountain->saturation = 100;
		
		multiColourFountains.addTriggerSettings(triggerRocketFountain);
		multiColourFountains.addTriggerSettings();
	}
	addTriggerPattern(multiColourFountains); 
	
	
	TriggerPattern patternNewColour;
	patternNewColour.addTriggerSettings(triggerFluffy);
	patternNewColour.addTriggerSettings();
	patternNewColour.addTriggerSettings(triggerFountain);
	patternNewColour.addTriggerSettings();
	patternNewColour.addTriggerSettings(triggerFlowerPurple);
	patternNewColour.addTriggerSettings();
	
	addTriggerPattern(patternNewColour);
	
	
	TriggerPattern endPattern;
	TriggerSettingsRocket* triggerBigFlower = getSphereFlowerRocket(140);
	
	triggerBigFlower->hue = 140;
	triggerBigFlower->saturation = 200;
	triggerBigFlower->radius= 10;
	
	endPattern.addTriggerSettings(triggerFlower);
	endPattern.addTriggerSettings();
	endPattern.addTriggerSettings(triggerBigFlower);
	endPattern.addTriggerSettings();
	endPattern.addTriggerSettings(triggerBanger);
	endPattern.addTriggerSettings();
	endPattern.addTriggerSettings(triggerFountain);
	
	addTriggerPattern(endPattern);

	 
	 
}


TriggerSettingsRocket*  SceneRealistic :: getFountain(float hueStartOffset , float hueChange){
	
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
	
	ps.hueStartMin = 0;
	ps.hueStartMax = 30;
	ps.hueChange = hueChange;
	
	ps.brightnessStartMin = 255;
	ps.brightnessStartMax = 255;
	ps.brightnessEnd = 255;
	
	ps.saturationMin = 0;
	ps.saturationMax = 0;
	ps.saturationEnd = 0;
	
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
	ps2.saturationMax = 100;
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
	
	rocketSettings.addParticleSystemSetting(ps);
	rocketSettings.addParticleSystemSetting(ps2);
	
	TriggerSettingsRocket* ts = new TriggerSettingsRocket();
	
	ts->rocketSettings = &rocketSettings;
	ts->rechargeSettings = TriggerRechargeSettings::fast;
	
	return ts;
	
	
	
}



TriggerSettingsRocket*  SceneRealistic :: getFlowerRocket(float hue , float hueChange ){
	
	RocketSettings& rocketSettings = *new RocketSettings();
	
	rocketSettings.startSpeedMin = 1200;
	rocketSettings.startSpeedMax = 1500;
	rocketSettings.directionVar = 4;
	rocketSettings.gravity.y = 200; 
	rocketSettings.drag = 0.95;
	
	ParticleSystemSettings trails = getFlowerTrailParticles(hue, hueChange);
	ParticleSystemSettings explosion = getFlowerExplosionParticles(hue, hueChange);
	ParticleSystemSettings explosionLines = getLineExplosionParticles(150, hueChange);
	
	
	
	explosion.emitDelay = explosionLines.emitDelay = trails.emitLifeTime = 2;
	
	rocketSettings.addParticleSystemSetting(trails);
	rocketSettings.addParticleSystemSetting(explosion);
	rocketSettings.addParticleSystemSetting(explosionLines);
	
	TriggerSettingsRocket* ts = new TriggerSettingsRocket();
	
	ts->rocketSettings = &rocketSettings;
	ts->rechargeSettings = TriggerRechargeSettings::medium;
	
	return ts;

	

	
};


TriggerSettingsRocket* SceneRealistic :: getSphereFlowerRocket(float hue , float hueChange ){
	
	RocketSettings& rocketSettings =* new RocketSettings();
	
	rocketSettings.startSpeedMin = 1200;
	rocketSettings.startSpeedMax = 1500;
	rocketSettings.directionVar = 4;
	rocketSettings.gravity.y = 200;
	rocketSettings.drag = 0.95;
	
	ParticleSystemSettings trails = getFlowerTrailParticles(hue, hueChange);
	ParticleSystemSettings explosion = getFlowerExplosionParticles(hue, hueChange);
	explosion.directionZ = 0;
	explosion.directionZVar = 90;
	explosion.directionY = 0;
	explosion.directionYVar = 180;
	explosion.speedMin = 900;
	explosion.speedMax = 1000;
	
	ParticleSystemSettings explosionLines = getLineExplosionParticles(150, hueChange);
	ParticleSystemSettings crackles = FireworkFactory::instance()->getBangerCrackles();
	crackles.renderer = new ParticleRendererStar(20, 70);
	crackles.brightnessStartMax = 150;
	crackles.brightnessStartMin = 100;
	crackles.sizeStartMax = 5;
	crackles.sizeStartMin = 3;
//	crackles.emitDelay = 0;
//	crackles.startSound = "";
//	crackles.emitMode = PARTICLE_EMIT_CONTINUOUS;
//	crackles.renderDelayMin = 0.01;
//	crackles.renderDelayMax = 0.2;
//	crackles.speedMin = 0;
//	crackles.speedMax = 0.5;
	
	
	
	
	explosion.emitDelay = explosionLines.emitDelay = crackles.emitDelay = trails.emitLifeTime = 2;
	
	rocketSettings.addParticleSystemSetting(trails);
	rocketSettings.addParticleSystemSetting(explosion);
	rocketSettings.addParticleSystemSetting(explosionLines);
	rocketSettings.addParticleSystemSetting(crackles);
	
	TriggerSettingsRocket* ts = new TriggerSettingsRocket();
	
	ts->rocketSettings = &rocketSettings;
	ts->rechargeSettings = TriggerRechargeSettings::medium;
	
	return ts;
	
	
};


ParticleSystemSettings SceneRealistic :: getFlowerTrailParticles(float hue, float hueChange ){
	
	
	ParticleSystemSettings trails;
	trails.renderer = new ParticleRendererLine(1.5, true);
	//pss.directionZVar = 20;
	trails.speedMin = 10;
	trails.speedMax = 10;
	trails.sizeStartMin = trails.sizeStartMax = 3;
	trails.hueStartMin = trails.hueStartMax = hue;
	trails.hueChange = hueChange;
	trails.saturationMin = trails.saturationMax = 0;
	trails.saturationEnd = 300;
	trails.brightnessStartMin = trails.brightnessStartMin = trails.brightnessEnd = 255;
	
	trails.emitInheritVelocity = -0.1;
	trails.emitCount = 500;
	
	
	trails.shimmerMin = 0;
	trails.lifeMin = 0.1;
	trails.lifeMax = 0.3;
	trails.startSound = "LaunchRocketSharp";
	
	return trails;

	
};
ParticleSystemSettings SceneRealistic :: getFlowerExplosionParticles(float hue, float hueChange){
	
	
	
	ParticleSystemSettings explosion;
	explosion.renderer = new ParticleRendererBitmap(&softWhiteImage);
	
	//pss.directionZVar = 20;
	explosion.speedMin = 300;
	explosion.speedMax = 500;
	explosion.drag = 0.9;
	
	explosion.sizeStartMin = 20;
	explosion.sizeStartMax = 40;
	explosion.hueStartMin = explosion.hueStartMax = hue;
	explosion.hueChange = hueChange;
	explosion.saturationMin = explosion.saturationMax = 0;
	explosion.saturationEnd = 500;
	explosion.brightnessStartMin = explosion.brightnessStartMin = 255;
	explosion.brightnessEnd = 0;
	
	explosion.shimmerMin = 0.5;
	explosion.lifeMin = 0.5;
	explosion.lifeMax = 1;
	
	//explosion.emitMode = PARTICLE_EMIT_BURST;
	explosion.emitLifeTime = 0.1;
	explosion.emitCount = 3000;
	
	explosion.startSound = "SoftExplosion";
	
	
	return explosion;
	
	
}
ParticleSystemSettings SceneRealistic :: getLineExplosionParticles(float hue, float hueChange){
	
	
	
	ParticleSystemSettings explosion;
	explosion.renderer = new ParticleRendererLine(2, true);
	
	//pss.directionZVar = 20;
	explosion.speedMin = 300;
	explosion.speedMax = 500;
	explosion.drag = 0.95;
	explosion.gravity.y = 100;
	
	explosion.sizeStartMin = 5;
	explosion.sizeStartMax = 10;
	explosion.hueStartMin = explosion.hueStartMax = hue;
	explosion.hueChange = hueChange;
	explosion.saturationMin = explosion.saturationMax = 0;
	explosion.saturationEnd = 150;
	explosion.brightnessStartMin = explosion.brightnessStartMin =  255;
	explosion.brightnessEnd = 0;
	
	explosion.shimmerMin = 0.5;
	explosion.lifeMin = 1;
	explosion.lifeMax = 2;
	
	//explosion.emitMode = PARTICLE_EMIT_BURST;
	explosion.emitLifeTime = 0.1;
	explosion.emitCount = 2000;
	
	//explosion.startSound = "RetroExplosion";
	
	
	return explosion;
	
	
}


