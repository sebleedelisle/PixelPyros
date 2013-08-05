//
//  SettingFloat.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 31/08/2012.
//
//

#pragma once

class SettingFloat {


	public :
	SettingFloat(float * targetvalue = NULL, string xmllabel = "", string osclabel = "" , float rangemin = 0, float rangemax = 0) {
		
		target = targetvalue;
		
		xmlLabel = xmllabel;
		oscLabel = osclabel;
		rangeMin = rangemin;
		rangeMax = rangemax;
		value = 0; 
		
	}

	bool checkChanged() {
		if(target == NULL) return false; 
		if(value!=*target) {
			value = *target; 
			return true;
		}
		else return false;
		
		
	}
	
	float setFromUnit(float unitValue) {
		*target = ofMap(unitValue, 0, 1, rangeMin, rangeMax);
		return *target;
		
	}
	
	float getUnitValue() {
		 return ofMap(*target,rangeMin, rangeMax, 0,1);
		
	}
	
	float * target;
	float value;
	string oscLabel;
	string xmlLabel;
	float rangeMin;
	float rangeMax;
	
	

	
	
};