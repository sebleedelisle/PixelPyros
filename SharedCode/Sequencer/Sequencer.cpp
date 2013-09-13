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
}

bool Sequencer::update() {
	if(currentSequence!=NULL) {
		currentSequence->update(*sceneManager);
	}
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
