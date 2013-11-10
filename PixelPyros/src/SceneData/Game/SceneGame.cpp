

#include "SceneGame.h"


SceneGame :: SceneGame(string scenename ) : Scene(scenename), psm(*ParticleSystemManager::instance())
{

	

	pixelSize = 1;
	loadMusicFile("FireCrackerEdit.aif");
	
	invaderImage1.loadImage("img/Invader.png");
	invaderImage1.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
	activeInvaders = 0;
	activeAsteroids = 0;
	numRows = 0;
	numCols = 0;
	
	addEmptyTriggerPattern();

	
	TriggerSettingsRocket* ts = getInvaderBulletRocket(170);
	ts->rechargeSettings = new TriggerRechargeSettings();
	ts->rechargeSettings->restoreSpeed = 0.000001;
	
	TriggerPattern tp;
	tp.addTriggerSettings(ts);
	addTriggerPattern(tp, "invader ships");
	
	TriggerPattern bulletsPattern;
	
	bulletsPattern.addTriggerSettings(getInvaderBulletRocket(170));
	addTriggerPattern(bulletsPattern, "invader ships active");
	
	
	ts = getAsteroidsBulletRocket();
	ts->rechargeSettings = new TriggerRechargeSettings();
	ts->rechargeSettings->restoreSpeed = 0.000001;
	
	TriggerPattern tp2;
	tp2.addTriggerSettings(ts);
	addTriggerPattern(tp2, "asteroid ships");
	
	TriggerPattern bulletsPatternAsteroids;
	
	bulletsPatternAsteroids.addTriggerSettings(getAsteroidsBulletRocket());
	
	addTriggerPattern(bulletsPatternAsteroids, "asteroid ships active");
	
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
	
	
	ofTrueTypeFont::setGlobalDpi(72);

	pixelFont.loadFont("bender_light.ttf", 60, true, true);
	pixelFont.setLineHeight(68.0f);
	pixelFont.setLetterSpacing(1.035);
	
	
};


void SceneGame::start() {
	
	
	Scene::start();
	
	//level = 0;
	changeGame(GAME_INVADERS);
//	changeState(STATE_INTRO);
	
	
}


void SceneGame::changeGame(int newgame) {
	
	//if(currentGame == newgame) return;
	
	
	level = 0;
	
	currentGame = newgame;
	
	
	if(newgame == GAME_INVADERS) {
		//resetInvaders();
		gameState = -1;
		changeState(STATE_PREINTRO);

	} else if(newgame == GAME_ASTEROIDS) {
		gameState = -1;
		changeState(STATE_INTRO);
			
	}
	
	
}

void SceneGame::changeState(int newstate) {
	if(gameState == newstate) return;
	
	lastStateChangeTime = ofGetElapsedTimef();
	gameState = newstate;
	
	if(currentGame == GAME_INVADERS) {
		if(gameState == STATE_INTRO || gameState == STATE_WAITING){
			changeTriggerPattern(1);
			resetInvaders();
		} else if(gameState == STATE_PLAYING) {
			changeTriggerPattern(2);
			//triggerManager->emptyTriggers();
		} else {
			//cout << "CHANGING TRIGGER PATTERN" << endl;
			changeTriggerPattern(1);
			//triggerManager->emptyTriggers();
		}
		
		
	} else if(currentGame == GAME_ASTEROIDS) {
		if(gameState == STATE_PLAYING) {	
			changeTriggerPattern(4);
		} else {
			changeTriggerPattern(3);
			triggerManager->emptyTriggers();
			if(gameState!=STATE_GAMEOVER) resetAsteroids();
		}
		
		
	}
	
}

void SceneGame::stop() {
	Scene::stop();
	killInvadersAndAsteroids(); 
}

void SceneGame::killInvadersAndAsteroids() {
	for(int i = 0; i<invaders.size(); i++) {
		Invader &invader = *invaders[i];
		if(!invader.enabled) continue;
		invader.enabled = false;
		makeInvaderExplosion(invader);
		//spareInvaders.push_back(&invader);
	}
	
	for(int i = 0; i<asteroids.size(); i++) {
		Asteroid &asteroid = *asteroids[i];
		if(!asteroid.enabled) continue;
		asteroid.enabled = false;
		makeAsteroidExplosion(asteroid);
		//spareInvaders.push_back(&invader);
	}
	
}

