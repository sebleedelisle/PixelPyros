//
//  ControlPanels.cpp
//  PixelPyros
//
//  Created by Paul Hayes on 12/09/2013.
//
//

#include "ControlPanels.h"
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_COCOA
#define GLFW_EXPOSE_NATIVE_NSGL
#include "GLFW/glfw3native.h"


void ControlPanels::setup(ParameterManager * parameterManager) { // , vector<ofRectangle> screens){
	
	// no GUI for 0
	panelMode = 0;

	int heightSmall = 30;
	 
    ofxBaseGui::setDefaultWidth(500);
    ofxBaseGui::setDefaultHeight(20);
	ofxBaseGui::setDefaultSpacing(4);
    ofxBaseGui::setDefaultElementSpacing(5);
	ofxBaseGui::setDefaultElementIndentation(1);
	ofxBaseGui::setDefaultTextPadding(7);
    
	setupPanel( "App", "appSettings.xml", ofRectangle(0,0, 400, heightSmall ), appGui );
	appGui.add( *parameterManager->getParameterGroup("app") );
	appGui.load();
	
    setupPanel( "Laser", "laserSettings.xml", ofRectangle( 0, 0, 400, heightSmall ), laserGui );
	
	laserGui.add(&(LaserManager::instance()->connectButton));
    laserGui.add( *parameterManager->getParameterGroup("laser") );

    laserGui.load();
    laserGui.getGroup("Laser Manager").getToggle("Etherdream connect") = false;
    laserGui.getGroup("Laser Manager").getLabel("status") = "";
    
    setupPanel( "Renderer", "rendererSettings.xml", ofRectangle(0, 0, 400, heightSmall ), rendererGui );
    rendererGui.add( *parameterManager->getParameterGroup("renderer") );
    rendererGui.add( *parameterManager->getParameterGroup("particles") );
    rendererGui.load();
    
    setupPanel( "Triggers", "triggerSettings.xml", ofRectangle(0, 0, 400, heightSmall ), triggerGui );
    triggerGui.add( *parameterManager->getParameterGroup("triggers") );
    triggerGui.load();
    
    setupPanel( "Motion", "motionDetectionSettings.xml", ofRectangle( 0,0, 400, heightSmall ), motionGui );
    motionGui.add( *parameterManager->getParameterGroup("motion") );
    //motionGui.load();
	
	setupPanel( "Camera", "cameraSettings.xml", ofRectangle( 0,0, 400, heightSmall ), cameraGui );
    cameraGui.add( *parameterManager->getParameterGroup("camera") );
    cameraGui.load();
    
//    setupPanel( "Laser Calibration", "laserCalibrationSettings.xml", ofRectangle( 0, 0, 400, heightSmall ), laserCalibration );
//    laserCalibration.add( *parameterManager->getParameterGroup("laser calibration") );
//    laserCalibration.load();
	
	//updatePositions(screens);
    
}
void ControlPanels :: updatePositions(vector<ofRectangle> screens){
	
    // I kinda feel like the logic for figuring out which screen is for the UI
	// should be done in ofApp and just passed in here? - Seb 
	
	monitorCount = screens.size();
	// Assumes GUI will always be on the last monitor, ie
	// the right-most monitor.
	
	screen = screens.back();
	
	ofVec3f padding = ofVec3f(20,20);
	ofVec3f position = screen.getPosition() + padding;
	
	position.x = screen.getRight() - padding.x*2 - rendererGui.getWidth()- appGui.getWidth();
	position.y = screen.getTop() + padding.y;
	appGui.setPosition(position);
	
	position.x = screen.getRight() - padding.x - rendererGui.getWidth();
	position.y = screen.getTop() + padding.y;
	rendererGui.setPosition(position);
	
	
	// -----------------------
	
	position.x = screen.getRight() - padding.x*3 - cameraGui.getWidth() - motionGui.getWidth() - triggerGui.getWidth();
	position.y = screen.getTop() + padding.y;
	motionGui.setPosition(position);
	
	position.x = screen.getRight() - padding.x*2 - cameraGui.getWidth() - triggerGui.getWidth();
	position.y = screen.getTop() + padding.y;
	cameraGui.setPosition(position);
	
	
	position.x = screen.getRight() - padding.x - triggerGui.getWidth();
	position.y = screen.getTop() + padding.y;
	triggerGui.setPosition(position);

	
	
	// ---------------------------
	position.x = screen.getRight() - padding.x - laserGui.getWidth();
	position.y = screen.getTop() + padding.y;
	laserGui.setPosition(position);
	
   // cout << screen.x << ", " << screen.y;
}

