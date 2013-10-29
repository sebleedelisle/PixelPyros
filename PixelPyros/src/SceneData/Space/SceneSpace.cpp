//
//  SceneSpace.cpp
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 02/09/2012.
//
//

#include "SceneSpace.h"


SceneSpace::SceneSpace(string scenename) : Scene(scenename){
	
	loadMusicFile("StarlightFull.aif");
	
	starfield.speed = 100;
	
	FireworkFactory& fireworkFactory = *FireworkFactory::instance(); 
	
	softWhiteImage.loadImage("img/ParticleWhite.png");
	
	TriggerPattern blank;
	
	addTriggerPattern(blank);
	
	TriggerSettingsRocket* starFountain = getStarryFountain();
	
	// USED TO BE ROCKETFOUNTAIN OBJECT
	TriggerSettingsRocket* softCyanFountain = new TriggerSettingsFountain(120);

	TriggerPattern fountainPattern;
	fountainPattern.addTriggerSettings(softCyanFountain);
	
	addTriggerPattern(fountainPattern, "Soft fountains");

	
	TriggerPattern starryPattern;
	starryPattern.addTriggerSettings(starFountain);
	
	addTriggerPattern(starryPattern, "Starry fountains");
	
	TriggerSettingsRocket* planetTrigger = getPlanetRocket();
	
	planetTrigger->radius = 10;
	planetTrigger->hue = 20;
	planetTrigger->saturation = 150;

	TriggerPattern pattern;
	
	pattern.addTriggerSettings(softCyanFountain);
	pattern.addTriggerSettings(softCyanFountain);
	pattern.addTriggerSettings(planetTrigger);

	addTriggerPattern(pattern, "Fountains plus planet");
	
	TriggerSettingsRocket* triggerFluffy = fireworkFactory.getFluffyRocket();
	TriggerSettingsRocket* triggerFountain = new TriggerSettingsFountain(120);

	TriggerSettingsRocket* redFlower = getFlowerRocket(10);
	redFlower->radius = 8;
	redFlower->hue = 10;
	redFlower->saturation = 100;

	TriggerSettingsRocket* triggerBanger = fireworkFactory.getBangerRocket();
	
	TriggerPattern patternFluffy;
	
	patternFluffy.addTriggerSettings(triggerFluffy);
	patternFluffy.addTriggerSettings(triggerFountain);
	addTriggerPattern(patternFluffy, "Fluffy plus fountains");
	
	
	// fluffy with added flowers
	patternFluffy.addTriggerSettings(redFlower);
	addTriggerPattern(patternFluffy, "Fluffy plus red flower");
	
	
	// another fountain and banger
	patternFluffy.addTriggerSettings(triggerFountain);
	patternFluffy.addTriggerSettings(triggerBanger);
	
	addTriggerPattern(patternFluffy, "Fluffy, plus red flower plus bang");
	
	
	TriggerPattern multiColourFountains;
	
	float colours [4] = {170, 0, 220, 0};
	
	for(int i = 0; i<4; i++) {
		TriggerSettingsRocket* triggerRocketFountain = fireworkFactory.getFountain(colours[i]);
		triggerRocketFountain->getRocketSettings()->startSpeedMax *=2;
		triggerRocketFountain->getRocketSettings()->directionVar = 3;
				
		triggerRocketFountain->hue = colours[i];
		triggerRocketFountain->saturation = 100;
		
		multiColourFountains.addTriggerSettings(triggerRocketFountain);
	}
	addTriggerPattern(multiColourFountains, "multicolour fountains");
	
	
	
	TriggerSettingsRocket*  purpleFlower = getFlowerRocket(220);
	purpleFlower->radius = 8;
	purpleFlower->hue = 255-20;
	purpleFlower->saturation = 200;
	

	TriggerPattern patternNewColour;
	patternNewColour.addTriggerSettings(triggerFluffy);
	patternNewColour.addTriggerSettings(triggerFountain);
	patternNewColour.addTriggerSettings(purpleFlower);
	
	addTriggerPattern(patternNewColour, "fluffy plus purple flower");
	
	
	TriggerPattern endPattern;
	
	TriggerSettingsRocket*  bigCyanFlower = getSphereFlowerRocket(140);

	bigCyanFlower->hue = 140;
	bigCyanFlower->saturation = 200;
	bigCyanFlower->radius= 10;
	
	
	endPattern.addTriggerSettings(redFlower);
	endPattern.addTriggerSettings(bigCyanFlower);
	endPattern.addTriggerSettings(triggerBanger);
	endPattern.addTriggerSettings(triggerFountain);
	
	addTriggerPattern(endPattern, "Red flower, big cyan flower, bangs");
	
	
	
	ofMesh letterMesh;
	LetterWritingPatternMaker patternMaker;
	ParticleSystemManager& psm = *ParticleSystemManager::instance();
	TriggerPattern textPattern = patternMaker.getPattern(psm, "Goodnight!", 15, 0.2, 350, APP_WIDTH/2, 15, 5, 48, 1, APP_WIDTH*0.5, letterMesh);

	addTriggerPattern(textPattern, "Goodnight text");//, true );

		

	
	
}

