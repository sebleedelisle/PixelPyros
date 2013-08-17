#include "ofxTSP/Problem.h"

namespace ofxTSP {
	//---------
	void Problem::addJourneyCost(uint16_t start, uint16_t end, float cost) {
		this->addJourneyCost(Journey(start, end), cost);
	}

	//---------
	void Problem::addJourneyCost(const Journey & journey, float cost) {
		this->cost.insert(pair<Journey, float>(journey, cost));
	}

	//---------
	float Problem::getSymmetricCost(Journey & journey) const {
		constCostIterator it;
		it = this->cost.find(journey);
		if (it != this->cost.end()) {
			return it->second;
		} else {
			journey.invert();
			it = this->cost.find(journey);
			if (it != this->cost.end()) {
				return it->second;
			} else {
				return -1;
			}
		}
	}

	//---------
	void Problem::clear() {
		this->cost.clear();
		this->nodeCount = 0;
	}
}