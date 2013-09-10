

#include "SceneRetro.h"


SceneRetro :: SceneRetro(string scenename ) : Scene(scenename) {

	pixelSize = 3;
	
	/*
	TriggerRocket fastTriggerTemplate(psm);
	fastTriggerTemplate.restoreSpeed = 4;
	fastTriggerTemplate.minTriggerInterval = 0.1;
	fastTriggerTemplate.hue = 240;
	fastTriggerTemplate.saturation = 200;
	
	TriggerRocket mediumTriggerTemplate(psm, 8);
	mediumTriggerTemplate.restoreSpeed = 3;
	mediumTriggerTemplate.minTriggerInterval = 0.2;
	mediumTriggerTemplate.hue = 240;
	mediumTriggerTemplate.saturation = 200;
	
	TriggerRocket triggerRocketRed(mediumTriggerTemplate);
	TriggerRocket triggerRocketCyan(mediumTriggerTemplate);
	TriggerRocket triggerFountainRed(fastTriggerTemplate);
	TriggerRocket triggerFountainRedHigh(fastTriggerTemplate);
	TriggerRocket triggerFountainCyan(fastTriggerTemplate);
	TriggerRocket triggerFountainCyanHigh(fastTriggerTemplate);
	
	triggerRocketCyan.hue =
		triggerFountainCyan.hue =
		triggerFountainCyanHigh.hue = 120;
	
	*/
	
	TriggerSettings* redRocket = getRetroRocket();
	TriggerSettings* cyanRocket = getRetroRocket(120);
	TriggerSettings* redFountainLow = getRetroFountain();
	TriggerSettings* cyanFountainLow = getRetroFountain(180, -70);
	TriggerSettings* redFountainHigh = getRetroFountain(0,-128,1300,1900);
	TriggerSettings* cyanFountainHigh = getRetroFountain(180, -70,1300,1900);
	
	
	/*
	triggerRocketRed.addRocketSettings(redRocket);
	triggerRocketCyan.addRocketSettings(cyanRocket);
	triggerFountainRed.addRocketSettings(redFountainLow);
	triggerFountainCyan.addRocketSettings(cyanFountainLow);
	triggerFountainRedHigh.addRocketSettings(redFountainHigh);
	triggerFountainCyanHigh.addRocketSettings(cyanFountainHigh);
	*/
	
	
	TriggerPattern emptyPattern;
	addTriggerPattern(emptyPattern);
	
	
	
	TriggerPattern patternCyanChevrons;
	patternCyanChevrons.addTriggerSettings(cyanFountainLow);
	patternCyanChevrons.addTriggerSettings();
	patternCyanChevrons.addTriggerSettings(cyanFountainHigh);
	patternCyanChevrons.addTriggerSettings();
	addTriggerPattern(patternCyanChevrons);
	
	
	
	/*
	TriggerPattern fatRockets;
	float colours [4] = {170, 0, 220, 0};
	
	for(int i = 0; i<4; i++) {
		TriggerRocket triggerRocketFat(mediumTriggerTemplate);
		
		
		triggerRocketFat.radius = 5;
		triggerRocketFat.addRocketSettings(getFatRocket(colours[i]));
		triggerRocketFat.hue = colours[i];
		fatRockets.addTriggerSettings(triggerRocketFat);
		fatRockets.addTriggerSettings(); 
	}
	
	
	addTriggerPattern(fatRockets);

	
	
	TriggerPattern patternRedChevrons;
	patternRedChevrons.addTrigger(triggerFountainRed);
	patternRedChevrons.addTrigger(triggerFountainRedHigh);
	addTriggerPattern(patternRedChevrons);

	
	
	TriggerPattern fatRockets2;
	float colours2 [4] = {220, 180, 120, 180};
	
	for(int i = 0; i<4; i++) {
		TriggerRocket triggerRocketFat(mediumTriggerTemplate);
		
		
		triggerRocketFat.radius = 5;
		triggerRocketFat.addRocketSettings(getFatRocket(colours2[i]));
		triggerRocketFat.hue = colours2[i];
		fatRockets2.addTrigger(triggerRocketFat, 0,0,0.75);
	}
	
	addTriggerPattern(fatRockets2);

	
	TriggerPattern patternCyanMix;
	patternCyanMix.addTrigger(triggerRocketCyan);
	patternCyanMix.addTrigger(triggerFountainCyan);
	patternCyanMix.addTrigger(triggerFountainCyan);
	addTriggerPattern(patternCyanMix);
	
	
	TriggerPattern patternRedMix;
	patternRedMix.addTrigger(triggerRocketRed);
	patternRedMix.addTrigger(triggerFountainRed);
	patternRedMix.addTrigger(triggerFountainRed);
	addTriggerPattern(patternRedMix);

	
	TriggerPattern patternCyanRockets;
	patternCyanRockets.addTrigger(triggerRocketCyan);
	patternCyanRockets.addTrigger(triggerRocketCyan);
	
	patternCyanRockets.addTrigger(triggerFountainCyan);
	addTriggerPattern(patternCyanRockets);
	
	
	TriggerPattern patternRedRockets;
	patternRedRockets.addTrigger(triggerRocketRed);
	patternRedRockets.addTrigger(triggerRocketRed);
	patternRedRockets.addTrigger(triggerFountainRed);
	
	addTriggerPattern(patternRedRockets);
	
	
*/
	
};


