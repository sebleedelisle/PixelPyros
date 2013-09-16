//
//  Sequence.cpp
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 13/09/2013.
//
//

#include "Sequence.h"

Sequence :: Sequence(string sequencename) {

	playing = false;
	name = sequencename;
	//cout << " MUSIC LOADING " << music.loadSound("music/02 In Motion.aif") << endl;
	positionSeconds = 0;
	sceneManager = NULL;
	music.setVolume(0.1);

}

void Sequence :: setup(string scenename, string musicfile){
	
	sceneName = scenename;
	// TODO should probably separate path from file name? 
	musicFile = "../../../Music/"+musicfile;

}


void Sequence :: start(){
	
	if(!music.isLoaded()) {
		music.loadSound(musicFile);
		music.play();
		music.setPosition(0.9999999f);
		int ms = music.getPositionMS();
		lengthSeconds = (float)ms/1000.0f;
	}
	music.setPosition(0);
	positionSeconds = 0; 
	music.play();
	lastUpdate = 0;
	
	playing = true;
}

void Sequence :: stop(){
	music.stop();
}

void Sequence :: update(SceneManager& sm){
	sceneManager = &sm;
	
	if(!playing) return;
		
	positionSeconds = (float)music.getPositionMS()/1000.0f;
	
	for(int i = 0; i<commands.size(); i++) {
			
		SequenceCommand command = commands[i];
		if((command.time>=lastUpdate) && (command.time<positionSeconds)) {
			
			processCommand(command, sm);
			
			
		}
		
		
	}
	
	lastUpdate = positionSeconds;
	
}

void Sequence :: processCommand(SequenceCommand command, SceneManager& sm) {
	cout << "PROCESS COMMAND "<< command.arg1 << endl;
	if(command.type == SEQ_PATTERN_CHANGE) {
		sm.changeTriggerPattern(command.arg1);
		
	}
	
	
}


SequenceCommand Sequence :: addCommand(int time, SequenceCommandType type, int arg){
	
	SequenceCommand cmd(type, time, arg);
	commands.push_back(cmd);
	
	return cmd; 
	
}




bool Sequence :: togglePause(){
	if(playing) music.stop();
	else {
		music.play();
		music.setPositionMS(positionSeconds*1000);

	}
	
	playing = !playing;
	return playing; 
}

void Sequence :: goToTime(float timeSeconds){
	music.setPositionMS(timeSeconds*1000);
	positionSeconds = timeSeconds; 
	
	//TODO CYCLE THROUGH MESSAGES
	float lastPosition = 0;
	SequenceCommand* lastCommand = NULL;
	
	for(int i = 0; i<commands.size(); i++) {
		SequenceCommand c = commands[i];
		if((c.time>=lastPosition) && (c.time<timeSeconds)) {
			
			lastCommand = &commands[i];
			lastPosition = c.time;
			cout << i<<" " <<c.time << " " << timeSeconds << endl;
		}
		
	}
	
	if(lastCommand!=NULL) {
		cout << lastCommand->time << " " << lastCommand->arg1 << endl;
		processCommand(*lastCommand, *sceneManager);
		lastUpdate = timeSeconds;
	}
}

void Sequence :: setSpeed(float speed){
	//TODO IMPLEMENT SPEED
	
}