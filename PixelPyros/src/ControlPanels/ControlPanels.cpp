//
//  ControlPanels.cpp
//  PixelPyros
//
//  Created by Paul Hayes on 12/09/2013.
//
//

#include "ControlPanels.h"

void ControlPanels::setup(ParameterManager * parameterManager){
    
    laserGui.useFrameBuffer(false);
    laserGui.setDefaultWidth(300);
    
    laserGui.setDefaultHeight(18);
	
	laserGui.setDefaultTextPadding(7);
	
	
	laserGui.setDefaultSpacing(2);
	laserGui.setDefaultElementSpacing(5);
	laserGui.setDefaultElementIndentation(1);
	laserGui.loadFont("Verdana.ttf", 10, false);
	laserGui.setup("LaserTestGUI"); // most of the time you don't need a name
	
	laserGui.setSize(500,30);
	laserGui.setUseTTF(true);
    laserGui.setPosition(1600, 0);
    laserGui.setVisible(false);

    laserGui.add( *parameterManager->getParameterGroup("laser") );
    
	laserGui.loadFromFile("laserSettings.xml");

}

void ControlPanels::draw(){
    laserGui.draw();
}

void ControlPanels::exit(){
    laserGui.saveToFile("laserSettings.xml");
}

void ControlPanels::keyPressed(int key){
    if( key == '1' ){
        laserGui.setVisible( !laserGui.getVisibile() );
    }
}