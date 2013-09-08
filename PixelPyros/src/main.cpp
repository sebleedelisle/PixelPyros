#include "ofMain.h"
#include "ofApp.h"
#include "ofxFensterManager.h"
//#include "ofAppGlutWindow.h"

//========================================================================
int main( ){


    ofxFensterManager::setup(1536,1024,OF_WINDOW);
	//ofSetupOpenGL(1536,1024, OF_WINDOW);			// <--------
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new ofApp());

}
