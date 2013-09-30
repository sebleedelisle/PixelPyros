//
//  GeometrySphereGeodesic.h
//  geometryTest
//
//  Created by Seb Lee-Delisle on 29/09/2013.
//
//

#pragma once

#include "ofMain.h"
#include "triangle.h"

class GeometrySphereGeodesic : public ofMesh {

	public:
	GeometrySphereGeodesic(int subdivisions = 2);
	
	void subdivide(vector<Triangle>& triangles);

};