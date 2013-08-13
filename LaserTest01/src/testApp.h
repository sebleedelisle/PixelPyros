#pragma once

#include "ofMain.h"
#include "ofxEtherdream.h"
#include <math.h>
#include "Star.h"
#include "Quint.h"
#include "Linear.h"
#include "Expo.h"
#include "Back.h"
class testApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    
    
    
    ofxIlda::Frame ildaFrame;   // stores and manages ILDA frame drawings
	ofxIlda::Poly *triangle;
	
    ofxEtherdream etherdream;   // interface to the etherdream device
	
	vector<Star> stars;
	
	ofFloatColor white;
	ofFloatColor black;
	
	int endCount;
	int blankCount;

	
};
