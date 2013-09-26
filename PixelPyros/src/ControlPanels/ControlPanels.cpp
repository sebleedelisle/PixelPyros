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

    int x=0,y=0,w=0,h=0;
    ofVec2f offset(0,0);
    ofVec2f origin(FLT_MAX,0);
    padding = ofVec2f(40,40);
    int monitorLeft=0, monitorRight=0, monitorTop=0, monitorBottom=0;
    
    cout << "Positions:" << endl;
    for(int i = 0; i < monitorCount; i++){
        glfwGetMonitorPos(monitors[i],&x,&y);
        const GLFWvidmode * desktopMode = glfwGetVideoMode(monitors[i]);
        w = desktopMode->width;
        h = desktopMode->height;
        
        if( offset.x <= x ){
            
            offset.x = x;
            offset.y = y;
            screen.x = x;
            screen.y = y;
            screen.width = w;
            screen.height = h;
        }
        
        if( origin.x > x ){
            origin.x = x;
        }
        
        cout << offset.x << "," << offset.y << " " << x << "," << y << endl;

    }

    offset -= origin;
    screen = screen + origin * -1;
    
    cout << offset.x << "," << offset.y << " " << screen.x << "," << screen.y << endl;
    
    offset += padding;
    
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
    
    setupPanel( "Motion", "motionDetectionSettings.xml", ofRectangle( offset.x, offset.y + 2 * padding.y + laserGui.getHeight(), 400, 30 ), motionGui );
    motionGui.add( *parameterManager->getParameterGroup("motion") );
    motionGui.load();
    
    setupPanel( "Laser Calibration", ofRectangle( offset.x, offset.y, 400, 30 ), laserCalibration );
    laserCalibration.add( *parameterManager->getParameterGroup("laser calibration") );
    
}

void ControlPanels::draw(){
    
    //drawPreviewScreen();
    
    cameraCalibration.draw();
    laserCalibration.draw();
    projectorCalibration.draw();
    
    laserGui.draw();
    rendererGui.draw();
    triggerGui.draw();
    motionGui.draw();
}

void ControlPanels::drawPreviewScreen(){
    previewScreenPosition = screen.position;
    ofPushMatrix();
    ofScale(0.5, 0.5);
    main.draw(previewScreenPosition);
    ofPopMatrix();
}

void ControlPanels::exit(){
    laserCalibration.save();
    projectorCalibration.save();
    
    
    laserGui.save();
    rendererGui.save();
    triggerGui.save();
    motionGui.save();
}

void ControlPanels::keyPressed(int key){
    if( key == OF_KEY_TAB ){
        laserGui.toggleVisible();
        rendererGui.toggleVisible();
        triggerGui.toggleVisible();
        motionGui.toggleVisible();
        
        /*
         * I've had to disable this automatic layout, as something is wrong with the setPosition of ofxGui for nested GuiGroups
         */
       
        //layoutPanels( getVisiblePanels(), screen );
    }
}

void ControlPanels::mouseMoved(int x, int y){
    
}

void ControlPanels::setupPanel( string name, string filename, ofRectangle rect, ofxPanel & panel ){
    panel.setup( name, filename );
    panel.useFrameBuffer(false);
	panel.loadFont("Verdana.ttf", 10, false);
	
    panel.setSize( rect.width, rect.height );
	panel.setUseTTF(true);
    panel.setPosition(rect.x, rect.y);
    panel.setVisible(false);

}

void ControlPanels::setupPanel( string name, ofRectangle rect, ofxPanel & panel ){
    panel.setup( name );
    panel.useFrameBuffer(false);
	panel.loadFont("Verdana.ttf", 10, false);
	
    panel.setSize( rect.width, rect.height );
	panel.setUseTTF(true);
    panel.setPosition(rect.x, rect.y);
    panel.setVisible(false);
    
}

vector<ofxPanel> ControlPanels::getVisiblePanels(){
    vector<ofxPanel> visiblePanels(10);
    if( laserGui.getVisibile() )
        visiblePanels.push_back( laserGui );
    if( rendererGui.getVisibile() )
        visiblePanels.push_back( rendererGui );
    if( triggerGui.getVisibile() ){
        visiblePanels.push_back( triggerGui );
    }
    if( motionGui.getVisibile() ){
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
