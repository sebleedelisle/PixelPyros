//
//  SettingBool.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 31/08/2012.
//
//

#pragma once

class SettingBool {
	
	
	public :
	SettingBool(bool * targetvalue = NULL, string xmllabel = "", string osclabel = "", bool ignorefalse = false ) {
		
		target = targetvalue;
		
		xmlLabel = xmllabel;
		oscLabel = osclabel;
		ignoreFalse = ignorefalse;
		value = false;
		
	}
	
	bool checkChanged() {
		if(target == NULL) return false;
		if(value!=*target) {
			value = *target;
			return true;
		}
		else return false;
		
		
	}
	
	float set(bool value) {
		if ( !value && ignoreFalse )
			return !value ;
		
		*target = value;
		return *target;
		
	}
	
	int getValue() {
		return (int)value;
	}
	
	
	bool * target;
	bool value;
	bool ignoreFalse;
	string oscLabel;
	string xmlLabel;
	
	
	
	
	
	
};