bool SceneSpace::update(float deltaTime) {
	if(!Scene::update(deltaTime)) return false;
	starfield.update(deltaTime);
	
	
}

bool SceneSpace::draw() {
	
	if(!Scene::draw()) return false;
	starfield.draw();
	
	return true;
	
}




TriggerSettingsRocket* SceneSpace::getStarryFountain() {
	
	
	ParticleRendererStar* starRenderer = new ParticleRendererStar(8);
	
	ParticleSystemSettings stars;
	
	stars.renderer = starRenderer;
	
	stars.sizeStartMin = 0.2;
	stars.sizeStartMax = 0.5;
	stars.sizeChangeRatio = 3;
	
	stars.speedMin = 0;
	stars.speedMax = 20;
	
	stars.lifeMin = 1;
	stars.lifeMin = 1.2;
	
	stars.emitLifeTime =1.1;
	stars.emitDelay = 0;
	stars.emitCount = 200;
	stars.emitStartSizeModifier = 0;
	stars.emitSpeedModifier = 0;
	
	
	stars.brightnessEnd = 0;
	stars.saturationMin = 0;
	stars.saturationMax = 100;
	stars.hueStartMin = 100;
	stars.hueStartMax = 120;
	
	stars.shimmerMin = 0.1;
	stars.startSound = "Woosh";
	
	ParticleSystemSettings ps;
	
	ps.speedMin = 0;
	ps.speedMax = 20;
	ps.directionZ = 0;
	ps.directionZVar = 90;
	ps.directionYVar = 180;
	ps.drag = 0.90;
	ps.gravity.set(0,30);
	
	//LIFE
	ps.lifeMin = 0.5;
	ps.lifeMax = 1;
	
	//APPEARANCE
	
	ps.sizeStartMin = 10;
	ps.sizeStartMax = 15;
	ps.sizeChangeRatio = 0;
	
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
	ps.emitCount = 50;
	
	ps.emitDelay = 0;
	ps.emitLifeTime= stars.emitLifeTime;
	
	ps.emitStartSizeModifier = 0;
	ps.emitSpeedModifier = 1;
	ps.emitHueModifierOffset = 0;
	
	//ps.emitAttachedPhysicsObject = &rocket;
	ps.emitInheritVelocity = 0.3;
	ps.renderer = new ParticleRendererLine(1, true, 10);
		
	RocketSettings& rocketSettings = *new RocketSettings();
	
	rocketSettings.startSpeedMin = 900;
	rocketSettings.startSpeedMax = 1300;
	rocketSettings.direction = -90;
	rocketSettings.directionVar = 5;
	rocketSettings.gravity.y = 800;
	rocketSettings.drag = 0.96;
	rocketSettings.setLifeTime(stars.emitLifeTime);
	rocketSettings.timeSpeed = stars.timeSpeed =  ps.timeSpeed = 0.8;
	
	rocketSettings.addParticleSystemSetting(stars);
	rocketSettings.addParticleSystemSetting(ps);
	
	TriggerSettingsRocket* ts = new TriggerSettingsRocket();
	ts->addRocketSettings(&rocketSettings);
	ts->rechargeSettings = TriggerRechargeSettings::fast;
	
	return ts;
	
}





