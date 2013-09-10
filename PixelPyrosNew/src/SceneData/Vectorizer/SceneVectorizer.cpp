//
//  SceneVectorizer.cpp
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 01/09/2012.
//
//

#include "SceneVectorizer.h"

SceneVectorizer :: SceneVectorizer  (string scenename) : Scene(scenename){
	
	TriggerPattern empty;
	addTriggerPattern(empty);
	
	
	TriggerSettingsRocketRotator * rocketFountainBlue = getRocketTronFountain(130,10);
	TriggerSettingsRocketRotator * rocketFountainPink = getRocketTronFountain(-20,0);
	TriggerSettingsRocketRotator * rocketFountainBlueHigh = getRocketTronFountain(130,10);
	TriggerSettingsRocketRotator * rocketFountainPinkHigh = getRocketTronFountain(-20,0);

	
	rocketFountainBlue->hue = rocketFountainBlueHigh->hue = 130;
	rocketFountainPink->hue = rocketFountainPinkHigh->hue = 235;
	rocketFountainBlueHigh->rocketSettings->startSpeedMin *=2.8;
	rocketFountainBlueHigh->rocketSettings->startSpeedMax *=2.8;
	rocketFountainPinkHigh->rocketSettings->startSpeedMin *=2.8;
	rocketFountainPinkHigh->rocketSettings->startSpeedMax *=2.8;
	
	TriggerPattern glitchFountainPattern;
	
	glitchFountainPattern.addTriggerSettings(rocketFountainBlue);
	glitchFountainPattern.addTriggerSettings(rocketFountainBlue);
	glitchFountainPattern.addTriggerSettings(rocketFountainPink);
	glitchFountainPattern.addTriggerSettings(rocketFountainPink);
	
	
	addTriggerPattern(glitchFountainPattern);



	
	
	
	RocketTron& glitchRocket = *new RocketTron();
	glitchRocket.head.renderer = new ParticleRendererGlitchLine(1);
	glitchRocket.head.speedMin = 20;
	glitchRocket.head.speedMax = 60;
	glitchRocket.head.brightnessStartMax = 255;
	glitchRocket.head.brightnessStartMin = 255;
	glitchRocket.head.brightnessEnd = 255;
	
	glitchRocket.head.lifeMin= 0.1;
	glitchRocket.head.lifeMax= 0.15;
	glitchRocket.head.emitInheritVelocity  =0.0;
	glitchRocket.head.emitLifeTime= 3.0;
	
	glitchRocket.explosion.renderer = new ParticleRendererGlitchLine(1.1);
	glitchRocket.explosion.sizeStartMin = glitchRocket.explosion.sizeStartMax =2;
	
	glitchRocket.explosion.brightnessEnd = 0;
	glitchRocket.explosion.speedMin = 100;
	glitchRocket.explosion.speedMax = 1000;
	glitchRocket.explosion.directionZVar = 0;
	glitchRocket.explosion.lifeMin= 0.1;
	glitchRocket.explosion.lifeMax= 0.4;
	glitchRocket.explosion.hueStartMin = 130;
	glitchRocket.explosion.hueStartMax = 130;
	
	
	glitchRocket.explosion.emitCount = 5000;
	glitchRocket.explosion.emitLifeTime = 0.1;
	glitchRocket.explosion.emitDelay = 3.1;
	
	glitchRocket.explosion.drag = 0.99;
	
	glitchRocket.startSpeedMin = 700;
	
	glitchRocket.startSpeedMax = 800;
	glitchRocket.directionVar = 6;
	
	glitchRocket.addParticleSystemSetting(glitchRocket.head);
	glitchRocket.addParticleSystemSetting(glitchRocket.explosion);
	glitchRocket.timeSpeed = 	glitchRocket.head.timeSpeed = glitchRocket.explosion.timeSpeed= 0.7;
	
	glitchRocket.lifeTime = 2.4;
	
	TriggerSettingsRocket* glitchRocketTrigger = new TriggerSettingsRocket();
	glitchRocketTrigger->rocketSettings = &glitchRocket;
	
	glitchFountainPattern.addTriggerSettings();
	glitchFountainPattern.addTriggerSettings(glitchRocketTrigger);
	glitchFountainPattern.addTriggerSettings();
	
	addTriggerPattern(glitchFountainPattern);
	

	
	
	TriggerPattern glitchFountainPatternHigh;
	
	glitchFountainPatternHigh.addTriggerSettings(rocketFountainBlueHigh);
	glitchFountainPatternHigh.addTriggerSettings(rocketFountainBlue);
	glitchFountainPatternHigh.addTriggerSettings(rocketFountainPinkHigh);
	glitchFountainPatternHigh.addTriggerSettings(rocketFountainPink);
	
	addTriggerPattern(glitchFountainPatternHigh);
	
	
/*
	
	TriggerPattern rocketsAndFountainsPattern;
	
	RocketTron rocketTron;
	rocketTron.addParticleSystems();
	TriggerRocket rocketTronTrigger(particleSystemManager);
	rocketTronTrigger.addRocketSettings(rocketTron);
	// makes one shot type
	//rocketTronTrigger.type = TRIGGER_TYPE_FIRE_ON_MOTION;
	rocketTronTrigger.triggerLevel = 1;
	rocketTronTrigger.restoreSpeed = 2;
	rocketTronTrigger.triggerPower = 0.99;
	
	
	rocketsAndFountainsPattern.addTrigger(rocketTronTrigger);
	rocketsAndFountainsPattern.addTrigger(fountainTriggerBlue);

	
	addTriggerPattern(rocketsAndFountainsPattern);
	
	
	
	// Arrangement with only glitch fountains, closer spaced
	
	TriggerPattern crazyPattern;
	TriggerRotator crazyTrigger(particleSystemManager,20,1,false);
	crazyTrigger.triggerPower = 1;
	crazyTrigger.restoreSpeed = 1;
	crazyTrigger.addRocketSettings(rocketFountainBlueHigh);
	crazyTrigger.addRocketSettings(rocketFountainPinkHigh);
	crazyPattern.addTrigger(crazyTrigger,0,0,0.3);
	//pattern.addTrigger(trigger2);
	
	addTriggerPattern(crazyPattern);
	
	
	
	
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
	
	addTriggerPattern(bigPattern);
	
	
	TriggerPattern endPattern;
	
	
//	endPattern.addTrigger(circleFountainTrigger);
	bigPattern.addTrigger(rocketTronTrigger);
	endPattern.addTrigger(fountainTriggerPink);
//	endPattern.addTrigger(circleFountainTrigger);
	endPattern.addTrigger(glitchRocketTriggerMore);
	
	addTriggerPattern(endPattern);

	*/
	
	
	stretchyNet.init(ofRectangle(0,0,APP_WIDTH, APP_HEIGHT), 15, 15);
	
	
	
}

