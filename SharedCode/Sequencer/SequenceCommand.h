//
//  SequenceCommand.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 13/09/2013.
//
//

#pragma once
#include "ofMain.h"

typedef enum SequenceCommandType
{
	SEQ_PATTERN_CHANGE,
} SequenceCommandType;


class SequenceCommand {
	
	public:
	
	SequenceCommand(){
		type = SEQ_PATTERN_CHANGE;
		time = 0;
		arg1 = 0;

	};
	
	SequenceCommand(SequenceCommandType _type, float _time, int _arg1) {
		
		type = _type;
		time = _time;
		arg1 = _arg1;
		
	}

	SequenceCommandType type;
	float time;
	int arg1;


};