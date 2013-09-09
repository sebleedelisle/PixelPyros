//
//  FireworkFactory.cpp
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 09/09/2013.
//
//

#include "FireworkFactory.h"


FireworkFactory* FireworkFactory::instance() {
	
	if (factory == NULL) {
		factory = new FireworkFactory();
	}
	return factory;
	
}



TriggerSettings FireworkFactory::getBasicRocket(float hue , float hueChange ){
	
	
	TriggerSettings ts;
	
	// TODO - THIS IS BAD - should store these pointers somewhere and clear
	// them later.
	
	//ts.setRenderer(new TriggerRendererBase());
	TriggerableRocket* tr = new TriggerableRocket(particleSystemManager);
	
	RocketSettings rocketSettings;
	
	rocketSettings.startSpeedMin = 600;
	rocketSettings.startSpeedMax = 800;
	rocketSettings.direction = -90;
	rocketSettings.directionVar = 4;
	rocketSettings.gravity.y = 400;
	
	//rocketSettings.drag = 0.95;
	
	ParticleSystemSettings trails = getFlowerTrailParticles(hue, hueChange);
	ParticleSystemSettings explosion = getFlowerExplosionParticles(hue, hueChange);
	//ParticleSystemSettings explosionLines = getLineExplosionParticles(150, hueChange);
	
	trails.timeSpeed = explosion.timeSpeed = rocketSettings.timeSpeed = 0.7;
	
	explosion.emitDelay = trails.emitLifeTime = 2;
	
	rocketSettings.addParticleSystemSetting(trails);
	rocketSettings.addParticleSystemSetting(explosion);
	//rocketSettings.addParticleSystemSetting(explosionLines);
	
	tr->rocketSettings = rocketSettings;
	ts.setTriggerable(tr);
	
	return ts;
	
	
	
};

