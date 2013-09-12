//
//  ControlPanels.cpp
//  PixelPyros
//
//  Created by Paul Hayes on 12/09/2013.
//
//

#include "ControlPanels.h"

void ControlPanels::setup(ParameterManager * parameterManager){
    
    
    laserGui.setPosition(1600, 0);
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
    
	
    //laserGui.add(showParticles.setup("Show Particles", true));
	//laserGui.add(showRectangle.setup("Show Rectangle", false));
	
    
    //laserGui.add(speed.set( "Speed", 1, 0, 5 ));
    //laserGui.add(numParticles.set( "Num Particles", 40, 1, 300 ));
	
	
	//laserGui.add(color.setup("Particle Colour",ofColor(100,100,140),ofColor(0,0),ofColor(255,255)));
	//laserGui.add(particleFlicker.set("Flicker",0.5,0,1));
	
    laserGui.add( *parameterManager->getParameterGroup("laser") );
    
	laserGui.loadFromFile("laserSettings.xml");

}

void ControlPanels::draw(){
    laserGui.draw();
}