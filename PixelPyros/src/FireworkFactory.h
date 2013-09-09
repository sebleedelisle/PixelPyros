//
//  FireworkFactory.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 09/09/2013.
//
//

#pragma once
#include "ofMain.h"
#include "TriggerSettings.h"
#include "TriggerableRocket.h"
#include "ParticleSystemSettings.h"


class FireworkFactory {
	
	public:
	
	static FireworkFactory* factory;

	FireworkFactory* instance();
	


	TriggerSettings getBasicRocket(float hue = 20, float hueChange = -5);
	TriggerSettings getFountain(float hueStartOffset = 150, float hueChange = 0);







};