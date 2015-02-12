//
//  SceneSpace.cpp
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 02/09/2012.
//
//

#include "SceneSpace.h"



SceneSpace::SceneSpace(string scenename, ParticleSystemManager& psm) : Scene(scenename, psm){
	
	starfield.speed = 100;
	
	
	softWhiteImage.loadImage("img/ParticleWhite.png");
	bangerFlashImage.loadImage("img/ParticleBangerFlash.png");
	
	TriggerPattern blank;
	addTriggerPattern(blank);
	
	
	TriggerRocket planetTrigger(particleSystemManager);
	planetTrigger.addRocketSettings(getPlanetRocket());
	planetTrigger.type = TRIGGER_TYPE_FIRE_ON_MOTION;
	planetTrigger.triggerLevel = 1;
	planetTrigger.motionSensitivity = 5;
	planetTrigger.restoreSpeed = 3;
	planetTrigger.radius = 10;
	planetTrigger.hue = 20;
	planetTrigger.saturation = 150; 
	
	//pattern.addTrigger(trigger);
	
	
	
	// makes one shot type
	TriggerRocket starTrigger(psm);
	
	starTrigger.addRocketSettings(getStarryRocket());
	starTrigger.type = TRIGGER_TYPE_FIRE_ON_MOTION;
	starTrigger.triggerLevel = 1;
	starTrigger.restoreSpeed = 4;
	starTrigger.triggerPower = 0.2;
	
	
	TriggerRocket fountainTrigger(psm);
	
	fountainTrigger.addRocketSettings(RocketFountain(120));
	fountainTrigger.type = TRIGGER_TYPE_FIRE_ON_MOTION;
	fountainTrigger.triggerLevel = 1;
	fountainTrigger.restoreSpeed = 10;
	fountainTrigger.triggerPower = 0.2;
	
	
	TriggerPattern fountainPattern;
	fountainPattern.addTrigger(fountainTrigger);
	fountainPattern.addTrigger(fountainTrigger);
	fountainPattern.addTrigger(fountainTrigger);
	
	addTriggerPattern(fountainPattern);
	
	TriggerPattern starryPattern;
	starryPattern.addTrigger(starTrigger);
	
	addTriggerPattern(starryPattern);
	
	
	TriggerPattern pattern;
	
	pattern.addTrigger(starTrigger);
	pattern.addTrigger(planetTrigger);
	
	addTriggerPattern(pattern);

	
	
	TriggerRocket triggerFluffy(psm);
	triggerFluffy.restoreSpeed = 4;
	triggerFluffy.addRocketSettings(getFluffyRocket());
	
	TriggerRocket triggerFlower(psm);
	triggerFlower.addRocketSettings(getFlowerRocket(10));
	triggerFlower.radius = 8;
	triggerFlower.hue = 10;
	triggerFlower.saturation = 100;
	
	
	TriggerRocket triggerFountain(psm);
	triggerFountain.addRocketSettings(getFountain());
	triggerFountain.restoreSpeed = 4;
	
	
	TriggerRocket triggerBanger(psm);
	triggerBanger.triggerPower = 1;
	triggerBanger.addRocketSettings(getBangerRocket());
	triggerBanger.radius = 10;
	
	
	TriggerPattern patternFluffy;
	
	patternFluffy.addTrigger(triggerFluffy);
	patternFluffy.addTrigger(triggerFountain);
	
	addTriggerPattern(patternFluffy);
	
	// fluffy with added flowers
	patternFluffy.addTrigger(triggerFlower);
	addTriggerPattern(patternFluffy);
	
	
	// another fountain and banger
	patternFluffy.addTrigger(triggerFountain);
	patternFluffy.addTrigger(triggerBanger);
	addTriggerPattern(patternFluffy);
	
	
	TriggerRocket triggerFlowerPurple(psm);
	triggerFlowerPurple.addRocketSettings(getFlowerRocket(220));
	triggerFlowerPurple.radius = 8;
	triggerFlowerPurple.hue = 255-20;
	triggerFlowerPurple.saturation = 200;
	
	
	
	TriggerPattern multiColourFountains;
	
	float colours [4] = {170, 0, 220, 0};
	
	for(int i = 0; i<4; i++) {
		TriggerRocket triggerRocketFountain(psm);
		
		RocketSettings fountain = getFountain(colours[i]);
		fountain.startSpeedMax *=2;
		triggerRocketFountain.addRocketSettings(fountain);
		triggerRocketFountain.restoreSpeed= 4;
		
		triggerRocketFountain.hue = colours[i];
		triggerRocketFountain.saturation = 100;
		
		multiColourFountains.addTrigger(triggerRocketFountain, 0,0,1);
	}
	addTriggerPattern(multiColourFountains);
	
	
	TriggerPattern patternNewColour;
	patternNewColour.addTrigger(triggerFluffy);
	patternNewColour.addTrigger(triggerFountain);
	patternNewColour.addTrigger(triggerFlowerPurple);
	
	addTriggerPattern(patternNewColour);
	
	TriggerPattern endPattern;
	RocketSettings bigFlowerRocket = getSphereFlowerRocket(140);
	TriggerRocket triggerBigFlower(psm);
	triggerBigFlower.hue = 140;
	triggerBigFlower.saturation = 200;
	triggerBigFlower.radius= 10;
	triggerBigFlower.addRocketSettings(bigFlowerRocket);
	
	triggerBanger.restoreSpeed = 2; 
	
	endPattern.addTrigger(triggerFlower);
	endPattern.addTrigger(triggerBigFlower);
	endPattern.addTrigger(triggerBanger);
	endPattern.addTrigger(triggerFountain);
	endPattern.addTrigger(starTrigger);
	
	addTriggerPattern(endPattern);
	
	ofMesh letterMesh;
	LetterWritingPatternMaker patternMaker;
	TriggerPattern textPattern = patternMaker.getPattern(psm, "Goodnight!", 15, 0.2, 350, APP_WIDTH/2, 15, 5, 48, 1, APP_WIDTH*0.5, letterMesh);
	
	//TriggerPattern textPattern2 = patternMaker.getPattern(psm, "#BDF12", 20, 0.2, 300, APP_WIDTH/2, 15, 5, 52, 0.2, APP_WIDTH*0.7, letterMesh);
	
	addTriggerPattern(textPattern);//, true );

	
	TriggerPattern finalPattern;
		
	triggerBanger.restoreSpeed = 2;
	
	finalPattern.addTrigger(triggerBanger);
	finalPattern.addTrigger(triggerFountain);
	finalPattern.addTrigger(starTrigger);
	
	addTriggerPattern(finalPattern);
	
	
	
	//	pattern.addTrigger(triggerFlower);
	//	pattern.addTrigger(triggerFluffy);
	//	pattern.addTrigger(triggerFluffy);
	//	pattern.addTrigger(triggerFlower);
	//	pattern.addTrigger(triggerBanger);
	//
	//	addTriggerPattern(pattern);

	
	
	//-------------------------
	

	
	
}

