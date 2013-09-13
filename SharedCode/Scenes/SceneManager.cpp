

#include "SceneManager.h"


SceneManager :: SceneManager() : particleSystemManager(*ParticleSystemManager::instance()), triggerManager(*TriggerManager::instance()) {
	nextFlag = false;
	previousFlag = false;

	nextPatternFlag = false;
	previousPatternFlag = false;
}

void SceneManager::addScene(Scene *scene) {
  
	scenes.push_back(scene);
	
	if(scenes.size() ==1) {
		changeScene(0);
	}
}

bool SceneManager ::update(float deltaTime){

	if(nextFlag) nextScene();
	if(previousFlag) prevScene();
	
	if(showSlideShow)
	{
		changeScene(1);
		showSlideShow = false;
	}
	
	if(currentScene!=NULL) {
		if(nextPatternFlag) nextPattern();
		if(previousPatternFlag) previousPattern();
		
		currentSceneArrangement = ofToString ( currentScene->currentTriggerPatternIndex + 1 ) ;
	}
	nextPatternFlag = previousPatternFlag = false;
	
	for(int i = 0; i<scenes.size(); i++) {
		scenes[i]->update(deltaTime);
	}
}

void SceneManager::draw() {

	for(int i = 0; i<scenes.size(); i++) {
		scenes[i]->draw();
	}
	
//	string activeSceneMap = "";
//	string activeScenetriggerPatterns = "";
//	string activeArrangementNumbers = "";
//	for(int i = 0; i<scenes.size(); i++) {
//		Scene* scene = scenes[i];
//
//		//activeSceneMap += (scene->active ? "1 " : "0 ");
//		//activeScenetriggerPatterns += ofToString(scene->activetriggerPatterns)+" ";
//		//activeArrangementNumbers += ofToString(scene->currentArrangementIndex)+" ";
//	}
//	ofDrawBitmapString(ofToString(currentSceneIndex), 20,85);
//	ofDrawBitmapString(activeSceneMap,20,100);
//	ofDrawBitmapString(activeArrangementNumbers,20,115); ;

	
	
}
/*
void SceneManager ::updateMotion(MotionManager& motionManager, cv::Mat homography){
	
	if(currentScene!=NULL) currentScene->updateMotion(motionManager, homography); 

}*/
/*
void SceneManager::updateTriggerSettings(ofRectangle triggerarea, float spacing) {
	triggerSpacing = spacing;
	for ( int i = 0; i<scenes.size(); i++ ) {
		scenes[i]->updateTriggerSettings(triggerarea, spacing);
		
	}
}

void SceneManager::updateTriggerDebug(bool debug) {
	
	triggerShowDebug = debug;
	
	for ( int i = 0; i<scenes.size(); i++ ) {
		scenes[i]->setShowTriggerDebug (debug) ;
	}
}

void SceneManager::setTriggersDisabled(bool disabled) {
	
	triggersDisabled = disabled;
	
	for ( int i = 0; i<scenes.size(); i++ ) {
		scenes[i]->setTriggersDisabled (disabled) ;
	}
}
*/
bool SceneManager :: changeScene(int sceneIndex) {

	if(sceneIndex>=scenes.size()) return false;
	else return changeScene(scenes[sceneIndex]);
		
		
}

bool SceneManager :: changeScene(string scenename) {
	
	for(int i =0; i<scenes.size(); i++) {
		
		Scene *scene = scenes[i];
		if(scene->name == scenename) return changeScene(scene);
		
		
	}
	
	return false; 
	
	
}



bool SceneManager :: changeScene (Scene* scene) {

	if(scene == NULL ) return false;
	if(currentScene == scene) return false;
	
	int newSceneIndex = -1;
	
	for(int i = 0 ; i<scenes.size(); i++) {
		if(scenes[i] == scene) {
			newSceneIndex = i;
			scene->start();
			currentSceneIndex = newSceneIndex;
			currentScene = scene;
			currentSceneName = scene->name ;
			triggerManager.setPattern(currentScene->getCurrentTriggerPattern());

		} else {
			scenes[i]->stop();
		}
		
	}
	if(newSceneIndex == -1) {
		ofLog(OF_LOG_ERROR,"SceneManager :: changeScene - scene not found!");
		currentScene = NULL;
		currentSceneIndex = -1;
		return false;
	}
	
	return true;
}

bool SceneManager::nextScene(){
	
	nextFlag = false;

	if(currentSceneIndex == scenes.size()-1) {
		return false;
	} else {
		return changeScene(currentSceneIndex+1);

	}
	
}

bool SceneManager::prevScene(){
	
	previousFlag = false;
	if(currentSceneIndex == 0) {
		return false;
	} else {
		return changeScene(currentSceneIndex-1);
	}
	
}

bool SceneManager::changeTriggerPattern(int patternNum) {
	if(currentScene == NULL) return false;
	
	currentScene->changeTriggerPattern(patternNum);

	triggerManager.setPattern(currentScene->getCurrentTriggerPattern());

	return true; 
}


bool SceneManager::nextPattern(){
	if(currentScene == NULL) return false;
	
	currentScene->next();
	
	triggerManager.setPattern(currentScene->getCurrentTriggerPattern());
		
	return true;
}

bool SceneManager::previousPattern(){
	if(currentScene == NULL) return false;
	currentScene->previous();
	
	triggerManager.setPattern(currentScene->getCurrentTriggerPattern());
	return true;

	
}

void SceneManager::initSceneControls(SettingsManager & settingsManager) {
	
	settingsManager.addSettingString(&currentSceneName, "/PixelPyros/SceneData/content" );
	settingsManager.addSettingString(&currentSceneArrangement, "/PixelPyros/SceneArrangement/content" );
	
	settingsManager.addSettingBool(&showSlideShow, "", "/PixelPyros/Scenes/Restart/x", true, true);
	
	for(int i = 0; i<scenes.size(); i++) {

		Scene & scene = *scenes[i];
		
		
		for(int j = 0; j<scene.triggerPatterns.size(); j++) {
		
			settingsManager.addSettingBool(scene.triggerPatternChangeTriggers[j], "", "/PixelPyros/Scenes/"+scene.name+"Arr"+ofToString(j+1)+"/x", true, true);
			cout << "adding " << "/PixelPyros/Scenes/"+scene.name+"Arr"+ofToString(j+1)+"/x control"<< endl;
	
		}
		
		
	}
	
	
}


