

#include "SceneRetro.h"


SceneRetro :: SceneRetro(string scenename ) : Scene(scenename) {

	pixelSize = 2;
	loadMusicFile("1-05 TECHNOPOLIS.aif");
	
	invaderImage1.loadImage("img/Invader.png");
	invaderImage1.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
	activeInvaders = 0; 

	//TODO this should really be somewhere else - but where! 
	TriggerRechargeSettings::fastMultiples->minTriggerInterval = 0.2;
	TriggerRechargeSettings::fastMultiples->triggerPower = 0.3;
	TriggerRechargeSettings::fastMultiples->restoreSpeed = 0.7;
	
	
	TriggerSettings* redRocket = getRetroRocket();
	TriggerSettings* cyanRocket = getRetroRocket(120);
	TriggerSettings* redFountainLow = getRetroFountain();
	TriggerSettings* cyanFountainLow = getRetroFountain(180, -70);
	TriggerSettings* redFountainHigh = getRetroFountain(0,-128,1300,1600);
	TriggerSettings* cyanFountainHigh = getRetroFountain(180, -70,1300,1600);
	
	
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
	
	
	
	
	TriggerPattern pixelRockets;
	float colours [4] = {170, 0, 220, 0};
	
	for(int i = 0; i<4; i++) {
		TriggerSettingsRocket& triggerRocketFat = *getPixelRocket(colours[i]);
		triggerRocketFat.hue = colours[i];
		triggerRocketFat.saturation = 255;
		pixelRockets.addTriggerSettings(&triggerRocketFat);
		pixelRockets.addTriggerSettings(); 
	}
	
	
	addTriggerPattern(pixelRockets);

	
	
	TriggerPattern patternRedChevrons;
	patternRedChevrons.addTriggerSettings(redFountainLow);
	patternRedChevrons.addTriggerSettings();
	patternRedChevrons.addTriggerSettings(redFountainHigh);
	patternRedChevrons.addTriggerSettings();

	addTriggerPattern(patternRedChevrons);

	
	
	TriggerPattern pixelRockets2;
	float colours2 [4] = {220, 180, 120, 180};
	
	for(int i = 0; i<4; i++) {
		
		TriggerSettingsRocket& triggerRocketFat = *getPixelRocket(colours2[i]);
		triggerRocketFat.hue = colours2[i];
		triggerRocketFat.saturation = 255;
		pixelRockets2.addTriggerSettings(&triggerRocketFat);
		pixelRockets2.addTriggerSettings();
		
	}
	
	addTriggerPattern(pixelRockets2);

	
	TriggerPattern patternCyanMix;
	patternCyanMix.addTriggerSettings(cyanRocket);
	patternCyanMix.addTriggerSettings();
	patternCyanMix.addTriggerSettings(cyanFountainLow);
	patternCyanMix.addTriggerSettings();
	addTriggerPattern(patternCyanMix);
	
	
	TriggerPattern patternRedMix;
	patternRedMix.addTriggerSettings(redRocket);
	patternRedMix.addTriggerSettings();
	patternRedMix.addTriggerSettings(redFountainLow);
	patternRedMix.addTriggerSettings();
	addTriggerPattern(patternRedMix);
	
	/*
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
	
	
	for(int x = 200; x<APP_WIDTH-200; x+=48) {
		for(int y = 200; y<APP_HEIGHT-500; y+=60) {
		
			Invader* invader = new Invader(&invaderImage1, 12, 12);
			invader->pos.set(x, y);
			invader->vel.set(4,0);
			invader->scale = 3;
			invader->colour.setSaturation(255);
			invader->colour.setHue(colours[(int)floor(ofMap(y,200,APP_HEIGHT-500, 0,3.9,true))]);
			
			invaders.push_back(invader);
		}
	}

	
	
	
};


bool SceneRetro::update(float deltaTime) {
	
	if(!Scene::update(deltaTime)) return false;

	ParticleSystemManager& psm = *ParticleSystemManager::instance();
	
	activeInvaders = 0;
	int rightEdge = 0;
	int leftEdge = APP_WIDTH; 

	for(int i = 0; i<invaders.size(); i++) {
		
		Invader& invader = *invaders[i];
		
		if(!invader.enabled) continue;
		
		invader.update();
		
		if(invader.pos.x+invader.width>rightEdge) rightEdge = invader.pos.x+invader.width;
		if(invader.pos.x<leftEdge) leftEdge = invader.pos.x;
		
		
		activeInvaders++; 
		
	}
	
	if(rightEdge>APP_WIDTH-50) {
		for(int i = 0; i<invaders.size(); i++) {
			
			Invader& invader = *invaders[i];
			invader.vel.x = -4;
		}
	}
			
	if(leftEdge<50) {
		for(int i = 0; i<invaders.size(); i++) {
			
			Invader& invader = *invaders[i];
			invader.vel.x = 4;
		}
	}
	
	vector<PhysicsObject*>& rockets = psm.physicsObjects;
	
	for(int i = 0; i<invaders.size(); i++) {
		
		Invader& invader = *invaders[i];
		
		if(!invader.enabled) continue;
		
		for(int j = 0; j<rockets.size(); j++) {
			PhysicsObject& rocket = *rockets[j];
			if(!rocket.isEnabled()) continue;
			
			//ofRectangle invaderRect(invader.pos, invader.width, invader.height);
			if(invader.getRect().inside(rocket.pos)) {
				invader.enabled = false;
				//rocket.life.end();
				break;
			}
			
			
			
			
			
		}
		
		
		
	}
	
	
}




bool SceneRetro :: draw() {
	if(!Scene::draw()) return false;
	
	
	
	for(int i = 0; i<invaders.size(); i++) {
		
		Invader& invader = *invaders[i];
		
		if(!invader.enabled) continue;
		
		invader.draw();
		activeInvaders++;
		
	}
	
	
	
	ofPushStyle();
	ofDisableSmoothing();
	ofDisableBlendMode();
	ofEnableAlphaBlending();
	
	
	ofMesh mesh;
	mesh.setMode(OF_PRIMITIVE_LINES);
	ofSetLineWidth(1);
	// TODO This brightness needs to be adjustable
	ofColor lineColour(0,0,0,100);
	
	
	for(int x = 0; x<APP_WIDTH; x+=pixelSize) {
		
		mesh.addVertex(ofVec3f(x+0.5,0));
		mesh.addVertex(ofVec3f(x+0.5,APP_HEIGHT));
		mesh.addColor(lineColour);
		mesh.addColor(lineColour);
		
		
	}
	for(int y = 0; y<APP_HEIGHT; y+=pixelSize) {
		
		mesh.addVertex(ofVec3f(0,y+0.5));
		mesh.addVertex(ofVec3f(APP_WIDTH,y+0.5));
		mesh.addColor(lineColour);
		mesh.addColor(lineColour);
		
		
	}
	mesh.draw();
	
	ofPopStyle();
	
}


TriggerSettingsRocket* SceneRetro:: getPixelRocket(float hue) {

	
	RocketSettings& rocketSettings = *new RocketSettings();
	ParticleSystemSettings pss;
	//pss.renderer = new ParticleRendererShape();
	pss.renderer = new ParticleRendererLowRes(pixelSize,1);
	pss.speedMin = pss.speedMax = 0;
	pss.emitCount = 100;
	pss.sizeStartMin = pss.sizeStartMax = pixelSize*2;
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
	
	rocketSettings.timeSpeed = pss.timeSpeed = 0.7;
	
	rocketSettings.gravity.set(0,1800);
	
	TriggerSettingsRocket* ts = new TriggerSettingsRocket();
	
	ts->rocketSettings = &rocketSettings;
	ts->rechargeSettings = TriggerRechargeSettings::fast;

	return ts;


};

TriggerSettingsRocket* SceneRetro:: getRetroFountain(float hueOffset, float hueChange, float minSpeed, float maxSpeed ) {
	
	
	RocketSettings& rocketSettings = *new RocketSettings();
	ParticleSystemSettings pss;
	pss.renderer = new ParticleRendererLowRes(pixelSize);
	pss.speedMin = 50;
	pss.speedMax = 50;
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
	pss.timeSpeed = 0.7;
	
	ParticleSystemSettings pss2(pss); 
	pss2.directionZ = 180;
	
	pss2.startSound = "RetroFountain";
	
	rocketSettings.startSpeedMin = minSpeed;
	rocketSettings.startSpeedMax = maxSpeed;
	rocketSettings.setLifeTime(0.5);
	rocketSettings.drag = 0.99;
	rocketSettings.gravity.y = 1000;
	rocketSettings.addParticleSystemSetting(pss);
	rocketSettings.addParticleSystemSetting(pss2);
	rocketSettings.timeSpeed = 0.7;
	
	TriggerSettingsRocket* ts = new TriggerSettingsRocket();
	ts->rocketSettings = &rocketSettings;
	ts->rechargeSettings = TriggerRechargeSettings::fastMultiples;

	return ts;
	
};




TriggerSettingsRocket* SceneRetro::getRetroRocket(float hue, float hueChange) {
	
	TriggerSettingsRocket& ts = *new TriggerSettingsRocket();
	
	RocketSettings& rocketSettings = *new RocketSettings();
	
	rocketSettings.startSpeedMin = 1100;
	rocketSettings.startSpeedMax = 1400;
	rocketSettings.drag = 0.94;
	
	
	ParticleSystemSettings trails = getPixelTrailParticles(hue, hueChange);
	ParticleSystemSettings explosion = getPixelExplosionParticles(hue, hueChange);
	
	explosion.emitDelay = trails.emitLifeTime;
	
	rocketSettings.addParticleSystemSetting(trails);
	rocketSettings.addParticleSystemSetting(explosion);
	
	ts.rocketSettings = &rocketSettings;
	
	rocketSettings.timeSpeed = trails.timeSpeed = explosion.timeSpeed = 0.7;
	
	
	ts.rechargeSettings = TriggerRechargeSettings::medium;
	
	return &ts;
	
	
}




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
	trails.emitLifeTime = 2.5;
	trails.emitStartSizeModifier = 0.2;

	trails.shimmerMin = 0;
	trails.lifeMin = trails.lifeMax = 0.3;
	trails.startSound = "RetroLaunch"; 

	return trails;
	
};

ParticleSystemSettings SceneRetro::  getPixelExplosionParticles(float hue, float hueChange){
	
	ParticleSystemSettings explosion;
	explosion.renderer = new ParticleRendererLowRes(pixelSize);
	

	explosion.speedMin = 250;
	explosion.speedMax = 300;

	explosion.sizeStartMin = explosion.sizeStartMax = 20;
	explosion.hueStartMin = explosion.hueStartMax = hue;
	explosion.hueChange = hueChange;
	explosion.saturationMin = explosion.saturationMax = 0;
	explosion.saturationEnd = 500;
	explosion.brightnessStartMin = explosion.brightnessStartMin = explosion.brightnessEnd = 255;
	
	explosion.shimmerMin = 0;
	explosion.lifeMin = explosion.lifeMax = 0.6;
	
	
	ofMesh* circleMesh = new ofMesh();
	for(int i = 0; i<30; i++) {
		ofVec3f v(1,0,0);
		v.rotate(ofMap(i,0,30,0,360), ofVec3f(0,0,1));
		circleMesh->addVertex(v);
	}
	
	explosion.directionYVar = 0;
	explosion.directionZVar = 0;
	
	//explosion.emitMode = PARTICLE_EMIT_BURST;
	explosion.emitLifeTime = 0.1;
	explosion.emitShape = circleMesh; 
	explosion.emitCount = 1200;
	explosion.startSound = "RetroExplosion";

	
	return explosion;
	
};

