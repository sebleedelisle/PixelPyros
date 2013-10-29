//
//  QuadWarp.cpp
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 30/08/2012.
//
//  The QuadWarp object is used to calculate homography between two quads.
//  Its functionality overlaps Warper, except that Warper owns a bitmap, whereas
//  this doesn't. In many ways this method is better as it doesn't actually do any
//  pixel manipulation. It's primarily used to warp the projector images to map onto
//  the screen, but it's also used to warp the laser output to match the screen. 

#include "QuadWarp.h"

#include "matrix_funcs.h"

QuadWarp :: QuadWarp (string saveLabel) {
	
	label = saveLabel;

	pointColour = ofColor :: white;
	dstPoints.resize(4);
	srcPoints.resize(4);
    dstPointsStartDrag.resize(4);
    offset = ofVec2f(0,0);
	
	for(int i = 0; i<4;i++) {
		srcPoints[i].set( (i%2)*100, floor(i/2)*100);
		dstPoints[i].set( (i%2)*100, floor(i/2)*100);
	}
	/*
	ofVec3f midpoint = srcPoints[0] + ((srcPoints[3] - srcPoints[0]) / 2);
	srcPoints[4] = dstPoints[4] = midpoint;
	*/
	updateHomography();
	
	visible = false;
    useBoundsRect = false;
	pointRadius = 10;
	curDragPointIndex = -1;
	lastMousePress = 0;
	
	ofAddListener(ofEvents().mousePressed, this, &QuadWarp::mousePressed);
	ofAddListener(ofEvents().mouseDragged, this, &QuadWarp::mouseDragged);
	ofAddListener(ofEvents().mouseReleased, this, &QuadWarp::mouseReleased);


}

QuadWarp :: ~QuadWarp() {
	
	ofRemoveListener(ofEvents().mousePressed, this, &QuadWarp::mousePressed);
	ofRemoveListener(ofEvents().mouseDragged, this, &QuadWarp::mouseDragged);
	ofRemoveListener(ofEvents().mouseReleased, this, &QuadWarp::mouseReleased);

}

void QuadWarp :: draw() {
	draw(ofGetKeyPressed(OF_KEY_SHIFT));

}