bool SceneSpace::update(float deltaTime) {
	if(!Scene::update(deltaTime)) return false;
	starfield.update(deltaTime);
	
	
}

bool SceneSpace::draw() {
	
	if(!Scene::draw()) return false;
	starfield.draw();
	
	return true;
	
}

RocketSettings SceneSpace::getPlanetRocket() {
	
	renderer = new ParticleRendererShape();
	ParticleSystemSettings ps;
	// PHYSICS
	ps.speedMin = 20;
	ps.speedMax = 60;
	ps.directionZ = 0;
	ps.directionZVar = 90;
	ps.directionYVar = 180;
	ps.drag = 0.90;
	ps.gravity.set(0,30);
	
	//LIFE
	ps.lifeMin = 0.5;
	ps.lifeMax = 0.8;
	
	//APPEARANCE
	
	ps.sizeStartMin = 4;
	ps.sizeStartMax = 6;
	ps.sizeChangeRatio = 1;
	
	ps.hueStartMin = 0;
	ps.hueStartMax = 30;
	ps.hueChange = 0;
	
	ps.brightnessStartMin = 150;
	ps.brightnessStartMax = 255;
	ps.brightnessEnd = 0;
	
	ps.saturationMin = 150;
	ps.saturationMax = 255;
	ps.saturationEnd = 255;
	
	//ps.shimmerMin = 0.1;
	
	// but also :
	// lifeExpectancy
	// delay
	
	ps.emitMode = PARTICLE_EMIT_CONTINUOUS;
	ps.emitCount = 1000;
	
	ps.emitDelay = 0;
	ps.emitLifeTime= 2;
	
	ps.emitStartSizeModifier = 0;
	ps.emitSpeedModifier = 0;
	ps.emitHueModifierOffset = 0;
	
	//ps.emitAttachedPhysicsObject = &rocket;
	ps.emitInheritVelocity = -0.5;
	
	ps.renderer = renderer;
	//psystem.init(ps);
	
	ps.startSound = "LaunchRocketSharp";
	
	
	// optional colour modifier
	
	ParticleSystemSettings ps2;
	// PHYSICS
	ps2.speedMin = 650;
	ps2.speedMax = 700;
	ps2.directionZ = 0;
	ps2.directionZVar = 90;
	ps2.directionYVar = 180;
	ps2.drag = 0.90;
	ps2.gravity.set(0,30);
	
	//LIFE
	ps2.lifeMin = 0.5;
	ps2.lifeMax = 0.8;
	
	//APPEARANCE
	
	ps2.sizeStartMin = 5;
	ps2.sizeStartMax = 7;
	ps2.sizeChangeRatio = 0;
	
	ps2.hueStartMin = 20;
	ps2.hueStartMax = 25;
	ps2.hueChange = -20;
	
	ps2.brightnessStartMin = 155;
	ps2.brightnessStartMax = 155;
	ps2.brightnessEnd = 100;
	
	ps2.saturationMin = 50;
	ps2.saturationMax = 100;
	ps2.saturationEnd = 500;
	
	//ps.shimmerMin = 0.1;
	
	// but also :
	// lifeExpectancy
	// delay
	
	//ps2.emitMode = PARTICLE_EMIT_BURST;
	ps2.emitCount = 10000;
	
	ps2.emitDelay = 2;
	ps2.emitLifeTime= 0.05;
	
	ps2.renderer = renderer;
	
	// optional colour modifier
	
	ParticleSystemSettings ps3;
	// PHYSICS
	ps3.speedMin = 550;
	ps3.speedMax = 800;
	ps3.directionZ = 0;
	ps3.directionZVar = 0;
	ps3.directionYVar = 180;
	ps3.drag = 0.99;
	ps3.gravity.set(0,30);
	
	//LIFE
	ps3.lifeMin = 0.5;
	ps3.lifeMax = 0.8;
	
	//APPEARANCE
	
	ps3.sizeStartMin = 10;
	ps3.sizeStartMax = 12;
	ps3.sizeChangeRatio = 0;
	
	ps3.hueStartMin = 10;
	ps3.hueStartMax = 15;
	ps3.hueChange = 0;
	
	ps3.brightnessStartMin = 200;
	ps3.brightnessStartMax = 200;
	ps3.brightnessEnd = 100;
	
	ps3.saturationMin = 200;
	ps3.saturationMax = 200;
	ps3.saturationEnd = 250;
	
	//ps.shimmerMin = 0.1;
	
	// but also :
	// lifeExpectancy
	// delay
	
	//ps3.emitMode = PARTICLE_EMIT_BURST;
	ps3.emitCount = 10000;
	
	ps3.emitDelay = 1.95;
	ps3.emitLifeTime= 0.05;
	
	ps3.startSound = "SoftExplosion";
	
	
	//ps3.startSound = "ExplosionSynth1";
	
	ps3.renderer = renderer;
	
	
	RocketSettings rocketSettings;
	
	rocketSettings.startSpeedMin = 600;
	rocketSettings.startSpeedMax = 700;
	rocketSettings.direction = -90;
	rocketSettings.directionVar = 5;
	rocketSettings.gravity.y = 400;
	
	rocketSettings.addParticleSystemSetting(ps);
	rocketSettings.addParticleSystemSetting(ps2);
	rocketSettings.addParticleSystemSetting(ps3);
	
	return rocketSettings;
	
	
	
	
}

