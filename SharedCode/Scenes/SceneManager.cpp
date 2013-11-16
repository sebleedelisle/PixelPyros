

#include "SceneManager.h"


SceneManager :: SceneManager() : particleSystemManager(*ParticleSystemManager::instance()), triggerManager(*TriggerManager::instance()) {
	
	nextFlag = false;
	previousFlag = false;
	nextPatternFlag = false;
	previousPatternFlag = false;
	
	currentScene = NULL;
	
	showInterface = true;
	dragPlayHead = false;
	dragCommandIndex = -1;
	mouseOverCommandIndex =-1; 
	
	ofAddListener(ofEvents().mousePressed, this, &SceneManager::mousePressed);
	ofAddListener(ofEvents().mouseDragged, this, &SceneManager::mouseDragged);
	ofAddListener(ofEvents().mouseReleased, this, &SceneManager::mouseReleased);
	ofAddListener(ofEvents().keyPressed, this, &SceneManager::keyPressed);
	ofAddListener(ofEvents().keyReleased, this, &SceneManager::keyReleased);
	
	parameters.add(musicVolume.set("music volume", 0.7,0,1));
	
	playHeadRect = ofRectangle(0,0,20,20);
	altPressed = false;
	shiftPressed = false;

}

void SceneManager::addScene(Scene *scene) {
  
	scenes.push_back(scene);
	scene->triggerManager = &triggerManager;
	
	if(scenes.size() ==1) {
		changeScene(0);
	}
    
    scene->load();

}

bool SceneManager ::update(float deltaTime){

	if(nextFlag) nextScene();
	if(previousFlag) prevScene();
	
	if(currentScene!=NULL) {
		
		if(dragPlayHead) currentScene->finished = false;
			
		if(nextPatternFlag) nextPattern();
		if(previousPatternFlag) previousPattern();
		
		currentSceneArrangement = ofToString ( currentScene->currentTriggerPatternIndex + 1 ) ;
		if((currentScene->finished) && (autoPlayNext) ) {
			if(nextScene()) {
				currentScene->togglePlayPause();
			}

		}
		
		
		
	}

	autoSave(); 
	
	nextPatternFlag = previousPatternFlag = false;
	
	for(int i = 0; i<scenes.size(); i++) {
		scenes[i]->update(deltaTime);
		scenes[i]->setMusicVolume(musicVolume);
	}
	
	
	if((!dragPlayHead) && (dragCommandIndex==-1)) {
		mouseOverCommandIndex = getCommandIndexAtPosition(ofPoint(ofGetMouseX(), ofGetMouseY()));
	} else {
		mouseOverCommandIndex = -1;
		
	}
	
}

void SceneManager::draw() {

	for(int i = 0; i<scenes.size(); i++) {
		scenes[i]->draw();
	}
	
}


bool SceneManager:: autoSave() {
	// save
	
	if((currentScene!=NULL) && (currentScene->playing)) {
		if (ofGetElapsedTimef() - lastAutoSave > 1.0f){
			// save position ***
			// position is currentScene->positionSeconds
			// scene index is currentSceneIndex
			
            
			lastAutoSave = ofGetElapsedTimef();
			
            autoSaveXml.clear();
            autoSaveXml.addTag("sceneIndex");
            autoSaveXml.setValue("sceneIndex", currentSceneIndex);
            
            autoSaveXml.addTag("position");
            autoSaveXml.setValue("position", currentScene->positionSeconds);
            
            autoSaveXml.saveFile("autosave.xml");
            
			return true;
		
		}
		
	} else {
		
        ofFile autoSaveFile("autosave.xml");
        autoSaveFile.remove();
        
		// delete file
	}
	return false;
	
}

void SceneManager:: resumeAutoSave(){
        
    currentSceneIndex = autoSaveXml.getValue("sceneIndex", 0);
    currentScene->positionSeconds = autoSaveXml.getValue("position", 0.0);
    
    
}

bool SceneManager :: checkAutoSave() {
    return autoSaveXml.loadFile("autosave.xml");
}


