//
//  ControlPanels.h
//  PixelPyros
//
//  Created by Paul Hayes on 12/09/2013.
//
//

#pragma once

#include <iostream>
#include "ParameterManager.h"
#include "ofxPanel.h"
#include "ofxToggle.h"
#include "ofxSliderGroup.h"

class ControlPanels {
    
    public:
    
    ControlPanels():parameterManager(*ParameterManager::instance()){};
    void setup(ParameterManager * parameterManager);
    void draw();
    void drawPreviewScreen();
    void exit();
    void keyPressed(int key);
    void mouseMoved(int x, int y);
    
    ofFbo main;
    ofFbo camera;
    ofFbo motion;
    
    protected:

    void setupPanel( string name, ofRectangle rect, ofxPanel & panel );
    void setupPanel( string name, string filename, ofRectangle rect, ofxPanel & panel );
    void layoutPanels(vector<ofxPanel> panels,ofRectangle space );
    vector<ofxPanel> getVisiblePanels();
    
    ParameterManager& parameterManager;
    
    ofxPanel laserCalibration;
    ofxPanel projectorCalibration;
    ofxPanel cameraCalibration;
    
    ofxPanel laserGui;
    ofxPanel rendererGui;
    ofxPanel triggerGui;
    ofxPanel motionGui;
    
    ofVec2f previewScreenPosition;
    
    
    ofRectangle screen;
    ofVec2f padding;
    
    int monitorCount;
    
    
};