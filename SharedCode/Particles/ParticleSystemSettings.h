//
//  ParticleSystemSettings.h
//
//  Created by Seb Lee-Delisle on 31/07/2012.
//  Copyright (c) 2012 seb.ly. All rights reserved.
//

#pragma once
#include "ofMain.h"

#include "ColourModifier.h"
#include "VelocityModifierSettings.h"
#include "ParticleRendererBase.h"
#include "ParticleRendererShape.h"

typedef enum {
	PARTICLE_EMIT_BURST, 
	PARTICLE_EMIT_CONTINUOUS
} ParticleEmitMode;


class ParticleSystemSettings{

	public : 

	ParticleSystemSettings() {
		
		
	// PHYSICS
		speedMin = speedMax = 100;
		directionZ = -90;
		directionZVar = 180;
		directionY = directionYVar = 0; 
	
		drag = 1; 
		gravity.set(0,0,0); 
	
		// LIFE 
		lifeMin = lifeMax = 1; 

		// APPEARANCE
		sizeStartMin = sizeStartMax = 10;
		sizeChangeRatio = 0; 
		
		// COLOUR
		hueStartMin = hueStartMax = hueChange = 0; 
		brightnessStartMin = brightnessStartMax = brightnessEnd = 255; 
		saturationMin = saturationMax = saturationEnd = 0;
		
		// if you don't want the particle to start rendering yet, use this!
		renderDelayMin = renderDelayMax =0;
		
		shimmerMin = 1;
		timeSpeed = 1; 
		
		//EMISSION LIFE CYCLE
		emitLifeTime = 1;
		emitDelay = 0;
		
		// EMISSION MODE AND PARTICLE COUNT
		emitMode = PARTICLE_EMIT_CONTINUOUS;
		emitCount = 100; // number of Particles per second
		emitShape = NULL;
		emitShapeUseHue = false;
		emitPositionShape = NULL;
		
		
		// EMISSION CHANGE OVER TIME 
		// This will change the start size and hue of emitted
		// particles over time. Probably all I need to change. 
		emitStartSizeModifier = 1;  // Multiplier
		emitSpeedModifier = 1;		// Multiplier
		emitHueModifierOffset = 0;	// Offset
		
		emitInheritVelocity = 0;
		
		rotateMin = rotateMax = 0;
		rotateAxis.set(0,1,0);
		
		velocityModifierSettings = NULL;
		
		renderer = NULL;
		emitShape = NULL;
		doNotScale = false;
		
	};

	
	
	void initVelocity(ofVec3f& vel, int particleCount = 0) {
		
		if(emitShape==NULL) {
			vel.set(ofRandom(speedMin, speedMax), 0);
			vel.rotate(0,0,ofRandom(directionZ-directionZVar, directionZ+directionZVar));
			vel.rotate(0,ofRandom(directionY-directionYVar, directionY+directionYVar), 0 );
		} else {
			vel = emitShape->getVertex(particleCount%emitShape->getNumVertices());
			vel*=ofRandom(speedMin, speedMax);
			vel.rotate(0,ofRandom(-directionYVar, directionYVar),ofRandom(-directionZVar, directionZVar) );
			
		}
	};
	
	void initColourModifier (ColourModifier* c, LifeCycle& life) { 
		c->hueStart = ofRandom(hueStartMin, hueStartMax);
		
		if(emitHueModifierOffset!=0) { 
			c->hueStart += (life.unitLifeProgress *emitHueModifierOffset) ; 
		}
		c->hueEnd = c->hueStart + hueChange; 
		
		c->brightnessStart = ofRandom(brightnessStartMin, brightnessStartMax); 
		c->brightnessEnd = brightnessEnd; 
		
		c->saturationStart = ofRandom(saturationMin, saturationMax); 
		c->saturationEnd = saturationEnd;
		
	}
	
	bool doNotScale; 
	// PHYSICS
	float speedMin; 
	float speedMax; 
	
	float directionZ; 
	float directionZVar; 
	float directionY; 
	float directionYVar; 

	float drag; 
	ofVec3f gravity; 
	
	// PARTICLE LIFE
	float lifeMin; 
	float lifeMax; 

	// APPEARANCE : 
	float sizeStartMin; 
	float sizeStartMax;
	float sizeChangeRatio; 
	
	float hueStartMin; 
	float hueStartMax;
	float hueChange; 
	
	float brightnessStartMin; 
	float brightnessStartMax; 
	float brightnessEnd;
	
	float saturationMin; 
	float saturationMax;
	float saturationEnd;
	
	float renderDelayMin;
	float renderDelayMax;
	
	float timeSpeed;
	
	float shimmerMin; 

	ParticleRendererBase* renderer;

	//EMISSION LIFE CYCLE
	float emitLifeTime; 
	float emitDelay;
	
	// rotate around y axis from emit point
	float rotateMin;
	float rotateMax;
	ofVec3f rotateAxis;
	
	// EMISSION MODE AND PARTICLE COUNT
	ParticleEmitMode emitMode; 
	float emitCount; // number of Particles per second
	
	// EMISSION SHAPE FOR TEXT AND GEOMETRY
	ofMesh* emitShape;
	bool emitShapeUseHue;
	
	// shape for the particles to come from (for letters mostly)
	ofMesh* emitPositionShape;
	
	
	// EMISSION CHANGE OVER TIME 
	// This will change the start size, speed and hue of emitted
	// particles over time. Probably all I need to change. 
	float emitStartSizeModifier; 
	float emitSpeedModifier; 
	float emitHueModifierOffset; 
	//PhysicsObject * emitAttachedPhysicsObject; 
	float emitInheritVelocity;
	
	string startSound;

	VelocityModifierSettings * velocityModifierSettings;
	

};





