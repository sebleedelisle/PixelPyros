//
//  ColourStop.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 29/10/2013.
//
//

class ColourStop {


	public :
	ColourStop(ofColor& c, float pos) {
		colour = c;
		position = pos;
	}
	
	ofColor colour;
	float position; 


	inline bool operator< (const ColourStop& rhs) const{
		return this->position<rhs.position;
	};
	inline bool operator> (const ColourStop& rhs) const{
		return this->position>rhs.position;
	};

};