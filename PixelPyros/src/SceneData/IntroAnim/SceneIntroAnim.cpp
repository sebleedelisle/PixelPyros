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
	addTriggerPattern();
	
	video.loadMovie("video/pp titles v01.mov");
	video.setLoopState(OF_LOOP_NONE); 

	
	
}

void SceneIntroAnim::start() {
	
	Scene::start();
	video.play();

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
	
	float vidPosition = video.getPosition();
	
	if(vidPosition > 0.90) starBrightness = ofMap(vidPosition, 0.90,0.92,1,0, true);
	if(starBrightness<1.0) starBrightness+=0.005;
	
	//if(vidPosition > 0.98) next();
	//cout << starBrightness << endl;
	//cout << video.getPosition() << endl;
}

bool SceneIntroAnim::draw() {
	
	if(!Scene::draw()) return false;
	starfield.draw(starBrightness);
	
	ofPushStyle();
	ofPushMatrix();
	ofTranslate(APP_WIDTH/2, APP_HEIGHT/2);
	ofScale(0.7,0.7);
	ofTranslate(-APP_WIDTH/2, -APP_HEIGHT/2);
	
	ofSetColor(ofFloatColor(ofMap(video.getPosition(), 0.90,0.92,1,0, true)));
	
	video.draw(0,0, APP_WIDTH, APP_HEIGHT);
	ofPopMatrix();
	ofPopStyle();
	return true;
	
}


