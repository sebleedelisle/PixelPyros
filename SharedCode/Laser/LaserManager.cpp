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
	pointPreviewImage.loadImage("img/LaserPointPreview.png");
}


void LaserManager:: connectToEtherdream() {

	etherdream.setup();
   // etherdream.setPPS(pps);
	isConnected = true;
	
}
void LaserManager:: disconnectFromEtherdream() {
	
	etherdream.kill();
	isConnected = false;
	
}

void LaserManager:: setup (int width, int height) {
    
    appWidth = width; // ofGetWidth();
    appHeight = height;//ofGetHeight();
    
    isConnected = false;
	showSyncTest = false;
	//connectButton = false;
	
	minPoints = 1000;
    
	white.set(1,1,1);
	black.set(0,0,0);
	
	//endCount = 1;
	//blankCount = 0;
	
	pmin.set(0,0);
	pmax.set(appWidth, appHeight);
	
	showRegistration = true;
	showMovePoints = false;
	showLaserPath = true;
	intensity = 1;
	
    float x1 = APP_WIDTH * 0.2;
    float x2 = APP_WIDTH * 0.8;
    float y1 = APP_HEIGHT * 0.2;
    float y2 = APP_HEIGHT * 0.8;
	
	maskRectangle.set(0, 0, APP_WIDTH, y2);
	maskRectangle.initUI();

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

	parameters.setName("Laser Manager");
	
	connectButton.setup("Etherdream connect");
	connectButton.addListener(this, &LaserManager::connectButtonPressed);
	//parameters.add(&connectButton);
	parameters.add(etherdreamStatus.set("status", "test"));
	parameters.add(showWarpPoints.set("show warp points", false));
	parameters.add(showMaskRectangle.set("show mask rect", false));

	parameters.add(pps.set("points per second", 80000, 30000, 100000));
	parameters.add(intensity.set("intensity", 1, 0, 1));
	parameters.add(colourChangeDelay.set("colour change offset", -6, -15, 15));
	
	parameters.add(showRegistration.set("show registration", false));
	parameters.add(flipX.set("flip x", true));
	parameters.add(flipY.set("flip y", true));
	
	parameters.add(showMovePoints.set("laser move points", false));
	parameters.add(showSyncTest.set("show sync test", false));
	parameters.add(showLaserPath.set("show laser path", true));
	parameters.add(renderLaserPreview.set("render laser preview", true));

	parameters.add(moveSpeed.set("move speed", 3,2,20));
	parameters.add(movePointsPadding.set("move points padding", 1,0,20));
	
	parameters.add(shapePreBlank.set("shape pre blank points", 1, 0, 20));
	parameters.add(shapePostBlank.set("shape post blank points", 1, 0, 20));
	
	parameters.add(dotMaxPoints.set("dot max points", 7, 0, 100));
	
	parameters.add(accelerationLine.set("line acceleration", 0.5, 0.1, 10));
	parameters.add(speedLine.set("line speed", 20,2, 100));
	parameters.add(overlapCircle.set("circle overlap", 20,0, 100));
	
	parameters.add(speedEasedLine.set("eased line speed", 8, 2, 20));
	parameters.add(paddingEasedLine.set("eased line padding", 1,0, 20));
  	parameters.add(spiralSpacing.set("spiral spacing", 10,1, 200));
    
    // where is this getting set up? 
	calibrationParameters.setName("Laser Calibration");
	
	colourChangeDelay = -6;
	
	warp.visible = true;
    
	warp.dragSpeed = 1; 
    
    
}

void LaserManager:: connectButtonPressed(){
	
	//if(connectButton!=isConnected) {
		if(!isConnected) {
			connectToEtherdream();
		} else {
			disconnectFromEtherdream();
		}
	//}

	
}


