//
//  SceneTron.cpp
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 01/09/2012.
//
//

#include "SceneTron.h"

SceneTron :: SceneTron  (string scenename, ParticleSystemManager& psm, ofRectangle triggerarea) : Scene(scenename, psm, triggerarea){
	
	TriggerPattern empty;
	addArrangement(empty);
	
	
	RocketTronFountain rocketFountainBlue(130,10);
	rocketFountainBlue.startSpeedMin = 500;
	rocketFountainBlue.startSpeedMax = 800;
	RocketTronFountain rocketFountainPink(-20,0);
	rocketFountainPink.startSpeedMin = 500;
	rocketFountainPink.startSpeedMax = 800;
	
	TriggerRotator fountainTriggerBlue(particleSystemManager,20,1,true);
	fountainTriggerBlue.restoreSpeed = 2;
	fountainTriggerBlue.saturation = 200;
	
	TriggerRotator fountainTriggerPink(fountainTriggerBlue);
	fountainTriggerBlue.hue = 130;
	fountainTriggerPink.hue = 255-20;
	
	TriggerRotator fountainTriggerBlueHigh(fountainTriggerBlue);
	TriggerRotator fountainTriggerPinkHigh(fountainTriggerPink);
	fountainTriggerBlueHigh.radius =
	fountainTriggerPinkHigh.radius = 10;
	fountainTriggerBlueHigh.rotationExtent =
	fountainTriggerPinkHigh.rotationExtent = 5;
	
	
	
	fountainTriggerBlue.addRocketSettings(rocketFountainBlue);
	fountainTriggerPink.addRocketSettings(rocketFountainPink);

	RocketSettings rocketFountainBlueHigh(rocketFountainBlue);
	RocketSettings rocketFountainPinkHigh(rocketFountainPink);
	
	
	rocketFountainBlueHigh.startSpeedMin *=2.8;
	rocketFountainBlueHigh.startSpeedMax *=2.8;
	rocketFountainPinkHigh.startSpeedMin *=2.8;
	rocketFountainPinkHigh.startSpeedMax *=2.8;
	
	fountainTriggerBlueHigh.addRocketSettings(rocketFountainBlueHigh);
	fountainTriggerPinkHigh.addRocketSettings(rocketFountainPinkHigh);

	
	TriggerRocket glitchRocketTrigger(particleSystemManager);
	//glitchRocketTrigger.triggerLevel = 1;
	glitchRocketTrigger.restoreSpeed = 2;
	glitchRocketTrigger.triggerPower = 0.99;
	glitchRocketTrigger.radius = 8;
	glitchRocketTrigger.hue = 130;
	glitchRocketTrigger.saturation = 160;
	
	
	TriggerPattern glitchFountainPattern;
	
	glitchFountainPattern.addTrigger(fountainTriggerBlue);
	glitchFountainPattern.addTrigger(fountainTriggerBlue);
	glitchFountainPattern.addTrigger(fountainTriggerPink);
	glitchFountainPattern.addTrigger(fountainTriggerPink);
	
	
	addArrangement(glitchFountainPattern);



	
	
	
	RocketTron glitchRocket;
	glitchRocket.head.renderer = new ParticleRendererGlitchLine(2);
	glitchRocket.head.speedMin = 30;
	glitchRocket.head.speedMax = 100;
	glitchRocket.head.brightnessStartMax = 255;
	glitchRocket.head.brightnessStartMin = 255;
	glitchRocket.head.brightnessEnd = 255;
	
	glitchRocket.head.lifeMin= 0.1;
	glitchRocket.head.lifeMax= 0.15;
	glitchRocket.head.emitInheritVelocity  =0.0;
	
	glitchRocket.explosion.renderer = new ParticleRendererGlitchLine(1.1);
	glitchRocket.explosion.sizeStartMin = glitchRocket.explosion.sizeStartMax =2;
	
	glitchRocket.explosion.brightnessEnd = 0;
	glitchRocket.explosion.speedMin = 200;
	glitchRocket.explosion.speedMax = 2000;
	glitchRocket.explosion.directionZVar = 0;
	glitchRocket.explosion.lifeMin= 0.1;
	glitchRocket.explosion.lifeMax= 0.4;
	glitchRocket.explosion.hueStartMin = 130;
	glitchRocket.explosion.hueStartMax = 130;
	
	
	glitchRocket.explosion.emitCount = 5000;
	glitchRocket.explosion.emitLifeTime = 0.1;
	glitchRocket.explosion.emitDelay = 2.1;
	
	glitchRocket.explosion.drag = 0.99;
	
	glitchRocket.startSpeedMin = 700;
	glitchRocket.directionVar = 6;
	
	glitchRocket.addParticleSystemSetting(glitchRocket.head);
	glitchRocket.addParticleSystemSetting(glitchRocket.explosion);
	
	
	glitchRocketTrigger.addRocketSettings(glitchRocket);
	
		
	glitchFountainPattern.addTrigger(glitchRocketTrigger);
	
	addArrangement(glitchFountainPattern);
	
	
	
	
	TriggerPattern glitchFountainPatternHigh;
	
	glitchFountainPatternHigh.addTrigger(fountainTriggerBlueHigh);
	glitchFountainPatternHigh.addTrigger(fountainTriggerBlue);
	glitchFountainPatternHigh.addTrigger(fountainTriggerPinkHigh);
	glitchFountainPatternHigh.addTrigger(fountainTriggerPink);
	
	addArrangement(glitchFountainPatternHigh);
	
	
	
	
	TriggerPattern rocketsAndFountainsPattern;
	
	RocketTron rocketTron;
	rocketTron.addParticleSystems();
	TriggerRocket rocketTronTrigger(particleSystemManager);
	rocketTronTrigger.addRocketSettings(rocketTron);
	// makes one shot type
	rocketTronTrigger.type = TRIGGER_TYPE_FIRE_ON_MOTION;
	rocketTronTrigger.triggerLevel = 1;
	rocketTronTrigger.restoreSpeed = 2;
	rocketTronTrigger.triggerPower = 0.99;
	
	
	rocketsAndFountainsPattern.addTrigger(rocketTronTrigger);
	rocketsAndFountainsPattern.addTrigger(fountainTriggerBlue);

	
	addArrangement(rocketsAndFountainsPattern);
	
	
	
	// Arrangement with only glitch fountains, closer spaced
	
	TriggerPattern crazyPattern;
	TriggerRotator crazyTrigger(particleSystemManager,20,1,false);
	crazyTrigger.triggerPower = 1;
	crazyTrigger.restoreSpeed = 1;
	crazyTrigger.addRocketSettings(rocketFountainBlueHigh);
	crazyTrigger.addRocketSettings(rocketFountainPinkHigh);
	crazyPattern.addTrigger(crazyTrigger,0,0,0.3);
	//pattern.addTrigger(trigger2);
	
	addArrangement(crazyPattern);
	
	
	
	
	RocketTron glitchRocketMore;
	glitchRocketMore.head.renderer = new ParticleRendererGlitchLine(1, false, false);
	glitchRocketMore.head.speedMin = 30;
	glitchRocketMore.head.speedMax = 100;
	glitchRocketMore.head.brightnessStartMax = 255;
	glitchRocketMore.head.brightnessStartMin = 255;
	glitchRocketMore.head.brightnessEnd = 255;
	
	glitchRocketMore.head.lifeMin= 0.1;
	glitchRocketMore.head.lifeMax= 0.15;
	glitchRocketMore.head.emitInheritVelocity  =0.0;
	
	glitchRocketMore.explosion.renderer = new ParticleRendererGlitchLine(0.5, false, true);
	glitchRocketMore.explosion.sizeStartMin = glitchRocket.explosion.sizeStartMax =2;
	
	
	glitchRocketMore.explosion.brightnessStartMax = 100;
	glitchRocketMore.explosion.brightnessStartMax = 200;
	glitchRocketMore.explosion.brightnessEnd = 10;
	glitchRocketMore.explosion.speedMin = 400;
	glitchRocketMore.explosion.speedMax = 700;
	glitchRocketMore.explosion.directionZVar = 90;
	glitchRocketMore.explosion.lifeMin= 0.1;
	glitchRocketMore.explosion.lifeMax= 0.4;
	glitchRocketMore.explosion.hueStartMin = 130;
	glitchRocketMore.explosion.hueStartMax = 130;
	
	
	glitchRocketMore.explosion.emitCount = 10000;
	glitchRocketMore.explosion.emitLifeTime = 0.1;
	glitchRocketMore.explosion.emitDelay = 2.1;
	
	glitchRocketMore.explosion.drag = 0.91;
	
	glitchRocketMore.startSpeedMin = 700;
	glitchRocketMore.directionVar = 6;
	
	glitchRocketMore.addParticleSystemSetting(glitchRocketMore.head);
	glitchRocketMore.addParticleSystemSetting(glitchRocketMore.explosion);
	
	TriggerRocket glitchRocketTriggerMore(particleSystemManager);
	//glitchRocketTrigger.triggerLevel = 1;
	glitchRocketTriggerMore.restoreSpeed = 2;
	glitchRocketTriggerMore.triggerPower = 0.99;
	glitchRocketTriggerMore.radius = 8;
	glitchRocketTriggerMore.hue = 130;
	glitchRocketTriggerMore.saturation = 160;

	glitchRocketTriggerMore.addRocketSettings(glitchRocketMore);

	
	
	
	
	RocketSettings circleFountain = getCircleFountain();
	TriggerRocket circleFountainTrigger(particleSystemManager) ;
	
	circleFountainTrigger.addRocketSettings(circleFountain);
	
	TriggerPattern bigPattern;
	
	
	bigPattern.addTrigger(circleFountainTrigger);
	bigPattern.addTrigger(rocketTronTrigger);
	bigPattern.addTrigger(fountainTriggerPink);
	bigPattern.addTrigger(rocketTronTrigger);
	
	addArrangement(bigPattern);
	
	
	TriggerPattern endPattern;
	
	
//	endPattern.addTrigger(circleFountainTrigger);
	bigPattern.addTrigger(rocketTronTrigger);
	endPattern.addTrigger(fountainTriggerPink);
//	endPattern.addTrigger(circleFountainTrigger);
	endPattern.addTrigger(glitchRocketTriggerMore);
	
	addArrangement(endPattern);

	
	
	
	stretchyNet.init(ofRectangle(0,0,APP_WIDTH, APP_HEIGHT));
	
	
	
}

