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
		enabled = true;

	};
	
	SequenceCommand(SequenceCommandType _type, float _time, int _arg1) {
		
		type = _type;
		time = _time;
		arg1 = _arg1;
		enabled = true;
	}

	
	inline bool operator< (const SequenceCommand& rhs) const{
		return this->time<rhs.time;
		};
		
	
	SequenceCommandType type;
	float time;
	int arg1;
	bool enabled;
        
        friend ostream& operator<<(ostream& os, const SequenceCommand& command){
            os << (float)command.time << ", " << (int) command.arg1 << ", " << (bool) command.enabled << endl;
            
            return os;
        };
    
        friend istream& operator>>(istream& is, SequenceCommand& command){
            is >> command.time;
            is.ignore(2);
            is >> command.arg1;
            is.ignore(2);
            is >> command.enabled;
            is.ignore(1);
            
            return is;
        };


};