RocketSettings SceneSpace::getStarryRocket() {
	
	
	ParticleRendererStar* starRenderer = new ParticleRendererStar(10);
	ParticleSystemSettings ps;
	// PHYSICS
	ps.speedMin = 20;
	ps.speedMax = 60;
	ps.directionZ = 0;
	ps.directionZVar = 90;
	ps.directionYVar = 180;
	ps.drag = 0.90;
	ps.gravity.set(0,30);
	
	//LIFE
	ps.lifeMin = 0.5;
	ps.lifeMax = 0.8;
	
	//APPEARANCE
	
	ps.sizeStartMin = 0.1;
	ps.sizeStartMax = 0.15;
	ps.sizeChangeRatio = 7;
	
	ps.hueStartMin = 100;
	ps.hueStartMax = 120;
	ps.hueChange = 0;
	
	ps.brightnessStartMin = 255;
	ps.brightnessStartMax = 255;
	ps.brightnessEnd = 0;
	
	ps.saturationMin = 150;
	ps.saturationMax = 255;
	ps.saturationEnd = 255;
	
	//ps.shimmerMin = 0.1;
	
	// but also :
	// lifeExpectancy
	// delay
	
	ps.emitMode = PARTICLE_EMIT_CONTINUOUS;
	ps.emitCount = 1000;
	
	ps.emitDelay = 0;
	ps.emitLifeTime= 2;
	
	ps.emitStartSizeModifier = 0;
	ps.emitSpeedModifier = 0;
	ps.emitHueModifierOffset = 0;
	
	//ps.emitAttachedPhysicsObject = &rocket;
	ps.emitInheritVelocity = -0.5;
	
	ps.renderer = starRenderer;
	//psystem.init(ps);
	
	ParticleSystemSettings stars;
	
	stars.renderer = starRenderer;
	
	stars.sizeStartMin = 0.2;
	stars.sizeStartMax = 1;
	stars.sizeChangeRatio = 3;
	
	stars.speedMin = 0;
	stars.speedMax = 40;
	
	stars.lifeMin = 1;
	stars.lifeMin = 1.2;
	
	stars.emitLifeTime =1.6;
	stars.emitDelay = 0;
	stars.emitCount = 500;
	stars.emitStartSizeModifier = 0;
	stars.emitSpeedModifier = 0;
	
	
	stars.brightnessEnd = 0;
	stars.saturationMin = 0;
	stars.saturationMax = 100;
	stars.hueStartMin = 100;
	stars.hueStartMax = 120;
	
	stars.shimmerMin = 0.1;
	stars.startSound = "Woosh";
	
	
	
	RocketSettings rocketSettings;
	
	rocketSettings.startSpeedMin = 1200;
	rocketSettings.startSpeedMax = 1600;
	rocketSettings.direction = -90;
	rocketSettings.directionVar = 15;
	rocketSettings.gravity.y = 800;
	rocketSettings.drag = 0.96;
	rocketSettings.lifeTime = 1.5;
	
	//rocketSettings.addParticleSystemSetting(ps);
	rocketSettings.addParticleSystemSetting(stars);
	
	return rocketSettings;
	
	
	
}




