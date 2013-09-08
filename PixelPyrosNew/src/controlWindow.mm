
#include "controlWindow.h"


void controlWindow::setup() {
    ofSetWindowShape(800, 600);
    ofSetWindowTitle("PixelPyros Control Panel");
    
    ofSetVerticalSync(true);
    
    gui.setDefaultHeight(32);
	gui.setDefaultWidth(400);
	gui.setDefaultTextPadding(10);
    gui.useFrameBuffer(true);
	
	gui.setDefaultSpacing(2);
	gui.setDefaultElementSpacing(5);
	gui.setDefaultElementIndentation(1);
    
	gui.loadFont("Verdana.ttf", 12, false);
    gui.setup("BetterGUI Test"); // most of the time you don't need a name
    
    gui.add(toggleDemo.setup("Toggle Button", true));
    gui.add(sliderDemo.setup("Slider Demo",0.5,0,1));
	gui.add(intSliderDemo.setup("Integer Slider Demo", 0, 128, 255));
    gui.add(colorSliderDemo.setup("Color Demo", ofColor::black, ofColor::black, ofColor::white));
    gui.add(buttonDemo.setup("Butto Demo"));
    gui.add(labelDemo.setup("Label Demo","label text"));

}

void controlWindow::update() {
	
}

void controlWindow::draw() {

	ofBackground(0, 125, 200);
	
	ofSetHexColor(0xffffff);
	ofDrawBitmapString(ofToString(ofGetFrameRate()), 10, 10);
    
    gui.draw();

}



void controlWindow::keyPressed(int key) { 

}

void controlWindow::keyReleased(int key) { 

}

void controlWindow::mouseMoved(int x, int y) { 

}

void controlWindow::mouseDragged(int x, int y, int button) {

}

void controlWindow::mousePressed(int x, int y, int button) { 

}

void controlWindow::mouseReleased() { 

}

void controlWindow::mouseReleased(int x, int y, int button ){ 

}
 
void controlWindow::mouseScrolled(float x, float y) { 

}

