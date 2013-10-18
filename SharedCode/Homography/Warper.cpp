//
//  Warper.cpp
//  HomographyExample
//
//  Created by Seb Lee-Delisle on 08/08/2012.
//  Copyright (c) 2012 seb.ly. All rights reserved.
//
//  The primary purpose of the warper is to project the camera
//  image into screen space. It has 4 source points (usually the
//  4 corners of the where the projection appears in the camera)
//  and 4 destination points (usually the 4 corners of the screen
//  space). 


#include "Warper.h"


Warper :: Warper() { 
		
	guiVisible = false; 
	changed = true; 
	
	ofAddListener(ofEvents().mousePressed, this, &Warper::mousePressed);
	ofAddListener(ofEvents().mouseDragged, this, &Warper::mouseDragged);
	ofAddListener(ofEvents().mouseReleased, this, &Warper::mouseReleased);

	dstPreviewScale = 0.5;
	
	autoSave =true;
	verbose = false;
	movingPoint = false;
	curPoint = NULL; 
	
};

bool Warper :: init (float srcwidth, float srcheight, float dstwidth, float dstheight, string label){
	
	dstWidth = dstwidth; 
	dstHeight = dstheight; 
	srcWidth = srcwidth; 
	srcHeight = srcheight; 

	settingsFileLabel = label; 
	
	// create defaults if there is no saved setting yet. 
	if(!loadSettings()){
		for(int i = 0; i<4;i++) {
			
			if(srcVecs.size()==i) srcVecs.push_back(ofVec2f()); 
			srcVecs[i].set( ((i%2)*0.8 + 0.1) * dstWidth, (floor(i/2)*0.2 + 0.7) * dstHeight);
		}
		for(int i = 0; i<4;i++) { 
			
			if(dstVecs.size()==i) dstVecs.push_back(ofVec2f()); 
			dstVecs[i].set( ((i%2)*0.8 + 0.1) * dstWidth, (floor(i/2)*0.2 + 0.7) * dstHeight);
		}
	}
	
	if(warpedImage.isAllocated()) warpedImage.clear();
	
	warpedImage.allocate(dstwidth * dstPreviewScale, dstheight * dstPreviewScale, OF_IMAGE_COLOR);
	
	changed = true;
}


bool Warper :: update(ofPixels& sourcePixels) {
	
	
	if(changed) { 
	
		vector<Point2f> srcPoints, dstPoints;
		for(int i = 0; i < srcVecs.size(); i++) {
			srcPoints.push_back(Point2f(srcVecs[i].x *srcWidth/dstWidth, srcVecs[i].y * srcHeight/dstHeight));
			dstPoints.push_back(Point2f(dstVecs[i].x, dstVecs[i].y));
		}			
		
		homography = findHomography(Mat(srcPoints), Mat(dstPoints));
		inverseHomography = homography.inv();
		
		if(autoSave) saveSettings();
	
	}
	
	
	if(guiVisible) { 
		
		if(sourcePixels.getImageType()!=warpedImage.getPixelsRef().getImageType()){
			warpedImage.allocate(dstWidth* dstPreviewScale, dstHeight* dstPreviewScale, sourcePixels.getImageType());
		}
		vector<Point2f> srcPoints, dstPoints;
		
		for(int i = 0; i < srcVecs.size(); i++) {
			srcPoints.push_back(Point2f(srcVecs[i].x *srcWidth/dstWidth, srcVecs[i].y * srcHeight/dstHeight));
			dstPoints.push_back(Point2f(dstVecs[i].x*dstPreviewScale, dstVecs[i].y*dstPreviewScale));
		}		
		Mat previewHomography = findHomography(Mat(srcPoints), Mat(dstPoints)); 
		
		// I guess for a moving image we need to warp the pixels every time.
		// but we could do it with a similar function to "apply" in QuadWarper
		
		warpPerspective(sourcePixels, warpedImage, previewHomography, CV_INTER_NN);
		warpedImage.update();
		
	}
		
	if(changed) { 
		changed = false; 
		return true; 
	} else { 
		return false; 
	}
};

void Warper :: drawPoints(vector<ofVec2f>& points, ofColor colour) {
	
	
	ofPushStyle();
	ofNoFill();
	ofPushMatrix(); 

	//ofEnableSmoothing();
	//ofScale(1024, 768); 
	for(int i = 0; i < points.size(); i++) {
		ofSetColor(ofColor::black); 
		ofSetLineWidth(6);
		
		ofCircle(points[i], 1);
		ofSetColor(colour); 
		ofSetLineWidth(2);
		ofCircle(points[i], 20);
		ofCircle(points[i], 1);
		
		
		
	}
	ofPopMatrix(); 
	ofPopStyle();

}



void Warper :: draw(ofPixels& pix) { 
	if(!guiVisible) return; 
	
	// draw GUI
	
	//ofSetColor(255);
	
	warpedImage.draw(0,0, dstWidth, dstHeight);
	
	/*
	ofPushMatrix();
	
	ofTranslate(dstWidth/4, dstHeight/4);
	ofScale(srcWidth/dstWidth/2, srcWidth/dstWidth/2);	
	
	//ofImage img(pix);
	//img.draw(0,0, dstWidth, dstHeight);
	//cout << dstWidth << " " << dstHeight << endl;
	drawPoints(srcVecs, ofColor::cyan);

	ofPopMatrix();
	 
	 */
	drawPoints(srcVecs, ofColor::cyan);
	
	drawPoints(dstVecs); 
	
	
};


