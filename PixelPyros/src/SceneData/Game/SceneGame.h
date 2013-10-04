
#pragma once

#include "Scene.h"
#include "ParticleRendererShape.h"
#include "ParticleRendererLowRes.h"
#include "ParticleRendererCircle.h"

#include "ParticleRendererLaser.h"
#include "RocketSettings.h"
#include "ParticleSystemSettings.h"
#include "Invader.h"
#include "Asteroid.h"
#include "TriggerSettingsAsteroids.h"
#include "TriggerSettingsInvaders.h"

class SceneGame : public Scene {

	public :

	SceneGame (string scenename) ;

	bool draw();
	bool update(float deltaTime);
	void start();
	void stop();
	

	TriggerSettingsRocket* getInvaderBulletRocket(float hue = 0);
	TriggerSettingsRocket* getAsteroidsBulletRocket();
	
	void changeGame(int newgame);
	void changeState(int newstate);
	
	void updateInvaders(); 
    void checkInvaderCollisions();
	
	void checkAsteroidCollisions();
	
	void resetAsteroids(); 
	void updateAsteroids(float deltaTime);
	
	void drawStringCentered(String string, float x, float y);
	
	ParticleSystemManager& psm;
	
	unsigned int pixelSize;
    ofMesh explodeMesh;
	
	int currentGame;
	const int GAME_NONE = 0;
	const int GAME_INVADERS = 1;
	const int GAME_ASTEROIDS = 2;
	
	int gameState;
	const int STATE_INTRO = 0;
	const int STATE_PLAYING = 1;
	const int STATE_WAITING = 2;
	const int STATE_GAMEOVER = 3;
	
	float lastStateChangeTime;
	
	int level; 
	
	// ------------ INVADERS
	
	vector<Invader*> invaders;
	//vector<Invader*> spareInvaders;
	
	void makeInvaderExplosion(Invader& invader);
	void resetInvaders();
	Invader* getNewInvader(); 
	
	int activeInvaders; 
	ofImage invaderImage1;
	
	int currentUpdateInvader;
	
	/// ------------- ASTEROIDS
	void makeAsteroidExplosion(Asteroid& asteroid);

	vector<Asteroid*> asteroids;
	//vector<Asteroid*> spareAsteroids;
	int activeAsteroids;
	
	
	ofTrueTypeFont	pixelFont;
	
	
	//-----------------------
	
	TriggerSettingsRocket* getRetroRocket(float hue = -30, float hueChange = 40);
	TriggerSettingsRocket* getRetroFountain(float hueOffset = 0, float hueChange = -128, float minSpeed = 600, float maxSpeed = 900);
	
	
	ParticleSystemSettings getPixelTrailParticles(float hue = -30, float hueChange = 40);
	ParticleSystemSettings getPixelExplosionParticles(float hue = -30, float hueChange = 40);

	
};