bool SceneGame::update(float deltaTime) {
	
	if(!Scene::update(deltaTime)) return false;
	finished = false; 
	
	//if(!playing) lastStateChangeTime+=deltaTime;
	timeSinceLastStateChange = ofGetElapsedTimef() - lastStateChangeTime; 

	if(currentGame == GAME_INVADERS) {
		
		if(gameState == STATE_PREINTRO) {
			if(ofGetElapsedTimef()-lastStateChangeTime>20) {
				changeState(STATE_INTRO);
			}
			
		}
		else if((gameState == STATE_INTRO) || (gameState == STATE_WAITING)) {
			if(ofGetElapsedTimef()-lastStateChangeTime>5) {
				changeState(STATE_PLAYING);
			}
		} else if(gameState == STATE_GAMEOVER) {
			if(ofGetElapsedTimef()-lastStateChangeTime>5) {
				changeGame(GAME_ASTEROIDS);
			}

		} else if(gameState == STATE_PLAYING) {
			if(activeInvaders==0) {
				level++;
				if(positionSeconds>lengthSeconds/2) {
					changeState(STATE_GAMEOVER) ;
				} else {
					changeState(STATE_WAITING);
				}
				
			} else {
				updateInvaders();
				checkInvaderCollisions();
			}
		}
		
		if(gameState == STATE_PLAYING || gameState == STATE_INTRO || gameState == STATE_WAITING) {
			updateInvaders();
			checkInvaderCollisions();
		}
		
	} else if (currentGame == GAME_ASTEROIDS) {
		
		updateAsteroids(deltaTime);

		if((gameState == STATE_INTRO) || (gameState == STATE_WAITING)) {
			if(ofGetElapsedTimef()-lastStateChangeTime>5) {
				changeState(STATE_PLAYING);
			}
		} else if(gameState == STATE_PLAYING) {
			if(activeAsteroids==0) {
				level++;
				if(positionSeconds>lengthSeconds-20) {
					changeState(STATE_GAMEOVER) ;
					
				} else {
					changeState(STATE_WAITING);
				}
			} else {
				checkAsteroidCollisions();
			}
		} else if(gameState == STATE_GAMEOVER) {
			
			if((!playing) && (timeSinceLastStateChange>5)) {
				finished = true;
			}
		}
	}
}



