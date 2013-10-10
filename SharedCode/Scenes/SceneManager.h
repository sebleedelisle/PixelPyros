

#pragma once 

#include "Scene.h"
#include "ParticleSystemManager.h"
#include "TriggerManager.h"

class SceneManager {

public :
	
	SceneManager();
	
	void addScene(Scene * scene);
    
	bool changeScene(int sceneIndex);
	bool changeScene(Scene * scene);
	bool changeScene(string scenename);
	bool nextScene();
	bool prevScene();
	
	bool update(float deltaTime);
	void draw();
	void drawGUI(); 
    void exit();
	
	bool nextPattern();
	bool previousPattern();
	bool changeTriggerPattern(int patternNum);
	
	bool togglePlayPause();
	bool toggleShowInterface();
	bool toggleRecord();

	
	void mousePressed(ofMouseEventArgs &e);
	void mouseDragged(ofMouseEventArgs &e);
	void mouseReleased(ofMouseEventArgs &e);
	void keyPressed(ofKeyEventArgs &e);
	
	void updateUIScreen(ofRectangle screen);
	
	ofRectangle screenUI;

	vector <Scene*> scenes;
	
	int currentSceneIndex;
	Scene * currentScene;
	string currentSceneName;
	string currentSceneArrangement;

	bool nextFlag;
	bool previousFlag; 
	bool nextPatternFlag;
	bool previousPatternFlag;
		
	ParticleSystemManager & particleSystemManager;
	TriggerManager & triggerManager;
	
	ofParameter<float> musicVolume;
	ofParameterGroup parameters;
	
	
	bool showInterface;
	
	bool dragPlayHead;
	ofPoint playHeadClickOffset;
	ofRectangle playHeadRect;
	// time bar is the track along the bottom
	ofRectangle timeBarRect;

	
	
    
};