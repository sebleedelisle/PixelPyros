#include "ofxTSP/Journey.h"

namespace ofxTSP {
	//---------
	Journey::Journey(uint16_t start, uint16_t end) {
		this->start = start;
		this->end = end;
	}

	//---------
	bool Journey::operator<(const Journey & other) const {
		return this->asInt32() < other.asInt32();
	}

	//---------
	uint32_t Journey::asInt32() const {
		return ((uint32_t)this->start << 16) + (uint32_t)this->end;
	}

	//---------
	void Journey::invert() {
		std::swap(start, end);
	}
}