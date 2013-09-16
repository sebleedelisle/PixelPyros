//
//  Sequencer.cpp
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 13/09/2013.
//
//

#include "Sequencer.h"


Sequencer :: Sequencer(SceneManager* sm) {
	currentSequence = NULL;
	sceneManager = sm;
	showInterface = true;
	dragPlayHead = false; 
	
	ofAddListener(ofEvents().mousePressed, this, &Sequencer::mousePressed);
	ofAddListener(ofEvents().mouseDragged, this, &Sequencer::mouseDragged);
	ofAddListener(ofEvents().mouseReleased, this, &Sequencer::mouseReleased);
	ofAddListener(ofEvents().keyPressed, this, &Sequencer::keyPressed);

	playHeadRect = ofRectangle(0,0,20,20);
}

bool Sequencer::update() {
	if(currentSequence!=NULL) {
		currentSequence->update(*sceneManager);
	}
}

void Sequencer::draw() {
	
	if(!showInterface) return;
	if(currentSequence==NULL) return;
	
	ofPushStyle();
	ofFill();
	ofSetColor(100,120,255);
	ofRect(0,APP_HEIGHT-4,APP_WIDTH,4);
	
	float pos = ofMap(currentSequence->positionSeconds,0,currentSequence->lengthSeconds,0,APP_WIDTH);
	ofNoFill();
	ofSetLineWidth(2);

	playHeadRect.setPosition(pos-10,APP_HEIGHT-20);
//	
	
	ofSetColor(128);
	vector <SequenceCommand>& commands = currentSequence->commands;
	for(int i = 0; i<commands.size(); i++) {
		float pos = ofMap(commands[i].time, 0, currentSequence->lengthSeconds, 0, APP_WIDTH);
		ofLine(pos, APP_HEIGHT-20,pos,APP_HEIGHT);
		
	}
	
	ofSetColor(255);

	ofRect(playHeadRect);
	ofLine(pos, APP_HEIGHT-20,pos,APP_HEIGHT-15);
	ofLine(pos, APP_HEIGHT-5,pos,APP_HEIGHT);

	ofDrawBitmapString(ofToString(currentSequence->positionSeconds, 2), pos-12,APP_HEIGHT-28);
	
	ofPopStyle();
	
	
}


bool Sequencer::toggleShowInterface() {
	showInterface = !showInterface;
	return showInterface;
	
	
}


Sequence* Sequencer:: loadSequence(string name, string scenename, string musicfile) {
	
	// test sequence!
	Sequence* seq = sequences[name];
	
	if(seq==NULL) {
		//ofLog(OF_LOG_ERROR, "sequence already loaded");
		//return sequences[name];
		seq = new Sequence(name);
		sequences[name] = seq;
	}
	
	setupSequence(seq, scenename, musicfile);

	currentSequence = seq;
	
	return seq;
		
}

Sequence* Sequencer:: setupSequence(Sequence *seq, string scenename, string musicfile) {
	
	seq->setup(scenename, musicfile); 
	
}


void Sequencer :: runSequence(string name) {
	
	Sequence* seq = sequences[name];
	if(seq==NULL) {
		ofLogError() <<  "Couldn't find sequence name : " << name << endl;
		return;
	}
	
	if(currentSequence==seq) {
		if(!currentSequence->playing) runSequence(currentSequence);
		return;
	}
	if (currentSequence!=NULL) {
		currentSequence->stop();
	}
	
	runSequence(seq);
	 
	
}

void Sequencer::runSequence(Sequence* sequence) {
	
	sceneManager->changeScene(sequence->sceneName); 
	sequence->start();
	
	currentSequence = sequence;
}

bool Sequencer :: pauseCurrentSequence() {
	
	if(currentSequence!=NULL) {
		return currentSequence->togglePause();
	}
	return false;
	
}


void Sequencer :: mousePressed(ofMouseEventArgs &e) {
	
	if(!showInterface) return;
	if(!currentSequence) return;
	
	ofVec2f cur(e.x, e.y);
	if(playHeadRect.inside(cur)) {
		dragPlayHead = true;
		playHeadClickOffset = cur - playHeadRect.getPosition();
		if(currentSequence->playing) currentSequence->togglePause(); 
		
	}
	
	
};


void Sequencer :: mouseDragged(ofMouseEventArgs &e) {
	if(!showInterface) return;
	if(!currentSequence) return;

	
	if(dragPlayHead) {
		
		//playHeadRect.setPosition(ofPoint(e.x, e.y) - playHeadClickOffset);
		
		//currentSequence->positionSeconds = ofMap(e.x, 0, APP_WIDTH, 0, currentSequence->lengthSeconds);
		
		currentSequence->goToTime(ofMap(e.x, 0, APP_WIDTH, 0, currentSequence->lengthSeconds));
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



void Sequencer :: mouseReleased(ofMouseEventArgs &e) {
	dragPlayHead = false;
	
	if(!showInterface) return;
	
	/*
	 if(movingPoint) {
	 movingPoint = false;
	 changed = true;
	 }
	 
	 
	 saveSettings();
	 //loadSettings();
	 */
	
};



void Sequencer :: keyPressed(ofKeyEventArgs &e) {
	if(!showInterface) return;
	if(!currentSequence) return;
	
	if(e.key==' ') {
		currentSequence->togglePause();
	}
	
	/*
	 if(movingPoint) {
	 movingPoint = false;
	 changed = true;
	 }
	 
	 
	 saveSettings();
	 //loadSettings();
	 */
	
};



