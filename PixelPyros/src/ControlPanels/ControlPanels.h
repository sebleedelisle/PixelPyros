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

class ControlPanels {
    
    public:
    
    ControlPanels():parameterManager(*ParameterManager::instance()){};
    void setup();
    
    protected:
    ParameterManager& parameterManager;
    
};