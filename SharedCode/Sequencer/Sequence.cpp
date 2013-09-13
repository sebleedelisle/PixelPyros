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


}

void Sequence :: setup(string scenename, string musicfile){
	
	sceneName = scenename;
	// TODO should probably separate path from file name? 
	musicFile = "music/"+musicfile;

}


void Sequence :: start(){
	
	if(!music.isLoaded()) music.loadSound(musicFile);
	music.setPosition(0);
	music.play();
	lastUpdate = 0; 
}

void Sequence :: stop(){
	music.stop();
}

void Sequence :: update(SceneManager& sm){
	
	float currentTime = (float)music.getPositionMS()/1000.0f;
	
		for(int i = 0; i<commands.size(); i++) {
			
		SequenceCommand command = commands[i];
		if((command.time>=lastUpdate) && (command.time<currentTime)) {
			
			processCommand(command, sm);
			
			
		}
		
		
	}
	
	lastUpdate = currentTime;
	
}

void Sequence :: processCommand(SequenceCommand command, SceneManager& sm) {
	cout << "PROCESS COMMAND "<<endl;
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
	else music.play();
	playing = !playing;
	return playing; 
}

void Sequence :: goToTime(float time){
	music.setPosition(time);
	
	//TODO CYCLE THROUGH MESSAGES
	
}

void Sequence :: setSpeed(float speed){
	//TODO IMPLEMENT SPEED
	
}