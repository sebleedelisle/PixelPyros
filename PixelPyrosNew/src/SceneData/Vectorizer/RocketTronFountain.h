//
//  RocketBasic.h
//  ArchitectureCamera
//
//  Created by Seb Lee-Delisle on 17/08/2012.
//
//

#pragma once

#include "ParticleSystemSettings.h"
#include "ParticleRendererSquare.h"
#include "ParticleRendererGlitchLine.h"
//#include "ParticleRendererBitmap.h"

class RocketTronFountain : public RocketSettings {
	
    public :
    
    RocketTronFountain(float hueStartOffset = 0, float hueChange = 0, float explosionHue = 20, ParticleRendererBase * renderer1 = NULL, ParticleRendererBase * renderer2 = NULL) : RocketSettings() {
        
		
		particleRenderer = new ParticleRendererSquare();
		particleLineRenderer = new ParticleRendererGlitchLine(1.5);
		//particleLineRenderer->lineWidth = 2;
		//whiteImage.loadImage("img/ParticleWhite.png");
        
        // ParticleData
		// size range
		// size modifier
		// velocity range
		// life range
		// drag
		// gravity
		// colour
		// colour modifier
		// renderer
		
		// EmmisionData
		// Frequency
		// Burst/continuous
		// range of start sizes for particles
		// range of colours for particles
		
		// optional colour modifier
		
		// PHYSICS
		ps.speedMin = 0;
		ps.speedMax = 30;
		ps.directionZ = -90;
		ps.directionZVar = 90;
		//ps.directionZVar = 0;
		ps.directionYVar = 0;
		
		ps.drag = 0.90;
		ps.gravity.set(0,0);
		
		//LIFE
		ps.lifeMin = 0.5;
		ps.lifeMax = 0.7;
		
		//APPEARANCE
		
		ps.sizeStartMin = 4;
		ps.sizeStartMax = 6;
		ps.sizeChangeRatio = 1;
		
		ps.hueStartMin = -5+hueStartOffset;
		ps.hueStartMax = 0+hueStartOffset;
		ps.hueChange = hueChange;
		
		ps.brightnessStartMin = 230;
		ps.brightnessStartMax = 255;
		ps.brightnessEnd = 0;
		
		ps.saturationMin = 150;
		ps.saturationMax = 255;
		ps.saturationEnd = 255;
		
		//ps.shimmerMin = 0.1;
		
		// but also :
		// lifeExpectancy
		// delay
		
		ps.emitMode = PARTICLE_EMIT_CONTINUOUS;
		ps.emitCount = 30;
		
		ps.emitDelay = 0;
		ps.emitLifeTime= 1.4;
		
		ps.emitStartSizeModifier = 0;
		ps.emitSpeedModifier = 10;
		ps.emitHueModifierOffset = 0;
		
		//ps.emitAttachedPhysicsObject = &rocket;
		ps.emitInheritVelocity = 0;
		
		ps.startSound = "DirtyTechno";
		
		if(renderer1!=NULL)
			ps.renderer = renderer1;
		else
			ps.renderer = particleLineRenderer;
		
		
		// PHYSICS
		ps2.speedMin = 15;
		ps2.speedMax = 20;
		ps2.directionZ = 0;
		ps2.directionZVar = 90;
		ps2.directionYVar = 180;
		ps2.drag = 0.90;
		ps2.gravity.set(0,-30);
		
		//LIFE
		ps2.lifeMin = 1;
		ps2.lifeMax = 1.5;
		
		//APPEARANCE
		
		ps2.sizeStartMin = 2;
		ps2.sizeStartMax = 5;
		ps2.sizeChangeRatio = 5;
		
		ps2.hueStartMin = 0+hueStartOffset;
		ps2.hueStartMax = 0+hueStartOffset;
		ps2.hueChange = 0;
		
		ps2.brightnessStartMin = 20;
		ps2.brightnessStartMax = 70;
		ps2.brightnessEnd = 0;
		
		ps2.saturationMin = 100;
		ps2.saturationMax = 100;
		ps2.saturationEnd = 100;
		
		//ps.shimmerMin = 0.1;
		
		// but also :
		// lifeExpectancy
		// delay
		
		ps2.emitStartSizeModifier = 0;
		//ps2.emitSpeedModifier = 0;
		
		
		ps2.emitMode = PARTICLE_EMIT_CONTINUOUS;
		ps2.emitCount = 500;
		
		ps2.emitDelay = 0;
		ps2.emitLifeTime= 0.5;
		ps2.renderer = new ParticleRendererShape(); 
		
		
        startSpeedMin = 800;
		startSpeedMax = 950;
		direction = -90;
		directionVar = 10;
		gravity.y = 0;
		lifeTime =1.4;
		drag = 0.9; 
		
		addParticleSystemSetting(ps);
		//addParticleSystemSetting(ps2);
		
        
    };
	
	
	
	
	ofImage whiteImage;
	
	
	ParticleRendererBase* particleRenderer;
	ParticleRendererBase* particleLineRenderer;
	
	ParticleSystemSettings ps;
	
	ParticleSystemSettings ps2;
	
	
	
};
