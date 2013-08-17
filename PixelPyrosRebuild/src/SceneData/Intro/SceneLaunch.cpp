
#include "SceneLaunch.h"

SceneLaunch :: SceneLaunch(string scenename, ParticleSystemManager& psm, ofRectangle triggerarea) : Scene(scenename, psm, triggerarea) {

	
	
	TriggerPattern empty;
	addArrangement(empty);
	
	textWriter.glyphLineWeight = 1;
	textWriter.colour.set(80,240,250);
	
	LetterWritingPatternMaker patternMaker; 
	TriggerPattern textPattern = patternMaker.getPattern(psm, "Activated!", 15, 0.2, 400, APP_WIDTH/2, 12, 5, 48, 0.2, APP_WIDTH*0.7, letterMesh);

	//TriggerPattern textPattern2 = patternMaker.getPattern(psm, "#BDF12", 20, 0.2, 300, APP_WIDTH/2, 15, 5, 52, 0.2, APP_WIDTH*0.7, letterMesh);

	addArrangement(textPattern, true );
	

}

bool SceneLaunch :: draw() {
	if (Scene :: draw()) {
		// draw letters
		textWriter.lineRandomness = 0.02;
		textWriter.glyphLineWeight = 3;
		textWriter.colourFlickerMin = 0.4;
		textWriter.smooth = false;
		textWriter.drawFixedSize(ofRectangle(APP_WIDTH*0.2, APP_HEIGHT*0.1, APP_WIDTH *0.6, APP_HEIGHT * 0.2), "Brighton Digital ",8,true);
		textWriter.drawFixedSize(ofRectangle(APP_WIDTH*0.2, APP_HEIGHT*0.1 + 60, APP_WIDTH *0.6, APP_HEIGHT * 0.2), "Festival 2012 ",8,true);
		
		ofSetColor(200);
		letterMesh.setMode(OF_PRIMITIVE_POINTS);
		
		letterMesh.draw();
		
		
		
		return true;
	} else {
		
		return false;
	}
	
	
}
bool SceneLaunch :: update(float deltaTime) {
	// disables reworking of arrangements
	
	//updateTriggerArea = false;
	
	return Scene :: update(deltaTime);
	
}


ParticleSystemSettings SceneLaunch:: getSmoke() {
	
	float hueStartOffset = 200;
	float saturation = 0;
	ParticleSystemSettings ps2;
	// PHYSICS
	ps2.speedMin = 15;
	ps2.speedMax = 70;
	ps2.directionZ = -90;
	ps2.directionZVar = 90;
	ps2.directionY = -90; 
	ps2.directionYVar = 20;
	ps2.drag = 0.90;
	ps2.gravity.set(-40,-100);
	
	//LIFE
	ps2.lifeMin = 0.5;
	ps2.lifeMax = 2;
	
	//APPEARANCE
	
	ps2.sizeStartMin = 2;
	ps2.sizeStartMax = 5;
	ps2.sizeChangeRatio = 5;
	
	ps2.hueStartMin = 0+hueStartOffset;
	ps2.hueStartMax = 0+hueStartOffset;
	ps2.hueChange = 0;
	
	ps2.brightnessStartMin = 10;
	ps2.brightnessStartMax = 20;
	ps2.brightnessEnd = 0;
	
	ps2.saturationMin = saturation;
	ps2.saturationMax = saturation;
	ps2.saturationEnd = saturation;
	
	//ps2.shimmerMin = 0.8;
	
	// but also :
	// lifeExpectancy
	// delay
	
	ps2.emitStartSizeModifier = 0;
	//ps2.emitSpeedModifier = 0;
	
	
	ps2.emitMode = PARTICLE_EMIT_CONTINUOUS;
	ps2.emitCount = 800;
	
	ps2.emitDelay = 0;
	ps2.emitLifeTime= 0.5;
	
	ps2.renderer = new ParticleRendererShape();
	

	
	return ps2;
	
	
}

ParticleSystemSettings SceneLaunch:: getLetterSparks() {
	ParticleSystemSettings ps;
	
	ps.renderer = new ParticleRendererShape();
	ps.speedMin = 0;
	ps.speedMax = 200;
	
	ps.directionZ = 0;
	ps.directionZVar = 0;
	ps.directionY = -90;
	ps.drag = 0.93;
	ps.lifeMin = 0.01;
	ps.shimmerMin = 0;
	ps.emitCount = 1000;
	ps.emitSpeedModifier = 1;
	ps.emitStartSizeModifier = 1;
	
	ps.brightnessEnd = 0;
	
	ps.gravity.y = 200;
	
	
	return ps;
	
}



ParticleSystemSettings SceneLaunch:: getFuseSparkles() {
	ParticleSystemSettings ps;
	
	ps.renderer = new ParticleRendererLine(1,false);
	
	ps.directionZ = 0;
	ps.directionZVar = 90;
	ps.directionY = 0;
	ps.directionYVar = 180;
	ps.drag = 0.8;
	
	ps.lifeMin = 0.01;
	ps.lifeMax = 0.2; 
	ps.shimmerMin = 0;
	ps.emitCount = 1000;
	//ps.emitSpeedModifier = 0;
	
	ps.brightnessEnd = 0;
	ps.saturationEnd = 800;
	ps.hueStartMin = 20;
	ps.hueStartMax = 30;
	
	ps.speedMin = 100;
	ps.speedMax = 500;
	ps.gravity.y = 500;
	
	
	return ps;
	
}


ParticleSystemSettings SceneLaunch:: getLetterBurst() {
	ParticleSystemSettings ps;
	
	ps.renderer = new ParticleRendererLine(0,false);
	
	ps.speedMin = 200;
	ps.speedMax = 600;
	ps.gravity.y = 100;
	
	
	ps.directionZ = 0;
	ps.directionZVar = 10;
	ps.directionY = -90;
	ps.directionYVar = 10;
	
	ps.drag = 0.93;
	ps.lifeMin = 0.01;
	//ps.shimmerMin = 0;
	ps.emitCount = 5000;
	ps.emitSpeedModifier = 0.5;
	
	ps.sizeStartMin = 0;
	ps.sizeStartMin = 3;
	ps.brightnessStartMin =
		ps.brightnessStartMax = 255;
	
	ps.brightnessEnd = 0;
	ps.saturationEnd = 500;
	ps.hueStartMin = 20;
	ps.hueStartMax = 30;

	
	
	
	//ps.brightnessEnd = 0;
	
	ps.emitLifeTime = 10;
	
	
	
	return ps;
	
}


