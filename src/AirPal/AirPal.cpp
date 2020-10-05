#include "AirPal.h"


void AirPal::on_searchButton_clicked()
{
	string source = ui.searchQuery->text().toStdString();
	string destination = ui.searchQuery_2->text().toStdString();

	//IF they are just the default values, or null, return empty (ignore)
	if (source == "Source" || source == "" || destination == "Destination" || destination == "")
		return;



	//ELSE process the other query inputs

	this->pageNumber = 0;

	int effectiveness = 0;
	if (ui.efficiencyBox->currentText() != "Cost")
		effectiveness = 1;


	double costRange = this->ui.costBox->value();

	Date dateRange(ui.dateEdit->date().day(), ui.dateEdit->date().month(), ui.dateEdit->date().year());

	string airline = ui.airlineSelect->currentText().toStdString();
	int transitTimeStart = 0;	//hardcoded
	int transitTimeEnd = 0;		//hardcoded

	string anyChanges = "";

	int param_directOrIndirect = 0;
	if (directbool == 1) {
		param_directOrIndirect = OPTION1;
	}
	if (indirectbool == 1) {
		if (param_directOrIndirect == 1) {
			param_directOrIndirect = BOTH;
		}
		else {
			param_directOrIndirect = OPTION2;
		}
	}



	//Empty the state of the searchResultsList
	refreshsearchResultsList();

	//Get the data from "getFlights" API and update the searchList with "populateSearchList" function
	populateSearchList(AirSearch.getFlightsSummary(source, destination, effectiveness, transitSelection, costRange, param_directOrIndirect, dateRange, airline, transitTimeStart, transitTimeEnd, anyChanges));
}

void AirPal::on_addTransitsbutton_clicked() {

	TransitDialog dialog(this);
	int dialogCode = dialog.exec();
	//if (dialogCode == dialog.Accepted) {
	//	dialog.toggleParams_DIRECT();
	//	dialog.toggleParams_INDIRECT();
	//	dialog.toggleParams_TRANSIT();
	//	param_directOrIndirect = 0;
	//	if (directbool==1) {
	//		param_directOrIndirect = OPTION1;
	//	}
	//	if (indirectbool==1) {
	//		if (param_directOrIndirect == 1) {
	//			param_directOrIndirect = BOTH;
	//		}
	//		else {
	//			param_directOrIndirect = OPTION2;
	//		}
	//	}
	//	//qDebug() << "Transit: " << transitSelection;
	//	////qDebug() << "Types: " << QString("String") << QChar('x') << QRect(0, 10, 50, 40);
	//	//qDebug() << "Direct or Connecting? " << param_directOrIndirect;
	//	transitLocation =  transitSelection;
	//}
}

void AirPal::analyzeText1() {
	QLineEdit* theInputFieldSender = qobject_cast<QLineEdit*>(sender()); // retrieve the Text Input which called this function

	//If the text field is null, just send it back lol don't waste my time
	if (theInputFieldSender->text().toStdString() == "")
		return;

	//Get the search suggestions then throw them in a new Completer, and attach the Completer to the Text Input
	completer = new QCompleter(AirSearch.getSearchSuggestions(theInputFieldSender->text().toStdString()), this);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
	theInputFieldSender->setCompleter(completer);
	theInputFieldSender->completer()->complete();
}

void AirPal::populateSearchList(Vector<CityNode*> currentQueryResults) {
	if (currentQueryResults.isEmpty()) {
		ui.searchResultsList->addItem(QString::fromStdString("Couldn't find anything related to this query.\nPlease change your search terms or try again later."));
	}
	else {

		try {
			string temp;
			double tempprice = 0;
			string airlines;
			Date startDate, endDate;
			for (int i = 0; i < currentQueryResults.Size(); i++) {
				CityNode* cursor = currentQueryResults[i];

				temp = "\n" + AirSearch.capitalize(cursor->CityName) + " to ";
				tempprice = 0;
				airlines = "";

				if (cursor) {
					cursor = cursor->next;
					startDate = cursor->Date_of_travel;
				}

				while (cursor != nullptr) {
					temp += ((AirSearch.capitalize(cursor->CityName) + " (" + cursor->Date_of_travel.getStringDate()) + "), ");
					tempprice += cursor->Ticket_price;
					airlines += cursor->Name_of_airline + ", ";
					if (cursor->next == nullptr)
						endDate = cursor->Date_of_travel;
					cursor = cursor->next;
				}
				temp += ("\nTotal Price (excluding stay): " + to_string(tempprice));
				temp += ("\nDates: From " + startDate.getStringDate() + " to " + endDate.getStringDate());
				temp += ("\nAirline(s): " + airlines);
				temp += '\n';
				ui.searchResultsList->addItem(QString::fromStdString(temp));

			}
		}
		catch (...) {
			ui.searchResultsList->addItem(QString::fromStdString("Couldn't find anything related to that.\nPlease change your search terms or try again later."));
		}
	}
}

