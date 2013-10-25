#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){

    ofAppGLFWWindow* window = new ofAppGLFWWindow();
    window->setMultiDisplayFullscreen(true);

	ofSetupOpenGL(window,1536,1024, OF_FULLSCREEN);			// <--------
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new ofApp());

}
