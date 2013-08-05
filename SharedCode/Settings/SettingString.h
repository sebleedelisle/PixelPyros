//
//  SettingString.h
//  PixelPyros
//
//  Created by Jack Lang on 02/09/2012.
//  Copyright (c) 2012 JLFlash. All rights reserved.
//

#pragma once

class SettingString {
	
	
	public :
	SettingString(string * targetvalue = NULL, string osclabel = "") {
		
		target = targetvalue;
		
		oscLabel = osclabel;
		
		value = "";
		
	}
	
	bool checkChanged() {
		if(target == NULL) return false;
		if(value!=*target) {
			value = *target;
			return true;
		}
		else return false;
		
		
	}
	
	string set(string value) {
		*target = value;
		return *target;
		
	}
	
	
	string * target;
	string value;
	string oscLabel;
	
};