bool Warper:: loadSettings() { 
	
	ofxXmlSettings settings;
	if(verbose) cout << "Loading warpdata/"+settingsFileLabel+".xml" << endl;
	if(!settings.loadFile("warpdata/"+settingsFileLabel+".xml")) return false;
	
	if(settings.getNumTags("srcvec")!=4) return false; 
	if(settings.getNumTags("dstvec")!=4) return false; 
	if(verbose) cout << "Success!";
	
	float dstwidth = settings.getValue("dstWidth", dstWidth);
	float dstheight = settings.getValue("dstHeight", dstHeight); 
	
	ofVec2f dstScale(dstWidth/dstwidth, dstHeight/dstheight);
	
	float srcwidth = settings.getValue("srcWidth", srcWidth);
	float srcheight = settings.getValue("srcHeight", srcHeight); 
	
	ofVec2f srcScale(srcWidth/srcwidth, srcHeight/srcheight);
	
	if(verbose) cout << "dstScale " << dstScale << endl;
	if(verbose) cout << "srcScale " << srcScale << endl;
    
    //srcWidth = srcwidth;
    //srcHeight = srcheight;
 
    //dstWidth = dstwidth;
    //dstHeight = dstheight;
    
	
    
    // NOTE src vectors are in the same scale space as the dst
    // vectors. Then they're scaled down to fit the source video
    // when it comes to creating the homography. 
	for(int i = 0; i<4;i++) { 

		if(srcVecs.size()==i) srcVecs.push_back(ofVec2f()); 

		
		settings.pushTag("srcvec", i); 
		srcVecs[i].set(settings.getValue("x", (i%2)*dstwidth),
						 settings.getValue("y", floor(i/2)*dstheight));
		
		if(verbose) cout << "src" << i << " " << srcVecs[i] << endl;
		
		srcVecs[i] *= dstScale;
		
		settings.popTag();
	}
	for(int i = 0; i<4;i++) { 
		
		
		if(dstVecs.size()==i) dstVecs.push_back(ofVec2f()); 
		
		settings.pushTag("dstvec", i); 
		
		dstVecs[i].set(settings.getValue("x", (i%2)*dstwidth),
					   settings.getValue("y", floor(i/2)*dstheight));
		

		if(verbose) cout << "dstc" << i << " " << srcVecs[i] << endl;

		dstVecs[i]*=dstScale;
		
		settings.popTag();
	}
	
   
	return true; 
		
}


bool Warper:: saveSettings() {
	
	ofDirectory dir("warpdata"); 
	if(!dir.exists()) dir.create();
	
	ofxXmlSettings positions; 

	//positions.addTag("settings"); 
	//positions.pushTag("settings"); 
	
	for(int i = 0; i < srcVecs.size(); i++){
		positions.addTag("srcvec"); 
		positions.pushTag("srcvec", i); 
		//so set the three values in the file
		//positions.addTag("x", ); 
		positions.addValue("x", srcVecs[i].x); 
		positions.addValue("y", srcVecs[i].y); 
		
		
		positions.popTag(); 
		//	
	}

	//positions.popTag(); 

	for(int i = 0; i < dstVecs.size(); i++){
		
		positions.addTag("dstvec"); 
		positions.pushTag("dstvec", i); 
		
		//so set the three values in the file
		positions.addValue("x", dstVecs[i].x);
		positions.addValue("y", dstVecs[i].y);
		positions.popTag(); 
		
		
	}

	positions.addValue("srcWidth", srcWidth);
	positions.addValue("srcHeight", srcHeight);

	positions.addValue("dstWidth", dstWidth); 
	positions.addValue("dstHeight", dstHeight); 	
	
	positions.saveFile("warpdata/"+settingsFileLabel+".xml");	
	//cout << "saving settings " << "warpdata/"+settingsFileLabel+".xml" << endl;
	
	
}

bool Warper :: hitTestPoints ( vector<ofVec2f>& points, ofVec2f& point) {
	
	for(int i = 0; i < points.size(); i++) {
		if(points[i].distance(point) < 40) {
			movingPoint = true;
			
			curPoint = &points[i];
			clickOffset.set(curPoint->x  - point.x, curPoint->y - point.y);
			dragStartPoint = point;
			return true;
		}
	}
	
}


void Warper :: showGui() { 
	if(!guiVisible) { 
		guiVisible = true; 
		changed = true;
	}
	
}

void Warper :: hideGui() { 
	if(guiVisible) { 
		guiVisible = false;
		
		if(autoSave) saveSettings(); 
		
	}
	
}

bool Warper :: toggleGui() {
	
	if(!guiVisible) showGui(); 
	else hideGui(); 

	return guiVisible; 
}


void Warper :: mousePressed(ofMouseEventArgs &e) {

	if(!guiVisible) return; 
	
	ofVec2f cur(e.x, e.y);
	
	hitTestPoints(dstVecs, cur); 
	hitTestPoints(srcVecs, cur); 
	
};


void Warper :: mouseDragged(ofMouseEventArgs &e) {
	if(!guiVisible) return; 
	
	
	if(movingPoint) { 

		ofVec2f diff(e.x, e.y);
		diff-=dragStartPoint;
		diff*=0.3; 
		
		
		*curPoint = dragStartPoint+diff+clickOffset;
		//*curPoint+=clickOffset;
	
		changed = true;
	
	}
	
};



void Warper :: mouseReleased(ofMouseEventArgs &e) {
	if(!guiVisible) return; 
	
	if(movingPoint) {
		movingPoint = false; 
		changed = true; 
	}
	
	
	saveSettings(); 
	//loadSettings(); 
};