void QuadWarp :: draw(bool lockAxis) {
	
	if(!visible) return;
	
    if( curDragPointIndex == 8 ){
        ofVec3f diff(ofGetMouseX() - offset.x - dragStartPoint.x, ofGetMouseY() - offset.y - dragStartPoint.y );
                
        for( int i=0; i< dstPoints.size();i++){
            dstPoints[i] = dstPointsStartDrag[i] + diff;
        }
        
        updateHomography();
        
    }
	else if(curDragPointIndex>=0 && curDragPointIndex<4) {
		
		ofVec3f diff(ofGetMouseX() - offset.x, ofGetMouseY() - offset.y );
        
        
        if(dragAltPressed){
            
            if(lockAxis) {
                if(abs(diff.x)-abs(diff.y)>1) diff.y = 0;
                else if (abs(diff.y)-abs(diff.x)>1) diff.x = 0;
            }
            
            
            diff-=dragStartPoint;
            diff*=dragSpeed;
            
            ofVec3f& curPoint = dstPoints[curDragPointIndex];
            
            curPoint = dragStartPoint+diff+clickOffset;
            
            curPoint.x = round(curPoint.x*10)/10;
            curPoint.y = round(curPoint.y*10)/10;
            
            if(useBoundsRect) {
                if(curPoint.x<boundsRectangle.getLeft()) curPoint.x = boundsRectangle.getLeft();
                if(curPoint.x>boundsRectangle.getRight()) curPoint.x = boundsRectangle.getRight();
                if(curPoint.y<boundsRectangle.getTop()) curPoint.y = boundsRectangle.getTop();
                if(curPoint.y>boundsRectangle.getBottom()) curPoint.y = boundsRectangle.getBottom();
            }
        }
        else {
            ofVec3f& center = dragCenterStart;
            
            float scale = diff.distance( center ) / dragStartPoint.distance(center);
            
            for( int i=0; i< dstPoints.size();i++){
                float len = dstPointsStartDrag[i].distance( center );
                dstPoints[i] = center + ( dstPointsStartDrag[i] - center ).normalize() * len * scale;
            }
        }

		
		switch(curDragPointIndex) {
			case 0 :
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
		}
		
		
		updateHomography();
				
	}else if(curDragPointIndex>=4 && curDragPointIndex<8){
        ofVec3f diff(ofGetMouseX() - offset.x - dragStartPoint.x, ofGetMouseY() - offset.y - dragStartPoint.y );
        
        if(lockAxis) {
            if(abs(diff.x)-abs(diff.y)>1) diff.y = 0;
            else if (abs(diff.y)-abs(diff.x)>1) diff.x = 0;
        }
        
        diff += clickOffset;
        int i = curDragPointIndex-4;
        int j = (i+1)%dstPoints.size();
        dstPoints[i] = dstPointsStartDrag[i] + diff;
        dstPoints[j] = dstPointsStartDrag[j] + diff;
        
        updateHomography();
    }

	
	
	ofPushStyle();
	ofNoFill();
	
	ofPushMatrix();
	
    ofTranslate(offset.x, offset.y);
	
	//ofEnableSmoothing();
	//ofScale(1024, 768);
	for(int i = 0; i < dstPoints.size(); i++) {
		
		
		ofVec3f& point = dstPoints[i];
        drawMarker(point, pointColour, pointRadius);
	
		if(i == curDragPointIndex){
			
			ofLine(point.x, point.y - 100, point.x, point.y+100); 
			ofLine(point.x-100, point.y, point.x+100, point.y);
			
			//ofDrawBitmapStringHighlight(ofToString(point.x), point.x, point.y-30, ofColor(0,0,0,100));
			//ofDrawBitmapStringHighlight(ofToString(point.y), point.x-30, point.y, ofColor(0,0,0,100));
		}
        
        int j = (i+1)%dstPoints.size();
        ofVec3f side = 0.5f * ( dstPoints[i] + dstPoints[j] );
		drawMarker(side, ofColor::cyan, pointRadius);
		
	}
	
    ofVec3f center = getCenter();
    drawMarker(center, ofColor::greenYellow, pointRadius);
    if( curDragPointIndex == 4 ){
        ofLine(center.x, center.y - 100, center.x, center.y+100);
        ofLine(center.x-100, center.y, center.x+100, center.y);
    }
    
	ofPopMatrix();
	ofPopStyle();
	
}

void QuadWarp::drawMarker(ofVec3f& point, const ofColor & color, float radius){
    ofSetColor(ofColor::black);
    ofSetLineWidth(3);
    ofCircle(point, 1);
    ofSetColor(color);
    ofSetLineWidth(1);
    ofCircle(point, radius);
    ofCircle(point, 1);
}

void QuadWarp::setOffset(float x,float y){
    offset.x = x;
    offset.y = y;
}

void QuadWarp ::setDstPoint(int index, ofVec3f point){
	
	if(index>=dstPoints.size()) {
		dstPoints.resize(index+1);
		setSrcPoint(index, point);
	}
	
	dstPoints[index] = point;
	updateHomography();
	
	
}

void QuadWarp ::setSrcPoint(int index, ofVec3f point){
	
	if(index>=srcPoints.size()) {
		srcPoints.resize(index+1);
		setDstPoint(index, point); 
	}
	
	srcPoints[index] = point;
	updateHomography();
	
	
}

ofVec3f QuadWarp::getCenter(){
    ofVec3f centre = ofVec3f(0,0,0);
    for(int i = 0; i < dstPoints.size(); i++) {
        centre+=dstPoints[i];
    }
    centre /= dstPoints.size();
    
    return centre;
}

// stolen from ofxAppUtils - thanks danomatika !