bool SceneRetro :: draw() {
	if(!Scene::draw()) return false;
	
	ofPushStyle();
	ofDisableSmoothing();
	ofDisableBlendMode();
	ofEnableAlphaBlending();
	
	ofMesh mesh;
	mesh.setMode(OF_PRIMITIVE_LINES);
	
	ofColor lineColour(0,0,0,100);
	
	
	for(float x = 0; x<APP_WIDTH; x+=pixelSize) {
		
		mesh.addVertex(ofVec3f(x,0));
		mesh.addVertex(ofVec3f(x,APP_HEIGHT));
		mesh.addColor(lineColour);
		mesh.addColor(lineColour);
		
		
	}
	for(float y = 0; y<APP_HEIGHT; y+=pixelSize) {
		
		mesh.addVertex(ofVec3f(0,y));
		mesh.addVertex(ofVec3f(APP_WIDTH,y));
		mesh.addColor(lineColour);
		mesh.addColor(lineColour);
		
		
	}
	mesh.draw(); 
	
	ofPopStyle();
	
}

TriggerSettings* SceneRetro:: getFatRocket(float hue) {

	TriggerSettings* ts = new TriggerSettings();
	TriggerableRocket* tr = new TriggerableRocket();

	RocketSettings rocketSettings;
	ParticleSystemSettings pss;
	//pss.renderer = new ParticleRendererShape();
	pss.renderer = new ParticleRendererLowRes(pixelSize,1);
	pss.speedMin = pss.speedMax = 0;
	pss.emitCount = 100;
	pss.sizeStartMin = pss.sizeStartMax = pixelSize*1.5;
	pss.sizeChangeRatio = 0;
	pss.saturationEnd =500;
	pss.hueStartMin = pss.hueStartMax = hue; 
	//pss.brightnessEnd = 128;
	pss.lifeMin = 0.4;
	pss.lifeMax = 0.4;
	
	pss.emitLifeTime = 1.5;
	
	pss.startSound = "SynthKick";

	
	rocketSettings.addParticleSystemSetting(pss);
	
	rocketSettings.startSpeedMin = 1600;
	rocketSettings.startSpeedMax= 1700;
	rocketSettings.directionVar = 0;
	//rocketSettings.drag = 0.98;
	rocketSettings.gravity.set(0,1800);
	tr->rocketSettings = rocketSettings;
	ts->setTriggerable(tr);
	return ts;


};

TriggerSettings* SceneRetro::getRetroRocket(float hue, float hueChange) {
	
	TriggerSettings* ts = new TriggerSettings();
	TriggerableRocket* tr = new TriggerableRocket();
	
	RocketSettings rocketSettings;
	
	rocketSettings.startSpeedMin = 1000;
	rocketSettings.startSpeedMax = 1200;
	rocketSettings.drag = 0.95; 
		
	ParticleSystemSettings trails = getPixelTrailParticles(hue, hueChange);
	ParticleSystemSettings explosion = getPixelExplosionParticles(hue, hueChange);
	
	
	
	explosion.emitDelay = trails.emitLifeTime; 

	rocketSettings.addParticleSystemSetting(trails);
	rocketSettings.addParticleSystemSetting(explosion);
	
	tr->rocketSettings = rocketSettings;
	ts->setTriggerable(tr);
	return ts;

	
}