void SceneManager :: drawGUI() {
	
	if(!showInterface) return;
	if(currentScene==NULL) return;
	if(!currentScene->music.isLoaded()) return;
	ofPushStyle();
	ofFill();
	ofSetColor(25,15,64);
	ofRect(timeBarRect);
	ofSetColor(100,120,255);
	ofRect(timeBarRect.x, timeBarRect.y+timeBarRect.height-2,timeBarRect.width, 2);

	
	
	ofNoFill();
	ofSetLineWidth(2);
	
	
	playHeadRect.setPosition(getPositionForTime(currentScene->positionSeconds)-playHeadRect.width/2,timeBarRect.getTop()-1);
	
	
	ofSetColor(128);
	vector <SequenceCommand>& commands = currentScene->commands;
	for(int i = 0; i<commands.size(); i++) {
		if(!commands[i].enabled) continue;
		
		float pos = getPositionForTime(commands[i].time);
		
		ofRectangle commandRect = (getRectangleForCommand(i));
		
		
		if(i==dragCommandIndex) {
			ofSetColor(255,0,255);
			ofFill();
			
			if(timeBarRect.y - ofGetMouseY() > 100) {
				commandRect.y = ofGetMouseY()-(commandRect.height/2); 
				
			}
			
			ofRect(commandRect);
			ofSetColor(0);
			ofDrawBitmapString(ofToString(commands[i].arg1), commandRect.x, commandRect.getTop()+12);
			
		} else if(i==mouseOverCommandIndex) {
			ofSetColor(255);
			ofFill();
			
			ofRect(commandRect);
			ofSetColor(0);
			ofDrawBitmapString(ofToString(commands[i].arg1), commandRect.x, commandRect.getTop()+12);
		} else {
			ofSetColor(186);
			ofDrawBitmapString(ofToString(commands[i].arg1), commandRect.x, commandRect.getTop()+12);
			ofLine(pos, timeBarRect.getTop(),pos,timeBarRect.getBottom());
		}
		ofNoFill(); 
		
		
	}
	
	ofSetColor(255);
	if((currentScene) && (currentScene->recording)) ofSetColor(ofColor::red);
	else if((currentScene) && (currentScene->finished)) ofSetColor(ofColor::gray);
	
	ofRect(playHeadRect);
	ofLine(playHeadRect.getCenter().x, timeBarRect.getTop()-1,playHeadRect.getCenter().x, timeBarRect.getTop()+4);
	ofLine(playHeadRect.getCenter().x, timeBarRect.getBottom()-4,playHeadRect.getCenter().x,timeBarRect.getBottom()+1);
	
	ofDrawBitmapString(ofToString(currentScene->positionSeconds, 2) + " " +ofToString(mouseOverCommandIndex), playHeadRect.getCenter().x-12,screenUI.getBottom()-28);
	
	/*
	 ofSetLineWidth(20);
	 ofFill();
	 ofRect(screenUI);
	 
	 ofRect(ofGetMouseX(), ofGetMouseY(), 20,20);
	 */
	ofPopStyle();

	
}