bool SceneGame :: draw() {
	if(!Scene::draw()) return false;
	
	float centreX = APP_WIDTH/2;
	float centreY = APP_HEIGHT/2;
	
	
	ofPushStyle();
	if(currentGame == GAME_INVADERS) {
		
		for(int i = 0; i<invaders.size(); i++) {
			
			Invader& invader = *invaders[i];
			
			if(!invader.enabled) continue;
			
			invader.draw();
			activeInvaders++;
			
		}
		
		ofSetColor(255);

		if((gameState == STATE_PREINTRO)&&(playing)) {
			if(timeSinceLastStateChange<8) {
				String s = "READY TO PLAY INVADERS?";
				drawStringCentered(s, centreX, centreY-50);
				float flashspeed = 1.0f; 
				if(modff(timeSinceLastStateChange,&flashspeed)<0.7)	{
					drawStringCentered("YES / NO", centreX, centreY+50);
				}
			} else if((timeSinceLastStateChange>9) && (timeSinceLastStateChange<18)) {
				String s = "I SAID";
				drawStringCentered(s, centreX, centreY-100);
				if(timeSinceLastStateChange>11) {
					drawStringCentered("ARE YOU READY TO PLAY?", centreX, centreY);
					float flashspeed = 1.0f;
					if(modff(timeSinceLastStateChange,&flashspeed)<0.7)	{
						drawStringCentered("YES OR NO", centreX, centreY+100);
					}
				}
				
			}
		} else if(gameState == STATE_INTRO) {
						
			String s = "PLAYERS GET READY";
			
			drawStringCentered(s, centreX, centreY-50);
			
			int secondsToGo = 5-ceil(timeSinceLastStateChange);
			if(secondsToGo<=3) {
				s= ofToString(secondsToGo);
				drawStringCentered(s, centreX, centreY+50);
				
			}
			
			
		} else if(gameState == STATE_WAITING) {
			
			String s = "LEVEL "+ofToString(level)+" CLEARED!";
			drawStringCentered(s, centreX, centreY-50);
			
			int secondsToGo = 5-ceil(timeSinceLastStateChange);
			if(secondsToGo<=3) {
				s= "NEXT LEVEL IN "+ ofToString(secondsToGo);
				drawStringCentered(s, centreX, centreY+50);
			}
			
		} else if(gameState == STATE_GAMEOVER) {
			ofSetColor(255);
			
			drawStringCentered("GAME OVER", centreX, centreY);
		}
	} else if(currentGame == GAME_ASTEROIDS) {
		
		for(int i = 0; i<asteroids.size(); i++) {
			
			Asteroid& asteroid = *asteroids[i];
			
			if(!asteroid.enabled) continue;
			
			asteroid.draw();
						
		}
		
		if(gameState == STATE_INTRO) {
						
			
			String s = "PLAYERS GET READY";
			
			drawStringCentered(s, centreX, centreY-50);
			
			int secondsToGo = 5-ceil(timeSinceLastStateChange);
			if(secondsToGo<=3) {
				s= ofToString(secondsToGo);
				drawStringCentered(s, centreX, centreY+50);
				
			}
			
			
			
		} else if(gameState == STATE_WAITING) {
			
			String s = "LEVEL "+ofToString(level)+" CLEARED!";
			drawStringCentered(s, centreX, centreY-50);
			
			int secondsToGo = 5-ceil(timeSinceLastStateChange);
			if(secondsToGo<=3) {
				s= "NEXT LEVEL IN "+ ofToString(secondsToGo);
				drawStringCentered(s, centreX, centreY+50);
			}
			
			
			
			
			
			
			//ofDrawBitmapString("LEVEL "+ofToString(level)+" CLEARED " + ofToString(ofGetElapsedTimef()-lastStateChangeTime), 500,500);
			
		} else if(gameState == STATE_GAMEOVER) {
			ofSetColor(255);
			//ofDrawBitmapString("GAME OVER" + ofToString(ofGetElapsedTimef()-lastStateChangeTime), 500,500);
			
			drawStringCentered("GAME OVER", centreX, centreY);
			
		}
	}
	
	
//	ofDrawBitmapString("GAME: " + ofToString(currentGame), 10,500);
//	ofDrawBitmapString("STATE: " + ofToString(gameState), 10,550);
//	ofDrawBitmapString("TIME SINCE CHANGE: " + ofToString(timeSinceLastStateChange), 10,600);
	
	ofPopStyle();
			
}


void SceneGame::drawStringCentered(String string, float x, float y) {
	float width = pixelFont.stringWidth(string);
	float height = pixelFont.stringHeight(string); 
	pixelFont.drawString(string, x-width/2, y-height/2);
	
	
}

void SceneGame:: updateAsteroids(float deltaTime) {
	activeAsteroids = 0;
	
	ofRectangle playRect(0,0,APP_WIDTH, APP_HEIGHT); // TODO use trigger area?
	for(int i = 0; i<asteroids.size(); i++) {
		
		Asteroid& asteroid = *asteroids[i];
		if(!asteroid.enabled) continue;
		
		asteroid.update(deltaTime, playRect);
		activeAsteroids++; 
	}
		
}