TriggerSettings* SceneRetro:: getRetroFountain(float hueOffset, float hueChange, float minSpeed, float maxSpeed ) {
	
	TriggerSettings* ts = new TriggerSettings;
	TriggerableRocket* tr = new TriggerableRocket();
	
	RocketSettings rocketSettings;
	ParticleSystemSettings pss;
	pss.renderer = new ParticleRendererLowRes(pixelSize);
	pss.speedMin = 100;
	pss.speedMax = 100;
	pss.drag = 0.9;
	
	pss.directionZVar = 0;
	pss.directionZ = 0; 
	
	pss.sizeStartMin = 4;
	pss.sizeStartMax = 4;
	pss.sizeChangeRatio = 0;
	
	pss.hueStartMin = pss.hueStartMax = hueOffset;
	pss.brightnessEnd = 255;
	pss.saturationMin = 0;
	pss.saturationMax = 0;
	pss.saturationEnd = 700;
	pss.shimmerMin = 1;
	
	pss.lifeMin= 0.2;
	pss.lifeMax= 0.8;
	
	
	pss.emitCount = 100;
	pss.emitLifeTime = 0.5;
	pss.emitHueModifierOffset = hueChange;
	pss.emitSpeedModifier = 0;
	pss.emitInheritVelocity = 0.5;
	pss.timeSpeed = 0.5;
	
	ParticleSystemSettings pss2(pss); 
	pss2.directionZ = 180;
	
	pss2.startSound = "RetroFountain";
	
	rocketSettings.startSpeedMin = 700;
	rocketSettings.startSpeedMax = 1200;
	rocketSettings.lifeTime = 0.5; 
	rocketSettings.drag = 0.99;
	rocketSettings.gravity.y = 1000;
	rocketSettings.addParticleSystemSetting(pss);
	rocketSettings.addParticleSystemSetting(pss2);
	rocketSettings.timeSpeed = 0.5;
	
	tr->rocketSettings = rocketSettings;
	ts->setTriggerable(tr);
	return ts;
	
};



ParticleSystemSettings SceneRetro::  getPixelTrailParticles(float hue, float hueChange){
	
	ParticleSystemSettings trails;
	trails.renderer = new ParticleRendererLowRes(pixelSize);
	//pss.directionZVar = 20;
	trails.speedMin = 10;
	trails.speedMax = 10;
	trails.sizeStartMin = trails.sizeStartMax = 3;
	trails.hueStartMin = trails.hueStartMax = hue;
	trails.hueChange = hueChange;
	trails.saturationMin = trails.saturationMax = 0;
	trails.saturationEnd = 500;
	trails.brightnessStartMin = trails.brightnessStartMin = trails.brightnessEnd = 255;
	
	trails.shimmerMin = 0;
	trails.lifeMin = trails.lifeMax = 0.3;
	trails.startSound = "RetroLaunch"; 

	return trails;
	
};

ParticleSystemSettings SceneRetro::  getPixelExplosionParticles(float hue, float hueChange){
	
	ParticleSystemSettings explosion;
	explosion.renderer = new ParticleRendererLowRes(pixelSize);
	
	//pss.directionZVar = 20;
	explosion.speedMin = 500;
	explosion.speedMax = 500;

	explosion.sizeStartMin = explosion.sizeStartMax = 30;
	explosion.hueStartMin = explosion.hueStartMax = hue;
	explosion.hueChange = hueChange;
	explosion.saturationMin = explosion.saturationMax = 0;
	explosion.saturationEnd = 500;
	explosion.brightnessStartMin = explosion.brightnessStartMin = explosion.brightnessEnd = 255;
	
	explosion.shimmerMin = 0;
	explosion.lifeMin = explosion.lifeMax = 0.6;
	
	//explosion.emitMode = PARTICLE_EMIT_BURST;
	explosion.emitLifeTime = 0.1;
	explosion.emitCount = 500;
	explosion.startSound = "RetroExplosion";

	
	return explosion;
	
};

