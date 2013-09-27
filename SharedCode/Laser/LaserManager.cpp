//
//  LaserManager.cpp
//  LaserTest02
//
//  Created by Seb Lee-Delisle on 08/08/2013.
//
//

#include "LaserManager.h"


LaserManager * LaserManager :: laserManager = NULL;

LaserManager * LaserManager::instance() {
	if(laserManager == NULL) {
		laserManager = new LaserManager();
	}
	return laserManager;
}


LaserManager:: LaserManager() {

}


void LaserManager:: connectToEtherdream() {

	etherdream.setup();
    etherdream.setPPS(80000);
	isConnected = true;
	
}
void LaserManager:: disconnectFromEtherdream() {
	
	etherdream.stop();
	isConnected = false;
	
}

void LaserManager:: setup (int width, int height) {
    
    appWidth = width; // ofGetWidth();
    appHeight = height;//ofGetHeight();
    
    isConnected = false;
	showSyncTest = false;
	
	minPoints = 1000;
    
	white.set(1,1,1);
	black.set(0,0,0);
	
	endCount = 1;
	blankCount = 0;
	
	pmin.set(0,0);
	pmax.set(appWidth, appHeight);
	
	showRegistration = true;
	showMovePoints = false;
	renderLaserPath = true;
	intensity = 1;
    
	//float x1 = appWidth*0.2;
	//float x2 = appWidth*0.7;
	//float y1 = appHeight*0.2;
	//float y2 = appHeight*0.65;
	
    float x1 = APP_WIDTH * 0.2;
    float x2 = APP_WIDTH * 0.8;
    float y1 = APP_HEIGHT * 0.2;
    float y2 = APP_HEIGHT * 0.8;
	
    warp = warpParam;
	warp.label = "laserWarp";
    
	warp.setDstPoint(0, ofVec2f(x1,y1));
	warp.setDstPoint(1, ofVec2f(x2,y1));
	warp.setDstPoint(2, ofVec2f(x2,y2));
	warp.setDstPoint(3, ofVec2f(x1,y2));
	
	warp.setSrcPoint(0, ofVec2f(x1,y1));
	warp.setSrcPoint(1, ofVec2f(x2,y1));
	warp.setSrcPoint(2, ofVec2f(x2,y2));
	warp.setSrcPoint(3, ofVec2f(x1,y2));
	
    warp.loadSettings();
    
	intensity = 1;
	dotPreBlank = 3;
	dotPostBlank = 3;
	dotMaxPoints = 10;
	parameters.setName("Laser Manager");
	
	//p1.setName("Etherdream");
	parameters.add(connectButton.set("Etherdream connect", false));
	parameters.add(etherdreamStatus.set("status", ""));
	
	//p2.setName("laser");
    
	parameters.add(intensity.set("intensity", 1, 0, 1));
	parameters.add(colourChangeDelay.set("colour change offset", -6, -15, 15));
	
	parameters.add(showRegistration.set("show registration", false));
	
	parameters.add(showMovePoints.set("show move points", false));
	parameters.add(showSyncTest.set("show sync test", false));
	parameters.add(renderLaserPath.set("render laser path", true));
	
    calibrationParameters.setName("Laser Calibration");
    calibrationParameters.add(warpParam.set("Homography", warp) );
    
	//p3.setName("laser graphics");
	
	
	parameters.add(moveSpeed.set("move speed", 3,0.01,10));
	parameters.add(circleMoveSpeed.set("circle speed", 3,0.01,10));
	parameters.add(movePointsPadding.set("move points padding", 0,0,20));
	
	parameters.add(dotPreBlank.set("dot pre blank", 3, 0, 20));
	parameters.add(dotPostBlank.set("dot post blank", 3, 0, 20));
	parameters.add(dotMaxPoints.set("dot max points", 7, 0, 100));
	
	parameters.add(acceleration.set("acceleration", 0.5, 0.001, 20));
	parameters.add(maxSpeed.set("max speed", 20,0.1, 100));
    
    
	
    //	parameters.add(p1);
    //	parameters.add(p2);
    //	parameters.add(p3);
    
	
	colourChangeDelay = -6;
	
	warp.visible = true;
    
	warp.dragSpeed = 1; 
    
    
}