TriggerSettingsRocket* SceneSpace::getPlanetRocket() {
	
	renderer = new ParticleRendererShape();
	
	// ps = trails
	ParticleSystemSettings ps;
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
	
	ps.sizeStartMin = 2;
	ps.sizeStartMax = 3;
	ps.sizeChangeRatio = 0.5;
	
	ps.hueStartMin = 0;
	ps.hueStartMax = 30;
	ps.hueChange = 0;
	
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
	ps.emitLifeTime= 1.5;
	
	ps.emitStartSizeModifier = 0;
	ps.emitSpeedModifier = 0;
	ps.emitHueModifierOffset = 0;
	
	//ps.emitAttachedPhysicsObject = &rocket;
	ps.emitInheritVelocity = -0.5;
	
	ps.renderer = renderer;
	//psystem.init(ps);
	
	ps.startSound = "LaunchRocketSharp";
	
	
	// optional colour modifier
	
	// PLANET PARTICLES PS2
	
	ParticleSystemSettings ps2;
	// PHYSICS
	ps2.speedMin = 550;
	ps2.speedMax = 600;
	ps2.directionZ = 0;
	ps2.directionZVar = 3; //90;
	ps2.directionYVar = 3; //180;
	ps2.drag = 0.86;
	ps2.gravity.set(0,30);
	
	//LIFE
	ps2.lifeMin = 1.5;
	ps2.lifeMax = 2.5;
	
	//APPEARANCE
	
	ps2.sizeStartMin = 3;
	ps2.sizeStartMax = 6;
	ps2.sizeChangeRatio = 0;
	
	ps2.hueStartMin = 20;
	ps2.hueStartMax = 25;
	ps2.hueChange = -20;
	
	ps2.brightnessStartMin = 155;
	ps2.brightnessStartMax = 155;
	ps2.brightnessEnd = 100;
	
	ps2.saturationMin = 50;
	ps2.saturationMax = 100;
	ps2.saturationEnd = 500;
	
	//ps.shimmerMin = 0.1;
	
	// but also :
	// lifeExpectancy
	// delay
	
	ps2.emitCount = 20000;
	
	ps2.emitDelay = ps.emitLifeTime+0.2;
	ps2.emitLifeTime= 0.05;
	
	
	ps2.emitMode = PARTICLE_EMIT_BURST;
	ps2.emitShape = new ofMesh(ofMesh::icosphere(1,3));
	
	ps2.renderer = new ParticleRendererDoubleCircle();
		
	
	// RINGS PS3
	ParticleSystemSettings ps3;
	// PHYSICS
	ps3.speedMin = 650;
	ps3.speedMax = 750;
	ps3.directionZ = 0;
	ps3.directionZVar = 0;
	ps3.directionYVar = 180;
	ps3.drag = 0.92;
	ps3.gravity.set(0,30);
	
	//LIFE
	ps3.lifeMin = 1.5;
	ps3.lifeMax = 2.5;
	
	//APPEARANCE
	
	ps3.sizeStartMin = 5;
	ps3.sizeStartMax = 7;
	ps3.sizeChangeRatio = 0;
	
	ps3.hueStartMin = 10;
	ps3.hueStartMax = 15;
	ps3.hueChange = 0;
	
	ps3.brightnessStartMin = 200;
	ps3.brightnessStartMax = 255;
	ps3.brightnessEnd = 100;
	
	ps3.saturationMin = 200;
	ps3.saturationMax = 200;
	ps3.saturationEnd = 250;
	
	ps3.shimmerMin = 0.9;
	
	// but also :
	// lifeExpectancy
	// delay
	
	//ps3.emitMode = PARTICLE_EMIT_BURST;
	ps3.emitCount = 20000;
	
	ps3.emitDelay = ps2.emitDelay+0.1;
	ps3.emitLifeTime= 0.05;
	
	ps3.startSound = "SoftExplosion";
	
	
	//ps3.startSound = "ExplosionSynth1";
	
	ps3.renderer = new ParticleRendererCircle(7, true, 1, ofVec3f(90,0,0)); 
	
	
	ps2.rotateMin = -20;
	ps2.rotateMax = 20;
	ps3.rotateMin = -20;
	ps3.rotateMax = 20;
	
	RocketSettings& rocketSettings = *new RocketSettings();
	
	rocketSettings.startSpeedMin = 1100;
	rocketSettings.startSpeedMax = 1300;
	rocketSettings.direction = -90;
	rocketSettings.directionVar = 5;
	rocketSettings.gravity.y = 400;
	rocketSettings.drag = 0.97;
	
	rocketSettings.timeSpeed = 0.5;
	
	//ps.timeSpeed = ps2.timeSpeed = ps3.timeSpeed = 0.8;

	rocketSettings.addParticleSystemSetting(ps);
	rocketSettings.addParticleSystemSetting(ps2);
	rocketSettings.addParticleSystemSetting(ps3);
	
	TriggerSettingsRocket* ts = new TriggerSettingsRocket();
	ts->addRocketSettings(&rocketSettings);
	ts->rechargeSettings = TriggerRechargeSettings::slow;
	
	return ts;

	
	
	
}


