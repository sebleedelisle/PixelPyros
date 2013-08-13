#include "testApp.h"
#include "ofxIldaFrame.h"


//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0);
    
    etherdream.setup();
    etherdream.setPPS(50000);

	//ofSetFrameRate(60);
	
	white.set(1,1,1);
	black.set(0,1,0);
	
	endCount = 1;
	blankCount = 30;
	
	pmin.set(0,0);
	pmax.set(ofGetWidth(), ofGetHeight());

	laserDirty = true;
	previewPointIndex = 0; 
	
}

//--------------------------------------------------------------
void testApp::update(){
}

/// OK WHAT HAVE I LEARNED?
/*
 
 * it takes a few frames for the laser to switch off and seems to switch off early
 * it turns on actually before it's meant to. Weird.
 * MAYBE it thinks it's further along than it actually is? 
 
 */




//--------------------------------------------------------------
void testApp::draw() {
    
//	
//	if(laserDirty) {
//	
//		points.clear();
//		
//		ofFloatColor pointcolour;
//		
//		int pointcount = 100;
//		
//		for(float x =0; x<=pointcount; x+=1) {
//			
//			ofPoint pos(100,0);
//			pos.rotate(ofMap(x,0,pointcount, 0,360),ofPoint(0,0,1));
//			pos.x+=ofGetWidth()/2;
//			pos.y+=ofGetHeight()/2;
//			//pointcolour.setHsb(ofMap(x,0,pointcount, 0,1), 1, 1);
//			pointcolour.setHsb(0, 1, 1);
//			
//			//cout << pointcolour.r << " " << pointcolour.g << " " << pointcolour.b << "\n";
//			addLaserPoint(pos, pointcolour);
//		
//		}
//	
//		closeLaserLoop();
//	
//    		
//		laserDirty = false;
//	}
	
	
	resetIldaPoints();
	
	//addLaserLine(ofPoint(300,200), ofPoint(200, 200), white);
	//addLaserLine(ofPoint(200,200), ofPoint(200, 300), white);
	//addLaserLine(ofPoint(200,300), ofPoint(300, 300), white);
	//addLaserLine(ofPoint(300,300), ofPoint(300, 200), white);

	
//	for (int i = 0; i<6; i++) {
//		
//		float y = ofMap(i, 0, 6,300,400);
//		addLaserLine(ofPoint(200,y), ofPoint(450, y), white);
//		addLaserLine(ofPoint(y,200), ofPoint(y, 450), white);
//		
//		
//		
//	}
	//closeLaserLoop();
	// send points to the etherdream
	
	
	ofFloatColor pointcolour;

	int pointcount = 500;

	for(float x =0; x<=pointcount; x+=1) {

		ofPoint pos((100+(x/50)),0);
		float angle = ofMap(x,0,pointcount, 0,1080);
		pos.rotate(angle,ofPoint(0,0,1));
		pos.x+=ofGetWidth()/2;
		pos.y+=ofGetHeight()/2;
		//pointcolour.setHsb(ofMap(x,0,pointcount, 0,1), 1, 1);
		//pointcolour.setHsb(0, 1, 1);
		if(x==0) {
			startVel.set(0,10,0);
			startPosition = pos;
		}
		//cout << pointcolour.r << " " << pointcolour.g << " " << pointcolour.b << "\n";
		if((angle>=360) && (angle<(360+180)) && fmod(x,2)==0) addIldaPoint(pos, white);
		else addIldaPoint(pos, black);
	
	}

	addLaserLine(ofPoint(450,350), ofPoint(250,350), white);
	closeLaserLoop();
	
	etherdream.setPoints(ildaPoints);
	etherdream.checkConnection(true);
    
    //ofSetColor(255);
    //ofDrawBitmapString(ildaFrame.getString(), 10, 30);
	
	ofNoFill();
	ofMesh mesh;
	

//	for(int i = 0; i<stars.size(); i++) {
//		ofPoint& star = stars.at(i);
//		
//		mesh.addVertex(star);
//	}
//	
//	ofSetColor(50,0,0);
//	mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
//	mesh.draw();
//	
//	ofSetColor(255,255,255);
//	mesh.setMode(OF_PRIMITIVE_POINTS);
//	mesh.draw();
//	
//	
//	mesh.clear();
	
	for(int i = 0; i<ildaPoints.size(); i++) {
		ofxIlda::Point& p = ildaPoints.at(i);
		
		ofPoint v = ofPoint(p.x, p.y);
		v/= (kIldaMaxPoint - kIldaMinPoint);
		//v.y = 1-v.y;
		v.x+=0.5;
		v.y-=0.5;
		v*=ofGetWidth();

		
		
		
		mesh.addVertex(v);
		//mesh.addColor(ofFloatColor(p.r, p.g, p.b));
		
		//cout << v.x << " " <<  v.y << "\n";
	}
	
	ofSetColor(0,100,0);
	mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
	mesh.draw();
	
	//ofSetColor(255,255,255);
	mesh.setMode(OF_PRIMITIVE_POINTS);
	//mesh.draw();
	
	ofSetColor(50,0,0);
	previewMesh.setMode(OF_PRIMITIVE_LINE_LOOP);
	previewMesh.draw();
	ofSetColor(255,255,255);
	previewMesh.setMode(OF_PRIMITIVE_POINTS);
	previewMesh.draw();
	
	previewPointIndex = floor(ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, ofPoints.size()-1, true));
	ofCircle(ofPoints.at(previewPointIndex),10);
	//previewPointIndex++;
	//if(previewPointIndex>=ofPoints.size()) previewPointIndex = 0;
	

}


