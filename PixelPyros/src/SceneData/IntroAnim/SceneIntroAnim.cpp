//
//  SceneSpace.cpp
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 02/09/2012.
//
//

#include "SceneIntroAnim.h"


SceneIntroAnim::SceneIntroAnim(string scenename) : Scene(scenename){
	
	
	starfield.speed = 100;
	addEmptyTriggerPattern();
	addEmptyTriggerPattern();
	addEmptyTriggerPattern();
	addEmptyTriggerPattern();
	
	video.loadMovie("../../../Music/pp titles v05 NOLOGO.mov");
	video.setLoopState(OF_LOOP_NONE);
	video.setVolume(0.5); 
	textWriter.lineRandomness = 0;
	textWriter.colourFlickerMin = 1;
	
	textWriter.colour = ofColor::cyan;
	//laserWordMesh = textWriter.getMesh(textlines, ofPoint(768, 500), 20, true);
	//laserWordMesh.setMode(OF_PRIMITIVE_LINES);
	
	logo.load("img/logo.svg");
	
	//logo.getPathAt(0).draw();
	
	//logo.draw();
	
	//for(int i=0; i<logo.getNumPath(); i++ ) {
	/*
	vector<ofPolyline>lines = logo.getPathAt(0).getOutline();
	ofPolyline line = lines[0];
	float len = line.getPerimeter();
	
	for(float p = 0; p< line.getVertices().size(); p+=1) {
		
		cout << p<< " " <<line.getRotationAtIndexInterpolated(p) << endl;
		
		
	}
	*/
	//	for(int j=0; j<lines.size(); j++) {
	//		lm.addLaserPolyline(lines[j]);
	//	}
	//}

	ambientModeAllowed = false; 
	
}

void SceneIntroAnim::start() {
	
	Scene::start();
	video.play();
	video.setPosition(0);

	starBrightness = 0;		

}

void SceneIntroAnim::stop() {
	Scene::stop();
	
	video.stop();
}


bool SceneIntroAnim::update(float deltaTime) {
	if(!Scene::update(deltaTime)) return false;
	starfield.update(deltaTime);
	video.update();
	
	vidPosition = video.getPosition();
		
	if(vidPosition > 0.90) starBrightness = ofMap(vidPosition, 0.90,0.92,1,0, true);
	if(vidPosition > 0.97) finished = true;
	if(starBrightness<1.0) starBrightness+=0.005;
	
	//if(vidPosition > 0.98) next();
	//cout << starBrightness << ;;
	cout << video.getPosition() << endl;
}

bool SceneIntroAnim::draw() {
	
	if(!Scene::draw()) return false;
	starfield.draw(starBrightness);
	
	LaserManager& lm = *LaserManager::instance();
	

	ofPushStyle();
	
	ofPushMatrix();
	ofTranslate(APP_WIDTH/2, APP_HEIGHT/2);
	ofScale(0.6,0.6);
	ofTranslate(-APP_WIDTH/2, -APP_HEIGHT/2);
	
	ofSetColor(ofFloatColor(ofMap(video.getPosition(), 0.90,0.92,1,0, true)));
	
	video.draw(0,-200, APP_WIDTH, APP_HEIGHT);
	ofPopMatrix();
	
	ofPopStyle();
	
	float laserstart = 0.76;
	float laserend = 0.80;
	
	if((currentTriggerPatternIndex == 2) || ((vidPosition > laserstart) && (vidPosition<laserend))) {
		
		
		float progress = ofMap(vidPosition, laserstart,laserend,0,1,true);
		
		float brightness = 1;
		if(progress<0.2) brightness = ofMap(progress, 0, 0.2, 0,1);
		else if(progress>0.8) brightness = ofMap(progress, 0.8, 1, 1,0);
		if(currentTriggerPatternIndex == 2) brightness = 1;
		
		
		textWriter.colour = ofColor::cyan * brightness;
		
		laserWordMesh = textWriter.getMesh("LASERS", ofPoint(768, 400), ofMap(progress, 0, 1, 20, 23), true);;
		vector<ofVec3f>& vertices = laserWordMesh.getVertices();
		
		for(int i = 0; i<vertices.size(); i+=2) {
			if(i+1>=vertices.size()) break;
			
			lm.addLaserLineEased(vertices[i], vertices[i+1], laserWordMesh.getColors()[i]);
		}
	}
	// LASER LOGO
	
	
	float logostart = 0.49;
	float logoend = 0.53;
	
	if((currentTriggerPatternIndex == 1) || ((vidPosition>logostart) && ( vidPosition<logoend))) {
		
		float progress = ofMap(vidPosition, logostart,logoend,0,1,true);
		float scale = ofMap(progress,0,1,1.2,1.4,true);
		float brightness = 1;
		if(progress<0.2) brightness = ofMap(progress, 0, 0.2, 0,1);
		else if(progress>0.8) brightness = ofMap(progress, 0.8, 1, 1,0);
		
		if(currentTriggerPatternIndex == 1) brightness = 1;
		
		ofVec3f centrePoint = ofVec3f(logo.getWidth()/2, logo.getHeight()/2); 
		
		for(int i=0; i<logo.getNumPath(); i++ ) {
			
			vector<ofPolyline>& lines = logo.getPathAt(i).getOutline();
			for(int j=0; j<lines.size(); j++) {
				ofPolyline line = lines[j];
				vector<ofVec3f>& vertices = line.getVertices();
				for(int i = 0; i<vertices.size(); i++) {
					ofVec3f& v = vertices[i];
					v-=centrePoint;
					v*=scale;
					v.x+=APP_WIDTH/2;
					v.y +=APP_HEIGHT*0.3;
					
					
				}
				//cout << "brightness : " << brightness << endl;
				lm.addLaserPolyline(line,NULL, brightness);
			}
		}
	}
	
	
	if(currentTriggerPatternIndex == 3)  {	
		
		
		laserWordMesh = textWriter.getMesh("HAPPY BIRTHDAY BEN!", ofPoint(768, 400), 10, true);;
		vector<ofVec3f>& vertices = laserWordMesh.getVertices();
		
		for(int i = 0; i<vertices.size(); i+=2) {
			if(i+1>=vertices.size()) break;
			
			lm.addLaserLineEased(vertices[i], vertices[i+1], ofColor::cyan);
		}
	}
	
	
	return true;
	
}


