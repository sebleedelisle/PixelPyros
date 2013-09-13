//
//  ControlPanels.cpp
//  PixelPyros
//
//  Created by Paul Hayes on 12/09/2013.
//
//

#include "ControlPanels.h"

void ControlPanels::setup(ParameterManager * parameterManager){
    
    ofxBaseGui::setDefaultWidth(500);
    ofxBaseGui::setDefaultHeight(18);
	ofxBaseGui::setDefaultSpacing(2);
    ofxBaseGui::setDefaultElementSpacing(5);
	ofxBaseGui::setDefaultElementIndentation(1);
	ofxBaseGui::setDefaultTextPadding(7);
    
    float offsetX = 160;
    
    setupPanel( "Laser", "laserSettings.xml", ofRectangle( offsetX, 0, 400, 30 ), laserGui );
    laserGui.add( *parameterManager->getParameterGroup("laser") );
    laserGui.load();
    laserGui.getToggle("Etherdream connect") = false;
    laserGui.getToggle("status") = false;    
    
    setupPanel( "Renderer", "rendererSettings.xml", ofRectangle( offsetX + 420, 0, 400, 30 ), rendererGui );
    rendererGui.add( *parameterManager->getParameterGroup("renderer") );
    rendererGui.load();
    
    setupPanel( "Triggers", "triggerSettings.xml", ofRectangle( offsetX + 840, 0, 400, 30 ), triggerGui );
    triggerGui.add( *parameterManager->getParameterGroup("triggers") );
    triggerGui.load();

}

void ControlPanels::draw(){
    laserGui.draw();
    rendererGui.draw();
    triggerGui.draw();
}

void ControlPanels::exit(){
    laserGui.save();
    rendererGui.save();
    triggerGui.save();
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