void SceneGame :: resetAsteroids() {
	for(int i = 0; i<asteroids.size(); i++) {
		delete asteroids[i];
	}
	
	asteroids.clear();
	//spareAsteroids.clear();
	
	for(int i = 0; i< 20; i++) {
	
		Asteroid * asteroid = new Asteroid(ofRandom(0,APP_WIDTH), ofRandom(0,APP_HEIGHT*0.6), 50);
		
		if(asteroid->vel.y>0) asteroid->pos.y = ofRandom(0,APP_HEIGHT*0.3);
		else asteroid->pos.y = ofRandom(APP_HEIGHT*0.3, APP_HEIGHT*0.6);

		asteroids.push_back(asteroid);
		
	}
	activeAsteroids = asteroids.size();
	
	
}


void SceneGame :: checkAsteroidCollisions() {
	
	vector<PhysicsObject*>& rockets = psm.physicsObjects;
	
	for(int i = 0; i<asteroids.size(); i++) {
		
		Asteroid& asteroid = *asteroids[i];
		
		if(!asteroid.enabled) continue;
		
		for(int j = 0; j<rockets.size(); j++) {
			PhysicsObject& rocket = *rockets[j];
			if(!rocket.isEnabled()) continue;
			
			if(asteroid.pos.distance(rocket.pos) < asteroid.radius) {
				makeAsteroidExplosion(asteroid);
				if(asteroid.radius<20) {
					asteroid.enabled = false;
					
				} else {
					Asteroid* newasteroid = new Asteroid(0,0,asteroid.radius/2);
					newasteroid->pos = asteroid.pos;
					asteroid.updateSize(newasteroid->radius);
					asteroids.push_back(newasteroid);
				}
					
				psm.killPhysicsObject(&rocket, true);
				
				break;
			}
		}
	}
	
}


void SceneGame::updateInvaders() {
	
	activeInvaders = 0;
	//int rightEdge = 0;
	//int leftEdge = APP_WIDTH;
	//int topEdge = APP_HEIGHT;
	//int bottomEdge = 0;
	
	ofRectangle invaderRect;
	bool firstInvader = true;
	
	
	for(int i = 0; i<invaders.size(); i++) {
		
		Invader& invader = *invaders[i];
		if(!invader.enabled) continue;

		if(invader.delay<=0) {
			if(firstInvader) {
				invaderRect.set(invader.getRect());
				firstInvader = false; 
			} else {
				invaderRect.growToInclude(invader.getRect()); 
			}
		}
		//if(i ==currentUpdateInvader) invader.update(true);
		//else
		invader.update();
		
		activeInvaders++;
		
	}
	
	for(int i = 0; i<invaders.size(); i++) {
		Invader& invader = *invaders[i];
		
		if(nextUpdateCountdown == i%invaderUpdateFrequency){
			invader.pos+=allInvadersVel;
			invader.nextFrame();
		}
		
	}
	
	if(invaderRect.getBottom()<APP_HEIGHT*0.6) {
		
		float speed = 2;
		//if(invaderRect.getBottom()<APP_HEIGHT*0.3) speed = 6;
		
		for(int i = 0; i<invaders.size(); i++) {
			Invader& invader = *invaders[i];
			
			invader.pos.y+=speed;
			
		}
	}
	
	if(nextUpdateCountdown == 0) {
		
		//if(invaderRect.getBottom()<APP_HEIGHT*0.6) {
		//	allInvadersVel.y = 18;
		//} else {
			allInvadersVel.y = 0;
		//}
		if((allInvadersVel.x>0) && (invaderRect.getRight()>triggerManager->triggerArea.getRight()+12)) {
			allInvadersVel.set(-18,18);
		}
		
		if((allInvadersVel.x<0) && (invaderRect.getLeft()<triggerManager->triggerArea.getLeft()-12)) {
			allInvadersVel.set(18,18);
			
		}
		
		if(invaderRect.getBottom() > triggerManager->triggerArea.getTop()) {
			// INSERT EXPLOSIONS
			//changeState(STATE_WAITING);
			allInvadersVel.y = 0; 
		}

		
		invaderUpdateFrequency = min((float)numCols, ceil((float)activeInvaders/5.0f));
		if(invaderUpdateFrequency <=0) invaderUpdateFrequency = 1;
		nextUpdateCountdown = invaderUpdateFrequency;
	} else {
		nextUpdateCountdown--;
	}
	
//	if(invaderRect.getBottom() > triggerManager->triggerArea.getCenter().y) {
//		// INSERT EXPLOSIONS
//		changeState(STATE_WAITING);
//	}
	
}