void LaserManager:: update() {
	
	etherdream.update();
	
	resetIldaPoints();
	previewMesh.clear();
	pathMesh.clear();
	

	
	//etherdreamStatus = etherdream.stateIsFound() ? "connected" : "disconnected";
	etherdreamStatus = etherdream.getDeviceStateString() + (etherdream.stateIsFound() ? " FOUND " : " NOT FOUND ") + ofToString(isConnected);
	
	//connectButton.se(etherdream.getDeviceStateString() == "Running")||(etherdream.getDeviceStateString() == "Ready");
	
	
	 if(isConnected) {
		 if(!etherdream.checkConnection(false)) {
			 isConnected = false;
			 disconnectFromEtherdream();
			 // auto reconnect
			 connectToEtherdream();
		}
	 }
	
	
			
	if(showSyncTest) {
		addDelayTest();
	}
	
	
	if(showRegistration) {
		
		//addLaserRectEased(pmin, pmax, white);
		addLaserLineEased(pmin, pmax, white);
		addLaserLineEased(ofPoint(pmax.x, pmin.y), ofPoint(pmin.x, pmax.y), white);
		
		ofPoint v = pmax - pmin;
		
		for(float x =0 ; x<=1; x+=0.2) {
			for(float y = 0; y<=1; y+=0.2) {
				addLaserDot(ofPoint(pmin.x + (v.x*x), pmin.y + (v.y*y)), white, 1);
				if(x<1) addLaserLineEased(ofPoint(pmin.x + (v.x*x), pmin.y + (v.y*y)), ofPoint(pmin.x + (v.x*(x+0.2)), pmin.y + (v.y*y)), ofColor::red);
				if(y<1) addLaserLineEased(ofPoint(pmin.x + (v.x*x), pmin.y + (v.y*y)), ofPoint(pmin.x + (v.x*x), pmin.y + (v.y*(y+0.2))), ofColor::red);
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
	
	//addLaserSpiral(ofPoint(200,200), ofFloatColor::white, 100, 200);
	

	
		
	// at this point we should report if the laser has disconnected.
	
	
	
	
}

void LaserManager::draw() {
	
	drawShapes();
	
	while(ildaPoints.size()<minPoints) {
		
		addIldaPoint(currentPosition, black);
		
	}
	
	
	vector<ofxIlda::Point> adjustedPoints;

	// SORT OUT COLOUR CHANGE DELAY.
	
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
	
	if((etherdream.getDeviceStateString() == "Running")||(etherdream.getDeviceStateString() == "Ready")) {
		etherdream.setPoints(adjustedPoints);
		etherdream.setPPS(pps);
	}
	

	
	
	ofPushStyle();
	
	
	if(renderLaserPreview) {
		
		renderPreview();
		
	}
	
	
  	ofNoFill();
	
	if(showMaskRectangle) maskRectangle.draw();
	
	
	
	ofPopStyle();
	
	// PATH TEST
	
	/*
	 ofPath laserPath;
	 laserPath.setMode(ofPath::COMMANDS);
	 laserPath.setStrokeWidth(2);
	 laserPath.setPolyWindingMode(OF_POLY_WINDING_POSITIVE);
	 laserPath.circle(100, 100, 100);
	 laserPath.circle(150, 100, 100);
	 //
	 laserPath.draw(300,300);
	 vector<ofPolyline> outlines = laserPath.getOutline();
	 
	 if(outlines.size()>0) {
	 ofPolyline line = outlines[0];
		 line.simplify(5);
		 line.draw();
	 }
	*/
	
	
	
}

void LaserManager::renderLaserPath(ofRectangle previewRectangle) {
	
	ofPushStyle();
	
	
	if((showLaserPath)){//||(showRegistration)) {
		
		ofPushMatrix();
		
		ofTranslate(previewRectangle.getTopLeft());
		float scale =  previewRectangle.width / appWidth;
		ofScale(scale, scale);
		
		ofDisableBlendMode();
		ofNoFill();
		ofSetLineWidth(1);
		ofSetColor(255,0,255);
		pathMesh.setMode(OF_PRIMITIVE_LINE_LOOP);
		pathMesh.draw();
		
		
		ofSetColor(255,255,255);
		pathMesh.setMode(OF_PRIMITIVE_POINTS);
		pathMesh.draw();
		ofPopMatrix();
	}
	
	
	// TODO - this needs to go somewhere else!
	warp.visible = showWarpPoints;
	warp.draw();

	ofPopStyle();

}


void LaserManager::addLaserDot(const ofPoint& ofpoint, ofFloatColor colour, float intensity){
	
	//ofPoint target = warp.getWarpedPoint(ofpoint);
	
	shapes.push_back(new LaserDot(ofpoint, colour, intensity));
}


void LaserManager::addLaserCircle(const ofPoint& ofpoint, ofFloatColor colour, float radius, float intensity){
	
	shapes.push_back(new LaserCircle(ofpoint, colour, radius, intensity, overlapCircle));
}

void LaserManager::addLaserSpiral(const ofPoint& position, ofFloatColor col, float rad1,float rad2, float fadeoutpoint,  float intens){
	shapes.push_back(new LaserSpiral(position, col, rad1, rad2,  fadeoutpoint,intens));
	
}


void LaserManager:: drawShapes() {
	
	
	// sort the dots by nearest neighbour
	
	if(shapes.size()==0) return; 
	vector<LaserShape*> sortedShapes;
	
	int numberSorted = 0;
	//int dotNum = shapes.size();
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
	
	//ofDrawBitmapString(ofToString(travelDistanceUnsorted)+"\n" +ofToString(travelDistanceSorted), ofPoint(10,40));
	
	ofPoint startPosition = sortedShapes[0]->startPos;
	
	for(int i = 0; i<sortedShapes.size(); i++) {
		
		LaserShape* shape = sortedShapes.at(i);

		if(!currentPosition.match(shape->startPos, 0.01)) {
			moveLaser(shape->startPos);
		}
		
		// PRE BLANK
		for(int i = 0; i<shapePreBlank; i++) {
			addIldaPoint(shape->startPos, black, 1);
		}
		
		
		// Is it a dot?
		LaserDot * dot = dynamic_cast<LaserDot*>(shape);
		if(dot) {
			drawLaserDot(*dot); 
		}
		
		// Is it a circle?
		LaserCircle * circle = dynamic_cast<LaserCircle*>(shape);
		if(circle) {
			drawLaserCircle(*circle);
		}
		
		// Is it a line?
		LaserLine * line = dynamic_cast<LaserLine*>(shape);
		if(line) {
			drawLaserLine(*line);
		}
		// Is it a spiral?
		LaserSpiral * spiral = dynamic_cast<LaserSpiral*>(shape);
		if(spiral) {
			drawLaserSpiral(*spiral);
		}
	
		// POST BLANK
		for(int i = 0; i<shapePostBlank; i++) {
			addIldaPoint(shape->endPos, black, 1);
		}
		
	}
	
	moveLaser(startPosition);
	
		
}

void LaserManager :: moveLaser(const ofPoint & targetpoint){
	
	ofPoint target = targetpoint;
	ofPoint start = currentPosition;

	ofPoint v = target-start;
		
	float blanknum = v.length()/moveSpeed + movePointsPadding;
	
	for(int j = 0; j<blanknum; j++) {
		
		float t = Quint::easeInOut((float)j, 0.0f, 1.0f, blanknum);
		
		ofPoint c = (v* t) + start;
		addIldaPoint(c, (showMovePoints && j%2==0) ? ofColor(100,0,0) : ofColor::black);
		
	}
	
}



void LaserManager:: addLaserLineEased(const ofPoint&startpoint, const ofPoint&endpoint, ofFloatColor colour) {
	shapes.push_back(new LaserLine(startpoint, endpoint, colour, 1));
}


void LaserManager:: drawLaserDot(LaserDot &dot) {
	//cout << i << " DOT!" << endl;
	int particlecount = dotMaxPoints;// ceil(dotMaxPoints* dot->intensity);

	for(int i = 0; i<particlecount; i++) {
		addIldaPoint(dot.startPos, dot.colour, dot.intensity);
	}
	
}

void LaserManager:: drawLaserCircle(LaserCircle &circle){
	
	float distanceTravelled = 2*PI*circle.radius + circle.overlapDistance;
	vector<float> unitDistances = getPointsAlongDistance(distanceTravelled, accelerationLine, speedLine);
	
	ofPoint p;
	ofColor segmentColour;
	
	for(int i = 0; i<unitDistances.size(); i++) {
		
		float unitDistance = unitDistances[i];
		float angle = ofMap(unitDistance,0,1,-circle.overlapAngle/2,360+(circle.overlapAngle/2)) ;
		
		segmentColour = circle.colour;
		
		if(angle<circle.overlapAngle/2) {
			segmentColour*= ofMap(angle, -circle.overlapAngle/2,circle.overlapAngle/2, 0, 1);
		} if(angle> 360 - circle.overlapAngle/2) {
			segmentColour *= ofMap(angle, 360 -circle.overlapAngle/2,360 + circle.overlapAngle/2, 1, 0);
		}			
		
		p.set(circle.pos);
		p.x+=sin(ofDegToRad(angle))*circle.radius;
		p.y-=cos(ofDegToRad(angle))*circle.radius;
		
		addIldaPoint(p, circle.colour, circle.intensity);
	}
}


vector<float> LaserManager:: getPointsAlongDistance(float distance, float acceleration, float maxspeed){
	
	vector<float> unitDistances;
	
	float acceleratedistance = (maxspeed*maxspeed) / (2*acceleration);
	float timetogettospeed = maxspeed / acceleration;
	
	float totaldistance = distance;
	
	float constantspeeddistance = totaldistance - (acceleratedistance*2);
	float constantspeedtime = constantspeeddistance/maxspeed;
	
	if(totaldistance<(acceleratedistance*2)) {
		
		constantspeeddistance = 0 ;
		constantspeedtime = 0;
		acceleratedistance = totaldistance/2;
		maxspeed = sqrt( acceleratedistance * 2 * acceleration);
		timetogettospeed = maxspeed / acceleration;
		
	}
	
	float totaltime = (timetogettospeed*2) + constantspeedtime;
	
	float timeincrement = totaltime / (floor(totaltime));
	
	float currentdistance;
	
	float t = 0;
		
	while (t <= totaltime + 0.001) {
		
		if(t>totaltime) t = totaltime;
		
		if(t <=timetogettospeed) {
			currentdistance = 0.5 * acceleration * (t*t);
			//ofSetColor(0,255,0);
		} else if((t>timetogettospeed) && (t<=timetogettospeed+constantspeedtime)){
			currentdistance = acceleratedistance + ((t-timetogettospeed) * maxspeed);
			//ofSetColor(255);
		} else  {
			float t3 = t - (timetogettospeed + constantspeedtime);
			
			currentdistance = (acceleratedistance + constantspeeddistance) + (maxspeed*t3)+(0.5 *(-acceleration) * (t3*t3));
			//ofSetColor(255,0,0);
			
		}
		
		unitDistances.push_back(currentdistance/totaldistance); 
		
		t+=timeincrement;
		
	}
	
	return unitDistances; 
	
}





void LaserManager:: drawLaserLine(LaserLine& line) {
	
	ofPoint start = line.startPos;// warp.getWarpedPoint(startpoint);
	ofPoint end = line.endPos;//warp.getWarpedPoint(endpoint);
	
	ofPoint vec = end - start;
	
	float speed = speedEasedLine;
	
	int iterations = floor(vec.length()/speed) + paddingEasedLine; // arbitrary amount to create enough ease points!
	
	// TODO add start and end blanks for lines?
	 
	for(float i = 0; i<iterations; i++) {
		
		float t = Quad::easeInOut(i/iterations, 0, 1, 1);
		
		addIldaPoint(start + (vec*t), line.colour, line.intensity);
		
	}
	
	
}

// can the shape itself be put in the object?

void LaserManager::drawLaserSpiral(LaserSpiral& spiral){
	
	// should probably be a setting
	
	//float spacing = spiralSpacing;
	int revolutions = ceil((spiral.radius2 - spiral.radius1)/spiralSpacing);
	//float spaceBetweenRevs = (spiral.radius2 - spiral.radius1)/revolutions;
	
	float maxAngle = 360 * revolutions;
	
	float currentAngle = 0;
	
	ofVec2f pos = spiral.startPos;
	
	float speed = 0;
	float maxSpeed = 20;
	
	float rotateSpeed = 1; 
	ofPolyline path;
	//path.setFilled(false);
	//path.setStrokeWidth(1);
	
	path.addVertex(spiral.startPos);
	
	while (currentAngle<=maxAngle) {
		
		pos.set(ofMap(currentAngle, 0, maxAngle, spiral.radius1, spiral.radius2), 0);
		pos.rotate(currentAngle);
		pos+=spiral.pos;
		
		//rotateSpeed = ofMap(currentAngle, 1, 45,0,maxSpeed, true);
		// should be a setting!
		currentAngle+=rotateSpeed;
		path.addVertex(pos); 
		
			
		//addIldaPoint(pos, spiral.colour, spiral.intensity);
		
	}
	
	float totaldistance = path.getPerimeter();
	
	vector<float> unitDistances = getPointsAlongDistance(totaldistance, accelerationLine, speedLine);

	for(int i = 0; i<unitDistances.size(); i++) {
		pos = path.getPointAtLength(min(unitDistances[i]*totaldistance, totaldistance-0.01f));
		cout << unitDistances[i] << endl; 
		addIldaPoint(pos, spiral.colour, spiral.intensity);
		
	}
	
	
}



void LaserManager::addLaserRectEased(const ofPoint&topLeft, const ofPoint&dimensions, ofFloatColor colour){
	
	addLaserLineEased(topLeft, ofPoint(topLeft.x+dimensions.x,topLeft.y), colour);
	addLaserLineEased(ofPoint(topLeft.x+dimensions.x,topLeft.y), topLeft+dimensions, colour);
	addLaserLineEased(topLeft+dimensions, ofPoint(topLeft.x,topLeft.y+dimensions.y), colour);
	addLaserLineEased(ofPoint(topLeft.x,topLeft.y+dimensions.y), topLeft, colour);
	
}

ofxIlda::Point LaserManager::ofPointToIldaPoint(const ofPoint& ofpoint, ofFloatColor colour){
	
	
	ofxIlda::Point ildapoint;
	
	ofPoint p = ofpoint;
	if(flipY) p.y= appHeight-p.y;
	if(flipX) p.x= appWidth-p.x;
	
	p.x = ofClamp(p.x, 0, appWidth);
	p.y = ofClamp(p.y, 0, appHeight);
	

	ildapoint.set(p, colour, pmin, pmax);
	return ildapoint;
	
}
ofPoint LaserManager::ildaPointToOfPoint(const ofxIlda::Point& ildapoint){
	
}

void LaserManager::addIldaPoint(ofPoint p, ofFloatColor c, float pointIntensity){
	
	bool offScreen = false;

	// TODO should be smarter about this. Ideally we should mark the on / off screen
	// points and add a move between them. 
	if(!maskRectangle.inside(p)) {
		offScreen = true;
		p.x = max(maskRectangle.x, p.x);
		p.x = min(maskRectangle.getRight(), p.x);
		p.y = max(maskRectangle.y, p.y);
		p.y = min(maskRectangle.getBottom(), p.y);
		
	}
	
	if(offScreen) c = ofFloatColor::black;
	
	previewMesh.addVertex(p);
	previewMesh.addColor(c);
	
	pathMesh.addVertex(p);
	//pathMesh.addColor(c);
	
	ofPoint warpedpoint = warp.getWarpedPoint(p);;
	
	//ofPoints.push_back(warpedpoint);

	c.r*=intensity*pointIntensity;
	c.g*=intensity*pointIntensity;
	c.b*=intensity*pointIntensity;
	
		
	ildaPoints.push_back(ofPointToIldaPoint(warpedpoint, c));
	
	currentPosition = p;
	
}

void LaserManager::resetIldaPoints() {
	
	ildaPoints.clear();

	
	//ofPoints.clear();
	
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

void LaserManager :: renderPreview() {
	
	// do dots first
	ofPushStyle(); 

	ofMesh mesh;
	
	vector <ofVec3f> vertices;
	vector <ofVec2f> texCoords;
	ofImage* image = &pointPreviewImage; 
	
	vertices.push_back(ofVec3f(    -0.5, -0.5 ));
	vertices.push_back(ofVec3f(  -0.5,  0.5 ));
	vertices.push_back(ofVec3f(  0.5,  -0.5 ));
	vertices.push_back(ofVec3f( 0.5,  0.5 ));
	
	texCoords.clear();
	texCoords.push_back(ofVec2f(0,0));
	texCoords.push_back(ofVec2f(0, image->height));
	texCoords.push_back(ofVec2f(image->width, 0));
	texCoords.push_back(ofVec2f(image->width, image->height));
	
	
	mesh.setMode(OF_PRIMITIVE_TRIANGLES);

	
	for(int i = 0; i<shapes.size(); i++) {
		
		LaserShape* shape = shapes[i];

			
		// Is it a dot?
		LaserDot * dot = dynamic_cast<LaserDot*>(shape);
		if(dot) {
			
			int vertexIndex = mesh.getNumVertices();
			
			for(int i = 0; i<vertices.size(); i++) {
				ofVec3f v = vertices[i];
				
				v*=dot->intensity*10;
				v+=dot->startPos;
				mesh.addVertex(v);
				mesh.addColor(dot->colour);
				mesh.addTexCoord(texCoords[i]);
				
			}
			
			mesh.addTriangle(vertexIndex, vertexIndex+1, vertexIndex+2);
			mesh.addTriangle(vertexIndex+1, vertexIndex+2, vertexIndex+3);
			
			
			// if you want a brighter spot in the middle...
			
			/*
			vertexIndex = mesh.getNumVertices();
			
			ofColor brighterColour = dot->colour;
			brighterColour.r+=50;
			brighterColour.g+=50;
			brighterColour.b+=50;
			
			
			for(int i = 0; i<vertices.size(); i++) {
				ofVec3f v = vertices[i];
				
				v*=dot->intensity*5;
				v+=dot->startPos;
				mesh.addVertex(v);
				mesh.addColor(brighterColour);
				mesh.addTexCoord(texCoords[i]);
				
			}
			
			mesh.addTriangle(vertexIndex, vertexIndex+1, vertexIndex+2);
			mesh.addTriangle(vertexIndex+1, vertexIndex+2, vertexIndex+3);
			*/
			
		}
				
		
	}
	image->bind();
	mesh.draw();
	image->unbind();
	
	
	mesh.clear();
	mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
	
	
	for(int i = 0; i<shapes.size(); i++) {
		
		LaserShape* shape = shapes[i];
		
		
		// Is it a dot?
		LaserCircle * circle = dynamic_cast<LaserCircle*>(shape);
		if(circle) {
			
			ofVec3f v(0,-circle->radius);
			mesh.addColor(ofColor::black);
			mesh.addVertex(v + circle->pos);
			
			for(int i = 0; i<=360; i+=20) {
				
				v.set(0, -circle->radius);
				v.rotate(i, ofVec3f(0,0,1)); 
				mesh.addColor(circle->colour);
				mesh.addVertex(v+circle->pos);
				
			}
			
			v.set(0, -circle->radius);
			mesh.addColor(ofColor::black);
			mesh.addVertex(v+circle->pos);
			
			
			
		}
		
		
		// Is it a line?
		LaserLine * line = dynamic_cast<LaserLine*>(shape);
		if(line) {
			mesh.addColor(ofColor::black);
			mesh.addVertex(line->startPos);
			
			mesh.addColor(line->colour);
			mesh.addVertex(line->startPos);
			mesh.addColor(line->colour);
			mesh.addVertex(line->endPos);
			
			mesh.addColor(ofColor::black);
			mesh.addVertex(line->endPos);
		}
		
	}
	
	ofSetLineWidth(1);
	mesh.draw();
	
	vector<ofFloatColor>& colours = mesh.getColors();
	
	for(int i = 0; i<colours.size(); i++) {
		colours[i].r*=0.2;
		colours[i].g*=0.2;
		colours[i].b*=0.2;
	}
	
	ofSetLineWidth(5);
	mesh.draw();
	
	ofSetLineWidth(9);
	mesh.draw();

	
	/*
	
	
	 
	 // Is it a circle?
	 LaserCircle * circle = dynamic_cast<LaserCircle*>(shape);
	 if(circle) {
	 
	 
	 path.clear();
	 path.setFilled(true);
	 path.setColor(circle->colour);
	 //path.setStrokeWidth(2);
	 path.circle(circle->pos, circle->radius);
	 path.draw();
	 
	 }
	 

	// Is it a line?
	LaserLine * line = dynamic_cast<LaserLine*>(shape);
	if(line) {
		drawLaserLine(*line);
	}
	// Is it a spiral?
	LaserSpiral * spiral = dynamic_cast<LaserSpiral*>(shape);
	if(spiral) {
		drawLaserSpiral(*spiral);
	}
	*/
	
	ofPopStyle();
	
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

