#include "testApp.h"
#include "ofxIldaFrame.h"


//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0);
    
    etherdream.setup();
    etherdream.setPPS(50000);

	ofSetFrameRate(60);
	
	white.set(1,1,1);
	black.set(0,0,0);
	
	endCount = 15;
	blankCount = 30;

	
}

//--------------------------------------------------------------
void testApp::update(){
}


bool my_compare( ofPoint a, ofPoint b){
	return a.y < b.y;
}



//--------------------------------------------------------------
void testApp::draw() {
    
	
	if((stars.size()<100) && (ofGetFrameNum()%1==0)) {
		
		Star star;
		//star.delay = (float)i/(float)numPoints*2;
		stars.push_back(star);
		
	}
	
		
	vector<ofxIlda::Point> points;

	
	ofPoint pmin(ofGetWidth(), ofGetHeight());
	ofPoint pmax(ofGetWidth(), ofGetHeight());
	
	
	ofBeginShape();
	
	for(int i = 0; i<stars.size(); i++) {
		
		Star& star = stars.at(i);
		star.update(); 

	}
	
	
	ofSort(stars, my_compare);
	
	Star lastStar;
	
	
	for(int i = 0; i<=stars.size(); i++) {
		
		
		Star star = stars.at(i%stars.size());
		
		star.x /=ofGetWidth();
		star.y /=ofGetHeight();
		star.y = 1-star.y;
		
		//if(star.y<0) continue;
		
		
		//star*=0.7;
		//star.x +=0.5 - 0.35;
		//star.y +=0.5 - 0.35;
		
		
		if(i>0) {
			
			ofxIlda::Point point;
			
			
			ofPoint v = star-lastStar;
			
			float blanknum =  blankCount; //= v.length()*800;
			
			//cout << blanknum << "\n";
			
			
			//cout <<  "--------------------------------\n";
			for(int j = 0; j<blanknum; j++) {
				
				
				float t = Quint::easeOut((float)j, 0.0f, 1.0f, (float)blanknum);
				//cout << t<< "\n";
	//			((float)j/(float)blanknum);
				
				ofPoint c = (v* t) + lastStar;
				point.set(c, black);
				
				points.push_back(point);

				

			}
			
			
			
			point.set(star, white);
			for(int j = 0; j<endCount *star.brightness; j++) {
				points.push_back(point);
			}
			
			
			// to draw circles
			/*
			ofPoint circlePoint = star;
			float radius = 0.01;
			for(int j = 0; j<endCount; j++) {
				
				circlePoint.set(radius,0);
				
				float t = ((float)j/(float)endCount);
				circlePoint.rotate(t*360, ofPoint(0,0,1));
				circlePoint.y+=radius;
				circlePoint+=star; 
				point.set(circlePoint, white); 
				points.push_back(point);

			}*/
		}
		
		
		lastStar = star;
				
	}
	while (points.size()<600)  {
		ofxIlda::Point point;
		point.set(ofPoint(ofGetWidth()/2, ofGetHeight()/2), black);
		
		points.push_back(point);
		
	}
	
    // send points to the etherdream
    etherdream.setPoints(points);
	etherdream.checkConnection(true);
    
    //ofSetColor(255);
    //ofDrawBitmapString(ildaFrame.getString(), 10, 30);
	
	ofNoFill();
	ofMesh mesh;
	

	for(int i = 0; i<stars.size(); i++) {
		ofPoint& star = stars.at(i);
		
		mesh.addVertex(star);
	}
	
	ofSetColor(50,0,0);
	mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
	mesh.draw();
	
	ofSetColor(255,255,255);
	mesh.setMode(OF_PRIMITIVE_POINTS);
	mesh.draw();
	
	
	mesh.clear();
	
		for(int i = 0; i<points.size(); i++) {
		ofxIlda::Point& p = points.at(i);
		
		ofPoint v = ofPoint(p.x, p.y);
		v/=(float)INT16_MAX;
		v.y = 1-v.y; 
		v*=ofGetWidth();
		v.x+=ofGetWidth()/2;
		v.y-=ofGetWidth()/2;
		
		
		
		mesh.addVertex(v);
		
		//cout << v.x << " " <<  v.y << "\n";
	}
	
	ofSetColor(50,0,0);
	mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
	mesh.draw();
	
	ofSetColor(255,255,255);
	mesh.setMode(OF_PRIMITIVE_POINTS);
	mesh.draw();
	
	
	
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    switch(key) {
        case 'f': ofToggleFullscreen(); break;
            
            
            // clear the frame
        case 'c': ildaFrame.clear(); break;
            
            // draw rectangle
        case 'r': {
            ofPolyline p = ofPolyline::fromRectangle(ofRectangle(ofRandomuf(), ofRandomuf(), 0.01, 0.01));
			//ofPolyline p;// = new ofPolyline();
				
			//p.arc(ofRandomuf(),ofRandomuf(),0.005, 0.005,0,360,5);
            ildaFrame.addPoly(p);
			
        }
            break;

           // change color
			
        case 'R':
//			ildaFrame.params.output.color.r +=0.1;
//			if(ildaFrame.params.output.color.r  > 1.01) ildaFrame.params.output.color.r = 0;
			ildaFrame.params.output.color.r = 1-ildaFrame.params.output.color.r;
			break;
		case 'G':
			//ildaFrame.params.output.color.g +=0.1;
			//if(ildaFrame.params.output.color.g  > 1.01) ildaFrame.params.output.color.g = 0;
			ildaFrame.params.output.color.g = 1-ildaFrame.params.output.color.g;
			break;
        case 'B':
//			ildaFrame.params.output.color.b +=0.1;
//			if(ildaFrame.params.output.color.b  > 1.01) ildaFrame.params.output.color.b = 0;
			ildaFrame.params.output.color.b = 1-ildaFrame.params.output.color.b;

			break;            // toggle draw lines (on screen only)
        case 'l': ildaFrame.params.draw.lines ^= true; break;
            
            // toggle loop for last poly
        case 'o': ildaFrame.getLastPoly().setClosed(ildaFrame.getLastPoly().isClosed()); break;
            
            // toggle draw points (on screen only)
        case 'p': ildaFrame.params.draw.points ^= true; break;
            
            // adjust point count
        case '.': ildaFrame.polyProcessor.params.targetPointCount++; break;
        case ',': if(ildaFrame.polyProcessor.params.targetPointCount > 10) ildaFrame.polyProcessor.params.targetPointCount--; break;

            // adjust point count quicker
        case '>': ildaFrame.polyProcessor.params.targetPointCount += 10; break;
        case '<': if(ildaFrame.polyProcessor.params.targetPointCount > 20) ildaFrame.polyProcessor.params.targetPointCount -= 10; break;
            
            // flip image
        case 'x': ildaFrame.params.output.transform.doFlipX ^= true; break;
        case 'y': ildaFrame.params.output.transform.doFlipY ^= true; break;

            // cap image
        case 'X': ildaFrame.params.output.doCapX ^= true; break;
        case 'Y': ildaFrame.params.output.doCapY ^= true; break;

            // move output around
        case OF_KEY_UP: ildaFrame.params.output.transform.offset.y -= 0.05; break;
        case OF_KEY_DOWN: ildaFrame.params.output.transform.offset.y += 0.05; break;
        case OF_KEY_LEFT: ildaFrame.params.output.transform.offset.x -= 0.05; break;
        case OF_KEY_RIGHT: ildaFrame.params.output.transform.offset.x += 0.05; break;
            
            // scale output
        case 'w': ildaFrame.params.output.transform.scale.y += 0.05; break;
        case 's': ildaFrame.params.output.transform.scale.y -= 0.05; break;
        case 'a': ildaFrame.params.output.transform.scale.x -= 0.05; break;
        case 'd': ildaFrame.params.output.transform.scale.x += 0.05; break;
            
        case 'C': ildaFrame.drawCalibration(); break;
    }
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    // draw a line to the mouse cursor (normalized coordinates) in the last poly created
    //ildaFrame.getLastPoly().lineTo(x / (float)ofGetWidth(), y / (float)ofGetHeight());
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    // create a new poly in the ILDA frame
	ofxIlda::Poly poly = ildaFrame.addPoly();
	
}