void SceneGame :: checkInvaderCollisions() {
	
	vector<PhysicsObject*>& rockets = psm.physicsObjects;
	
	for(int i = 0; i<invaders.size(); i++) {
		
		Invader& invader = *invaders[i];
		
		if(!invader.enabled) continue;
		
		for(int j = 0; j<rockets.size(); j++) {
			PhysicsObject& rocket = *rockets[j];
			if(!rocket.isEnabled()) continue;
			if(invader.delay>0) continue;
			if(invader.getRect().inside(rocket.pos)) {
				invader.enabled = false;
				//spareInvaders.push_back(&invader);
				makeInvaderExplosion(invader);
				psm.killPhysicsObject(&rocket);
				
				break;
			}
		}
	}
	
}

void SceneGame :: resetInvaders() {
	
	for(int i = 0; i<invaders.size(); i++) {
		delete invaders[i];
	}
	
	//spareInvaders.clear();
	invaders.clear();

	float colours [4] = {128, 0, 220, 0};
	int invadercount = 0;
	
	
	ofRectangle rect(triggerManager->triggerArea.getLeft() + 18, -APP_HEIGHT*1.6,   triggerManager->triggerArea.width-36, APP_HEIGHT * 1.5);
	
	numRows = floor(rect.height/60.0f);
	numCols = floor(triggerManager->triggerArea.width/50.0f);

	
	for(int y = 0; y<numRows; y++) {
		for(int x = 0; x<numCols; x++) {
		
			Invader* invader = getNewInvader();
			invader->pos.set(ofMap(x, 0, numCols, rect.getLeft(),rect.getRight() ), ofMap(y,numRows,0, rect.getTop(), rect.getBottom()));
			invader->currentPos = invader->pos + ofPoint(500,-1000);
			//invader->vel.set(10,0);
			invader->scale = 2;
			invader->colour.setSaturation(255);

			invader->hue = colours[(int)floor(ofMap(y, 0, numRows, 0, 3.99))];
			invader->colour.setHue(invader->hue);

			invader->delay = 0;//x + y*20;
			//invader->update();
			invadercount++;
		}
	}

	currentUpdateInvader = 0; 
	activeInvaders = invadercount;
	invaderUpdateFrequency = 20;
	nextUpdateCountdown = 20;
	
	allInvadersVel.set(10,0);

}

void SceneGame::makeInvaderExplosion(Invader &invader){
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
	pss.doNotScale = true; 
	
	ps.pos = invader.getRect().getCenter();
	ps.init(pss);
	
}

void SceneGame::makeAsteroidExplosion(Asteroid &asteroid){
	ParticleSystem &ps = *psm.getParticleSystem();
	ParticleSystemSettings pss;
	pss.emitLifeTime = 0.1;
	pss.emitCount = 500;
	pss.renderer = new ParticleRendererShape();
	pss.speedMin = pss.speedMax = 600; //  * asteroid.radius;
	pss.drag = 0.96;
	pss.sizeStartMin = 5;
	pss.sizeStartMax = 12;
	pss.sizeChangeRatio = 0;
	//pss.emitShape = &explodeMesh;
	pss.directionYVar = 0;
	pss.directionZVar = 180;
	pss.hueStartMin = pss.hueStartMax = 128;
	pss.hueChange = 0;
	pss.saturationMin = pss.saturationMax = 0;
	pss.saturationEnd = 220;
	pss.brightnessStartMin = pss.brightnessStartMax =pss.brightnessEnd = 255;
	pss.lifeMin = pss.lifeMax = 0.3;
	pss.startSound = "RetroExplosion";
	//pss.shimmerMin = 0;
	pss.timeSpeed = 0.7;
	pss.doNotScale = true; 
	
	ps.pos = asteroid.pos; 
	ps.init(pss);
	
}
Invader* SceneGame :: getNewInvader() {
	Invader* invader = new Invader(&invaderImage1, 13, 12);
	invaders.push_back(invader);
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
	pss.doNotScale = true; 
	
	rocketSettings.addParticleSystemSetting(pss);
	
	TriggerSettingsRocket* ts = new TriggerSettingsInvaders();
	
	
	ts->addRocketSettings(&rocketSettings);
	ts->rechargeSettings = TriggerRechargeSettings::mediumMultiples;
	ts->startEmpty = true;
	ts->rotateMirrorOffset = 0; 
	
	return ts;
	
}




