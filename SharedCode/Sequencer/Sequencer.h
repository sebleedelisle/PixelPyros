//
//  Sequencer.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 13/09/2013.
//
//

#pragma once

#include "Sequence.h"
#include "SequenceCommand.h"

class Sequencer {

	public :
	
	Sequencer(SceneManager* sm);
	
	Sequence* loadSequence(string name, string scenename, string musicfile);
	Sequence* setupSequence(Sequence * seq, string scenename, string musicfile);

	
	void runSequence(string name);
	void runSequence(Sequence* );
	
	bool pauseCurrentSequence();
	bool toggleShowInterface(); 
	
	bool update();
	void draw();
	
	void mousePressed(ofMouseEventArgs &e);
	void mouseDragged(ofMouseEventArgs &e);
	void mouseReleased(ofMouseEventArgs &e);
	void keyPressed(ofKeyEventArgs &e);


	map <string, Sequence*> sequences;
	
	Sequence* currentSequence;
	
	SceneManager* sceneManager; 

	bool showInterface;
	bool dragPlayHead;
	ofPoint playHeadClickOffset; 
	ofRectangle playHeadRect; 
	
};