void LaserManager:: update() {
	
	ofPushStyle();
	
	if(connectButton!=isConnected) {
		if(connectButton) {
			connectToEtherdream();
		} else {
			disconnectFromEtherdream();
		}
		
		
	}
	
	if(showSyncTest) {
		addDelayTest();
		
		
	}
	
	
	if(showRegistration) {
		
		//addLaserRectEased(pmin, pmax, white);
		//addLaserLineEased(pmin, pmax, white);
		//addLaserLineEased(ofPoint(pmax.x, pmin.y), ofPoint(pmin.x, pmax.y), white);
		
		ofPoint v = pmax - pmin;
		
		for(float x =0 ; x<=1; x+=0.2) {
			for(float y = 0; y<=1; y+=0.2) {
				addLaserDot(ofPoint(pmin.x + (v.x*x), pmin.y + (v.y*y)), white, 1);
				ofCircle(pmin.x + (v.x*x), pmin.x + (v.x*x), 10); 
			}
		}
		
		addLaserCircle(ofPoint(appWidth/2, appHeight/2), white, 10);
		addLaserCircle(ofPoint(appWidth/2, appHeight/2), ofFloatColor(1,0,0), 50);
			
		
		/*
		addLaserDot(pmin, white, 1);
		addLaserDot(ofPoint(pmax.x, pmin.y), white, 1);
		addLaserDot(pmax, white, 1);
		addLaserDot(ofPoint(pmin.x, pmax.y), white, 1);
		*/
		
		
	}
	
	drawShapes();
	
	
		
	
	while(ildaPoints.size()<minPoints) {
		
		addIldaPoint(currentPosition, black);
		
	}
	
	
	// SORT OUT COLOUR CHANGE DELAY. 
	vector<ofxIlda::Point> adjustedPoints;
	
	for(int i = 0; i<ildaPoints.size(); i++) {
		
		ofxIlda::Point p = ildaPoints.at(i);
		
		int colourPointIndex = i+colourChangeDelay;
		while(colourPointIndex<0) colourPointIndex+=ildaPoints.size();
		
		ofxIlda::Point colourPoint = ildaPoints.at(colourPointIndex%ildaPoints.size());
		
		p.r = round(colourPoint.r);
		p.g = round(colourPoint.g);
		p.b = round(colourPoint.b);
		
		adjustedPoints.push_back(p); 
		
		
	}
	
	if(isConnected) {
		etherdream.setPoints(adjustedPoints);
		etherdream.checkConnection(true);
		//etherdream.setPPS(50000);
	}
    
	if((renderLaserPath)||(showRegistration)) {
		
		ofNoFill();
		
		ofSetColor(50,0,0);
		previewMesh.setMode(OF_PRIMITIVE_LINE_LOOP);
		previewMesh.draw();
		ofSetColor(255,255,255);
		previewMesh.setMode(OF_PRIMITIVE_POINTS);
		previewMesh.draw();
		
	}
	//ofDrawBitmapString("POINTS : "+ofToString(ildaPoints.size())+" "+ofToString(colourChangeDelay), ofPoint(10,10));

	
	resetIldaPoints();
	
	warp.draw();
	
	ofPopStyle(); 
	
}

void LaserManager::addLaserDot(const ofPoint& ofpoint, ofFloatColor colour, float intensity){
	
	//ofPoint target = warp.getWarpedPoint(ofpoint);
	
	shapes.push_back(new LaserDot(ofpoint, colour, intensity));
}


void LaserManager::addLaserCircle(const ofPoint& ofpoint, ofFloatColor colour, float radius, float intensity){
	
	shapes.push_back(new LaserCircle(ofpoint, colour, radius, intensity));
}


