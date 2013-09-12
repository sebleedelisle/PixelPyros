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
    
    protected:
    ParameterManager& parameterManager;
    
    /*-- Laser GUI begin --*/
    
    ofxPanel laserGui;
    
    ofParameter<int> numParticles;
	ofParameter<float> particleFlicker;
	ofParameter<float> speed;
    
	ofxColorSlider color;
    ofxToggle showParticles;
	ofxToggle showRectangle;
    
    /*-- Laser GUI end --*/

    
};