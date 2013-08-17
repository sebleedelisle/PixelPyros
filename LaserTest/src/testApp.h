#pragma once

#include "ofMain.h"

#include "LaserManager.h"
#include "Particle.h"


class testApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
   
	LaserManager laserManager;
	
	vector <Particle> particles; 

};
