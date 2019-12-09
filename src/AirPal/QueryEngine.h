#pragma once
#include "Trie.h"
#include "NaiveBayes.h"
#include "Graph.h"

using namespace std;

struct QueryEngine {
	TRIE dictionary;
	Graph allFlights;

	QueryEngine() {
		dictionary.CreateDictionary("Resources\\keywords.txt");
		allFlights.CreateGraph("Flights.txt", "HotelCharges_perday.txt");
	}

	Vector<CityNode*> processSentence(string source, string destination, int effectiveness, string transitlocation, double costRange, int directOrIndirect, Date dateRange, string priorityAirline, int transitTimeStart, int transitTimeEnd) {

		toLowerCase(source);
		toLowerCase(destination);

		Vector<CityNode*> results;
		if (!dictionary.isCity(source) || !dictionary.isCity(destination) || source==destination) {
			return results;
		}


		allFlights.clearallTempsGraph();
		
		allFlights.printAllPathsWithNode(source, destination);
		

		PQueue pq(allFlights.gettempallPathGraph().Size(), allFlights.gettempallPathGraph(), allFlights);

		bool isChanged = false;
		//apply filters here
		if (directOrIndirect == 0)
			results = pq.directFlight(isChanged);
		else if (directOrIndirect == 1)
			results = pq.connectingFlight(isChanged);
		
		
		if (effectiveness == 0)
			results = pq.costEffective(100);
		else
			results = pq.minTimePriority();

		if (costRange) {
			results = pq.costRange(costRange, isChanged);
		}

		if (transitlocation != "")
			results = pq.transitLocation(transitlocation, isChanged);

		if (priorityAirline != "Any Airline")
			results = pq.priorityAirline(priorityAirline, isChanged);

		if (transitTimeStart >= 0 && transitTimeEnd > 0)
			results = pq.specificTransitTime(transitTimeStart, transitTimeEnd, isChanged);

		if (dateRange.getDay() != 1 && dateRange.getMonth() != 1 && dateRange.getYear() != 2019)
			results = pq.datePriority(dateRange, isChanged);

		return results;
	}

	string capitalize(string &word) {
		if (word[0] >= 'a' && word[0] <= 'z')
			word[0] -= 32;
		return word;
	}

	void toLowerCase(string &word) {
		for (int i = 0; i < word.size(); i++) {
			if (word[i] >= 'A' && word[i] <= 'Z') {
				word[i] += 32;
			}
		}
	}

};