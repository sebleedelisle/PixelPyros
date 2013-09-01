//
//  TriggerableBase.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 28/08/2013.
//
//

#pragma once
#include "ofMain.h"

class TriggerableBase {

	public:
	
	virtual void doTrigger(ofVec3f& pos) {
		doTrigger(pos, 1,0);
		
		
	};
	virtual void doTrigger(ofVec3f& pos, float power) {
		
		doTrigger(pos, power, 0);
		
	};

	
	virtual void doTrigger(ofVec3f& pos, float power, float direction) {
		ofLog(OF_LOG_WARNING, "triggered");
	};
/*
	virtual TriggerableBase* clone() {
		return new TriggerableBase(*this);
	}
*/	

};