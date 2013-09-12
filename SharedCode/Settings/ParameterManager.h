//
//  ParameterManager.h
//  PixelPyrosNew
//
//  Created by Paul Hayes on 10/09/2013.
//
//

#pragma once

#include <map>
#include "ofMain.h"

class ParameterManager {
    public:
    
    ParameterManager(){};
    
    static ParameterManager * instance();
    
    void setup();
    
    void registerParameter(ofAbstractParameter);
    
    ofParameter<bool> getBoolParameter();
    ofParameter<float> getFloatParamter();
    ofParameter<int> getIntParamter();
    
    protected:
    static ParameterManager * parameterManager;
    
};

