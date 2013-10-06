// =============================================================================
//
// Copyright (c) 2009-2013 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#include "ofApp.h"


//------------------------------------------------------------------------------
void ofApp::setup()
{
    ofSetLogLevel(OF_LOG_VERBOSE);

 	connectCamera(); 


}


//------------------------------------------------------------------------------
void ofApp::videoResized(const void* sender, ofResizeEventArgs& arg)
{
    
        if(sender == &grabber)
        {
            std::stringstream ss;
            ss << "videoResized: ";
            ss << "Camera connected to: " << grabber->getURI() + " ";
            ss << "New DIM = " << arg.width << "/" << arg.height;
            ofLogVerbose("ofApp") << ss.str();
        }
    
}


//------------------------------------------------------------------------------
void ofApp::update()
{
    // update the cameras
	if(grabber!=NULL)
		grabber->update();
 
}

//------------------------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0,0,0);

	ofSetHexColor(0xffffff);
    
    int row = 0;
    int col = 0;
    
    int x = 0;
    int y = 0;
    
    int w = 640;
    int h = 480;
    
    float totalKbps = 0;
    float totalFPS = 0;
    
           
	ofPushMatrix();
	ofTranslate(x,y);
	ofSetColor(255,255,255,255);
	grabber->draw(0,0,w,h); // draw the camera
	
	ofEnableAlphaBlending();
	
	// draw the info box
	ofSetColor(0,80);
	ofRect(5,5,w-10,h-10);
	
	float kbps = grabber->getBitRate() / 1000.0f; // kilobits / second, not kibibits / second
	totalKbps+=kbps;
	
	float fps = grabber->getFrameRate();
	totalFPS+=fps;
	
	std::stringstream ss;
	
	// ofToString formatting available in 0072+
	ss << "          NAME: " << grabber->getCameraName() << endl;
	ss << "          HOST: " << grabber->getHost() << endl;
	ss << "           FPS: " << ofToString(fps,  2/*,13,' '*/) << endl;
	ss << "          Kb/S: " << ofToString(kbps, 2/*,13,' '*/) << endl;
	ss << " #Bytes Recv'd: " << ofToString(grabber->getNumBytesReceived(),  0/*,10,' '*/) << endl;
	ss << "#Frames Recv'd: " << ofToString(grabber->getNumFramesReceived(), 0/*,10,' '*/) << endl;
	ss << "Auto Reconnect: " << (grabber->getAutoReconnect() ? "YES" : "NO") << endl;
	ss << " Needs Connect: " << (grabber->getNeedsReconnect() ? "YES" : "NO") << endl;
	ss << "Time Till Next: " << grabber->getTimeTillNextAutoRetry() << " ms" << endl;
	ss << "Num Reconnects: " << ofToString(grabber->getReconnectCount()) << endl;
	ss << "Max Reconnects: " << ofToString(grabber->getMaxReconnects()) << endl;
	ss << "  Connect Fail: " << (grabber->hasConnectionFailed() ? "YES" : "NO");

	ofSetColor(255);
	ofDrawBitmapString(ss.str(), 10, 10+12);
	
	ofDisableAlphaBlending();
	
	ofPopMatrix();
    
    ofEnableAlphaBlending();
    ofSetColor(0,80);
    ofRect(5,5, 150, 40);
    
    ofDisableAlphaBlending();

}

//------------------------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if(key == ' ')
    {
		
		ofRemoveListener(grabber->videoResized, this, &ofApp::videoResized);
		
		
		connectCamera();

	
    }
}

void ofApp::connectCamera() {
	
	
	grabber = IPVideoGrabber::makeShared();
	
	// if your camera uses standard web-based authentication, use this
	// c->setUsername(cam.username);
	// c->setPassword(cam.password);
	
	// if your camera uses cookies for authentication, use something like this:
	// c->setCookie("user", cam.username);
	// c->setCookie("password", cam.password);
	
	grabber->setUsername("root");
	grabber->setPassword("sebseb");
	
	grabber->setCameraName("cam name");
	grabber->setURI("http://10.0.1.19/axis-cgi/mjpg/video.cgi?resolution=640x480");
	
	//grabber->setURI("http://148.61.142.228/axis-cgi/mjpg/video.cgi?resolution=320x240");
	
	
	
	
	grabber->connect(); // connect immediately
	
	// if desired, set up a video resize listener
	ofAddListener(grabber->videoResized, this, &ofApp::videoResized);

	
}
