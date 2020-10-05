#pragma once
#include <string>
#include "Vector.h"
#include "Date.h"
#include "Queue.h"
using namespace std;



struct Ticket {
	int id;
	string src, dest;
	double price;
	string startTime, endTime;
	Date date;
	string airline;

	Ticket() {
		id = 0;
		src = "";
		dest = "";
		price = 0;
		startTime = "";
		endTime = "";
		airline = "";
	}

	Ticket(string Source, string Destination, double Price, string StartTime, string EndTime, int day, int month, int year, string Airline = ""):date (day, month, year) {
		id = 0;
		src = Source;
		dest = Destination;
		price = Price;
		startTime = StartTime;
		endTime = EndTime;
		airline = Airline;
	}

	Ticket(string Source, string Destination, double Price, string StartTime, string EndTime, string newDate, string Airline = "") {
		id = 0;
		src = Source;
		dest = Destination;
		price = Price;
		startTime = StartTime;
		endTime = EndTime;
		date = newDate;
		airline = Airline;
	}

	Ticket(string Source, string Destination, double Price, string StartTime, string EndTime, Date newDate, string Airline = "") {
		id = 0;
		src = Source;
		dest = Destination;
		price = Price;
		startTime = StartTime;
		endTime = EndTime;
		date = newDate;
		airline = Airline;
	}
};


struct Booking {
	string ID; 
	int totalprice;
	//if Size is greater than 1, then there are transits
	Queue <Ticket> tickets;

	//No need for this data as it can be taken from the ticket.src instead
	//Queue <string> hotels;
		
	Booking() {
		this->ID = "AP-"+ to_string(time(NULL)) + "-T1";
	}

	Booking(int totalprice, Queue <Ticket> tickets) {
		this->ID = "AP-" + to_string(time(NULL)) + "-T1";
		this->tickets = tickets;
	}

	void setNewID() {
		this->ID = "AP-" + to_string(time(NULL)) + "-T1";
	}
};