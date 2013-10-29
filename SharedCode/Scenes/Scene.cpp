//
//  Scene.cpp
//  SceneCalibration
//
//  Created by Seb Lee-Delisle on 02/08/2012.
//  Copyright (c) 2012 seb.ly. All rights reserved.
//

#include "Scene.h"
#include <stdio.h>

Scene::Scene(string scenename) {
	active = false;
	//stopping = false;
	
	triggerManager = NULL;
	
	currentTriggerPatternIndex = 0;
	//activeTriggerPatterns = 0;
	
	name = scenename;
	
	playing = false;
	recording = false;
	overwriteMode = false; 
	positionSeconds = 0;
	lengthSeconds = 1;

    _addCommand(0, SEQ_PATTERN_CHANGE, 0);
}
void Scene :: loadMusicFile(string musicfile){
	
	musicFile = "../../../Music/"+musicfile;
	
	music.loadSound(musicFile);
	// ridiculous hack to get the sound file length #facepalm
	music.play();
	music.setPosition(0.9999999f);
	int ms = music.getPositionMS();
	lengthSeconds = (float)ms/1000.0f;
	music.stop();
	
	
}

void Scene :: start() {
	//stopping = false;
	//if ((triggerPatterns.size()==0)|| (changeTriggerPattern(0))) active = true;
	playing = false; 
	if(music.isLoaded()) {
		music.setPosition(0);
		positionSeconds = 0;
		//music.play();
		lastUpdate = 0;
		
		//playing = true;
	}
	active = true;
}

void Scene :: stop() { 
	
	// TODO : tell triggerManager to stop the triggers
	if(music.isLoaded())
		music.stop(); 
	
	active = false; 
}

bool Scene :: update(float deltaTime) {

	
	// WHAT DOES THIS HAVE TO DO NOW?
	// MAYBE JUST THE SEQUENCER? 
	
	/*
	// check to see if a changeTriggerPattern message has come in from
	// the external UI and if so, change to that arrangement
	for(int i = 0; i<triggerPatternChangeTriggers.size(); i++) {
		if(*triggerPatternChangeTriggers[i] && currentTriggerPatternIndex!=i) {
			if(active) {
				cout << "CHANGING ARRANGEMENT " << i << endl;
				changeTriggerPattern(i);
			} 
		} 		
		*triggerPatternChangeTriggers[i] = false;
	}*/
	
	//if(!active) return false;
	
	
	
	//activeTriggerPatterns = 0;
	
	//for(int i=0; i<triggerPatterns.size(); i++) {
		//if( triggerPatterns[i]->update(deltaTime)) activeTriggerPatterns++;
		
		//THIS LINE MAKES IT AUTO CONTINUE - maybe a scene flag? 
		//else if ((!stopping) && (i==currentTriggerPatternIndex)) next();
		
	//}
	
	
	//if(stopping)  {
	//	active = false;
	//}

	
	if((!active)) return false;
	
	playing= music.getIsPlaying();
	
	if(playing) positionSeconds = (float)music.getPositionMS()/1000.0f;
	
	vector<int> deleteIndices; 
	
	for(int i = 0; i<commands.size(); i++) {
		
		SequenceCommand& command = commands[i];
		if((command.time>lastUpdate) && (command.time<=positionSeconds)) {
			
			if(recording && overwriteMode) {
				command.enabled = false;
                save();
			} else if(command.enabled){
				processCommand(command);
			}
		}
	}
	
	lastUpdate = positionSeconds;

	return active;
	
	
}

SequenceCommand Scene:: addCommand(float time, SequenceCommandType type, int arg){
    SequenceCommand cmd = _addCommand(time,type,arg);
    
    updateCommands();
    
    return cmd;
	
}

bool Scene::setCommandTime(int i, float time) {
	if(i>=commands.size()) return false;
	
	commands[i].time = ofClamp(time, 0, lengthSeconds);
	updateCommands();
	return true; 
}


SequenceCommand Scene :: _addCommand(float time, SequenceCommandType type, int arg){
	
	SequenceCommand cmd(type, time, arg);
	commands.push_back(cmd);
	
	return cmd;
	
}



void Scene :: processCommand(SequenceCommand command) {
	//cout << "PROCESS COMMAND "<< command.arg1 << endl;
	if(!command.enabled) return; 
	if(command.type == SEQ_PATTERN_CHANGE) {
		changeTriggerPattern(command.arg1);
		
	}
	
	
}

void Scene :: updateCommands() {
	
	sort(commands.begin(), commands.end());
	// AUTO SAVE HERE AND DO UNDO STUFF; 
	save();
}


bool Scene::disableCommand(int i) {
	
	if((i<0) || (commands.size()<=i)) {
		return false;
	} else {
		
		commands[i].enabled = false;
		
		updateCommands();
		
		return true;
	}
	
}


bool Scene:: draw() {

	if(!active) return false;
	
	
	return true; 

}