void QuadWarp ::apply(ofRectangle sourceRect){
	
	
	// we set it to the default - 0 translation
	// and 1.0 scale for x y z and w
	for(int i = 0; i < 16; i++) {
		if(i % 5 != 0) _glWarpMatrix[i] = 0.0;
		else _glWarpMatrix[i] = 1.0;
	}
	
	// source and destination points
	double src[srcPoints.size()][2];
	double dest[dstPoints.size()][2];
	
	// we set the warp coordinates
	// source coordinates as the dimensions of our window

	for(int i = 0; i<srcPoints.size(); i++) {
		src[i][0] = srcPoints[i].x;
		src[i][1] = srcPoints[i].y;
	}

	for(int i = 0; i < dstPoints.size(); i++){
		dest[i][0] = dstPoints[i].x;
		dest[i][1] = dstPoints[i].y;
	}
	
	// perform the warp calculation
	mapQuadToQuad(src, dest, _warpMatrix);
	
	// copy the values
	_glWarpMatrix[0]	= _warpMatrix[0][0];
	_glWarpMatrix[1]	= _warpMatrix[0][1];
	_glWarpMatrix[3]	= _warpMatrix[0][2];
	
	_glWarpMatrix[4]	= _warpMatrix[1][0];
	_glWarpMatrix[5]	= _warpMatrix[1][1];
	_glWarpMatrix[7]	= _warpMatrix[1][2];
	
	_glWarpMatrix[12]	= _warpMatrix[2][0];
	_glWarpMatrix[13]	= _warpMatrix[2][1];
	_glWarpMatrix[15]	= _warpMatrix[2][2];
	
	// finally lets multiply our matrix
	glMultMatrixf(_glWarpMatrix);

	
	
	
}; 

void QuadWarp::updateHomography() {
	
	
	vector<Point2f> srcCVPoints, dstCVPoints;
	if(srcPoints.size()!=dstPoints.size()) {
		cout << "RUH ROH" << endl;
	}
		
	
	for(int i = 0; i < srcPoints.size(); i++) {
		srcCVPoints.push_back(Point2f(srcPoints[i].x , srcPoints[i].y));
		dstCVPoints.push_back(Point2f(dstPoints[i].x, dstPoints[i].y));
	}

	
	//cout << srcPoints[3] << " " << dstPoints[3] << endl;
	homography = cv::findHomography(cv::Mat(srcCVPoints), cv::Mat(dstCVPoints));
	inverseHomography = homography.inv();
}

ofVec3f QuadWarp::getWarpedPoint(ofVec3f point){
	
	vector<cv::Point2f> pre, post;
	
	
	pre.push_back(cv::Point2f(point.x, point.y));
	post.push_back(cv::Point2f());
	
	//cout << "getWarpedPoint" << pre[0] << endl;
	
	cv::perspectiveTransform(pre, post, homography);
	//cout << "warped" << post[0] << endl;

	return ofxCv::toOf(post[0]);
//	return ofxCv::toOf(pre[0]);
	
//	return point;

}


ofVec3f QuadWarp::getUnWarpedPoint(ofVec3f point){
	
	vector<cv::Point2f> pre, post;
	
	
	pre.push_back(cv::Point2f(point.x, point.y));
	post.push_back(cv::Point2f());
	
	//cout << "getWarpedPoint" << pre[0] << endl;
	
	cv::perspectiveTransform(pre, post, inverseHomography);
	//cout << "warped" << post[0] << endl;
	
	return ofxCv::toOf(post[0]);
	//	return ofxCv::toOf(pre[0]);
	
	//	return point;
	
}


void QuadWarp :: mousePressed(ofMouseEventArgs &e) {
	
	if(!visible) return;
	
		
	ofVec3f clickPoint(e.x - offset.x, e.y - offset.y);
	   
	for(int i = 0; i < dstPoints.size(); i++) {
        
        if(dstPoints[i].distance(clickPoint) < pointRadius) {
			curDragPointIndex = i;
			ofVec3f &curPoint = dstPoints[i];
            
			clickOffset = curPoint - clickPoint;
			dragStartPoint = clickPoint;
			dragCenterStart = getCenter();
            dragAltPressed = ofGetKeyPressed(OF_KEY_ALT);
            
            for(int j = 0; j < dstPoints.size(); j++) {
                dstPointsStartDrag[j].set( dstPoints[j] );
            }
			
            break;
		}
        
        int k = (i+1)%dstPoints.size();
        ofVec3f middlePoint = 0.5 * ( dstPoints[i] + dstPoints[k] );
        if(middlePoint.distance(clickPoint) < pointRadius) {
            curDragPointIndex = i+4;
            dragStartPoint = middlePoint;
            clickOffset = middlePoint - clickPoint;
            for(int j = 0; j < dstPoints.size(); j++) {
                dstPointsStartDrag[j].set( dstPoints[j] );
            }
            break;
        }
	}
    
    if( getCenter().distance( clickPoint ) < pointRadius ){
        curDragPointIndex = 8;
        dragStartPoint = clickPoint;
        clickOffset = getCenter() - clickPoint;
        for(int j = 0; j < dstPoints.size(); j++) {
            dstPointsStartDrag[j].set( dstPoints[j] );
        }
    }
		
};


