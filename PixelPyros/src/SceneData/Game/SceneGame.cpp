

#include "SceneGame.h"


SceneGame :: SceneGame(string scenename ) : Scene(scenename), psm(*ParticleSystemManager::instance())
{

	pixelSize = 1;
	loadMusicFile("1-05 TECHNOPOLIS.aif");
	
	invaderImage1.loadImage("img/Invader.png");
	invaderImage1.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
	activeInvaders = 0; 
	
	addTriggerPattern();

	
	TriggerSettingsRocket* ts = getInvaderBulletRocket(170);
	ts->rechargeSettings = new TriggerRechargeSettings();
	ts->rechargeSettings->restoreSpeed = 0.000001;
	
	TriggerPattern tp;
	tp.addTriggerSettings(ts);
	addTriggerPattern(tp);
	
	TriggerPattern bulletsPattern;
	
	bulletsPattern.addTriggerSettings(getInvaderBulletRocket(170));
	//bulletsPattern.addTriggerSettings();
	
	addTriggerPattern(bulletsPattern);
	
	explodeMesh.addVertex(ofPoint(1,0));
	explodeMesh.addVertex(ofPoint(0,1));
	explodeMesh.addVertex(ofPoint(-1,0));
	explodeMesh.addVertex(ofPoint(0,-1));
	
	explodeMesh.addVertex(ofPoint(0.8,0.8));
	explodeMesh.addVertex(ofPoint(-0.8,0.8));
	explodeMesh.addVertex(ofPoint(-0.8,-0.8));
	explodeMesh.addVertex(ofPoint(0.8,-0.8));
	currentGame = GAME_NONE;
	gameState = STATE_INTRO;
	
};


void SceneGame::start() {
	
	Scene::start();
	
	changeGame(GAME_INVADERS);
	changeState(STATE_INTRO); 
	
	
}


void SceneGame::changeGame(int newgame) {
	
	if(currentGame == newgame) return;
	
	if(newgame == GAME_INVADERS) {
		//resetInvaders();
		gameState = -1;
		changeState(STATE_INTRO);

	}
	
	currentGame = newgame;
	
	
}

void SceneGame::changeState(int newstate) {
	if(gameState == newstate) return;
	
	lastStateChangeTime = ofGetElapsedTimef();
	gameState = newstate;
	
	if(currentGame == GAME_INVADERS) {
		if(gameState == STATE_PLAYING) {
			resetInvaders();
			
			changeTriggerPattern(2);
		} else {
			changeTriggerPattern(1);
			triggerManager->emptyTriggers();
		}
		
		
	}
	
	
}

void SceneGame::stop() {
	Scene::stop();
	for(int i = 0; i<invaders.size(); i++) {
		Invader &invader = *invaders[i];
		if(!invader.enabled) continue;
		invader.enabled = false;
		explodeInvader(invader);
		spareInvaders.push_back(&invader);
	}
}

bool SceneGame::update(float deltaTime) {
	
	if(!Scene::update(deltaTime)) return false;

	
	if(currentGame == GAME_INVADERS) {
		
			
		if((gameState == STATE_INTRO) || (gameState == STATE_WAITING)) {
			if(ofGetElapsedTimef()-lastStateChangeTime>5) {
				changeState(STATE_PLAYING);
			}
		} else if(gameState == STATE_PLAYING) {
			if(activeInvaders==0) {
				changeState(STATE_WAITING);
				
				
			} else {
				updateInvaders();
				updateInvaders();
				updateInvaders();
				updateInvaders();

				checkInvaderCollisions();
			}
		}
	}
}



bool SceneGame :: draw() {
	if(!Scene::draw()) return false;
	
	ofPushStyle();
	if(currentGame == GAME_INVADERS) {
		
		for(int i = 0; i<invaders.size(); i++) {
			
			Invader& invader = *invaders[i];
			
			if(!invader.enabled) continue;
			
			invader.draw();
			activeInvaders++;
			
		}
		
		if(gameState == STATE_INTRO) {
			ofSetColor(255); 
			ofDrawBitmapString("READY TO PLAY " + ofToString(ofGetElapsedTimef()-lastStateChangeTime), 500,500);
			
		}
	}
	
	
	ofDrawBitmapString("GAME: " + ofToString(currentGame), 10,500);
	ofDrawBitmapString("STATE: " + ofToString(gameState), 10,550);
	ofDrawBitmapString("TIME SINCE CHANGE: " + ofToString(ofGetElapsedTimef()-lastStateChangeTime), 10,600);
	
	ofPopStyle();
			
}


void SceneGame::updateInvaders() {
	

	activeInvaders = 0;
	int rightEdge = 0;
	int leftEdge = APP_WIDTH;

	for(int i = 0; i<invaders.size(); i++) {
		
		Invader& invader = *invaders[i];
		
		if(!invader.enabled) continue;
		
		if(i == currentUpdateInvader) invader.update(true);
		else invader.update(false);
		
		if(invader.pos.x+invader.width>rightEdge) rightEdge = invader.pos.x+invader.width;
		if(invader.pos.x<leftEdge) leftEdge = invader.pos.x;
		
		
		activeInvaders++;
		
	}
	
	if(rightEdge>APP_WIDTH-50) {
		for(int i = 0; i<invaders.size(); i++) {
			Invader& invader = *invaders[i];
			if(invader.vel.x>0) {
				
				invader.vel.x = -10;
				invader.pos.y += 20;
			}
		}
	}
	
	if(leftEdge<50) {
		for(int i = 0; i<invaders.size(); i++) {
			
			Invader& invader = *invaders[i];
			if(invader.vel.x<0) {
				invader.vel.x = 10;
				invader.pos.y += 20;
			}
		}
	}
	
	
	if(activeInvaders == 0 ) {
		currentUpdateInvader = 0; 
	} else {
		
		do {
			currentUpdateInvader = (currentUpdateInvader+1) % invaders.size();
			
		} while(invaders[currentUpdateInvader]->enabled == false);
		
	}

	
}

