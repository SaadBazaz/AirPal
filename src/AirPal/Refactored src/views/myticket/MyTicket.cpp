#include "MyTicket.h"


MyTicket::MyTicket(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
}



MyTicket::MyTicket(Booking thisBooking, QWidget *parent )
	: QDialog(parent)
{
	setupUi(this);
	//Booking myBooking = getSelectedBooking();
/*	setLabels(myBooking);*/	
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

	TICKETID->setText(QString::fromStdString("ID#" + thisBooking.ID));
	
	try {
		string transits = "";
		string airlines = thisBooking.tickets[0].airline;
		airlines += '\n';
		for (int i = 1; i < thisBooking.tickets.Size(); i++) {
			transits += thisBooking.tickets[i].src;
			airlines += thisBooking.tickets[i].airline;
			if (i != thisBooking.tickets.Size() - 1) {
				transits += ", ";
				airlines += "\n";
			}
		}


		if (transits == "")
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

	}
	catch (...) {
		TRANSITS->setText("UNDEFINED");
	}
	
	//AIRLINE->setText("Qatar");


}

void MyTicket::setLabels() {

}

MyTicket::~MyTicket()
{
}

