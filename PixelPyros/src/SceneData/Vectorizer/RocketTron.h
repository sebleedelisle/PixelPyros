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
#include "ParticleRendererStar.h"
#include "ParticleRendererLine.h"
#include "ParticleRendererCircle.h"

class RocketTron : public TriggerSettingsRocket {
	
    public :
    
    RocketTron(float hueStartOffset = 0, float hueChange = 0, float explosionHue = 0, ParticleRendererBase * renderer1 = NULL, ParticleRendererBase * renderer2 = NULL) : TriggerSettingsRocket() {
     
		particleLineRenderer.lineWidth = 2;
		
		
		/// ROCKETS WITH CYAN SQUARE BURSTS
		
		// STAR ROCKET HEAD
		
		
		//head.renderer = new ParticleRendererStar(30,45);
		head.renderer = new ParticleRendererCircle(12, false, 2, ofVec3f(100,0,0));
		
		
		head.speedMin = head.speedMax =0;
		head.lifeMin = 0.5;
		head.lifeMax = 0.8;
		head.sizeStartMin = 1;
		head.sizeStartMax = 1.2;
		head.sizeChangeRatio = 10;
		head.brightnessStartMin = 255;
		head.brightnessStartMax = 255;
		head.shimmerMin = 1; 
		
		head.saturationMin = 150;
		head.saturationMax = 200;
		head.saturationEnd = 255;

		head.hueStartMin = head.hueStartMax = 120; 
		
		head.brightnessEnd = 0; 
		head.emitMode = PARTICLE_EMIT_CONTINUOUS;
		head.emitCount = 100;
		head.emitDelay = 0;
		head.emitLifeTime= 2.2;
		head.emitStartSizeModifier = 0.1;
		
		head.startSound = "LaunchSweep";
		
		
		// rocket thrusters
		
		trails.speedMin = 0;
		trails.speedMax = 0;
		trails.directionZ = 0;
		trails.directionZVar = 0;
		trails.directionYVar = 180;
		trails.drag = 0.90;
		trails.gravity.set(0,30);
		
		//LIFE
		trails.lifeMin = 0.2;
		trails.lifeMax = 0.5;
		
		//APPEARANCE
		
		trails.sizeStartMin = 10;
		trails.sizeStartMax = 20;
		trails.sizeChangeRatio = 0;
		
		trails.hueStartMin = 110+hueStartOffset;
		trails.hueStartMax = 130+hueStartOffset;
		trails.hueChange = 0;
		
		trails.brightnessStartMin = 50;
		trails.brightnessStartMax = 65;
		trails.brightnessEnd = 255;
		
		trails.saturationMin = 150;
		trails.saturationMax = 255;
		trails.saturationEnd = 255;
		
		trails.emitMode = PARTICLE_EMIT_CONTINUOUS;
		trails.emitCount = 100;
		
		trails.emitDelay = 0;
		trails.emitLifeTime= 2.2;
		
		trails.emitStartSizeModifier = 0;
		trails.emitSpeedModifier = 0;
		trails.emitHueModifierOffset = 0;
		
		//trails.emitAttachedPhysicsObject = &rocket;
		trails.emitInheritVelocity = 0;
		
		//trails.startSound = "SynthThud";
		
		trails.renderer = new ParticleRendererShape();
		
		
		// flat circle explosion
		
		// PHYSICS
		explosion.speedMin = 600;
		explosion.speedMax = 800;
		explosion.directionZ = 0;
		explosion.directionZVar =0;
		explosion.directionYVar = 180;
		explosion.drag = 0.959;
		explosion.gravity.set(0,0);
		
		//LIFE
		explosion.lifeMin = 0.8;
		explosion.lifeMax = 1.2;
		
		//APPEARANCE
		
		explosion.sizeStartMin = 25;
		explosion.sizeStartMax = 35;
		explosion.sizeChangeRatio = 0;
		
		explosion.hueStartMin = 110+explosionHue;
		explosion.hueStartMax = 130+explosionHue;
		explosion.hueChange = 0;
		
		explosion.brightnessStartMin = 255;
		explosion.brightnessStartMax = 255;
		explosion.brightnessEnd = 255;
		
		explosion.saturationMin = 25;
		explosion.saturationMax = 75;
		explosion.saturationEnd = 200;
		
		explosion.shimmerMin = 0.3;
		
		// but also :
		// lifeExpectancy
		// delay
		
		//explosion.emitMode = PARTICLE_EMIT_BURST;
		explosion.emitCount = 10000;
		
		explosion.emitDelay = 2.2;
		explosion.emitLifeTime= 0.1;
		
		explosion.startSound = "LaunchTechnoLow";
		explosion.renderer = new ParticleRendererSquare();

		rocketSettings = new RocketSettings();
		
		rocketSettings->startSpeedMin = 650;
		rocketSettings->startSpeedMax = 750;
		rocketSettings->direction = -90;
		rocketSettings->directionVar = 1;
		rocketSettings->gravity.y = 400;
		rocketSettings->lifeTime =2.3;
		
        
    };
	
	void addParticleSystems() {
		
		if(rocketSettings==NULL) {
			//OOPS
			return;
		}
		//addParticleSystemSetting(head);
		rocketSettings->addParticleSystemSetting(trails);
		rocketSettings->addParticleSystemSetting(explosion);
		
		
	};
	
	ParticleSystemSettings trails, explosion, head;
	
	ParticleRendererSquare particleRendererSquare;
	ParticleRendererLine particleLineRenderer;
	
};
