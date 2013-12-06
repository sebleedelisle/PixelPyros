//
//  SceneSpace.h
//  ArchitectureCamera
//
//  Created by Seb Lee-Delisle on 14/08/2012.
//  Copyright (c) 2012 seb.ly. All rights reserved.
//
#pragma once

#include "Scene.h"
#include "Starfield.h"
#include "TextWriter.h"
#include "LaserManager.h"
#include "ofxSvg.h"

class SceneIntroAnim : public Scene {
	
	public : 
	
	SceneIntroAnim(string scenename) ;
	
	void start();
	void stop(); 
	bool update(float deltaTime);
	bool draw();
	
	ofVideoPlayer video; 
	Starfield starfield;
	
	float starBrightness;
	
	TextWriter textWriter;
	ofMesh laserWordMesh;
	ofxSVG logo;
	vector<vector<ofPolyline> > logolines; 
	float vidPosition; 
	
};