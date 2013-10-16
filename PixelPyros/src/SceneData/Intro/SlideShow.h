//
//  SlideShow.h
//  SlideShowTest
//
//  Created by Seb Lee-Delisle on 21/08/2012.
//
//



#pragma once

#include "ofMain.h"


class SlideShow {
	
	public :
	
		SlideShow(string path = "") {
			
			folderPath = path;
			reloadImages();
			timePerImage = 5;
			lastChange = 0;
			transitionTime = 0.6;
			elapsedTime = 0;
			
			visible = true;
			active = true;
			transitioning = true;
			
			rect.set(0,ofGetHeight()/4,ofGetWidth(), ofGetHeight()/2);
		}
		
		
		void reloadImages() {
			
			images.clear();
			
			ofDirectory dir(folderPath);
			dir.listDir();
			
			
			//cout << "numFiles " << dir.numFiles() << endl;
			
			//cout << "path " << folderPath << endl;
			
			
			currentImageIndex = 0;
			
			for(int i = 0; i<dir.numFiles(); i++) {
				
				ofFile file = dir.getFile(i);
				
				//cout << "loading " << file.getFileName();
				
				if((file.getExtension()=="png") || (file.getExtension()=="jpg")) {
					images.push_back(ofImage(folderPath+file.getFileName()));
					
				}
				
			}
				
		
		
		}
	
		void draw(float deltaTime) {
			if(!visible) return;
			
			if(images.size()==0 ) return ;
			
			
			elapsedTime+=deltaTime;
			float timeSinceLastChange = elapsedTime - lastChange;
			
			if(timeSinceLastChange>timePerImage){
				
				currentImageIndex++;
				
				if(currentImageIndex >= images.size()){
					currentImageIndex = 0;
				}
				
				lastChange = elapsedTime;
				
				if(!active) visible = false;
				
				
			}
			
			if(!visible) return;
			
			ofPushMatrix();
			
			ofPushStyle();

			ofSetRectMode(OF_RECTMODE_CENTER);
			
			ofImage& image = images[currentImageIndex]; 
			
			ofTranslate(rect.getCenter());

			if(timeSinceLastChange<transitionTime) {
				ofSetColor(ofMap(timeSinceLastChange,0,transitionTime, 0,255,true));
				transitioning = true; 
			} else if(timePerImage - timeSinceLastChange < transitionTime) {
				ofSetColor(ofMap(timePerImage - timeSinceLastChange,0,transitionTime, 0,255,true));
				transitioning = true;
			} else {
				ofSetColor(255);
				transitioning = false; 
			}
				
			float xscale = rect.width / image.getWidth();
			float yscale = rect.height /image.getHeight();
			
			float scale = min(xscale, yscale);
			if(scale<1) ofScale(scale, scale);
			
		
			
			
			images[currentImageIndex].draw(0,0);

			ofPopMatrix();

			
			ofSetRectMode(OF_RECTMODE_CORNER);
			ofNoFill();
			
			ofRect(rect);
			
			ofPopStyle();
					
		}
	
		void show() {
			if(active || visible) return;
			
			lastChange = elapsedTime;
			visible = true;
			active = true;
			currentImageIndex = 0;
			
		}
	
		void hide() {
			if(!active) return;
			
			active = false;
			
			float offset = 0;
			// if we're part way through the transition in
			if(elapsedTime - transitionTime < lastChange) {
				// then we should offset
				offset = transitionTime - (elapsedTime-lastChange);
			}
			lastChange = elapsedTime-timePerImage+transitionTime - offset;
		}
		
	
	
	vector<ofImage> images;
	int currentImageIndex;
	string folderPath;
	float timePerImage;
	float lastChange;
	float elapsedTime;
	float transitionTime;
	
	bool active;
	bool visible; 
	bool transitioning;
	
	ofRectangle rect;
	
	
	
	
	
	
	
};