RocketSettings SceneSpace :: getFlowerRocket(float hue , float hueChange ){
	
	RocketSettings rocketSettings;
	
	rocketSettings.startSpeedMin = 1200;
	rocketSettings.startSpeedMax = 1500;
	rocketSettings.directionVar = 4;
	rocketSettings.gravity.y = 300;
	rocketSettings.drag = 0.95;
	
	ParticleSystemSettings trails = getFlowerTrailParticles(hue, hueChange);
	ParticleSystemSettings explosion = getFlowerExplosionParticles(hue, hueChange);
	ParticleSystemSettings explosionLines = getLineExplosionParticles(150, hueChange);
	
	
	
	explosion.emitDelay = explosionLines.emitDelay = trails.emitLifeTime = 2;
	
	rocketSettings.addParticleSystemSetting(trails);
	rocketSettings.addParticleSystemSetting(explosion);
	rocketSettings.addParticleSystemSetting(explosionLines);
	
	return rocketSettings;
	
	
	
};




RocketSettings SceneSpace :: getSphereFlowerRocket(float hue , float hueChange ){
	
	RocketSettings rocketSettings;
	
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
	ParticleSystemSettings crackles = getBangerCrackles();
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
	
	return rocketSettings;
	
	
	
};


ParticleSystemSettings SceneSpace :: getFlowerTrailParticles(float hue, float hueChange ){
	
	
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
ParticleSystemSettings SceneSpace :: getFlowerExplosionParticles(float hue, float hueChange){
	
	
	
	ParticleSystemSettings explosion;
	explosion.renderer = new ParticleRendererBitmap(&softWhiteImage);
	
	//pss.directionZVar = 20;
	explosion.speedMin = 650;
	explosion.speedMax = 700;
	explosion.directionZ = 0;
	explosion.directionZVar = 90;
	explosion.directionYVar = 180;
	explosion.drag = 0.90;
	explosion.gravity.set(0,30);

	
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
	
	explosion.emitMode = PARTICLE_EMIT_BURST;
	explosion.emitLifeTime = 0.1;
	explosion.emitCount = 3000;
	
	explosion.startSound = "SoftExplosion";
	
	
	return explosion;
	
	
}
ParticleSystemSettings SceneSpace :: getLineExplosionParticles(float hue, float hueChange){
	
	
	
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

RocketSettings SceneSpace :: getFountain(float hueStartOffset , float hueChange){
	
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
	
	
	RocketSettings rocketSettings;
	rocketSettings.startSpeedMin = 1000;
	rocketSettings.startSpeedMax = 1500;
	rocketSettings.direction = -90;
	rocketSettings.directionVar = 5;
	rocketSettings.gravity.y = 300;
	rocketSettings.drag = 0.9;
	rocketSettings.lifeTime = 1;
	
	rocketSettings.addParticleSystemSetting(ps);
	rocketSettings.addParticleSystemSetting(ps2);
	
	return rocketSettings;
	
	
	
}

RocketSettings SceneSpace :: getFluffyRocket(){
	
	
	
	RocketSettings rocketSettings;
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
	
	
	rocketSettings.startSpeedMin = 1000;
	rocketSettings.startSpeedMax = 1400;
	rocketSettings.gravity.y = 1200;
	
	
	
	rocketSettings.addParticleSystemSetting(pss);
	//rocketSettings.addParticleSystemSetting(getSmoke());
	
	return rocketSettings;
	
}

RocketSettings SceneSpace:: getBangerRocket() {
	
	RocketSettings rocketSettings;
	
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
	rocketSettings.addParticleSystemSetting(smoke1);
	rocketSettings.addParticleSystemSetting(smoke2);
	rocketSettings.addParticleSystemSetting(bang);
	rocketSettings.addParticleSystemSetting(bangCrackles);
	
	return rocketSettings;
	
}


ParticleSystemSettings SceneSpace :: getBangerTrails() {
	
	ParticleSystemSettings trails;
	trails.renderer = new ParticleRendererLine(1.5, true);
	//pss.directionZVar = 20;
	trails.speedMin = 5;
	trails.speedMax = 6;
	trails.sizeStartMin = trails.sizeStartMax = 3;
	trails.hueStartMin = trails.hueStartMax = 30;
	trails.hueChange = -10;
	trails.saturationMin = trails.saturationMax = 0;
	trails.saturationEnd = 0;
	trails.brightnessStartMin = trails.brightnessStartMin = trails.brightnessEnd = 255;
	
	trails.emitInheritVelocity = -0.01;
	trails.emitCount = 500;
	
	
	trails.shimmerMin = 0;
	trails.lifeMin = 0.1;
	trails.lifeMax = 0.3;
	trails.startSound = "Launch";
	
	return trails;
	
	
}


ParticleSystemSettings SceneSpace:: getBangerBang() {
	
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



ParticleSystemSettings SceneSpace:: getBangerCrackles() {
	
	ParticleSystemSettings explosion;
	explosion.renderer = new ParticleRendererCircle();
	
	
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
	explosion.brightnessStartMin = explosion.brightnessStartMin = 255;
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


ParticleSystemSettings SceneSpace:: getSmoke() {
	
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


