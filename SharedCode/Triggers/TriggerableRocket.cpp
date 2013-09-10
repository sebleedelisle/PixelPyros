//
//  TriggerableRocket.cpp
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 01/09/2013.
//
//

#include "TriggerableRocket.h"

TriggerableRocket :: TriggerableRocket() : particleSystemManager(*ParticleSystemManager::instance()) {
	
	//rocketSettings = NULL;





}



void TriggerableRocket ::doTrigger(ofVec3f& pos, float power, float direction){
	
	PhysicsObject *rocket = makeNewRocket(pos);

}



PhysicsObject * TriggerableRocket:: makeNewRocket(ofVec3f& pos) {
	
	//if(rocketSettings!=NULL) {
		PhysicsObject *rocket = particleSystemManager.addRocket(rocketSettings, pos);
	
	// can use this to adjust height of fireworks
	//rocket->velScalar.set(1,1,1);
	
	return rocket;
	
}
