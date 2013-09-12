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
    
    void registerParameter(ofAbstractParameter * params);
    
    void registerParameterGroup(string groupName, ofParameterGroup* group);
    
    ofParameter<bool> getBoolParameter(string name);
    ofParameter<float> getFloatParamter(string name);
    ofParameter<int> getIntParamter(string name);
    ofParameterGroup * getParameterGroup(string groupName);
    
    protected:
    static ParameterManager * parameterManager;
    
    map<string,ofAbstractParameter*> params;
    map<string,ofParameterGroup*> paramGroups;
};

