#include "MyQuery.h"
#include "QueryEngine.h"
MyQuery::MyQuery(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
}

MyQuery::MyQuery(int * flightIDs, QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);

	// then we assume that getFlightDetails (int * flightIDs) returns all the info in the flights of that Booking
	auto thisBooking = QueryEngine::getFlightDetails(flightIDs);


	try {
		CITY1->setText(QString::fromStdString(thisBooking.tickets.begin()->src));
	}
	catch (...) {
		CITY1->setText("UNDEFINED");
	}

	try {
		CITY2->setText(QString::fromStdString(thisBooking.tickets.end()->dest));
	}
	catch (...) {
		CITY2->setText("UNDEFINED");
	}

	try {
		PRICE->setText(QString::fromStdString("Total Price (with stay): " + to_string(thisBooking.totalprice)));
	}
	catch (...) {
		PRICE->setText("UNDEFINED");
	}

	try {
		HOTELSTAYS->setText("");
	}
	catch (...) {
		HOTELSTAYS->setText("UNDEFINED");
	}

	//TICKETID->setText(QString::fromStdString("ID#" + thisBooking.ID));

	try {
		string transits = "";
		string airlines = thisBooking.tickets[0].airline;
		string startTimestoEndTimes = thisBooking.tickets[0].startTime + " to " + thisBooking.tickets[0].endTime + ", ";
		airlines += '\n';
		for (int i = 1; i < thisBooking.tickets.Size(); i++) {
			transits += thisBooking.tickets[i].src;
			airlines += thisBooking.tickets[i].airline;
			startTimestoEndTimes += (thisBooking.tickets[i].startTime + " to " + thisBooking.tickets[i].endTime);
			if (i != thisBooking.tickets.Size() - 1) {
				transits += ", ";
				airlines += "\n";
				startTimestoEndTimes += ", ";
			}
		}


		if(transits == "")
			TRANSITS->setText("DIRECT FLIGHT");
		else {
			string before = "Transit through ";
			before += transits;
			TRANSITS->setText(QString::fromStdString(before));

		}

		if (airlines == "")
			AIRLINE->setText("No airlines could be retreived.");
		else
			AIRLINE->setText(QString::fromStdString(airlines));

		if (startTimestoEndTimes == "")
			DATEANDTIME->setText("No times could be retreived.");
		else
			DATEANDTIME->setText(QString::fromStdString(startTimestoEndTimes));


	}
	catch (...) {
		TRANSITS->setText("UNDEFINED");
	}

	//AIRLINE->setText("Qatar");
}


MyQuery::~MyQuery()
{
}
