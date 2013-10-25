//
//  TextWriter.h
//  PixelPyros
//
//  Created by Paul King on 27/08/2012.
//

#pragma once 

#include <map>
#include "ofGraphics.h"
#include "VectorFont.h"

class TextWriter {
    
public:
    
    TextWriter();
    void draw(ofRectangle, string, bool centered);
    void drawFixedSize(ofRectangle, string, float, bool);
    ofMesh getMesh(vector<string>& lines, ofVec3f pos, float size, bool centred);
    ofMesh getMesh(string line, ofVec3f pos, float size, bool centred);

	
    float glyphSpacing, glyphLineSpacing, glyphLineWeight;
	ofColor colour;
	
	float lineRandomness;
	float colourFlickerMin;
	bool smooth; 
    
	void addGlyphToMesh(Letter&, ofRectangle, ofMesh& );
	
	
	
private:
    
    int findBestBreak(string, int, int);
    int calculateBlockWidth(string, int, int);
    void drawGlyph(Letter&, ofRectangle);
    void renderGlyph(Letter&, int, int);

    int glyphWidth, glyphHeight;
    float glyphRatio;
    VectorFont font;
};
