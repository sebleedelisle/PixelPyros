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
	
    
    virtual void renderParticles(vector <Particle * > particles) = 0;
	
	int historyCount=0;


};