RocketSettings SceneTron :: getCircleFountain(float hue) {

	
	ParticleSystemSettings head;
	
	head.renderer = new ParticleRendererCircle(12, false, 1, ofVec3f(100,0,0));
	
	head.speedMin = head.speedMax =0;
	head.lifeMin = 0.5;
	head.lifeMax = 0.8;
	head.sizeStartMin = 0;
	head.sizeStartMax = 1.2;
	head.sizeChangeRatio = 10;
	head.brightnessStartMin = 255;
	head.brightnessStartMax = 255;
	head.shimmerMin = 0.8;
	
	head.saturationMin = 150;
	head.saturationMax = 200;
	head.saturationEnd = 255;
	
	head.hueStartMin = head.hueStartMax = 120;
	
	head.brightnessEnd = 0;
	head.emitMode = PARTICLE_EMIT_CONTINUOUS;
	head.emitCount = 500;
	head.emitDelay = 0;
	head.emitLifeTime= 1.5;
	head.emitStartSizeModifier = 0.1;
	
	head.startSound = "LaunchSweep";
	
	RocketSettings rocket; 

	
	rocket.addParticleSystemSetting(head);
	rocket.startSpeedMin = 1000;
	rocket.startSpeedMax = 1200;
	rocket.gravity.y = 1500;
	
	return rocket; 
	
	
}




bool SceneTron :: update(float deltaTime) {
	if(!Scene::update(deltaTime)) return false;
	
	stretchyNet.update(deltaTime, particleSystemManager);
	
	
}

bool SceneTron :: draw() {
	if(!Scene::draw()) return false;
	
	ofPushStyle();
	//ofEnableSmoothing();
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	stretchyNet.draw();
	ofPopStyle();
	
}