TriggerSettingsRocket* SceneGame:: getAsteroidsBulletRocket() {
	
	
	RocketSettings& rocketSettings = *new RocketSettings();
	ParticleSystemSettings pss;
	pss.renderer = new ParticleRendererCircle(8, false, 2);
	pss.speedMin = pss.speedMax = 0;
	pss.emitCount = 100;
	pss.sizeStartMin = pss.sizeStartMax = 3;
	pss.sizeChangeRatio = 0;
	pss.saturationEnd =255;
	pss.hueStartMin = pss.hueStartMax = 128;
	pss.brightnessEnd = 0;
	pss.lifeMin = 0.1;
	pss.lifeMax = 0.2;
	pss.emitInheritVelocity = 1;
	pss.drag = 0.95;
	pss.doNotScale = true; 
	
	rocketSettings.startSpeedMin = 400;
	rocketSettings.startSpeedMax = 400;
	rocketSettings.directionVar = 0;
	rocketSettings.setLifeTime(2.2);
	//rocketSettings.timeSpeed = 0.7;
	
	//rocketSettings.gravity.set(0,1800);
	
	//ParticleSystemSettings& pss = *rocketSettings.addParticleRenderer(new ParticleRendererLowRes(pixelSize,1));
	pss.startSound = "SynthKick";

	pss.emitLifeTime = rocketSettings.getLifeTime();
	
	//rocketSettings.addParticleSystemSetting(pss);
	
	ParticleSystemSettings& pss2 = *rocketSettings.addParticleRenderer(new ParticleRendererLaser());
	pss2.sizeStartMax = pss2.sizeStartMin = 4;
	pss2.sizeChangeRatio = 1;
	pss2.doNotScale = true;

	
	TriggerSettingsRocket* ts = new TriggerSettingsAsteroids();
	
	ts->addRocketSettings(&rocketSettings);
	ts->rechargeSettings = TriggerRechargeSettings::mediumMultiples;
	ts->rotationExtent = 20;
	ts->rotationSpeed = 4;
	ts->rotateOscillationOffset = 1;
	ts->startEmpty = true;

	
	return ts;
	
}

// ---------------- OLD ROCKETS

/*

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
	
	TriggerSettingsRocket* ts = new TriggerSettingsRocketOrb();
	ts->addRocketSettings(&rocketSettings);
	ts->rechargeSettings = TriggerRechargeSettings::fastMultiples;

	return ts;
	
};


TriggerSettingsRocket* SceneGame::getRetroRocket(float hue, float hueChange) {
	
	TriggerSettingsRocket& ts = *new TriggerSettingsRocketOrb();
	
	RocketSettings& rocketSettings = *new RocketSettings();
	
	rocketSettings.startSpeedMin = 1100;
	rocketSettings.startSpeedMax = 1400;
	rocketSettings.drag = 0.94;
	
	
	ParticleSystemSettings trails = getPixelTrailParticles(hue, hueChange);
	ParticleSystemSettings explosion = getPixelExplosionParticles(hue, hueChange);
	
	explosion.emitDelay = trails.emitLifeTime;
	
	rocketSettings.addParticleSystemSetting(trails);
	rocketSettings.addParticleSystemSetting(explosion);
	
	ts.addRocketSettings(&rocketSettings);
	
	rocketSettings.timeSpeed = trails.timeSpeed = explosion.timeSpeed = 0.7;
	
	
	ts.rechargeSettings = TriggerRechargeSettings::mediumMultiples;
	
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
*/
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
	explosion.doNotScale = true; 

	
	return explosion;
	
};