void LaserManager:: drawShapes() {
	
	
	// sort the dots by nearest neighbour
	
	if(shapes.size()==0) return; 
	vector<LaserShape*> sortedShapes;
	
	int numberSorted = 0;
	int dotNum = shapes.size();
	int currentIndex = 0; 
	
	int nextDotIndex = NULL;
	
	float travelDistanceSorted = 0; 
	
	
	do {
		
		LaserShape * dot1 = shapes.at(currentIndex);
		
		//LaserDot & nextDot = dots.at(nextDotIndex);
		dot1->tested = true;
		sortedShapes.push_back(dot1);
		
		float shortestDistance = INFINITY;
		nextDotIndex = -1;
		
		for(int j = 0; j<shapes.size(); j++) {
			
			LaserShape * dot2 = shapes.at(j);
			if((dot1==dot2) || (dot2->tested)) continue;
		
			if(dot1->endPos.distanceSquared(dot2->startPos) < shortestDistance) {
				shortestDistance = dot1->endPos.distanceSquared(dot2->startPos);
				nextDotIndex = j;
			}
			
		}
		
		if(nextDotIndex>-1) {
			travelDistanceSorted += sqrt(shortestDistance);
		}
			
		currentIndex = nextDotIndex;
		
		
		
	} while (currentIndex>-1);
	
	
	float travelDistanceUnsorted = 0;
	
	for(int i = 0; i<shapes.size()-1; i++) {
		LaserShape* dot1 = shapes.at(i);
		LaserShape* dot2 = shapes.at(i+1);
		
		travelDistanceUnsorted += dot1->endPos.distanceSquared(dot2->startPos); 
		
	}
	
	ofDrawBitmapString(ofToString(travelDistanceUnsorted)+"\n" +ofToString(travelDistanceSorted), ofPoint(10,40));
	
	
	for(int i = 0; i<sortedShapes.size(); i++) {
		
		LaserShape* shape = sortedShapes.at(i);

		if(!currentPosition.match(shape->startPos, 0.01)) {
			moveLaser(shape->startPos);
		}
		
		
		// CHECK FOR A DOT
		LaserDot * dot = dynamic_cast<LaserDot*>(shape);
		
		
		if(dot) {
		
			//cout << i << " DOT!" << endl;
			int particlecount = ceil(dotMaxPoints* dot->intensity);
			 
			for(int i = 0; i<dotPreBlank; i++) {
				addIldaPoint(dot->startPos, black);
			}
			for(int i = 0; i<particlecount; i++) {
				addIldaPoint(dot->startPos, dot->colour);
			}
			for(int i = 0; i<dotPostBlank; i++) {
				addIldaPoint(dot->startPos, black);
			}
		}
		
		
		// CHECK CIRCLES
		LaserCircle * circle = dynamic_cast<LaserCircle*>(shape);
		
		if(circle) {
			
			
			float acceleratedistance = (maxSpeed*maxSpeed) / (2*acceleration);
			float timetogettospeed = maxSpeed / acceleration;
			
			float totaldistance = 2*PI*circle->radius;
			
			float constantspeeddistance = totaldistance - (acceleratedistance*2);
			float constantspeedtime = constantspeeddistance/maxSpeed;
			
			if(totaldistance<(acceleratedistance*2)) {
				
				constantspeeddistance = 0 ;
				constantspeedtime = 0;
				acceleratedistance = totaldistance/2;
				maxSpeed = sqrt( acceleratedistance * 2 * acceleration);
				timetogettospeed = maxSpeed / acceleration;
				
			}
			
			float totaltime = (timetogettospeed*2) + constantspeedtime;
			
			float timeincrement = totaltime / (floor(totaltime));
			
			float currentdistance;
			currentdistance = 0;
			float t = 0;
			
			ofNoFill();
			
			ofPoint currentpos;
			
			for(int i = 0; i<endCount;i++){
				addIldaPoint(circle->startPos, circle->colour);
			}
			
			ofPoint p;
			
			while (t <= totaltime + 0.001) {
				
				if(t>totaltime) t = totaltime;
				
				if(t <=timetogettospeed) {
					currentdistance = 0.5 * acceleration * (t*t);
					ofSetColor(0,255,0);
				} else if((t>timetogettospeed) && (t<=timetogettospeed+constantspeedtime)){
					currentdistance = acceleratedistance + ((t-timetogettospeed) * maxSpeed);
					ofSetColor(255);
				} else  {
					float t3 = t - (timetogettospeed + constantspeedtime);
					
					currentdistance = (acceleratedistance + constantspeeddistance) + (maxSpeed*t3)+(0.5 *(-acceleration) * (t3*t3));
					ofSetColor(255,0,0);
					
				}
				
				//currentpos = (u * currentdistance) + start;
				
				//addIldaPoint(currentpos, colour);
				
				float angle = ofMap(currentdistance, 0, totaldistance, 0, PI*2);
				
				p.set(circle->pos);
				p.x+=sin(angle)*circle->radius;
				p.y-=cos(angle)*circle->radius;
				
				addIldaPoint(p, circle->colour);
				
				
				
				t+=timeincrement;
				
			}
			
			
			LaserLine * line = dynamic_cast<LaserLine*>(shape);
			
			if(line) {
				drawLaserLine(*line);
			}
				
					
			
		}
	
	}
	
	
	
}