void SceneManager::exit(){
    if( currentScene != NULL ) currentScene->save();
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

	if( currentScene != NULL ) currentScene->save();
    
	int newSceneIndex = -1;
	
	for(int i = 0 ; i<scenes.size(); i++) {
		if(scenes[i] == scene) {
			newSceneIndex = i;
			scene->start();
			currentSceneIndex = newSceneIndex;
			currentScene = scene;
			currentSceneName = scene->name ;
			//triggerManager.setPattern(currentScene->getCurrentTriggerPattern());
			currentScene->changeTriggerPattern(0);


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


string SceneManager::getCurrentSceneName(){
	
	if(currentScene!=NULL)
		return currentScene->name;
	else return "no scene"; 
	
}
string SceneManager::getCurrentTriggerPatternName(){
	
	if(currentScene!=NULL)
		return currentScene->getTriggerPatternName();
	else return "no scene";
	
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
		dragClickOffset = playHeadRect.getCenter() - cur;
		if(currentScene->playing) currentScene->togglePlayPause();
		
	} else {
	
		int commandIndex = getCommandIndexAtPosition(cur);
		if(commandIndex!=-1) {
			dragCommandIndex = commandIndex;
			dragClickOffset = getRectangleForCommand(dragCommandIndex).getCenter() - cur;
			mouseOverCommandIndex = -1;
		}
		
		
		
	}
	
	
	
};


void SceneManager :: mouseDragged(ofMouseEventArgs &e) {
	if(!showInterface) return;
	if(!currentScene) return;
	
	
	if(dragPlayHead) {
		
		currentScene->goToTime(getTimeForPosition(e.x+ dragClickOffset.x) );
		
		
	} else if(dragCommandIndex>-1){
		
		currentScene->commands[dragCommandIndex].time = getTimeForPosition(e.x+dragClickOffset.x);
		
		
		
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
	if((dragCommandIndex>-1)&&(currentScene!=NULL)){
		
		if(timeBarRect.y - ofGetMouseY() > 100) {
			
			 currentScene->disableCommand(dragCommandIndex);
			//currentScene->commands[dragCommandIndex].enabled = false;
			
			//if(getCommand(i)) {
			//	getCommand(i)->enabled = false;
				// SAVE HERE FOR UNDO AND AUTOSAVE
			//}
		}
		currentScene->updateCommands();
		
	}
	
	dragCommandIndex = -1; 
	
	if(!showInterface) return;
	
};


int SceneManager :: getCommandIndexAtPosition(ofPoint pos) {
	
	if(currentScene == NULL) return -1;
	
	for(int i = 0; i<currentScene->commands.size(); i++) {
		
		if(getRectangleForCommand(currentScene->commands[i]).inside(pos)){
			return i;
		}
		
	}
	
	
}
ofRectangle SceneManager::getRectangleForCommand(int i) {
	
	if(currentScene == NULL) return ofRectangle();
	else if((currentScene->commands.size()<=i) || (i<0)) return ofRectangle();
	else return getRectangleForCommand(currentScene->commands[i]);
	
}
ofRectangle SceneManager::getRectangleForCommand(SequenceCommand& command) {
	
	ofRectangle rect(0,timeBarRect.getTop()-12,8,timeBarRect.height+12);
	rect.x = getPositionForTime(command.time)-4;
	
	return rect;
	
}



float SceneManager::getTimeForPosition(float position) {
	
	return ofMap(position, timeBarRect.getLeft(), timeBarRect.getRight(), 0, currentScene->lengthSeconds);
}

float SceneManager:: getPositionForTime(float time){
	
	return ofMap(time,0,currentScene->lengthSeconds, timeBarRect.getLeft(),timeBarRect.getRight());
	
	
}


void SceneManager :: keyPressed(ofKeyEventArgs &e) {
	if(!showInterface) return;
	if(!currentScene) return;
	
	//bool shiftPressed = (glutGetModifiers() & GLUT_ACTIVE_SHIFT);
	if(e.key == OF_KEY_SHIFT) {
        shiftPressed = true;
    }
	
	if(e.key == OF_KEY_ALT){
        altPressed = true;
    }
	cout << altPressed << " " << shiftPressed<< endl;
	
	int newPattern = -1; 
	if(e.key==' ') {
		if(currentScene!=NULL) {
			if(currentScene->finished) {
				nextScene();
			}
			
			togglePlayPause();
		}
	} else if(e.key=='r') {
		toggleRecord();
	} 
	
	if(!shiftPressed) {
		if(!altPressed) {
			if(e.key=='0') {
				currentScene->changeTriggerPattern(newPattern = 0);
			} else if(e.key=='1') {
				currentScene->changeTriggerPattern(newPattern = 1);
			} else if(e.key=='2') {
				currentScene->changeTriggerPattern(newPattern = 2);
			} else if(e.key=='3') {
				currentScene->changeTriggerPattern(newPattern = 3);
			}else if(e.key=='4') {
				currentScene->changeTriggerPattern(newPattern = 4);
			}else if(e.key=='5') {
				currentScene->changeTriggerPattern(newPattern = 5);
			}else if(e.key=='6') {
				currentScene->changeTriggerPattern(newPattern = 6);
			}else if(e.key=='7') {
				currentScene->changeTriggerPattern(newPattern = 7);
			}else if(e.key=='8') {
				currentScene->changeTriggerPattern(newPattern = 8);
			}else if(e.key=='9') {
				currentScene->changeTriggerPattern(newPattern = 9);
			}
		} else {
			if(e.key=='0') {
				currentScene->changeTriggerPattern(newPattern = 10);
			} else if(e.key=='1') {
				currentScene->changeTriggerPattern(newPattern = 11);
			} else if(e.key=='2') {
				currentScene->changeTriggerPattern(newPattern = 12);
			} else if(e.key=='3') {
				currentScene->changeTriggerPattern(newPattern = 13);
			}else if(e.key=='4') {
				currentScene->changeTriggerPattern(newPattern = 14);
			}else if(e.key=='5') {
				currentScene->changeTriggerPattern(newPattern = 15);
			}else if(e.key=='6') {
				currentScene->changeTriggerPattern(newPattern = 16);
			}else if(e.key=='7') {
				currentScene->changeTriggerPattern(newPattern = 17);
			}else if(e.key=='8') {
				currentScene->changeTriggerPattern(newPattern = 18);
			}else if(e.key=='9') {
				currentScene->changeTriggerPattern(newPattern = 19);
			}
			
			
		}
	}
	
	if((currentScene->recording) && (newPattern>=0) ){
		currentScene->addCommand((float)currentScene->lastUpdate, SEQ_PATTERN_CHANGE, newPattern);
		//cout << currentScene->positionSeconds << " " << newPattern << endl;

	}
	
};

void SceneManager::keyReleased(ofKeyEventArgs &e){
	if(e.key == OF_KEY_SHIFT) shiftPressed = false;
	if(e.key == OF_KEY_ALT) altPressed = false;
}

void SceneManager :: updateUIScreen(ofRectangle screen){
	screenUI = screen;
	timeBarRect.set(screen.x+playHeadRect.width/2, screen.getBottom()-playHeadRect.height-1,screen.width - playHeadRect.width, playHeadRect.height-2);
	//cout << "SCENE MANAGER UPDATE SCREEN " << screen << endl; 

}


