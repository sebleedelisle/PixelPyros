//
//  SceneVectorizer.cpp
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 01/09/2012.
//
//

#include "SceneVectorizer.h"

SceneVectorizer :: SceneVectorizer  (string scenename) : Scene(scenename), particleSystemManager(*ParticleSystemManager::instance()){
	
	loadMusicFile("LightsKlaypex.aif");
	
	addTriggerPattern();
	
	TriggerSettingsRocketOrb * rocketFountainBlue = getRocketTronFountain(130,10);
	TriggerSettingsRocketOrb * rocketFountainPink = getRocketTronFountain(235,0);
	TriggerSettingsRocketOrb * rocketFountainBlueHigh = getRocketTronFountain(130,10, 2, true);
	TriggerSettingsRocketOrb * rocketFountainPinkHigh = getRocketTronFountain(235,0, 2, true);
		
	rocketFountainPink->addRocketSettings(rocketFountainBlue->getRocketSettings());
	rocketFountainBlue->addRocketSettings(rocketFountainPink->getRocketSettings());
	
	TriggerPattern glitchFountainPattern("glitch fountains small");
	
	glitchFountainPattern.addTriggerSettings(rocketFountainBlue);
	glitchFountainPattern.addTriggerSettings();
	glitchFountainPattern.addTriggerSettings(rocketFountainBlue);
	glitchFountainPattern.addTriggerSettings();
	glitchFountainPattern.addTriggerSettings(rocketFountainPink);
	glitchFountainPattern.addTriggerSettings();
	glitchFountainPattern.addTriggerSettings(rocketFountainPink);
	glitchFountainPattern.addTriggerSettings();

	addTriggerPattern(glitchFountainPattern);
	
	
	TriggerPattern glitchFountainPatternHigh("glitch fountains high");
	
	glitchFountainPatternHigh.addTriggerSettings(rocketFountainBlueHigh);
	glitchFountainPatternHigh.addTriggerSettings();
	glitchFountainPatternHigh.addTriggerSettings(rocketFountainBlue);
	glitchFountainPatternHigh.addTriggerSettings();
	glitchFountainPatternHigh.addTriggerSettings(rocketFountainPinkHigh);
	glitchFountainPatternHigh.addTriggerSettings();
	glitchFountainPatternHigh.addTriggerSettings(rocketFountainPink);
	glitchFountainPatternHigh.addTriggerSettings();
	
	addTriggerPattern(glitchFountainPatternHigh);

	TriggerSettingsRocketOrb* glitchRocketOnce = getGlitchRocket();

	glitchRocketOnce->rechargeSettings = TriggerRechargeSettings::oneShot; 
	TriggerPattern glitchRocketPattern("glitch rocket");
	glitchRocketPattern.addTriggerSettings(glitchRocketOnce);
	glitchRocketPattern.addTriggerSettings();
	glitchRocketPattern.addTriggerSettings();
	glitchRocketPattern.addTriggerSettings();
	glitchRocketPattern.addTriggerSettings();
	glitchRocketPattern.addTriggerSettings();
	glitchRocketPattern.addTriggerSettings();
	glitchRocketPattern.addTriggerSettings();
	glitchRocketPattern.addTriggerSettings();
	glitchRocketPattern.addTriggerSettings();
	
	addTriggerPattern(glitchRocketPattern);
		
	TriggerSettingsRocketOrb* glitchRocket = getGlitchRocket();

	TriggerPattern glitchFountainWithRocket("glitch fountains + rocket"); 
	glitchFountainWithRocket.addTriggerSettings(glitchRocket);
	glitchFountainWithRocket.addTriggerSettings();
	glitchFountainWithRocket.addTriggerSettings(rocketFountainBlue);
	glitchFountainWithRocket.addTriggerSettings();
	glitchFountainWithRocket.addTriggerSettings(rocketFountainBlue);
	glitchFountainWithRocket.addTriggerSettings();
	glitchFountainWithRocket.addTriggerSettings(rocketFountainPink);
	glitchFountainWithRocket.addTriggerSettings();
	glitchFountainWithRocket.addTriggerSettings(rocketFountainPink);
	glitchFountainWithRocket.addTriggerSettings();
	
	addTriggerPattern(glitchFountainWithRocket);
	
	TriggerPattern rocketsAndFountainsPattern;
	
	RocketTron* rocketTron = new RocketTron();
	rocketTron->addParticleSystems();
	
	
	rocketsAndFountainsPattern.addTriggerSettings(rocketTron);
	rocketsAndFountainsPattern.addTriggerSettings();
	rocketsAndFountainsPattern.addTriggerSettings(rocketFountainBlue);
	rocketsAndFountainsPattern.addTriggerSettings();
	rocketsAndFountainsPattern.addTriggerSettings(rocketFountainPink);
	rocketsAndFountainsPattern.addTriggerSettings();
	
	addTriggerPattern(rocketsAndFountainsPattern);
	
	// Arrangement with only glitch fountains, closer spaced
	 
	TriggerPattern rotatingHighFountains;
	//TriggerRotator crazyTrigger(particleSystemManager,20,1,false);
	//crazyTrigger.triggerPower = 1;
	//crazyTrigger.restoreSpeed = 1;
	//crazyTrigger.addRocketSettings(rocketFountainBlueHigh);
	//crazyTrigger.addRocketSettings(rocketFountainPinkHigh);
	//crazyPattern.addTrigger(crazyTrigger,0,0,0.3);
	//pattern.addTrigger(trigger2);
	
	TriggerSettingsRocketOrb* rotatingFountainBlueHigh = new TriggerSettingsRocketOrb(*rocketFountainBlueHigh);
	TriggerSettingsRocketOrb* rotatingFountainPinkHigh = new TriggerSettingsRocketOrb(*rocketFountainPinkHigh);
	
	rotatingFountainBlueHigh->rechargeSettings = TriggerRechargeSettings::superFastMultiples;
	rotatingFountainPinkHigh->rechargeSettings = TriggerRechargeSettings::superFastMultiples;
	rotatingFountainPinkHigh->rotateOnFire = false;
	rotatingFountainBlueHigh->rotateOnFire = false;
	
	rotatingFountainPinkHigh->rotationSpeed = 1;
	rotatingFountainBlueHigh->rotationSpeed = 1;
	
	rotatingHighFountains.addTriggerSettings(rotatingFountainBlueHigh);
	rotatingHighFountains.addTriggerSettings(rotatingFountainPinkHigh);
	
	
	addTriggerPattern(rotatingHighFountains);
	
	
	/*	
	
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

	*/
	
	
	
	TriggerSettingsRocketOrb* circleFountain = getCircleFountain(235);
	
	TriggerPattern bigPattern;
	
	bigPattern.addTriggerSettings(circleFountain);
	bigPattern.addTriggerSettings();
	bigPattern.addTriggerSettings(rocketTron);
	bigPattern.addTriggerSettings();
	bigPattern.addTriggerSettings(rocketFountainPink);
	bigPattern.addTriggerSettings();
	bigPattern.addTriggerSettings(rocketTron);
	bigPattern.addTriggerSettings();
	
	addTriggerPattern(bigPattern);

	
	
	
/*
	TriggerPattern endPattern;
	
	
//	endPattern.addTrigger(circleFountainTrigger);
	bigPattern.addTrigger(rocketTronTrigger);
	endPattern.addTrigger(fountainTriggerPink);
//	endPattern.addTrigger(circleFountainTrigger);
	endPattern.addTrigger(glitchRocketTriggerMore);
	
	addTriggerPattern(endPattern);	*/
	
	stretchyNet.init(ofRectangle(0,0,APP_WIDTH, APP_HEIGHT), 15, 15);
	
}