void LaserManager :: moveLaser(const ofPoint & targetpoint){
	
	ofPoint target = targetpoint;//alreadyWarped ? targetpoint : warp.getWarpedPoint(targetpoint),
	ofPoint start = currentPosition;


	ofPoint v = target-start;
	
	//if(v.length()>100) blanknum*=3;
	
	float blanknum = v.length()/moveSpeed + movePointsPadding;//max(v.length(), (float)blankCount);
	
	for(int j = 0; j<blanknum; j++) {
		
		float t = Quint::easeInOut((float)j, 0.0f, 1.0f, blanknum);
		
		ofPoint c = (v* t) + start;
		addIldaPoint(c, (showMovePoints && j%2==0) ? ofColor(100,0,0) : ofColor::black);
		
	}
	//currentVel.set(0,0);
}



void LaserManager:: addLaserLineEased(const ofPoint&startpoint, const ofPoint&endpoint, ofFloatColor colour) {
	
	
	shapes.push_back(new LaserLine(startpoint, endpoint, colour, intensity));
	
	
}


void LaserManager:: drawLaserLine(LaserLine& line) {
	
	ofPoint start = line.startPos;// warp.getWarpedPoint(startpoint);
	ofPoint end = line.endPos;//warp.getWarpedPoint(endpoint);
	
	if(!currentPosition.match(start, 0.01)) {
		moveLaser(start);
		
	}
	
	
	ofPoint vec = end - start;
	
	float speed = 8;
	int iterations = floor(vec.length()/speed) + 10; // arbitrary amount to create enough ease points!
	
	// TODO add start and end blanks for lines?
	
	for(int i = 0; i<endCount;i++)
		addIldaPoint(start, line.colour);
	
	
	for(float i = 0; i<iterations; i++) {
		
		float t = Quad::easeInOut(i/iterations, 0, 1, 1);
		
		addIldaPoint(start + (vec*t), line.colour);
		
	}
	
	for(int i = 0; i<blankCount; i++) {
		addIldaPoint(end, line.colour);
	}
}

/*
void LaserManager:: addLaserLine(const ofPoint&startpoint, const ofPoint&endpoint, ofFloatColor colour) {
	
	ofPoint start = warp.getWarpedPoint(startpoint);
	ofPoint end = warp.getWarpedPoint(endpoint);
	//ofPoint start = startpoint;
	//ofPoint end = endpoint;
	if(!currentPosition.match(start, 0.01)) {
		moveLaser(startpoint);
		
	}
	
	float acceleratedistance = (maxSpeed*maxSpeed) / (2*acceleration);
	float timetogettospeed = maxSpeed / acceleration;

	
	ofPoint u = end-start;
	
	
	float totaldistance = u.length();
	
	float constantspeeddistance = totaldistance - (acceleratedistance*2);
	float constantspeedtime = constantspeeddistance/maxSpeed;
	
	if(totaldistance<(acceleratedistance*2)) {
		
		constantspeeddistance = 0 ;
		constantspeedtime = 0;
		acceleratedistance = totaldistance/2;
		maxSpeed = sqrt( acceleratedistance * 2 * acceleration);
		timetogettospeed = maxSpeed / acceleration;
		
	}
	
	float totaltime = (timetogettospeed*2) + constantspeedtime;
	
	float timeincrement = totaltime / (floor(totaltime));
	
	u.normalize();
	
	float currentdistance;
	currentdistance = 0;
	float t = 0;
	
	ofNoFill();
	
	ofPoint currentpos;
	
	for(int i = 0; i<endCount;i++)
		addIldaPoint(start, colour);
		
	
	while (t <= totaltime + 0.001) {
		
		if(t>totaltime) t = totaltime;
		
		if(t <=timetogettospeed) {
			currentdistance = 0.5 * acceleration * (t*t);
			ofSetColor(0,255,0);
		} else if((t>timetogettospeed) && (t<=timetogettospeed+constantspeedtime)){
			currentdistance = acceleratedistance + ((t-timetogettospeed) * maxSpeed);
			ofSetColor(255);
		} else  {
			float t3 = t - (timetogettospeed + constantspeedtime);
			
			currentdistance = (acceleratedistance + constantspeeddistance) + (maxSpeed*t3)+(0.5 *(-acceleration) * (t3*t3));
			ofSetColor(255,0,0);
			
		}
		
		currentpos = (u * currentdistance) + start;
		
		addIldaPoint(currentpos, colour);
		
					 
		
		
		t+=timeincrement;
		
	}

	for(int i = 0; i<blankCount; i++) {
		addIldaPoint(end, colour);
	}
	
	

	
}
*/
/*
void LaserManager::addLaserRect(const ofPoint&topLeft, const ofPoint&dimensions, ofFloatColor colour){
	
	addLaserLine(topLeft, ofPoint(topLeft.x+dimensions.x,topLeft.y), colour);
	addLaserLine(ofPoint(topLeft.x+dimensions.x,topLeft.y), topLeft+dimensions, colour);
	addLaserLine(topLeft+dimensions, ofPoint(topLeft.x,topLeft.y+dimensions.y), colour);
	addLaserLine(ofPoint(topLeft.x,topLeft.y+dimensions.y), topLeft, colour);

}
*/

