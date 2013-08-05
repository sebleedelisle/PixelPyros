//
//  RocketBasic.h
//  ArchitectureCamera
//
//  Created by Seb Lee-Delisle on 17/08/2012.
//
//

#pragma once

#include "ParticleSystemSettings.h"
#include "ParticleRendererShape.h"
//#include "ParticleRendererBitmap.h"

class RocketBasic : public RocketSettings {

    public :
    
    RocketBasic(float hueStartOffset = 0, float hueChange = 0, float explosionHue = 20, ParticleRendererBase * renderer1 = NULL, ParticleRendererBase * renderer2 = NULL) : RocketSettings() {
        
		
		particleRenderer = new ParticleRendererShape(); 
		
		whiteImage.loadImage("img/ParticleWhite.png"); 
        
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
		ps.speedMin = 20;
		ps.speedMax = 60;
		ps.directionZ = 0;
		ps.directionZVar = 90;
		ps.directionYVar = 180;
		ps.drag = 0.90;
		ps.gravity.set(0,30);
		
		//LIFE
		ps.lifeMin = 0.5;
		ps.lifeMax = 0.8;
		
		//APPEARANCE
		
		ps.sizeStartMin = 4;
		ps.sizeStartMax = 6;
		ps.sizeChangeRatio = 1;
		
		ps.hueStartMin = 0+hueStartOffset;
		ps.hueStartMax = 30+hueStartOffset;
		ps.hueChange = hueChange;
		
		ps.brightnessStartMin = 150;
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
		ps.emitCount = 1000;
		
		ps.emitDelay = 0;
		ps.emitLifeTime= 2;
		
		ps.emitStartSizeModifier = 0;
		ps.emitSpeedModifier = 0;
		ps.emitHueModifierOffset = 0;
		
		//ps.emitAttachedPhysicsObject = &rocket;
		ps.emitInheritVelocity = -0.5;
		
		ps.startSound = "SynthThud";
		
		if(renderer1!=NULL)
			ps.renderer = renderer1;
		else
			ps.renderer = particleRenderer;
		
		
		
		// PHYSICS
		ps2.speedMin = 650;
		ps2.speedMax = 700;
		ps2.directionZ = 0;
		ps2.directionZVar = 90;
		ps2.directionYVar = 180;
		ps2.drag = 0.90;
		ps2.gravity.set(0,30);
		
		//LIFE
		ps2.lifeMin = 0.5;
		ps2.lifeMax = 0.8;
		
		//APPEARANCE
		
		ps2.sizeStartMin = 15;
		ps2.sizeStartMax = 25;
		ps2.sizeChangeRatio = 0;
		
		ps2.hueStartMin = 0+explosionHue;
		ps2.hueStartMax = 5+explosionHue;
		ps2.hueChange = -20;
		
		ps2.brightnessStartMin = 155;
		ps2.brightnessStartMax = 155;
		ps2.brightnessEnd = 100;
		
		ps2.saturationMin = 50;
		ps2.saturationMax = 100;
		ps2.saturationEnd = 500;
		
		ps2.shimmerMin = 0.1;
		
		// but also :
		// lifeExpectancy
		// delay
		
		//ps2.emitMode = PARTICLE_EMIT_BURST;
		ps2.emitCount = 10000;
		
		ps2.emitDelay = 2;
		ps2.emitLifeTime= 0.05;
		
		ps2.startSound = "ExplosionSynth1";
		if(renderer2!=NULL)
			ps2.renderer = renderer2;
		else
			ps2.renderer = particleRenderer;
		
		
        startSpeedMin = 600;
		startSpeedMax = 700;
		direction = -90;
		directionVar = 5;
		gravity.y = 400;
		lifeTime =3; 
		
		addParticleSystemSetting(ps);
		addParticleSystemSetting(ps2);
		        
        
    };




	ofImage whiteImage; 


	ParticleRendererShape* particleRenderer; 

	ParticleSystemSettings ps;
	
	ParticleSystemSettings ps2;
	


};
