#pragma once

#include <vector>
#include <stdint.h>

namespace ofxTSP {
	struct Journey {
		Journey() {	}
		Journey(uint16_t start, uint16_t end);
		uint16_t start;
		uint16_t end;

		///For sorting in a std::map we need operator<
		bool operator<(const Journey & other) const;

		///Cast the journey as a single int32 value
		uint32_t asInt32() const;

		///Invert the journey (i.e. swap(start, end))
		void invert();
	};
}