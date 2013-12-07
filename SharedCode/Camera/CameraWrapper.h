/*
 *  CameraWrapper.h
 *  PixelPhones
 *
 *  Created by Seb Lee-Delisle on 16/03/2012.
 *  Copyright 2012 seb.ly. All rights reserved.
 *
 */

#pragma once
#include "ofMain.h"
#include "ofxCv.h"

class CameraWrapper :public ofBaseDraws{ 

	public : 
	CameraWrapper() { 
		flipX = flipY = false; 
		greyScale = true; 
		
		
	};
	virtual bool setup(string _name, int width = 640, int height = 480, int framerate =30){
		greyImage.allocate(width, height, OF_IMAGE_GRAYSCALE);
		colImage.allocate(width, height, OF_IMAGE_COLOR);
		name = _name;
	
	};
	virtual bool update(){

		baseVideo->update(); 
		bool newFrame = baseVideo->isFrameNew();
		
		if(newFrame) { 
			
			
			cv::Mat camMat = ofxCv::toCv(baseVideo->getPixelsRef()); 
			
			if(flipX||flipY) { 
				int code; 
				if(flipX && flipY) 
					code = -1; 
				else if(flipX) 
					code = 1; 
				else 
					code = 0; 
				
				cv::flip(camMat, camMat, code);
				
			}
			
			if(greyScale) { 
				cv::Mat greyMat = ofxCv::toCv(greyImage); 
				ofxCv::convertColor(camMat, greyMat, CV_RGB2GRAY); 
				greyImage.update();
			} else {
				
				cv::Mat colMat = ofxCv::toCv(colImage);
				//ofxCv::convertColor(camMat, colMat, CV_RGB2GRAY);
				//ofxCv::convertColor(camMat, colMat,CV_RGB2GRAY);
				
				ofxCv::copy(camMat, colMat);
				colImage.update();

				
			}
		}
		
		return newFrame; 
		
	};  // returns true if frame is new
	
	virtual ofPixelsRef getPixelsRef(){
		return greyScale ? greyImage.getPixelsRef() : colImage.getPixelsRef();
	};	
	
	virtual void draw(float x, float y){
		ofBaseDraws * output = greyScale ? (ofBaseDraws*)&greyImage : (ofBaseDraws*)&colImage;
		
		output->draw(x, y); 
	}; 
	virtual void draw(float x, float y, float w, float h){
		
		ofBaseDraws * output = greyScale ? (ofBaseDraws*)&greyImage : (ofBaseDraws*)&colImage;
		
		output->draw(x, y, w, h);
	}; 

	
	virtual bool videoSettings(){}; 
	virtual void close(){
		
		baseVideo->close(); 
	}; 
    
	
	virtual float getWidth(){ 
		return baseVideo->getWidth();
	};
	virtual float getHeight(){ 
		return baseVideo->getHeight();
	};
	
  	virtual void setGain(int value){}; 
	virtual int getGain(){};
	virtual void setShutter(int value){}; 
	virtual int getShutter(){}; 
	
	virtual int getGamma(){};
	virtual void setGamma(int value){}; 
	virtual int getBrightness(){};
	virtual void setBrightness(int value){}; 

	bool flipX;
	bool flipY;
	bool greyScale;
	
	int frameNum; 
	

	string name; 
	
	ofImage greyImage;
	ofImage colImage; 
	
	
	
    ofBaseVideoDraws* baseVideo; 


};