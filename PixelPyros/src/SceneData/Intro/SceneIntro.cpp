//
//  SceneIntro.cpp
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 02/09/2012.
//
//

#include "SceneIntro.h"



SceneIntro :: SceneIntro(string scenename) : Scene(scenename) {
	
	FireworkFactory& fireworkFactory = *FireworkFactory::instance();
	
	softWhiteImage.loadImage("img/ParticleWhite.png");
	bangerFlashImage.loadImage("img/ParticleBangerFlash.png");

	TriggerPattern blank;
	addTriggerPattern(blank);
	
	// SIMPLE ROCKET
	
	TriggerPattern pattern1;
	pattern1.addTriggerSettings(fireworkFactory.getSimpleRocket(500,140,255));
	pattern1.addTriggerSettings(TriggerSettings::blank); 

	addTriggerPattern(pattern1);

	// SIMPLE ROCKET 2 colour
	pattern1.addTriggerSettings(fireworkFactory.getSimpleRocket(600,220,255));
	pattern1.addTriggerSettings(TriggerSettings::blank);
	addTriggerPattern(pattern1);
	
	
	// JUST WHITE ROCKETS
	
	TriggerPattern pattern3;
	// white rocket
	TriggerSettings* whiteRocket = fireworkFactory.getSimpleRocket(700,220,0,0.05,1);
	whiteRocket->rechargeSettings = TriggerRechargeSettings::oneShot;
	pattern3.addTriggerSettings(whiteRocket);
	//pattern3.addTriggerSettings(TriggerSettings::blank);
	addTriggerPattern(pattern3);

	
	// SIMPLE FOUNTAINS
	
	TriggerPattern pattern;
	pattern.addTriggerSettings(fireworkFactory.getFountain(180,0));
	pattern.addTriggerSettings(TriggerSettings::blank);
	addTriggerPattern(pattern);
	
	
	// RAINBOW FOUNTAINS
	TriggerPattern multiColourPattern;
	
	float colours [10] = {0, 30, 60, 90, 120, 150,180,210,240 };
	
	for(int i = 0; i<10; i++) {
		TriggerSettingsRocket* colourFountain = fireworkFactory.getFountain(colours[i],0);
				
		colourFountain->hue = colours[i];
		colourFountain->saturation = 255;
		
		multiColourPattern.addTriggerSettings(colourFountain);
		multiColourPattern.addTriggerSettings();
		
	}
	
	addTriggerPattern(multiColourPattern);
			
	// FOUNTAINS + ROCKETS
	TriggerPattern patternFountain;
	patternFountain.addTriggerSettings(fireworkFactory.getFountain(180,0));
	patternFountain.addTriggerSettings();
	patternFountain.addTriggerSettings(fireworkFactory.getFountain(180,0));
	patternFountain.addTriggerSettings();
	patternFountain.addTriggerSettings(fireworkFactory.getBasicRocket(5));
	patternFountain.addTriggerSettings();
	addTriggerPattern(patternFountain);
	
	
	
	
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