RocketSettings SceneVectorizer :: getCircleFountain(float hue) {

	/*
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
	 
	 */
	
	
}




bool SceneVectorizer :: update(float deltaTime) {
	if(!Scene::update(deltaTime)) return false;
	
	stretchyNet.update(deltaTime, particleSystemManager);
	
	
}

bool SceneVectorizer :: draw() {
	if(!Scene::draw()) return false;
	
	ofPushStyle();
	//ofEnableSmoothing();
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	stretchyNet.draw();
	ofPopStyle();
	
}



TriggerSettingsRocketRotator* SceneVectorizer :: getRocketTronFountain(float hueStartOffset, float hueChange) {
	
	
	ParticleRendererBase* particleRenderer = new ParticleRendererSquare();
	ParticleRendererBase* particleLineRenderer = new ParticleRendererGlitchLine(1.5);
	
	
	ParticleSystemSettings ps, ps2;

	
	//particleLineRenderer->lineWidth = 2;
	//whiteImage.loadImage("img/ParticleWhite.png");
	
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
	ps.speedMax = 30;
	ps.directionZ = -90;
	ps.directionZVar = 90;
	//ps.directionZVar = 0;
	ps.directionYVar = 0;
	
	ps.drag = 0.90;
	ps.gravity.set(0,0);
	
	//LIFE
	ps.lifeMin = 0.5;
	ps.lifeMax = 0.7;
	
	//APPEARANCE
	
	ps.sizeStartMin = 4;
	ps.sizeStartMax = 6;
	ps.sizeChangeRatio = 1;
	
	ps.hueStartMin = -5+hueStartOffset;
	ps.hueStartMax = 0+hueStartOffset;
	ps.hueChange = hueChange;
	
	ps.brightnessStartMin = 230;
	ps.brightnessStartMax = 255;
	ps.brightnessEnd = 0;
	
	ps.saturationMin = 150;
	ps.saturationMax = 255;
	ps.saturationEnd = 255;
	
	ps.emitMode = PARTICLE_EMIT_CONTINUOUS;
	ps.emitCount = 30;
	
	ps.emitDelay = 0;
	ps.emitLifeTime= 1.4;
	
	ps.emitStartSizeModifier = 0;
	ps.emitSpeedModifier = 10;
	ps.emitHueModifierOffset = 0;
	ps.emitInheritVelocity = 0;
	
	ps.startSound = "DirtyTechno";
	ps.renderer = particleLineRenderer;
	
	
	RocketSettings* rs = new RocketSettings();
	
	rs->startSpeedMin = 800;
	rs->startSpeedMax = 950;
	rs->direction = -90;
	rs->directionVar = 10;
	rs->gravity.y = 0;
	rs->lifeTime =1.4;
	rs->drag = 0.9;
	
	rs->addParticleSystemSetting(ps);
	
	TriggerSettingsRocketRotator* ts = new TriggerSettingsRocketRotator();
	ts->rocketSettings = rs;
	ts->radius = 6;
	return ts;
	
	
};

