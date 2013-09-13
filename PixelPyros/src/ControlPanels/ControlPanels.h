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
    void exit();
    void keyPressed(int key);
    
    protected:

    void setupPanel( string name, string filename, ofRectangle rect, ofxPanel & panel );

    ParameterManager& parameterManager;
    
    ofxPanel laserGui;
    ofxPanel rendererGui;
    ofxPanel triggerGui;
    ofxPanel motionGui;
    
};