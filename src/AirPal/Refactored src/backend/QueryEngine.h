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

	QStringList getSearchSuggestions(std::string text) {
		for (int i = 0; i < text.size(); i++) {
			if (text[i] >= 'A' && text[i] <= 'Z')
				text[i] += 32;
		}
		QStringList wordList;

		Vector <string> filteredWords;
		try {
			filteredWords = dictionary.CompleteString(text);
			for (int i = 0; i < filteredWords.Size(); i++) {
				filteredWords[i][0] -= 32;
				wordList << QString::fromStdString(filteredWords[i]);
			}

		}
		catch (...) {
			int maxEdit = 1;
			Vector <string> checkedWords;
			do {
				checkedWords = dictionary.SpellChecker(text, maxEdit++);
				for (int i = 0; i < checkedWords.Size(); i++) {
					checkedWords[i][0] -= 32;
					wordList << QString::fromStdString(checkedWords[i]);
				}
			} while (checkedWords.isEmpty() && maxEdit <= 3);

			//don't do anything if no matches found
			if (checkedWords.isEmpty())
				wordList << "Couldn't find!";
		}
		return wordList;
	}



	Vector<CityNode*> getFlights(string source, string destination, int effectiveness, string transitlocation, double costRange, int directOrIndirect, Date dateRange, string priorityAirline, int transitTimeStart, int transitTimeEnd, string &anyChanges) {

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
		if (directOrIndirect == 1)
			results = pq.directFlight(isChanged);
		else if (directOrIndirect == 2)
			results = pq.connectingFlight(isChanged);

		
		if (effectiveness == 0)
			results = pq.costEffective(100);
		else
			results = pq.minTimePriority();

		if (costRange) {
			results = pq.costRange(costRange, isChanged);
		}

		if (transitlocation != "Any Transit") {
			toLowerCase(transitlocation);
			results = pq.transitLocation(transitlocation, isChanged);
		}

		if (priorityAirline != "Any Airline")
			results = pq.priorityAirline(priorityAirline, isChanged);

		if (transitTimeStart >= 0 && transitTimeEnd > 0) {
			results = pq.specificTransitTime(transitTimeStart, transitTimeEnd, isChanged);
			if (!isChanged) {
				anyChanges += "TransitRange, ";
			}
		}

		if (dateRange.getStringDate() != "1/1/2019") {
			results = pq.datePriority(dateRange, isChanged);
			if (!isChanged) {
				anyChanges += "Date, ";
			}
		}

		return results;
	}


	Booking getFlightDetails(int * flightIDs) {
		Ticket one ("Point A", "Point B", 1.0, "1/1/2020", "1/1/2020", 4, 10, 2020 );
		Ticket two ("Point C", "Point D", 2.0, "1/1/2020", "1/1/2020", 4, 10, 2020);
		Queue <Ticket> theTickets;
		Booking hardcodedBooking(one.price + two.price, theTickets);
		return hardcodedBooking;
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