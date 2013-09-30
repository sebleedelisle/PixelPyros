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

void ParameterManager::registerParameterGroup(string groupName, ofParameterGroup* group){
    paramGroups[groupName] = group;
}

ofParameterGroup * ParameterManager::getParameterGroup(string groupName){
	//TODO Requires error checking
    return paramGroups[groupName];
}

ParameterManager * ParameterManager :: parameterManager = NULL;
