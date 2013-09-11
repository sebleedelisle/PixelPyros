//
//  CubicBezier.h
//  LaserTest02
//
//  Created by Seb Lee-Delisle on 05/08/2013.
//
//


#pragma once

class CubicBezier {
	
	public :
	
	
	
	CubicBezier(const ofPoint& startPoint, const ofPoint& controlPoint1,const ofPoint& endPoint, const ofPoint& controlPoint2) {

		p1 = startPoint;
		c1 = controlPoint1;
		p2 = endPoint;
		c2 = controlPoint2;
		// update mag?
	};
	
	ofPoint getPointAtT(float t) {
		ofPoint p;
		p.x = p1.x * B1(t) + c1.x*B2(t) + c2.x*B3(t) + p2.x*B4(t);
		p.y = p1.y * B1(t) + c1.y*B2(t) + c2.y*B3(t) + p2.y*B4(t);
		p.z = p1.z * B1(t) + c1.z*B2(t) + c2.z*B3(t) + p2.z*B4(t);
		
		return p;
		
	};
	
	float B4(float t) {
		return t*t*t;
	};
	float B3(float t) {
		return (3 * t * t * (1 - t));
	};
	float B2(float t) {
		return (3 * t * (1 - t) * (1 - t));
	};
	float B1(float t) {
		return ((1 - t) * (1 - t) * (1 - t));
	};
		
		
	// start point
	ofPoint p1;
	// control point 1
	ofPoint c1;
	// end point
	ofPoint p2;
	// control point 2
	ofPoint c2;
	

	
};

	
