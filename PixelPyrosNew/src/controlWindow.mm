
#include "controlWindow.h"

controlWindow::controlWindow(ofApp* app):laserManager(*LaserManager::instance()){
    mainApp = app;
}

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
    
    buttonDemo.addListener(this, &controlWindow::fullscreenButtonPressed);
    
    laserGui.ofxBaseGui::setPosition(500, 100);
    laserGui.useFrameBuffer(true);
    laserGui.setDefaultWidth(400);
    
    laserGui.setDefaultHeight(18);
	laserGui.setDefaultWidth(300);
	laserGui.setDefaultTextPadding(7);
	
	
	laserGui.setDefaultSpacing(2);
	laserGui.setDefaultElementSpacing(5);
	laserGui.setDefaultElementIndentation(1);
    
	
	//gui.setSpacing
	laserGui.loadFont("Verdana.ttf", 10, false);
	
	//ofDrawBitmapString("HELLO", 0,0);
	
	
	laserGui.setup("LaserTestGUI"); // most of the time you don't need a name
	
	//gui.setSize(500,30);
	//gui.setUseTTF(true);
	laserGui.add(showParticles.setup("Show Particles", true));
	laserGui.add(showRectangle.setup("Show Rectangle", false));
	laserGui.add(speed.set( "Speed", 1, 0, 5 ));
	laserGui.add(numParticles.set( "Num Particles", 40, 1, 300 ));
	
	
	laserGui.add(color.setup("Particle Colour",ofColor(100,100,140),ofColor(0,0),ofColor(255,255)));
	laserGui.add(particleFlicker.set("Flicker",0.5,0,1));
	laserGui.setPosition(0,0);
	laserGui.add(laserManager.parameters);
	
    
	laserGui.loadFromFile("settings.xml");


}

void controlWindow::fullscreenButtonPressed(){
    mainApp->getParent()->toggleFullscreen();
}

void controlWindow::update() {
}

void controlWindow::draw() {

	ofBackground(0, 0, 0);
	//ofSetHexColor(0xffffff);
	ofDrawBitmapString(ofToString(ofGetFrameRate()), 10, 10);
    
    gui.draw();
    laserGui.draw();

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

