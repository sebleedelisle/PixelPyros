

#include "SceneManager.h"


SceneManager :: SceneManager() : particleSystemManager(*ParticleSystemManager::instance()), triggerManager(*TriggerManager::instance()) {
	
	nextFlag = false;
	previousFlag = false;
	nextPatternFlag = false;
	previousPatternFlag = false;
	
	currentScene = NULL;
	
	showInterface = true;
	dragPlayHead = false;
	
	ofAddListener(ofEvents().mousePressed, this, &SceneManager::mousePressed);
	ofAddListener(ofEvents().mouseDragged, this, &SceneManager::mouseDragged);
	ofAddListener(ofEvents().mouseReleased, this, &SceneManager::mouseReleased);
	ofAddListener(ofEvents().keyPressed, this, &SceneManager::keyPressed);
	
	playHeadRect = ofRectangle(0,0,20,20);

}

void SceneManager::addScene(Scene *scene) {
  
	scenes.push_back(scene);
	scene->triggerManager = &triggerManager;
	
	if(scenes.size() ==1) {
		changeScene(0);
	}
}

bool SceneManager ::update(float deltaTime){

	if(nextFlag) nextScene();
	if(previousFlag) prevScene();
	
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
	
	if(!showInterface) return;
	if(currentScene==NULL) return;
	
	ofPushStyle();
	ofFill();
	ofSetColor(100,120,255);
	ofRect(0,APP_HEIGHT-4,APP_WIDTH,4);
	
	float pos = ofMap(currentScene->positionSeconds,0,currentScene->lengthSeconds,0,APP_WIDTH);
	ofNoFill();
	ofSetLineWidth(2);
	
	playHeadRect.setPosition(pos-10,APP_HEIGHT-20);
	//
	
	ofSetColor(128);
	vector <SequenceCommand>& commands = currentScene->commands;
	for(int i = 0; i<commands.size(); i++) {
		if(!commands[i].enabled) continue;
		float pos = ofMap(commands[i].time, 0, currentScene->lengthSeconds, 0, APP_WIDTH);
		ofLine(pos, APP_HEIGHT-20,pos,APP_HEIGHT);
		
	}
	
	ofSetColor(255);
	if((currentScene) && (currentScene->recording)) ofSetColor(ofColor::red);
	
	ofRect(playHeadRect);
	ofLine(pos, APP_HEIGHT-20,pos,APP_HEIGHT-15);
	ofLine(pos, APP_HEIGHT-5,pos,APP_HEIGHT);
	
	ofDrawBitmapString(ofToString(currentScene->positionSeconds, 2), pos-12,APP_HEIGHT-28);
	
	ofPopStyle();

	
}

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

	

	return true; 
}


bool SceneManager::nextPattern(){
	if(currentScene == NULL) return false;
	
	currentScene->next();
	
	//triggerManager.setPattern(currentScene->getCurrentTriggerPattern());
		
	return true;
}

bool SceneManager::previousPattern(){
	if(currentScene == NULL) return false;
	currentScene->previous();
	
	//triggerManager.setPattern(currentScene->getCurrentTriggerPattern());
	return true;

	
}






bool SceneManager::toggleShowInterface() {
	showInterface = !showInterface;
	return showInterface;
	
	
}

bool SceneManager::togglePlayPause(){
	if (!currentScene) return false;
	return currentScene->togglePlayPause();
}

bool SceneManager::toggleRecord(){
	if((!showInterface) || (!currentScene)) return false;
	return currentScene->toggleRecord();
}


void SceneManager :: mousePressed(ofMouseEventArgs &e) {
	
	if(!showInterface) return;
	if(!currentScene) return;
	
	ofVec2f cur(e.x, e.y);
	if(playHeadRect.inside(cur)) {
		dragPlayHead = true;
		playHeadClickOffset = cur - (playHeadRect.getPosition()+10);
		if(currentScene->playing) currentScene->togglePlayPause();
		
	}
	
	
};


void SceneManager :: mouseDragged(ofMouseEventArgs &e) {
	if(!showInterface) return;
	if(!currentScene) return;
	
	
	if(dragPlayHead) {
		
		//playHeadRect.setPosition(ofPoint(e.x, e.y) - playHeadClickOffset);
		
		//currentSequence->positionSeconds = ofMap(e.x, 0, APP_WIDTH, 0, currentSequence->lengthSeconds);
		
		currentScene->goToTime(ofMap(e.x-playHeadClickOffset.x, 0, APP_WIDTH, 0, currentScene->lengthSeconds));
	}
	
	/*
	 if(movingPoint) {
	 
	 ofVec2f diff(e.x, e.y);
	 diff-=dragStartPoint;
	 diff*=0.3;
	 
	 
	 *curPoint = dragStartPoint+diff+clickOffset;
	 //curPoint+=clickOffset;
	 
	 changed = true;
	 
	 }
	 */
};



void SceneManager :: mouseReleased(ofMouseEventArgs &e) {
	dragPlayHead = false;
	
	if(!showInterface) return;
	
};



void SceneManager :: keyPressed(ofKeyEventArgs &e) {
	if(!showInterface) return;
	if(!currentScene) return;
	
	int newPattern = -1; 
	if(e.key==' ') {
		togglePlayPause();
	} else if(e.key=='r') {
		toggleRecord();
	} else if(e.key=='0') {
		currentScene->changeTriggerPattern(newPattern = 0);
		} else if(e.key=='1') {
		currentScene->changeTriggerPattern(newPattern = 1);
		} else if(e.key=='2') {
		currentScene->changeTriggerPattern(newPattern = 2);
	} else if(e.key=='3') {
		currentScene->changeTriggerPattern(newPattern = 3);
	}
	
	if((currentScene->recording) && (newPattern>=0) ){
		currentScene->addCommand((float)currentScene->lastUpdate, SEQ_PATTERN_CHANGE, newPattern);
		cout << currentScene->positionSeconds << " " << newPattern << endl;

	}
	
};





// Here's the bit that gets all the patterns out of the scenes for the old OSC controller.
// Don't think we need it now, but keeping it just in case.

/*
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

*/
