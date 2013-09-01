//
//  SceneIntro.cpp
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 02/09/2012.
//
//

#include "SceneIntro.h"



SceneIntro :: SceneIntro(string scenename, ParticleSystemManager& psm) : Scene(scenename, psm) {
		
	softWhiteImage.loadImage("img/ParticleWhite.png");
	bangerFlashImage.loadImage("img/ParticleBangerFlash.png");
	
	//music.loadSound("music/02 In Motion.aif");

	TriggerPattern blank;
	addTriggerPattern(blank);
	
	TriggerSettings ts;
	
	// TODO - THIS IS BAD - should store these pointers somewhere and clear
	// them later.
	
	ts.setRenderer(new TriggerRendererBase());
	TriggerableRocket* tr = new TriggerableRocket(particleSystemManager);
	tr->rocketSettings = getFountain(180,0);
	
	ts.setTriggerable(tr);
	
	TriggerPattern pattern;
	
	pattern.addTriggerSettings(ts);
	addTriggerPattern(pattern);
	
	TriggerPattern multiColourFountains;
	
	float colours [10] = {0, 30, 60, 90, 120, 150,180,210,240 };
	
	for(int i = 0; i<10; i++) {
		TriggerSettings triggerColour;
		
		TriggerableRocket* tr = new TriggerableRocket(particleSystemManager);
		tr->rocketSettings = getFountain(colours[i],0);
		
		/*
		RocketSettings fountain = getFountain(colours[i]);
		fountain.startSpeedMax *=2;
		 
		 */
		
		//triggerColour.addRocketSettings(fountain);
		//triggerRocketFountain.restoreSpeed= 4;
		
		// TODO - THIS IS BAD - should store these pointers somewhere and clear
		// them later.
		triggerColour.setRenderer(new TriggerRendererBase());
		triggerColour.setTriggerable(tr);
		
		triggerColour.hue = colours[i];
		triggerColour.saturation = 255;
		
		multiColourFountains.addTriggerSettings(triggerColour);
	}
	addTriggerPattern(multiColourFountains);

	
	
	
	/*
	
	TriggerRocket triggerFountain(psm);
	triggerFountain.addRocketSettings(getFountain(180));
	triggerFountain.restoreSpeed = 4;
	
		
	TriggerPattern patternFountain;
	patternFountain.addTrigger(triggerFountain);
	
	addTriggerPattern(patternFountain);
	
	
	
	TriggerRocket triggerFlower(psm);
	triggerFlower.addRocketSettings(getBasicRocket(5));
	triggerFlower.radius = 8;
	
	TriggerPattern multiColourFountains;
	
	float colours [10] = {0, 30, 60, 90, 120, 150,180,210,240 };
	
	for(int i = 0; i<10; i++) {
		TriggerRocket triggerRocketFountain(psm);
		
		RocketSettings fountain = getFountain(colours[i]);
		fountain.startSpeedMax *=2;
		triggerRocketFountain.addRocketSettings(fountain);
		triggerRocketFountain.restoreSpeed= 4;
		
		triggerRocketFountain.hue = colours[i];
		triggerRocketFountain.saturation = 255;
		
		multiColourFountains.addTrigger(triggerRocketFountain, 0,0,1);
	}
	addTriggerPattern(multiColourFountains);
	
	// fountains with added flowers
	patternFountain.addTrigger(triggerFountain);
	patternFountain.addTrigger(triggerFlower);
	addTriggerPattern(patternFountain);
	
	*/
	
	
	texts.push_back("Welcome to PixelPyros");
	texts.push_back("The fireworks display that you control");
	texts.push_back("Move your hand across the orbs of light to trigger fireworks");
	texts.push_back("Larger orbs make bigger fireworks");
	texts.push_back("If the orbs stop spinning, wait a while for them to recharge");
	texts.push_back("");
	
	textWriter.colour = ofColor(240,255,255);
	textWriter.colourFlickerMin = 0.6;
	showText = true;
	currentText = 0;
	timePerText = 10;
	
	
	
}

bool SceneIntro:: update(float deltaTime){
	
	if(!Scene::update(deltaTime)) return false;
	
	elapsedTime+=deltaTime; 
	
	
}

void SceneIntro :: start() {
	
	Scene::start();
	
	
	elapsedTime = 0;
	//music.play();
	
}

bool SceneIntro:: draw() {
	
	if(!Scene::draw()) return false;

	if(showText) {
		currentText = floor(elapsedTime/timePerText);
		if(currentText>=texts.size()) {
			elapsedTime = 0;
			currentText = 0;
		
		}
		float brightness = 1;
		float fadeTime = 0.5; 
		
		if(fmod(elapsedTime,timePerText) < fadeTime) {
			brightness = ofMap (fmod(elapsedTime, timePerText), 0,fadeTime,0,1);
		} else if(fmod(elapsedTime, timePerText) > timePerText-fadeTime) {
			brightness = ofMap (fmod(elapsedTime, timePerText), timePerText-fadeTime,timePerText,1,0);
		}
		textWriter.colour = ofColor(240,255,255);		
		textWriter.colour.setBrightness(brightness*255);
		
		textWriter.draw(ofRectangle(APP_WIDTH*0.2, APP_HEIGHT*0.2, APP_WIDTH*0.6,APP_HEIGHT*0.2), texts[currentText], true);
		
		//cout << currentText << brightness << endl;
	}
	
}


RocketSettings SceneIntro :: getBasicRocket(float hue , float hueChange ){
	
	RocketSettings rocketSettings;
	
	rocketSettings.startSpeedMin = 600;
	rocketSettings.startSpeedMax = 800;
	rocketSettings.direction = -90;
	rocketSettings.directionVar = 4;
	rocketSettings.gravity.y = 400;
	//rocketSettings.drag = 0.95;
	
	ParticleSystemSettings trails = getFlowerTrailParticles(hue, hueChange);
	ParticleSystemSettings explosion = getFlowerExplosionParticles(hue, hueChange);
	//ParticleSystemSettings explosionLines = getLineExplosionParticles(150, hueChange);
	
	
	
	explosion.emitDelay = trails.emitLifeTime = 2;
	
	rocketSettings.addParticleSystemSetting(trails);
	rocketSettings.addParticleSystemSetting(explosion);
	//rocketSettings.addParticleSystemSetting(explosionLines);
	
	return rocketSettings;
	
	
	
};


ParticleSystemSettings SceneIntro :: getFlowerTrailParticles(float hue, float hueChange ){
	
	
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
ParticleSystemSettings SceneIntro :: getFlowerExplosionParticles(float hue, float hueChange){
	
	
	
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
ParticleSystemSettings SceneIntro :: getLineExplosionParticles(float hue, float hueChange){
	
	
	
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

RocketSettings SceneIntro :: getFountain(float hueStartOffset , float hueChange){
	
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

ParticleSystemSettings SceneIntro:: getSmoke() {
	
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


