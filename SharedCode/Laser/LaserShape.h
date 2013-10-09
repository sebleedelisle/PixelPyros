//
//  LaserShape.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 25/09/2013.
//
//

#pragma once

class LaserShape {

	public :

	LaserShape(){};
	
	virtual void renderPreview(){};
	
	bool tested = false;
	
	ofPoint startPos;
	ofPoint endPos; 

};