TriggerSettingsRocket* SceneSpace :: getFlowerRocket(float hue , float hueChange){
	
	RocketSettings& rocketSettings = *new RocketSettings();
	
	rocketSettings.startSpeedMin = 1500;
	rocketSettings.startSpeedMax = 1900;
	rocketSettings.directionVar = 4;
	rocketSettings.gravity.y = 200;
	rocketSettings.drag = 0.92;
	
	ParticleSystemSettings trails = getFlowerTrailParticles(hue, hueChange);
	ParticleSystemSettings explosion = getFlowerExplosionParticles(hue, hueChange);
	explosion.drag = 0.88;
	ParticleSystemSettings explosionLines = getLineExplosionParticles(150, hueChange);
	//explosion.drag = 0.88;
	explosion.emitDelay = explosionLines.emitDelay = trails.emitLifeTime = 2;
	

	rocketSettings.timeSpeed = trails.timeSpeed = explosion.timeSpeed = explosionLines.timeSpeed = 0.7;

	rocketSettings.addParticleSystemSetting(trails);
	rocketSettings.addParticleSystemSetting(explosion);
	rocketSettings.addParticleSystemSetting(explosionLines);
	
	
	
	TriggerSettingsRocket* ts = new TriggerSettingsRocket();
	ts->addRocketSettings(&rocketSettings);
	ts->rechargeSettings = TriggerRechargeSettings::slow;
	
	return ts;

	
	
};




TriggerSettingsRocket* SceneSpace :: getSphereFlowerRocket(float hue , float hueChange ){
	
	RocketSettings& rocketSettings = *new RocketSettings();
	
	rocketSettings.startSpeedMin = 1100;
	rocketSettings.startSpeedMax = 1400;
	rocketSettings.directionVar = 4;
	rocketSettings.gravity.y = 200;
	rocketSettings.drag = 0.95;
	
	ParticleSystemSettings trails = getFlowerTrailParticles(hue, hueChange);
	ParticleSystemSettings explosion = getFlowerExplosionParticles(hue, hueChange);
	explosion.directionZ = 0;
	explosion.directionZVar = 90;
	explosion.directionY = 0;
	explosion.directionYVar = 180;
	explosion.speedMin = 900;
	explosion.speedMax = 1000;
	explosion.rotateMin = -50;
	explosion.rotateMax = 50;
	
	
	ParticleSystemSettings explosionLines = getLineExplosionParticles(150, hueChange);
	ParticleSystemSettings crackles = FireworkFactory::instance()->getBangerCrackles();
	crackles.renderer = new ParticleRendererStar(20, 70);
	crackles.brightnessStartMax = 150;
	crackles.brightnessStartMin = 100;
	crackles.sizeStartMax = 5;
	crackles.sizeStartMin = 3;
	//	crackles.emitDelay = 0;
	//	crackles.startSound = "";
	//	crackles.emitMode = PARTICLE_EMIT_CONTINUOUS;
	//	crackles.renderDelayMin = 0.01;
	//	crackles.renderDelayMax = 0.2;
	//	crackles.speedMin = 0;
	//	crackles.speedMax = 0.5;
	
	explosion.emitDelay = explosionLines.emitDelay = crackles.emitDelay = trails.emitLifeTime = 2;
	
	ParticleSystemSettings laserExplosion = FireworkFactory::instance()->getLaserExplosionParticles(hue, hueChange);
	
	laserExplosion.emitDelay = explosion.emitDelay-0.05;
	rocketSettings.timeSpeed = trails.timeSpeed = explosion.timeSpeed = explosionLines.timeSpeed = crackles.timeSpeed = laserExplosion.timeSpeed = 0.5;
	
	rocketSettings.addParticleSystemSetting(trails);
	rocketSettings.addParticleSystemSetting(explosion);
	rocketSettings.addParticleSystemSetting(laserExplosion);
	rocketSettings.addParticleSystemSetting(explosionLines);
	rocketSettings.addParticleSystemSetting(crackles);
	
	TriggerSettingsRocket* ts = new TriggerSettingsRocket();
	ts->addRocketSettings(&rocketSettings);
	ts->rechargeSettings = TriggerRechargeSettings::slow;
	ts->rotateMirrorOffset = 10; 
	
	return ts;
	
	
	
};


