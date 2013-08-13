//
//  MotionManager.cpp
//  ArchitectureCamera
//
//  Created by Seb Lee-Delisle on 10/08/2012.
//  Copyright (c) 2012 seb.ly. All rights reserved.
//

#include "MotionManager.h"

using namespace ofxCv; 
using namespace cv; 
MotionManager :: MotionManager(int w, int h){ 
	
	//thresholdLevel = 20.0f;
	
	init(w, h);
	
	motionSensitivity = 1;
	

};


void MotionManager::init(int w, int h, ofImageType type) {
	
	
	if(current.isAllocated()) current.clear(); 
	if(previous.isAllocated()) previous.clear(); 
	if(diff.isAllocated()) diff.clear(); 
		
	current.allocate(w,h, type); 
	previous.allocate(w,h, type); 
	diff.allocate(w,h, type); 
	
	width = w; 
	height = h; 
	
	
	cout << "reinitialising images " << w << " " << h << endl; 
	
};


bool MotionManager :: update(ofPixelsRef image){
	
	if((image.getWidth()!=current.getWidth()) || (image.getHeight()!=current.getHeight()) || (image.getImageType()!=current.getPixelsRef().getImageType())) {
		
		init(image.getWidth(), image.getHeight(), image.getImageType());
		
		
	}
	
	
	
	// like ofSetPixels, but more concise and cross-toolkit
	copy(current, previous);
	
	
	//convertColor(image, current, CV_RGB2GRAY); 
	copy(image, current); 
	
	absdiff(previous, current, diff);
	if(thresholdLevel>0)
		threshold(diff, thresholdLevel);
	diff.update();
	
	motionPositions.clear(); 
	
};

void MotionManager :: draw() { 
	
	

}

float MotionManager :: getMotionAtPosition(ofVec2f pos, int width, Mat& homography){
	

	vector<cv::Point2f> pre, post;

	pre.push_back(cv::Point2f(pos.x - (width/2), pos.y - (width/2)));
	pre.push_back(cv::Point2f(pos.x + (width/2), pos.y + (width/2)));

	post.push_back(cv::Point2f());
	post.push_back(cv::Point2f());
	
	perspectiveTransform(pre, post, homography);
	
	ofVec2f topleft = toOf(post[0]);
	ofVec2f bottomright = toOf(post[1]);
	
	return getMotionAtPosition(topleft, bottomright); 
	
}

float MotionManager :: getMotionAtPosition(ofVec2f pos, int width){

	ofVec2f topleft = ofVec2f(pos.x-(width/2), pos.y-(width/2));
	ofVec2f bottomright = ofVec2f(pos.x+(width/2), pos.y+(width/2));;
	
	return getMotionAtPosition(topleft, bottomright); 
	
	
}


float MotionManager :: getMotionAtPosition(ofVec2f topleft, ofVec2f bottomright){
	
	topleft.x = ofClamp(topleft.x, 0, diff.width);
	topleft.y = ofClamp(topleft.y, 0, diff.height);
	bottomright.x = ofClamp(bottomright.x, 0, diff.width);
	bottomright.y = ofClamp(bottomright.y, 0, diff.height);
	
	ofVec2f dimensions = bottomright-topleft; 
	if((dimensions.x<=0) || (dimensions.y<=0)) return 0; 
	
	motionPositions.push_back(topleft);
	motionPositions.push_back(dimensions);

		Mat diffMat = toCv(diff); 
	Mat diffRoi(diffMat, cv::Rect(topleft.x, topleft.y, dimensions.x , dimensions.y ));
	
	//absdiff(prevRoi, curRoi, diffMat); 
	
	Scalar avg = mean(diffRoi);
	ofColor avgColor(avg[0]);
	return avgColor.getBrightness() * motionSensitivity;
	
};




void MotionManager:: initControlPanel(ofxAutoControlPanel &gui){
	
	//gui.addPanel("MotionManager");
	
	gui.addDrawableRect("Motion", &diff, 400, 300);
	
	gui.addSlider("Threshold","THRESHOLD", thresholdLevel, 0,255);
	gui.addSlider("Sensitivity","MOTION_SENSITIVITY", motionSensitivity, 1,5);
	
	ofAddListener(gui.guiEvent, this, &MotionManager::guiEventsIn);
	
	
}

void MotionManager::guiEventsIn(guiCallbackData & data){
	
	if (data.getXmlName() == "THRESHOLD") {
		
		//cout << "MotionManager::guiEventsIn threshold change : " << data.getFloat(0) << endl;
		thresholdLevel = data.getFloat(0);
		
	} else if (data.getXmlName() == "MOTION_SENSITIVITY") {
		
		//cout << "MotionManager::guiEventsIn threshold change : " << data.getFloat(0) << endl;
		motionSensitivity = data.getFloat(0);
		
	}
		
}


