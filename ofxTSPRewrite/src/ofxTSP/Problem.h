#pragma once
#include "ofxTSP/Journey.h"

#include <vector>
#include <map>
#include <stdint.h>

using namespace std;

namespace ofxTSP {
	/** A travelling salesman problem is defined
	by a start index, and the distance between nodes
	**/
	struct Problem {
		int nodeCount;
		map<Journey, float> cost; ///<defines the cost to travel between the nodes

		void addJourneyCost(uint16_t start, uint16_t end, float cost);
		void addJourneyCost(const Journey & journey, float cost);

		/**Find the cost of a journey given that a definition
		for the cost of the journey is defined in the distance
		dictionary.

		If no journey is found in the postive direction start->end
		then the journey is inverted, i.e. swap(start, end) and the
		check is performed again. This is also returned by modifying
		the variable passed in the input argument 'journey'.

		If still no journey is available, the distance is reported as
		-1
		**/
		float getSymmetricCost(Journey & journey) const;

		void clear();
	};

	typedef map<Journey, float>::const_iterator constCostIterator;
}