void Scene:: save(){
//    string filename = name + ".seq";
//    
//    ofFile fileHandle;
//    ofBuffer f;
//    fileHandle.open(filename, ofFile::WriteOnly, true);
//    
//    for(int i=0;i<commands.size();i++){
//        SequenceCommand command = commands[i];
//        fileHandle << command;
//    }
    ofxXmlSettings xml;
	
    ofxXmlSettings previousXml;
    
	string filename = "sequences/"+name+".xml";
    
    previousXml.load( filename );
    
    int a = 0;
    for(int i=1;i<commands.size();i++){
        SequenceCommand command = commands[i];
        if( !command.enabled ) continue;
        xml.addTag("command");
        xml.pushTag("command",a);
        xml.addValue("time", command.time );
        xml.addValue("arg1", command.arg1 );
        xml.popTag();
        a++;
	}

    string oldData;
    string newData;
    
    previousXml.copyXmlToString(oldData);
    xml.copyXmlToString(newData);
    
    oldData.erase(std::remove_if(oldData.begin(), oldData.end(), ::isspace ), oldData.end());
    newData.erase(std::remove_if(newData.begin(), newData.end(), ::isspace ), newData.end());
    
    if( oldData.compare( newData ) != 0 ){
        ofLogError() << "Scene data has changed, backing up and saving";
        
        if( newData.compare("") ){
            ofLogError() << "Scene data empty, has something gone wrong!?";
            //cout << endl << oldData << endl;
            //cout << endl << newData << endl;
        }
        
        std::time_t t = std::time(NULL);
        struct tm * ptr;
        char mbstr[100];
        ptr = localtime ( &t );
        strftime( mbstr, 100,"%Y-%m-%dT%H:%M:%S", ptr);
        char backupFilename[100] ;
        sprintf( backupFilename, "sequences/%s.%s.xml", name.c_str(), mbstr );
        previousXml.saveFile( backupFilename );
        xml.saveFile( filename );
        
        
    }

}

void Scene:: load(){
	string filename = "sequences/"+name+".xml";
	ofxXmlSettings xml;
    bool loaded = xml.loadFile(filename);
    if( !loaded ) return;
    int numCommands = xml.getNumTags("command");
    for(int i=0;i<numCommands;i++){
        _addCommand( xml.getValue("command:time", 0.0, i), SEQ_PATTERN_CHANGE, xml.getValue("command:arg1", 0, i) );
    }
    
}

void Scene::setMusicVolume(float volume){
	
	music.setVolume(volume);

}

bool Scene :: togglePlayPause(){
	if(playing) {
		music.stop();
		recording = false;
		playing = false; 
	}
	else if (music.isLoaded()){
		music.play();
		music.setPositionMS(positionSeconds*1000);
		playing = true; 
	}
	
	return playing;
}

bool Scene::toggleRecord() {
	recording = !recording;
	return recording; 
}

void Scene :: goToTime(float timeSeconds){
	
	
	sort(commands.begin(), commands.end());
	
	timeSeconds = ofClamp(timeSeconds, 0, lengthSeconds);
	music.setPositionMS(timeSeconds*1000);
	positionSeconds = timeSeconds;
	
	//TODO CYCLE THROUGH MESSAGES
	float lastPosition = 0;
	SequenceCommand* lastCommand = NULL;
	
	for(int i = 0; i<commands.size(); i++) {
		SequenceCommand c = commands[i];
		if(!c.enabled) return;
		if((c.time>=lastPosition) && (c.time<timeSeconds)) {
			
			lastCommand = &commands[i];
			lastPosition = c.time;
			//cout << i<<" " <<c.time << " " << timeSeconds << endl;
		}
		
	}
	
	if(lastCommand!=NULL) {
		//cout << lastCommand->time << " " << lastCommand->arg1 << endl;
		processCommand(*lastCommand);
		lastUpdate = timeSeconds;
	}
}



TriggerPattern Scene :: getCurrentTriggerPattern() {
	return triggerPatterns[currentTriggerPatternIndex];
}

string Scene :: getTriggerPatternName() {
	return getCurrentTriggerPattern().name;
}



void Scene ::addEmptyTriggerPattern() {
	
	TriggerPattern empty("Empty");
	addTriggerPattern(empty);
	
}

void Scene ::addTriggerPattern(TriggerPattern& pattern) {
	addTriggerPattern(pattern, "");
	
	//triggerPatternChangeTriggers.push_back(new bool(false));
}
void Scene ::addTriggerPattern(TriggerPattern& pattern, string label) {
	triggerPatterns.push_back(pattern);
	triggerPatterns.back().name = label;
	
	//triggerPatternChangeTriggers.push_back(new bool(false));
}

bool Scene :: changeTriggerPattern(int num) {

	//if(triggerPatterns.size()==0) addTriggerPattern();
	if(num>=triggerPatterns.size())  return false;
	
	//TODO this needs to tell the triggerManager to change stuff
	
	
	/*
	for(int i = 0; i< triggerPatterns.size(); i++) { 
		if(i!=num) {
			triggerPatterns[i]->stop();
			*arrangementChangeTriggers[i] = false;
		} else *arrangementChangeTriggers[i] = true;
	}
	
	triggerPatterns[num]->start();*/
	
		
	currentTriggerPatternIndex = num;
	if(triggerManager!=NULL)
		triggerManager->setPattern(getCurrentTriggerPattern());
	
		

	return true;
	
	
}




bool Scene :: next() {
	if(triggerPatterns.size()==0) return false;
	
	int nextPattern = currentTriggerPatternIndex+1;
	if(nextPattern>=triggerPatterns.size())
		nextPattern = 0;
	
	changeTriggerPattern(nextPattern);
	
	
}

bool Scene :: previous() {

	if(triggerPatterns.size()==0) return false;
	
	int prevArrangement = currentTriggerPatternIndex-1;
	if(prevArrangement<0)
		prevArrangement = triggerPatterns.size()-1;
	
	changeTriggerPattern(prevArrangement);


}

