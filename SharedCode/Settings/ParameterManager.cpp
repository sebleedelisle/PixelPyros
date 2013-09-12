//
//  ParameterManager.cpp
//  PixelPyros
//
//  Created by Paul Hayes on 10/09/2013.
//
//

#include "ParameterManager.h"

ParameterManager * ParameterManager::instance() {
	if( parameterManager==NULL) {
		parameterManager = new ParameterManager();
	}
	return parameterManager;
}

ParameterManager * ParameterManager :: parameterManager = NULL;