void LaserManager::addLaserRectEased(const ofPoint&topLeft, const ofPoint&dimensions, ofFloatColor colour){
	
	addLaserLineEased(topLeft, ofPoint(topLeft.x+dimensions.x,topLeft.y), colour);
	addLaserLineEased(ofPoint(topLeft.x+dimensions.x,topLeft.y), topLeft+dimensions, colour);
	addLaserLineEased(topLeft+dimensions, ofPoint(topLeft.x,topLeft.y+dimensions.y), colour);
	addLaserLineEased(ofPoint(topLeft.x,topLeft.y+dimensions.y), topLeft, colour);
	
}

ofxIlda::Point LaserManager::ofPointToIldaPoint(const ofPoint& ofpoint, ofFloatColor colour){
	
	
	ofxIlda::Point ildapoint;
	
	ofPoint p = ofpoint;
	p.y= appHeight-p.y;
	p.x= appWidth-p.x;

	ildapoint.set(p, colour, pmin, pmax);
	return ildapoint;
	
}
ofPoint LaserManager::ildaPointToOfPoint(const ofxIlda::Point& ildapoint){
	
}


void LaserManager::addIldaPoint(const ofPoint& p, ofFloatColor c){
	
	ofPoint warpedpoint = warp.getWarpedPoint(p);;
	
	ofPoints.push_back(warpedpoint);

	previewMesh.addVertex(warp.getUnWarpedPoint(warpedpoint));
	//previewMesh.addColor(c);
	c.r*=intensity;
	c.g*=intensity;
	c.b*=intensity; 
	
	ildaPoints.push_back(ofPointToIldaPoint(warpedpoint, c));
	
	currentPosition = p;
	
}

void LaserManager::resetIldaPoints() {
	
	ildaPoints.clear();
	previewMesh.clear();
	previewMesh.setMode(OF_PRIMITIVE_LINES);
	ofPoints.clear();
	
	for(int i = 0; i<shapes.size(); i++) {
		delete shapes[i];
	}
	
	shapes.clear();
}



void LaserManager::addDelayTest() {
	
	
	ofFloatColor pointcolour;
	
	int pointcount = 500;
	ofPoint pos;
	for(float x =0; x<=pointcount; x+=1) {
		
		pos.set((100+(x/50)),0);
		float angle = ofMap(x,0,pointcount, 0,1080);
		pos.rotate(angle,ofPoint(0,0,1));
		pos.x+=appWidth/2;
		pos.y+=appHeight/2;
		//pointcolour.setHsb(ofMap(x,0,pointcount, 0,1), 1, 1);
		//pointcolour.setHsb(0, 1, 1);
		
		//cout << pointcolour.r << " " << pointcolour.g << " " << pointcolour.b << "\n";
		pos = warp.getWarpedPoint(pos);
		
//		if(x==0) {
//			startVel.set(0,10,0);
//			startPosition = pos;
//		}
		
		if((angle>=360) && (angle<=(360+180)) && fmod(x,2)==0) addIldaPoint(pos, white);
		else addIldaPoint(pos, ofFloatColor(0,1,0));
		
	}
	//pos.set(500,350);
	pos = warp.getWarpedPoint(ofPoint(500,350));

//	addLaserLine(ofPoint(650,ofGetHeight()/2),(ofPoint(350,ofGetHeight()/2)), ofFloatColor(1,0,0));
	
}


bool LaserManager:: toggleRegistration() {
	
	showRegistration = !showRegistration;
	
}

/*
 void LaserManager:: moveLaserToPointAndVel(const ofPoint& targetPos, const ofPoint& targetVel) {
 
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
 */

