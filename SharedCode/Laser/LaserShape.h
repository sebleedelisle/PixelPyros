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
	virtual ~LaserShape(){
		//cout << "LASER SHAPE DESTROY!!!" << endl;
	};
	virtual void renderPreview(){};
	
	bool tested = false;
	bool reversed = false;
	bool reversable = false; 
	
	virtual ofPoint& getStartPos(){
		if(reversed) return endPos;
		else return startPos; 
	}
	virtual ofPoint& getEndPos(){
		if(reversed) return startPos;
		else return endPos;
	};
	
	protected :
	ofPoint startPos;
	ofPoint endPos; 

};