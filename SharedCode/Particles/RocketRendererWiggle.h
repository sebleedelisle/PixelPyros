//
//  RocketRendererWiggle.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 08/10/2013.
//
//

#pragma once
#include "ofMain.h"
#include "LifeCycle.h"
#include "RocketRenderer.h"
#include "Cubic.h"

class RocketRendererWiggle : public RocketRenderer {


	public :
	
	void render(ofVec3f pos, ofVec3f vel, LifeCycle &life);
	

};