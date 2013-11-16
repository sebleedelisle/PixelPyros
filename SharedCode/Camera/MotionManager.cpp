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
	
};

void MotionManager::init(int w, int h, ofImageType type) {
    motionSensitivityParam = 1;
    thresholdLevelParam = 20;
    
	// TODO - this is a bug - init gets called multiple times
    parameters.setName("Motion Detection");
    parameters.add( thresholdLevelParam.set("threshold", 1, 0, 50   ) );
    parameters.add( motionSensitivityParam.set("motion sensitivity", 1, 1, 20) );
	
	if(current.isAllocated()) current.clear(); 
	if(previous.isAllocated()) previous.clear(); 
	if(diff.isAllocated()) diff.clear(); 
		
	current.allocate(w,h, type); 
	previous.allocate(w,h, type); 
	diff.allocate(w,h, type); 
	
	width = w; 
	height = h;
	
	currentLabel = "";
	
	//cout << "reinitialising images " << w << " " << h << endl;
	
};


bool MotionManager :: update(ofPixelsRef image, string label){
	
	if(label!=currentLabel) {
		
		// save old label
		if(label!="") saveSettings();
		
		//load new label
		loadSettings(label); 
		currentLabel = label;
		
	}
	
	if((image.getWidth()!=current.getWidth()) || (image.getHeight()!=current.getHeight()) || (image.getImageType()!=current.getPixelsRef().getImageType())) {
		
		init(image.getWidth(), image.getHeight(), image.getImageType());
		
		
	}
	
	// copy the current image into the previous image
	copy(current, previous);
	
	// copy the new image into the current image
	copy(image, current);
	
	// difference blend between the two images to highlight the
	// changes between frames
	absdiff(previous, current, diff);
	
	// and run a threshold filter on it if required
	if(thresholdLevelParam>0)
		threshold(diff, thresholdLevelParam);
	
	
	diff.update();
	
};

void MotionManager :: draw() { 
	
	

}

float MotionManager :: getMotionAtPosition(ofVec2f pos, int width, Mat& homography){
	

	vector<cv::Point2f> from, to;

	from.push_back(cv::Point2f(pos.x - (width/2), pos.y - (width/2)));
	from.push_back(cv::Point2f(pos.x + (width/2), pos.y + (width/2)));

	to.push_back(cv::Point2f());
	to.push_back(cv::Point2f());
	
	perspectiveTransform(from, to, homography);
	
	ofVec2f topleft = toOf(to[0]);
	ofVec2f bottomright = toOf(to[1]);
	
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
	
	//motionPositions.push_back(topleft);
	//motionPositions.push_back(dimensions);

    Mat diffMat = toCv(diff);
	Mat diffRoi(diffMat, cv::Rect(topleft.x, topleft.y, dimensions.x , dimensions.y ));
	
	//absdiff(prevRoi, curRoi, diffMat); 
	
	Scalar avg = mean(diffRoi);
	ofColor avgColor(avg[0]);
	//cout << avgColor.getBrightness() * motionSensitivityParam << endl;
	return avgColor.getBrightness() * motionSensitivityParam;
	
};

void MotionManager::saveSettings() {
	if(currentLabel=="") return;
	ofDirectory dir("settings");
	if(!dir.exists()) dir.create();
	
	ofxXmlSettings settings;
	
	//positions.addTag("srcvec");
	//positions.pushTag("srcvec", i);
	
	settings.addValue("thresholdLevel", thresholdLevelParam);
	settings.addValue("motionSensitivity", motionSensitivityParam);
	
	//positions.addTag("srcvec");
	//positions.pushTag("srcvec", i);
		
	settings.saveFile("settings/motion"+currentLabel+".xml");
	//cout << "saving settings " << "settings/motion"+currentLabel+".xml" << endl;
	

	
}

void MotionManager::loadSettings(string label) {
	
	currentLabel = label;
	string settingsFileLabel = currentLabel;
	
	ofxXmlSettings settings;
	//cout << "Loading settings/motion"+settingsFileLabel+".xml" << endl;
	if(!settings.loadFile("settings/motion"+settingsFileLabel+".xml")) return false;
	//cout<< "LOADED! "<<endl;
	//if(settings.getNumTags("thresholdLevel")!=1) return false;
	//if(settings.getNumTags("motionSensitivity")!=1) return false;
	//if(verbose) cout << "Success!";
	
	
	thresholdLevelParam = (float)settings.getValue("thresholdLevel", 1.0f);
	motionSensitivityParam = (float)settings.getValue("motionSensitivity", 1.0f);
	
	
	currentLabel = label; 
}


//void MotionManager:: initControlPanel(ofxAutoControlPanel &gui){
//	
//	//gui.addPanel("MotionManager");
//	
//	gui.addDrawableRect("Motion", &diff, 400, 300);
//	
//	gui.addSlider("Threshold","THRESHOLD", thresholdLevel, 0,255);
//	gui.addSlider("Sensitivity","MOTION_SENSITIVITY", motionSensitivity, 1,5);
//	
//	ofAddListener(gui.guiEvent, this, &MotionManager::guiEventsIn);
//	
//	
//}

//void MotionManager::guiEventsIn(guiCallbackData & data){
//	
//	if (data.getXmlName() == "THRESHOLD") {
//		
//		//cout << "MotionManager::guiEventsIn threshold change : " << data.getFloat(0) << endl;
//		thresholdLevel = data.getFloat(0);
//		
//	} else if (data.getXmlName() == "MOTION_SENSITIVITY") {
//		
//		//cout << "MotionManager::guiEventsIn threshold change : " << data.getFloat(0) << endl;
//		motionSensitivity = data.getFloat(0);
//		
//	}
//		
//}


