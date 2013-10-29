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
	
	video.loadMovie("../../../Music/pp titles v01.mov");
	video.setLoopState(OF_LOOP_NONE); 
	textWriter.lineRandomness = 0;
	textWriter.colourFlickerMin = 1;
	vector<string> textlines;
	//textlines.push_back("PIXELPYROS");
	textlines.push_back("LASERS");
	textWriter.colour = ofColor::cyan;
	laserWordMesh = textWriter.getMesh(textlines, ofPoint(768, 300), 20, true);
	laserWordMesh.setMode(OF_PRIMITIVE_LINES);
	
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

	
	
}

void SceneIntroAnim::start() {
	
	Scene::start();
	//video.play();

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
	
	//textWriter.draw(ofRectangle(APP_WIDTH*0.2, APP_HEIGHT*0.2, APP_WIDTH*0.6,APP_HEIGHT*0.2), "LASERS", true);
	//laserWordMesh.draw();
	
	LaserManager& lm = *LaserManager::instance();
	
	
	
	vector<ofVec3f>& vertices = laserWordMesh.getVertices();
	
	for(int i = 0; i<vertices.size(); i+=2) {
		if(i+1>=vertices.size()) break;
		
		lm.addLaserLineEased(vertices[i], vertices[i+1], laserWordMesh.getColors()[i]);
		
		
	}
	
	ofSetColor(255);
	
	int pathnum = ofClamp(floor(ofMap(ofGetMouseX(), 0, APP_WIDTH, 0, logo.getNumPath(), true)), 0, logo.getNumPath()-1);
	
	logo.getPathAt(pathnum).draw(); 
	
	//logo.draw();
	
	
	for(int i=0; i<logo.getNumPath(); i++ ) {
		
		vector<ofPolyline>& lines = logo.getPathAt(i).getOutline();
		for(int j=0; j<lines.size(); j++) {
			ofPolyline& line = lines[j];
			/*
			vector <ofVec3f>& vertices = line.getVertices(); 
			for(int k = 0; k<vertices.size(); k++) {
				vertices[k]*=2;
			}*/
			
			lm.addLaserPolyline(line);
		}
	}
	
	
	return true;
	
}