void ControlPanels::draw(MotionManager& motionManager, CameraManagerWarped& cameraManager){
    
    ofDisableBlendMode();
    if( monitorCount > 1 ) drawPreviewScreen(motionManager,  cameraManager);
        
  	for(int i = 0; i<panels.size(); i++) {
        panels[i]->draw();
	}

}

void ControlPanels::drawPreviewScreen(MotionManager& motionManager, CameraManagerWarped& cameraManager){
	
	ofPushStyle();
	
	updatePreviewScreenSize(); 
	
    ofPushMatrix();
    ofTranslate(previewScreenRect.x, previewScreenRect.y);
	// TODO get app width and height from somewhere!
	float scale = previewScreenRect.width/main.getWidth();

    ofScale(scale, scale);
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	
    main.draw(0,0);
	 
    ofPopMatrix();
	
	ofSetColor(128);
	ofSetLineWidth(1);
	ofNoFill();
	ofRect(previewScreenRect.x-.5, previewScreenRect.y-.5, previewScreenRect.width+2, previewScreenRect.height+2);
	ofSetColor(255);
	if(panelMode == PANEL_MODE_MOTION) {
		motionManager.current.update();
		motionManager.current.draw(previewScreenRect.getLeft(), previewScreenRect.getBottom(), previewScreenRect.width/2, previewScreenRect.height/2);
		motionManager.diff.update();
		
		ofSetColor(96);
		
		motionManager.current.draw(previewScreenRect.getLeft()+previewScreenRect.width/2, previewScreenRect.getBottom(), previewScreenRect.width/2, previewScreenRect.height/2);
	
		
		ofSetColor(255,0,255);
		ofEnableBlendMode(OF_BLENDMODE_SCREEN);
		
		motionManager.diff.draw(previewScreenRect.getLeft()+previewScreenRect.width/2, previewScreenRect.getBottom(), previewScreenRect.width/2, previewScreenRect.height/2);
		
		vector <ofVec2f>& srcpoints =cameraManager.warper.srcVecs;
		ofPushMatrix();
		ofTranslate(previewScreenRect.getLeft(), previewScreenRect.getBottom());
		float scale = (cameraManager.warper.srcWidth/ cameraManager.warper.dstWidth)*((previewScreenRect.width/2)/cameraManager.warper.srcWidth);
		ofScale(scale, scale); 
		cameraManager.warper.drawPoints(cameraManager.warper.srcVecs, ofColor::cyan);
		ofPopMatrix();
	
	}	
	ofSetColor(255,0,0);
	ofRect(previewScreenRect);
	
	ofPopStyle();
	
	
}

void ControlPanels::updatePreviewScreenSize(){
	
	
	float targetwidth = main.getWidth()-2;
	float targetheight = main.getHeight()-2;
	
	previewScreenRect.set(0, 0, targetwidth, targetheight);
	

	if(panelMode == PANEL_MODE_MOTION) {
		targetwidth = screen.width;
	} else if(panelMode != PANEL_MODE_NONE){
		targetwidth *= 0.75;		
	}	
	
	float scale = targetwidth/previewScreenRect.width;
	
	if(previewScreenRect.height / targetheight < scale) scale = previewScreenRect.height /targetheight;
	if(scale>1) scale = 1;
    
	previewScreenRect.scale(scale);
	previewScreenRect.x = screen.x+1;
	previewScreenRect.y = screen.y + targetheight - previewScreenRect.height +1;
	
	if(panelMode == PANEL_MODE_MOTION) {
		previewScreenRect.y = main.getHeight()/2 - previewScreenRect.getHeight();
	}
	
	
}
ofRectangle ControlPanels::getPreviewScreenRect(){
	return previewScreenRect;
	
	
}


