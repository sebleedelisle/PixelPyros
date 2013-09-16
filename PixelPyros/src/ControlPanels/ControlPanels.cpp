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


void ControlPanels::setup(ParameterManager * parameterManager){
	int monitorCount;
    
    GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);

    int x,y,w,h;
    ofVec2f offset(0,0);
    int monitorLeft=0, monitorRight=0, monitorTop=0, monitorBottom=0;
    for(int i = 0; i < monitorCount; i++){
        glfwGetMonitorPos(monitors[i],&x,&y);
        glfwGetMonitorPhysicalSize(monitors[i],&w,&h);
        offset.x = MAX( offset.x, x );
    }
    
    offset += ofVec2f(40,40);
    
    ofxBaseGui::setDefaultWidth(500);
    ofxBaseGui::setDefaultHeight(18);
	ofxBaseGui::setDefaultSpacing(2);
    ofxBaseGui::setDefaultElementSpacing(5);
	ofxBaseGui::setDefaultElementIndentation(1);
	ofxBaseGui::setDefaultTextPadding(7);
    
    
    setupPanel( "Laser", "laserSettings.xml", ofRectangle( offset.x, offset.y, 400, 30 ), laserGui );
    laserGui.add( *parameterManager->getParameterGroup("laser") );
    laserGui.load();
    laserGui.getGroup("Laser Manager").getToggle("Etherdream connect") = false;
    laserGui.getGroup("Laser Manager").getLabel("status") = "";
    
    setupPanel( "Renderer", "rendererSettings.xml", ofRectangle( offset.x + 420, offset.y, 400, 30 ), rendererGui );
    rendererGui.add( *parameterManager->getParameterGroup("renderer") );
    rendererGui.add( *parameterManager->getParameterGroup("particles") );
    rendererGui.load();
    
    setupPanel( "Triggers", "triggerSettings.xml", ofRectangle( offset.x + 840, offset.y, 400, 30 ), triggerGui );
    triggerGui.add( *parameterManager->getParameterGroup("triggers") );
    triggerGui.load();
    
    setupPanel( "Motion", "motionDetectionSettings.xml", ofRectangle( offset.x, offset.y * 2 + laserGui.getHeight(), 400, 30 ), motionGui );
    motionGui.add( *parameterManager->getParameterGroup("motion") );
    motionGui.load();

}

void ControlPanels::draw(){
    laserGui.draw();
    rendererGui.draw();
    triggerGui.draw();
    motionGui.draw();
}

void ControlPanels::exit(){
    laserGui.save();
    rendererGui.save();
    triggerGui.save();
    motionGui.save();
}

void ControlPanels::keyPressed(int key){
    if( key == '1' ){
        laserGui.toggleVisible();
    }
    if( key == '2' ){
        rendererGui.toggleVisible();
    }
    if( key == '3' ){
        triggerGui.toggleVisible();
    }
    if( key == '4'){
        motionGui.toggleVisible();
    }
}

void ControlPanels::setupPanel( string name, string filename, ofRectangle rect, ofxPanel & panel ){
    panel.setup(name, filename);
    panel.useFrameBuffer(false);
	panel.loadFont("Verdana.ttf", 10, false);
	
    panel.setSize( rect.width, rect.height );
	panel.setUseTTF(true);
    panel.setPosition(rect.x, rect.y);
    panel.setVisible(false);

}