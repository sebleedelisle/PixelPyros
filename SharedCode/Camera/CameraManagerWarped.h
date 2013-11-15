//
//  CameraManagerWarped.h
//  ArchitectureCamera
//
//  Created by Seb Lee-Delisle on 09/08/2012.
//  Copyright (c) 2012 seb.ly. All rights reserved.
//

#pragma once

#include "CameraManager.h"
#include "Warper.h"

class CameraManagerWarped : public CameraManager { 

	public :
	
	
	CameraManagerWarped() : CameraManager() { 
		
		
		warper.guiVisible = false; 

	};
	
	void init() {
		
		CameraManager::init(); 
		warper.init(getWidth(), getHeight(), APP_WIDTH, APP_HEIGHT, camera->name);
		
	};
	
	bool update()  {
	
		
		if( CameraManager::update()) { 
			
			
			warper.update(camera->getPixelsRef()); 		
			return true;
		} else { 
			return false; 
			
		}
		
	};
	bool changeCamera(CameraWrapper* cam){
		
		CameraManager::changeCamera(cam); 
		//cout << "CameraWarped change camera"<< camera->name << " " << getWidth() << " " << getHeight() << endl;
		warper.init(getWidth(), getHeight(), APP_WIDTH, APP_HEIGHT, camera->name);
		
		
	}
	
	void draw()  { 
		if(warper.guiVisible)
			warper.draw();
		
		if(capturing) {
			ofPushStyle();
			ofSetColor(ofColor::red);
			ofCircle(10, 10, 10);
			ofPopStyle();
		}
		
	};

	bool toggleWarperGui() { 
		return warper.toggleGui(); 	
		
	};
	
	
	Warper warper;
	ofImage* warpSource; 
	

};