ParticleSystemSettings SceneSpace :: getFlowerTrailParticles(float hue, float hueChange ){
	
	
	ParticleSystemSettings trails;
	trails.renderer = new ParticleRendererLine(1.5, true, 3);
	//pss.directionZVar = 20;
	trails.speedMin = 10;
	trails.speedMax = 10;
	trails.sizeStartMin = trails.sizeStartMax = 3;
	trails.hueStartMin = trails.hueStartMax = hue;
	trails.hueChange = hueChange;
	trails.saturationMin = trails.saturationMax = 0;
	trails.saturationEnd = 300;
	trails.brightnessStartMin = trails.brightnessStartMin = trails.brightnessEnd = 255;
	
	trails.emitInheritVelocity = -0.1;
	trails.emitCount = 500;
	
	
	trails.shimmerMin = 0;
	trails.lifeMin = 0.1;
	trails.lifeMax = 0.3;
	trails.startSound = "LaunchRocketSharp";
	
	return trails;
	
	
};
ParticleSystemSettings SceneSpace :: getFlowerExplosionParticles(float hue, float hueChange){
	
	
	
	ParticleSystemSettings explosion;
	explosion.renderer = new ParticleRendererBitmap(&softWhiteImage);
	
	//pss.directionZVar = 20;
	explosion.speedMin = 550;
	explosion.speedMax = 600;
	explosion.directionZ = 0;
	explosion.directionZVar = 90;
	explosion.directionYVar = 180;
	explosion.drag = 0.90;
	explosion.gravity.set(0,30);

	
	explosion.sizeStartMin = 20;
	explosion.sizeStartMax = 40;
	explosion.hueStartMin = explosion.hueStartMax = hue;
	explosion.hueChange = hueChange;
	explosion.saturationMin = explosion.saturationMax = 0;
	explosion.saturationEnd = 500;
	explosion.brightnessStartMin = explosion.brightnessStartMin = 255;
	explosion.brightnessEnd = 0;
	
	explosion.shimmerMin = 0.5;
	explosion.lifeMin = 0.5;
	explosion.lifeMax = 1;
	
	explosion.emitMode = PARTICLE_EMIT_BURST;
	explosion.emitLifeTime = 0.1;
	explosion.emitCount = 3000;
	
	explosion.startSound = "SoftExplosion";
	
	
	return explosion;
	
	
}
ParticleSystemSettings SceneSpace :: getLineExplosionParticles(float hue, float hueChange){
	
	
	
	ParticleSystemSettings explosion;
	explosion.renderer = new ParticleRendererLine(2, true, 4);
	
	//pss.directionZVar = 20;
	explosion.speedMin = 300;
	explosion.speedMax = 400;
	explosion.drag = 0.95;
	explosion.gravity.y = 100;
	
	explosion.sizeStartMin = 5;
	explosion.sizeStartMax = 10;
	explosion.hueStartMin = explosion.hueStartMax = hue;
	explosion.hueChange = hueChange;
	explosion.saturationMin = explosion.saturationMax = 0;
	explosion.saturationEnd = 150;
	explosion.brightnessStartMin = explosion.brightnessStartMin =  255;
	explosion.brightnessEnd = 0;
	
	explosion.shimmerMin = 0.5;
	explosion.lifeMin = 0.8;
	explosion.lifeMax = 1.2;
	
	//explosion.emitMode = PARTICLE_EMIT_BURST;
	explosion.emitLifeTime = 0.1;
	explosion.emitCount = 2000;
	
	//explosion.startSound = "RetroExplosion";
	
	
	return explosion;
	
	
}