void ControlPanels::exit(){

	saveSettings();
	
}

void ControlPanels::saveSettings() {
	
	appGui.save();
    laserGui.save();
    rendererGui.save();
    triggerGui.save();
    //motionGui.save();
	cameraGui.save();

	
}

void ControlPanels::keyPressed(int key){
    if( key == OF_KEY_TAB ){
		
		// NOW AUTOSAVES WHENEVER YOU SWITCH TABS
		// is there anything else that needs to save?
		saveSettings();
		
		for(int i = 0; i<panels.size(); i++) {
			panels[i]->setVisible(false);
		}
		
		panelMode++;
		if(panelMode>3) panelMode = 0;
		
		if(panelMode == PANEL_MODE_APP) {
			
			appGui.setVisible(true);
			rendererGui.setVisible(true);
		} else if(panelMode == PANEL_MODE_MOTION) {
			
			triggerGui.setVisible(true);
			motionGui.setVisible(true);
			cameraGui.setVisible(true);
			
		} else if(panelMode == PANEL_MODE_LASER) {
			laserGui.setVisible(true);
        }
		
		updatePreviewScreenSize(); 
		
        /*
         * I've had to disable this automatic layout, as something is wrong with the setPosition of ofxGui for nested GuiGroups
         */
       
        //layoutPanels( getVisiblePanels(), screen );
    }
}

void ControlPanels::mouseMoved(int x, int y){
    
}

void ControlPanels::setupPanel( string name, string filename, ofRectangle rect, ofxPanel & panel ){
	
	panel.clear();
	
    panel.setup( name, "settings/"+filename );
    panel.useFrameBuffer(false);
	panel.loadFont("Verdana.ttf", 10, false);
	
    panel.setSize( rect.width, rect.height );
	//panel.setDefaultHeight(rect.height);
	panel.setUseTTF(true);
    panel.setPosition(rect.x, rect.y);
    panel.setVisible(false);
	
	panels.push_back(&panel); 

}	

void ControlPanels::setupPanel( string name, ofRectangle rect, ofxPanel & panel ){
	setupPanel(name, "settings.xml", rect, panel); 
    
}

/*

vector<ofxPanel> ControlPanels::getVisiblePanels(){
    vector<ofxPanel> visiblePanels(10);
    if( laserGui.getVisible() )
        visiblePanels.push_back( laserGui );
    if( rendererGui.getVisible() )
        visiblePanels.push_back( rendererGui );
    if( triggerGui.getVisible() ){
        visiblePanels.push_back( triggerGui );
    }
    if( motionGui.getVisible() ){
        visiblePanels.push_back( motionGui );
    }
    
    return visiblePanels;
}*/
/*
void ControlPanels::layoutPanels(vector<ofxPanel> panels,ofRectangle space ){
    ofVec2f pos(space.x,space.y);
    pos += padding;
    
    int len = panels.size();
    float lastRowHeight = 0;
    for( int i = 0; i < len; i++ ){
        if( pos.x + panels[i].getWidth() > space.width + space.x ) {
            pos.x = space.x;
            pos.y += lastRowHeight + padding.y;
            lastRowHeight = 0;
        }

        panels[i].setPosition( pos.x, pos.y );
        if( lastRowHeight < panels[i].getHeight() )
            lastRowHeight = panels[i].getHeight();
        
        pos.x += panels[i].getWidth() + padding.x;
    }
        
}
*/