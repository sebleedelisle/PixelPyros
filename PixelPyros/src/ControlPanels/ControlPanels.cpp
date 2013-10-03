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


void ControlPanels::setup(ParameterManager * parameterManager, vector<ofRectangle> screens){
	
	// no GUI for 0
	panelMode = 0;

	int heightSmall = 30;
	 
    ofxBaseGui::setDefaultWidth(500);
    ofxBaseGui::setDefaultHeight(26);
	ofxBaseGui::setDefaultSpacing(4);
    ofxBaseGui::setDefaultElementSpacing(5);
	ofxBaseGui::setDefaultElementIndentation(1);
	ofxBaseGui::setDefaultTextPadding(7);

	setupPanel( "App", "appSettings.xml", ofRectangle(0,0, 400, heightSmall ), appGui );
	
	appGui.add( *parameterManager->getParameterGroup("app") );
	appGui.load();
	
	
    setupPanel( "Laser", "laserSettings.xml", ofRectangle( 0, 0, 400, heightSmall ), laserGui );
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
    motionGui.load();
	
	setupPanel( "Camera", "cameraSettings.xml", ofRectangle( 0,0, 400, heightSmall ), cameraGui );
    cameraGui.add( *parameterManager->getParameterGroup("camera") );
    cameraGui.load();
    
    setupPanel( "Laser Calibration", "laserCalibrationSettings.xml", ofRectangle( 0, 0, 400, heightSmall ), laserCalibration );
    laserCalibration.add( *parameterManager->getParameterGroup("laser calibration") );
    laserCalibration.load();
	
	updatePositions(screens);
    
}
void ControlPanels :: updatePositions(vector<ofRectangle> screens){
	
	monitorCount = screens.size();
	// Assumes GUI will always be on the last monitor, ie
	// the right-most monitor.
	
	screen = screens[monitorCount-1];
	
	ofVec3f padding = ofVec3f(20,20);
	ofVec3f position = screen.getPosition() + padding;
	
	appGui.setPosition(position);
	position.x += appGui.getWidth() + padding.x;
	rendererGui.setPosition(position);
	
	position = screen.getPosition() + padding;
	triggerGui.setPosition(position);
	position.x += triggerGui.getWidth() + padding.x;
	motionGui.setPosition(position);
	position.x += motionGui.getWidth() + padding.x;
	cameraGui.setPosition(position);
	
	position = screen.getTopRight() - padding;
	position.x-=laserGui.getWidth(); 
	laserGui.setPosition(position);
	

	
}

void ControlPanels::draw(){
    
    if( monitorCount > 1 ) drawPreviewScreen();
    
//    cameraCalibration.draw();
//    laserCalibration.draw();
//    projectorCalibration.draw();

  	for(int i = 0; i<panels.size(); i++) {
		panels[i]->draw();
	}


}

void ControlPanels::drawPreviewScreen(){
    previewScreenRect = screen;
	
	if(panelMode != PANEL_MODE_NONE){
		previewScreenRect.scale(0.75);
		previewScreenRect.x = screen.x;
		previewScreenRect.y = screen.getBottom() - previewScreenRect.height;
	}
	
    ofPushMatrix();
    ofTranslate(previewScreenRect.x, previewScreenRect.y);
	// TODO get app width and height from somewhere!
	float scale = previewScreenRect.width/main.getWidth();
	if(previewScreenRect.height /main.getHeight() < scale) scale = previewScreenRect.height /main.getHeight();
	if(scale>1) scale = 1; 
    ofScale(scale, scale);
    main.draw(0,0);
    ofPopMatrix();
}

void ControlPanels::exit(){
    laserCalibration.save();
    projectorCalibration.save();
    
    
//    laserGui.save();
//    rendererGui.save();
//    triggerGui.save();
//    motionGui.save();
//	
	
  	for(int i = 0; i<panels.size(); i++) {
		panels[i]->save();
	}

	
}

void ControlPanels::keyPressed(int key){
    if( key == OF_KEY_TAB ){
		
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
	
    panel.setup( name, filename );
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
}

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