void testApp::addLaserDot(const ofPoint& ofpoint, ofFloatColor& colour) {
	
	if(ildaPoints.size()==0) {
		startPosition.set(ofpoint);
	} else {
		moveLaserQuintic(currentPosition, ofpoint);
	}
	
	
	ofFloatColor roundedColour;
	roundedColour.set(round(colour.r), round(colour.g), round(colour.b));
	for(int i = 0; i<endCount; i++) {
		addIldaPoint(ofpoint, roundedColour);
	}
	//			for(int j = 0; j<endCount *star.brightness; j++) {
	//				ildaPoints.push_back(point);
	//			}
	
	currentPosition.set(ofpoint); 
	
	currentVel.set(0,0); 
}

void testApp::closeLaserLoop() {
	
//	moveLaserQuintic(currentPosition, startPosition);
	
//	while(ildaPoints.size()<600) {
//		ildaPoints.push_back(ofPointToIldaPoint(startPosition, black));
//		
//	}
//	currentVel.set(0,0);
	
	moveLaserToPointAndVel(startPosition, startVel); 
	
}

void testApp :: moveLaserQuintic(const ofPoint & start, const ofPoint & end){
	
	
	ofPoint v = end-start;
	
	//if(v.length()>100) blanknum*=3;
	
	float blanknum = v.length();//max(v.length(), (float)blankCount);
	
	for(int j = 0; j<blanknum; j++) {
		
		
		float t = Quint::easeInOut((float)j, 0.0f, 1.0f, blanknum);
		
		ofPoint c = (v* t) + start;
		addIldaPoint(c, black);

	}
	currentVel.set(0,0); 
}

void testApp:: moveLaserToPointAndVel(const ofPoint& targetPos, const ofPoint& targetVel) {
	
	float controlPointLength = 0;
	
	CubicBezier b(currentPosition, currentPosition + (currentVel*controlPointLength), targetPos, targetPos+(targetVel*-controlPointLength));
	
	float blanknum = 20;//(float)blankCount;
	
	for(int j = 0; j<blanknum; j++) {
		
		
		float t = ofMap(j, 0, blanknum, 0,1);
		t = Quint::easeInOut(t, 0, 1, 1);
		
		ofPoint c = b.getPointAtT(t);
		// takes a while to come on so let's switch it on early!
		//if(j>blanknum-8) {
		//	addIldaPoint(c, white);
		//} else {
			addIldaPoint(c, black);
		//}
	}
	currentVel.set(targetVel);

}

void testApp:: addLaserLine(const ofPoint&start, const ofPoint&end, ofFloatColor& colour) {
	
	ofPoint vec = end - start;
	
	float speed = 2;
	int iterations = floor(vec.length()/speed);
	speed = vec.length()/iterations;
	
	ofPoint vel = vec;
	vel.normalize();
	vel*=speed;
	
//	if(ildaPoints.size()==0) {
//		startVel = vel;
//		startPosition = start; 
//	} else {
//	
//		moveLaserToPointAndVel(start, vel);
//	}
	
	// takes a while for the light to come on!
	
	for(float i = 0; i<iterations; i++) {
		//float t = Cubic::easeInOut(i/iterations, 0, 1, 1);
		float t = i/iterations;
		//if(fmod(i,2)==0)
			addIldaPoint(start + (vec*t), colour);
		//else
		//	addIldaPoint(start + (vec*t), black);

	}
	
	for(int i = 0; i<10; i++) {
		
		addIldaPoint(end, colour);
		
	}
	
	currentPosition = end;
	currentVel = vel; 

	
}




ofxIlda::Point testApp::ofPointToIldaPoint(const ofPoint& ofpoint, ofFloatColor& colour){
	ofxIlda::Point ildapoint;
	ofPoint p = ofpoint;
	p.y= ofGetHeight()-p.y;
	p.x= ofGetWidth()-p.x;
	
	ildapoint.set(p, colour, pmin, pmax);
	return ildapoint;
	
}
ofPoint testApp::ildatPointToOfPoint(const ofxIlda::Point& ildapoint){

}


void testApp::addIldaPoint(const ofPoint& p, ofFloatColor& c){
	
	previewMesh.addVertex(p);
	//previewMesh.addColor(c);
	
	ildaPoints.push_back(ofPointToIldaPoint(p, c));
	ofPoints.push_back(p); 
	
	
}

void testApp::resetIldaPoints() {
	
	ildaPoints.clear();
	previewMesh.clear();
	previewMesh.setMode(OF_PRIMITIVE_LINES);
	ofPoints.clear(); 
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
  
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
 	
}
