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

class TriggerSettingsFountain : public TriggerSettingsRocket {
	
    public :
    
    TriggerSettingsFountain(float hueStartOffset = 150, float hueChange = 0) : TriggerSettingsRocket() {
		
        ParticleRendererBase * renderer;
		ParticleSystemSettings ps, ps2;

		
		rocketSettings = new RocketSettings();
		
        renderer = new ParticleRendererShape();
		
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
		ps.speedMax = 20;
		ps.directionZ = 0;
		ps.directionZVar = 90;
		ps.directionYVar = 180;
		ps.drag = 0.90;
		ps.gravity.set(0,30);
		
		//LIFE
		ps.lifeMin = 0.5;
		ps.lifeMax = 2;
		
		//APPEARANCE
		
		ps.sizeStartMin = 10;
		ps.sizeStartMax = 15;
		ps.sizeChangeRatio = 0;
		
		ps.hueStartMin = 0;
		ps.hueStartMax = 30;
		ps.hueChange = hueChange;
		
		ps.brightnessStartMin = 255;
		ps.brightnessStartMax = 255;
		ps.brightnessEnd = 255;
		
		ps.saturationMin = 0;
		ps.saturationMax = 0;
		ps.saturationEnd = 0;
		
		ps.shimmerMin = 0.1;
		
		// but also :
		// lifeExpectancy
		// delay
		
		ps.emitMode = PARTICLE_EMIT_CONTINUOUS;
		ps.emitCount = 200;
		
		ps.emitDelay = 0;
		ps.emitLifeTime= 0.6;
		
		ps.emitStartSizeModifier = 0;
		ps.emitSpeedModifier = 1;
		ps.emitHueModifierOffset = 0;
		
		//ps.emitAttachedPhysicsObject = &rocket;
		ps.emitInheritVelocity = 0.3;
		ps.startSound = "RocketFountain"; 
		
		//psystem.init(ps);
		
		// optional colour modifier
	
		
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
		
		ps2.renderer = ps.renderer = renderer; 
		//ps2.velocityModifierSettings = new VelocityModifierSettings(200,300);
		
		
        
        rocketSettings->startSpeedMin = 500;
		rocketSettings->startSpeedMax = 1000;
		rocketSettings->direction = -90;
		rocketSettings->directionVar = 5;
		rocketSettings->gravity.y = 300;
		rocketSettings->drag = 0.9;
		rocketSettings->setLifeTime(1);
		
		rocketSettings->addParticleSystemSetting(ps);
		rocketSettings->addParticleSystemSetting(ps2);
	   
        rechargeSettings = TriggerRechargeSettings::fast;
        
        
    };
	
	
	
		
	
		
};