void AirPal::nextPage() {
	pageNumber++;
	refreshsearchResultsList();
}



// -------------------- FileHandling logic
void AirPal::openFile() {
	
		QString fileName = QFileDialog::getOpenFileName(this,
			tr("Open User Terminal"), "",
			tr("AirPal User Profile (*.apl);;All Files (*)"));

		//fileName contains the path of the file to be accessed. Use it to load the User
		//into the application
		if (fileName == "")
			return;
		loadedFile = fileName.toStdString();
		myBookings = QueryEngine::getUserBookings(loadedFile);
		refreshMainWindow();

}

void AirPal::saveFile() {
	if (loadedFile == "")
		saveAsFile();
	else
		if (QueryEngine::saveUserBookings(loadedFile, myBookings))
			isChanged = false;
	refreshMainWindow();
}

void AirPal::saveAsFile() {
	QString fileName = QFileDialog::getSaveFileName(this,
		tr("Save User Terminal"), "",
		tr("AirPal User Profile (*.apl);;All Files (*)"));

	//fileName contains the path of the file to be accessed. Use it to load the User
	//into the application
	if (fileName == "")
		return;

	loadedFile = fileName.toStdString();
	QueryEngine::saveUserBookings(loadedFile, myBookings);
	refreshMainWindow();

}

// -------------------- Query dialog functionality
void AirPal::openThisQuery() {
	// Let's assume we get the primary keys of all the Flights in this Booking from the row,
	int flightIDs[5] = { 1,2,3,4,5 };

	MyQuery dialog(flightIDs, this);
	int dialogCode = dialog.exec();
	if (dialogCode == dialog.Accepted) {
		buyThisTicket(flightIDs);
	}
}

void AirPal::buyThisTicket(int * flightIDs) {
	myBookings.enqueue(QueryEngine::postBuyTicket(flightIDs));
	triggerIsChanged();
	refreshBookings();
}



// -------------------- Ticket dialog functionality
void AirPal::openThisTicket() {

	MyTicket dialog( myBookings[   ui.bookingsList->currentRow()     ], this);
	int dialogCode=dialog.exec();
	if (dialogCode == dialog.Accepted) {
		cancelThisTicket(ui.bookingsList->currentRow());
	}
}

void AirPal::openAction_Documentation() {
	OpenProfile dialog(this);
	dialog.exec();
}


void AirPal::cancelThisTicket(int index) {
	myBookings.erase(myBookings.begin() + index);
	triggerIsChanged();
	refreshBookings();
}






// -------------------- isChanged function
void AirPal::triggerIsChanged() {
	this->isChanged = true;
	this->setWindowTitle("AirPal*");
}



// -------------------- refresher functions
void AirPal::refreshMainWindow() {
	if (isChanged) {
		this->setWindowTitle("AirPal*");
	}
	else
		this->setWindowTitle("AirPal");
	refreshBookings();
	refreshUserProfile();
	refreshsearchResultsList();
}

void AirPal::refreshUserProfile() {
	ui.userLoad->setText(QString::fromStdString(loadedFile));
}

void AirPal::refreshsearchResultsList() {
	this->ui.searchResultsList->clear();
	refreshpageSubtitle();
}

void AirPal::refreshpageSubtitle() {
	int offset = pageNumber * 20; //pageLength is constant 20 for now
}

void AirPal::refreshBookings() {
	this->ui.bookingsList->clear();
	for (int i = 0; i < myBookings.Size(); i++) {
		ui.bookingsList->addItem(QString::fromStdString(AirSearch.dictionary.getAbbreviation(myBookings[i].tickets.begin()->src) + " to " + AirSearch.dictionary.getAbbreviation(myBookings[i].tickets.end()->dest) + ", " + myBookings[i].tickets.begin()->date.getStringDate()));
	}
	
	string subtitle = "You have ";
	subtitle += to_string(myBookings.Size());
	subtitle += " upcoming flights.";

	ui.myBookingsSubtitle->setText(QString::fromStdString(subtitle));

}



// -------------------- constructor
AirPal::AirPal(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	this->pageNumber = 0;

	this->param_directOrIndirect = BOTH;
	
	completer = nullptr;

	//Put them into the list
	refreshBookings();

}