TriggerSettingsRocketOrb* SceneVectorizer :: getGlitchRocket(){
	
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
	
	RocketSettings& rs = *glitchRocket.getRocketSettings();
	rs.startSpeedMin = 700;
	
	rs.startSpeedMax = 800;
	rs.directionVar = 6;
	
	rs.addParticleSystemSetting(glitchRocket.head);
	rs.addParticleSystemSetting(glitchRocket.explosion);
	rs.timeSpeed = 	glitchRocket.head.timeSpeed = glitchRocket.explosion.timeSpeed= 0.7;
	
	rs.setLifeTime(2.4);
	
	return &glitchRocket;
	
}


TriggerSettingsRocketOrb* SceneVectorizer :: getCircleFountain(float hue) {

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
	
	head.hueStartMin = head.hueStartMax = hue;
	
	head.brightnessEnd = 0;
	head.emitMode = PARTICLE_EMIT_CONTINUOUS;
	head.emitCount = 500;
	head.emitDelay = 0;
	head.emitLifeTime= 1.5;
	head.emitStartSizeModifier = 0.1;
	
	head.startSound = "LaunchSweep";
	
	RocketSettings& rocket = *new RocketSettings();

	rocket.addParticleSystemSetting(head);
	rocket.startSpeedMin = 1000;
	rocket.startSpeedMax = 1200;
	rocket.gravity.y = 1500;
	
	TriggerSettingsRocketOrb* ts = new TriggerSettingsRocketOrb();
	ts->addRocketSettings(&rocket);

	ts->radius = 8;
	
	ts->rechargeSettings = TriggerRechargeSettings::fast;

	ts->hue = hue;
	ts->saturation = 200;
	
	return ts;

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



TriggerSettingsRocketOrb* SceneVectorizer :: getRocketTronFountain(float hueStartOffset, float hueChange, float speedMultiplier, bool useLaser) {
	
	
	ParticleRendererBase* particleLineRenderer;
		
	particleLineRenderer = new ParticleRendererGlitchLine(1.2);
	
	
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
	if(useLaser) ps.emitCount = 20;
	else ps.emitCount = 40;
	ps.emitDelay = 0;
	ps.emitLifeTime= 1.4;
	
	ps.emitStartSizeModifier = 0;
	ps.emitSpeedModifier = 10;
	ps.emitHueModifierOffset = 0;
	ps.emitInheritVelocity = 0;
	
	ps.startSound = "DirtyTechno";
	ps.renderer = particleLineRenderer;
	
	
	RocketSettings* rs = new RocketSettings();
	
	rs->startSpeedMin = 800 * speedMultiplier;
	rs->startSpeedMax = 950 * speedMultiplier;
	rs->direction = -90;
	rs->directionVar = 0;
	rs->gravity.y = 0;
	rs->setLifeTime(1.4);
	rs->drag = 0.9;
	//ps.timeSpeed = rs->timeSpeed = 0.8;
	
	RocketSettings* rs2 = NULL; 
	if(useLaser) {
		rs2 = new RocketSettings(*rs);
		
		ParticleRendererBase* particleLineRendererLaser = new ParticleRendererGlitchLineLaser();
		ParticleSystemSettings ps2(ps);
		ps2.renderer = particleLineRendererLaser;
		rs2->addParticleSystemSetting(ps2);
	}
	
	rs->addParticleSystemSetting(ps);
	
	TriggerSettingsRocketOrb* ts = new TriggerSettingsRocketOrb();
	ts->addRocketSettings(rs);
	if(rs2!=NULL) {
		ts->addRocketSettings(rs2);
		vector<float>probs;
		probs.push_back(9);
		probs.push_back(1);
		
		ts->setProbabilities(probs);
	}
	
	ts->rotateOnFire = true;
	ts->rotationExtent = 20;
	ts->rotationSpeed = 4;
	ts->radius = 6;
	ts->rechargeSettings = TriggerRechargeSettings::superFastMultiples;
	ts->hue = hueStartOffset;
	ts->saturation = 200; 
	return ts;
	
};