void QuadWarp :: mouseDragged(ofMouseEventArgs &e) {
	if(!visible) return;
	
	
		
};



void QuadWarp :: mouseReleased(ofMouseEventArgs &e) {
	if(!visible) return;
	
    if(curDragPointIndex==8){
        curDragPointIndex = -1;
        saveSettings();
    }
	else if(curDragPointIndex>=0) {
		
		if(ofGetElapsedTimef() - lastMousePress < 0.4 && curDragPointIndex<4) {
			dstPoints[curDragPointIndex] = srcPoints[curDragPointIndex];			
		}

		curDragPointIndex = -1;
		updateHomography();
		saveSettings();
	}
	
	lastMousePress  = ofGetElapsedTimef() ; 
	
};


bool QuadWarp::loadSettings() {
	  
	string filename = "warpdata/"+label+".xml";
	ofxXmlSettings xml;
	if(!xml.loadFile(filename)) {
		ofLog(OF_LOG_ERROR, "QuadWarp::loadSettings - file not found : "+filename);
		return false;
		
	}
	
	//cout << "Warp Pre load: " << filename << " " << dstPoints[0].x << ", " << dstPoints[0].y << endl;
    
    
	dstPoints[0].x	= xml.getValue("quad:upperLeft:x", 0.0);
	dstPoints[0].y	= xml.getValue("quad:upperLeft:y", 0.0);
	
	dstPoints[1].x	= xml.getValue("quad:upperRight:x", 1.0);
	dstPoints[1].y	= xml.getValue("quad:upperRight:y", 0.0);
	
	dstPoints[2].x	= xml.getValue("quad:lowerRight:x", 1.0);
	dstPoints[2].y	= xml.getValue("quad:lowerRight:y", 1.0);
	
	dstPoints[3].x	= xml.getValue("quad:lowerLeft:x", 0.0);
	dstPoints[3].y	= xml.getValue("quad:lowerLeft:y", 1.0);
	
    //cout << "Loading Warp: " << filename << " " << dstPoints[0].x << ", " << dstPoints[0].y << endl;
    
    updateHomography();
    
	return true;
}

void QuadWarp::saveSettings() {
	     
	ofxXmlSettings xml;
	
	string filename = "warpdata/"+label+".xml";
    
	xml.addTag("quad");
	xml.pushTag("quad");
	
	xml.addTag("upperLeft");
	xml.pushTag("upperLeft");
	xml.addValue("x", dstPoints[0].x);
	xml.addValue("y", dstPoints[0].y);
	xml.popTag();
	
	xml.addTag("upperRight");
	xml.pushTag("upperRight");
	xml.addValue("x", dstPoints[1].x);
	xml.addValue("y", dstPoints[1].y);
	xml.popTag();
	
	xml.addTag("lowerRight");
	xml.pushTag("lowerRight");
	xml.addValue("x", dstPoints[2].x);
	xml.addValue("y", dstPoints[2].y);
	xml.popTag();
	
	xml.addTag("lowerLeft");
	xml.pushTag("lowerLeft");
	xml.addValue("x", dstPoints[3].x);
	xml.addValue("y", dstPoints[3].y);
	xml.popTag();
	
	xml.saveFile(filename);
    
    
}

std::ostream& operator<< (std::ostream& stream, const QuadWarp& warp){

    for(int i=0;i<warp.dstPoints.size();i++){
        stream << (float) warp.dstPoints[i].x << ", ";
        stream << (float) warp.dstPoints[i].y << ": ";
    }
    
    return stream;
}

std::istream& operator>> (std::istream& stream, QuadWarp& warp){
    float component;
	
	// TODO I'm pretty sure we need some error checking here
	
    for(int i=0;i<warp.dstPoints.size();i++){
        stream >> component;
        warp.dstPoints[i].x = component;
        stream.ignore(2);
        stream >> component;
        warp.dstPoints[i].y = component;
        stream.ignore(2);
    }
    
    return stream;
}

