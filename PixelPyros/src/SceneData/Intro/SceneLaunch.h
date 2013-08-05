
#pragma once 

#include "Scene.h"
#include "ParticleRendererGlitchLine.h"

#include "ParticleRendererLine.h"
#include "ParticleRendererStar.h"
#include "ParticleRendererBitmap.h"
#include "RocketBasic.h"
#include "ParticleSystemManager.h"
#include "ofMain.h"
#include "TextWriter.h"

#include "LetterWritingPatternMaker.h"

class SceneLaunch : public Scene {
	
	public :
	
	SceneLaunch (string scenename, ParticleSystemManager& psm, ofRectangle triggerarea) ;
	
	bool update(float deltaTime); 
	bool draw(); 
	
	
	ParticleSystemSettings getSmoke();
	ParticleSystemSettings getLetterSparks();
	ParticleSystemSettings getFuseSparkles();
	
	ParticleSystemSettings getLetterBurst();

	ofMesh letterMesh;

	//ofImage softWhiteImage;
	
	TextWriter textWriter; 


};