void SceneGame :: checkInvaderCollisions() {
	
	vector<PhysicsObject*>& rockets = psm.physicsObjects;
	
	for(int i = 0; i<invaders.size(); i++) {
		
		Invader& invader = *invaders[i];
		
		if(!invader.enabled) continue;
		
		for(int j = 0; j<rockets.size(); j++) {
			PhysicsObject& rocket = *rockets[j];
			if(!rocket.isEnabled()) continue;
			
			if(invader.getRect().inside(rocket.pos)) {
				invader.enabled = false;
				spareInvaders.push_back(&invader);
				explodeInvader(invader);
				psm.killPhysicsObject(&rocket);
				
				break;
			}
		}
	}
	
}

void SceneGame :: resetInvaders() {
	
	
	float colours [4] = {128, 0, 220, 0};
	int invadercount = 0;
	
	spareInvaders.clear();
	invaders.clear();
	int numRows = 6;
	int numCols = 30;
	for(int y = 0; y<numRows; y++) {
		for(int x = 0; x<numCols; x++) {
		
			Invader* invader = getNewInvader();
			invader->pos.set(ofMap(x, 0, numCols, APP_WIDTH/6, APP_WIDTH/6*5), ofMap(y,0,numRows, APP_HEIGHT*0.3, APP_HEIGHT*0.6));
			invader->vel.set(10,0);
			invader->scale = 2;
			invader->colour.setSaturation(255);

			invader->hue = colours[(int)floor(ofMap(y, 0, numRows, 0, 3.99))];
			invader->colour.setHue(invader->hue);

			invader->delay = invadercount*5 + 100;
			invader->update(false); 
			invadercount++;
		}
	}

	currentUpdateInvader = 0; 
	activeInvaders = invadercount;
}

void SceneGame::explodeInvader(Invader &invader){
		ParticleSystem &ps = *psm.getParticleSystem();
	ParticleSystemSettings pss;
	pss.emitLifeTime = 0.2;
	pss.emitCount = 100;
	pss.renderer = new ParticleRendererLowRes(1,3);
	pss.speedMin = pss.speedMax = 200;
	pss.drag = 0.86;
	pss.sizeStartMin = pss.sizeStartMax = 2;
	pss.sizeChangeRatio = 0.5;
	pss.emitShape = &explodeMesh;
	pss.directionYVar = pss.directionZVar = 0;
	pss.hueStartMin = pss.hueStartMax = invader.hue;
	pss.hueChange = 0;
	pss.saturationMin = pss.saturationMax = 0;
	pss.saturationEnd = 500;
	pss.brightnessStartMin = pss.brightnessStartMax =pss.brightnessEnd = 255;
	pss.lifeMin = pss.lifeMax = 0.3;
	pss.startSound = "RetroExplosion";
	
	ps.pos = invader.pos + invader.offset + ofPoint(invader.width*invader.scale/2, invader.width*invader.scale/2);
	ps.init(pss);
	
}

Invader* SceneGame :: getNewInvader() {
	Invader* invader;
	if(spareInvaders.size()>0) {
		invader = spareInvaders.back();
		invader->enabled = true;
		spareInvaders.pop_back(); 
	} else {
		invader = new Invader(&invaderImage1, 12, 12);
		invaders.push_back(invader);
	}
	return invader; 
}


TriggerSettingsRocket* SceneGame:: getInvaderBulletRocket(float hue) {

	
	RocketSettings& rocketSettings = *new RocketSettings();
	ParticleSystemSettings pss;
	pss.renderer = new ParticleRendererLowRes(pixelSize,2);
	pss.speedMin = pss.speedMax = 0;
	pss.emitCount = 100;
	pss.sizeStartMin = pss.sizeStartMax = 4;
	pss.sizeChangeRatio = 1;
	pss.saturationEnd =255;
	pss.hueStartMin = pss.hueStartMax = hue; 
	pss.brightnessEnd = 0;
	pss.lifeMin = 0.1;
	pss.lifeMax = 0.2;
	pss.emitInheritVelocity = 0;//1;
	pss.drag = 0.95;
	
	rocketSettings.startSpeedMin = 400;
	rocketSettings.startSpeedMax = 400;
	rocketSettings.directionVar = 0;
	rocketSettings.setLifeTime(2);
	//rocketSettings.timeSpeed = 0.7;
	
	//rocketSettings.gravity.set(0,1800);

	//ParticleSystemSettings& pss = *rocketSettings.addParticleRenderer(new ParticleRendererLowRes(pixelSize,1));
	pss.startSound = "SynthKick";
	pss.sizeChangeRatio = 1;
	pss.sizeStartMax = pss.sizeStartMin = 1;
	pss.emitLifeTime = rocketSettings.getLifeTime();
	
	rocketSettings.addParticleSystemSetting(pss);

	
	TriggerSettingsRocket* ts = new TriggerSettingsRocket();
	
	ts->rocketSettings = &rocketSettings;
	ts->rechargeSettings = TriggerRechargeSettings::fastMultiples;

	return ts;

}

// ---------------- OLD ROCKETS

TriggerSettingsRocket* SceneGame:: getRetroFountain(float hueOffset, float hueChange, float minSpeed, float maxSpeed ) {
	
	
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




TriggerSettingsRocket* SceneGame::getRetroRocket(float hue, float hueChange) {
	
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




ParticleSystemSettings SceneGame::  getPixelTrailParticles(float hue, float hueChange){
	
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

ParticleSystemSettings SceneGame::  getPixelExplosionParticles(float hue, float hueChange){
	
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
