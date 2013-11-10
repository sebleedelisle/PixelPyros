//
//  ParticleRenderer.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 30/07/2012.
//  Copyright (c) 2012 seb.ly. All rights reserved.
//

#pragma once
#include "Particle.h"
#include "ofMain.h"



class ParticleRendererBase { 

	public:
	
    
    virtual void renderParticles(Particle* firstParticle, float scale = 1, float scaleCentreX = 0, float scaleCentreY = 0) = 0;
	
	void applyScaleMatrix(float scale, float scaleCentreX, float scaleCentreY) {
		ofTranslate(scaleCentreX, scaleCentreY);
		ofScale(scale, scale, scale);
		ofTranslate(-scaleCentreX, -scaleCentreY);
	}
	
	
	
	int historyCount=0;


};