#include "AirPal.h"

void AirPal::on_searchButton_clicked()
{
	string theQuery = ui.searchQuery->text().toStdString();
	string theQuery_2 = ui.searchQuery_2->text().toStdString();
	if (theQuery == "Source" || theQuery == "" || theQuery_2 == "Destination" || theQuery_2 == "")
		return;
	this->source = theQuery;
	this->destination = theQuery_2;
	processQuery();
}



void AirPal::analyzeText1() {
	if (ui.searchQuery->text().toStdString() == "")
		return;

	string theText=	ui.searchQuery->text().toStdString();
	for (int i = 0; i < theText.size(); i++) {
		if (theText[i] >= 'A' && theText[i] <= 'Z')
			theText[i] += 32;
	}
	QStringList wordList;

	//if (ui.searchQuery->text().size() > 3) {


		Vector <string> filteredWords;
		try {
			filteredWords = AirSearch.dictionary.CompleteString(theText);
			for (int i = 0; i < filteredWords.Size(); i++) {
				filteredWords[i][0] -= 32;
				wordList << QString::fromStdString(filteredWords[i]);
			}

		}
		catch (...) {
			int maxEdit = 1;
			Vector <string> checkedWords;
			do {
				checkedWords = AirSearch.dictionary.SpellChecker(theText, maxEdit++);
				for (int i = 0; i < checkedWords.Size(); i++) {
					checkedWords[i][0] -= 32;
					wordList << QString::fromStdString(checkedWords[i]);
				}
			} while (checkedWords.isEmpty() && maxEdit<=3);

				//don't do anything if no matches found
			if (checkedWords.isEmpty())
				wordList << "Couldn't find!";
		}




	//}
		

	completer = new QCompleter(wordList, this);
	//completer->complete();
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
	ui.searchQuery->setCompleter(completer);
	ui.searchQuery->completer()->complete();
}


void AirPal::analyzeText2() {
	if (ui.searchQuery->text().toStdString() == "")
		return;

	string theText = ui.searchQuery_2->text().toStdString();
	for (int i = 0; i < theText.size(); i++) {
		if (theText[i] >= 'A' && theText[i] <= 'Z')
			theText[i] += 32;
	}
	QStringList wordList;

	//if (ui.searchQuery->text().size() > 3) {


	Vector <string> filteredWords;
	try {
		filteredWords = AirSearch.dictionary.CompleteString(theText);
		for (int i = 0; i < filteredWords.Size(); i++) {
			filteredWords[i][0] -= 32;
			wordList << QString::fromStdString(filteredWords[i]);
		}

	}
	catch (...) {
		int maxEdit = 1;
		Vector <string> checkedWords;
		do {
			checkedWords = AirSearch.dictionary.SpellChecker(theText, maxEdit++);
			for (int i = 0; i < checkedWords.Size(); i++) {
				checkedWords[i][0] -= 32;
				wordList << QString::fromStdString(checkedWords[i]);
			}
		} while (checkedWords.isEmpty() && maxEdit <= 3);

		//don't do anything if no matches found
		if (checkedWords.isEmpty())
			wordList << "Couldn't find!";
	}




	//}


	completer = new QCompleter(wordList, this);
	//completer->complete();
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
	ui.searchQuery_2->setCompleter(completer);
	ui.searchQuery_2->completer()->complete();
}


void AirPal::processQuery() {
	//if empty...

	//else...

	this->pageNumber = 0;

	int effectiveness = 0;
	if (ui.efficiencyBox->currentText() != "Cost")
		effectiveness = 1;


	string transitLocation = "";
	double costRange = this->ui.costBox->value();
	int directOrIndirect = 2;

	Date dateRange(ui.dateEdit->date().day(), ui.dateEdit->date().month(), ui.dateEdit->date().year());

	string airline=ui.airlineSelect->currentText().toStdString();
	int transitTimeStart = 0;
	int transitTimeEnd = 0;

	currentQueryResults = AirSearch.processSentence(this->source, this->destination, effectiveness, transitLocation, costRange, directOrIndirect, dateRange,airline,transitTimeStart, transitTimeEnd);

	//if (this->ui.costBox->value()) {
	//	currentQueryResults = AirSearch.
	//}

	refreshsearchResultsList();
	populateSearchList();
}


void AirPal::populateSearchList() {
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
			ui.searchResultsList->addItem(QString::fromStdString("Couldn't find anything related to '" + this->source + "'.\nPlease change your search terms or try again later."));
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
		//ui.myBookingsSubtitle->setText(fileName);

		//fileName contains the path of the file to be accessed. Use it to load the User
		//into the application
		if (fileName == "")
			return;
		loadedFile = fileName.toStdString();
		openFileWorker();
		refreshMainWindow();

}

void AirPal::openFileWorker() {
	
	myBookings.clear();
	
	ifstream ifs(loadedFile);
	
	Ticket tempTicket;

	while (!ifs.eof()) {
		Booking thisBooking;
		getline(ifs, thisBooking.ID, ':');
		char c = '&';
		while (c != '\n' && !ifs.eof()){
			Ticket thisTicket;
		
			getline(ifs, thisTicket.src, ',');
			getline(ifs, thisTicket.dest, ',');
		
			string tempPrice = "";
			getline(ifs, tempPrice, ',');
			thisTicket.price = stod(tempPrice);

			getline(ifs, thisTicket.startTime, ',');
			getline(ifs, thisTicket.endTime, ',');
		
			string theDate;
			getline(ifs, theDate, ',');
			thisTicket.date = theDate;
		
			getline(ifs, thisTicket.airline, ',');

			thisBooking.tickets.enqueue(thisTicket);
			if (!ifs.eof())
				c = ifs.get();
		}
		this->myBookings.enqueue(thisBooking);
	}
	ifs.close();
}

void AirPal::saveFileWorker(string theFile) {
	ofstream ofs(theFile);

	for (int i = 0; i < myBookings.Size(); i++) {

		ofs << myBookings[i].ID << ":";
		for (int j = 0; j < myBookings[i].tickets.Size(); j++) {
			ofs << myBookings[i].tickets[j].src << ","
				<< myBookings[i].tickets[j].dest << ","
				<< myBookings[i].tickets[j].price << ","
				<< myBookings[i].tickets[j].startTime << ","
				<< myBookings[i].tickets[j].endTime << ","
				<< myBookings[i].tickets[j].date.getStringDate() << ","
				<< myBookings[i].tickets[j].airline << ",";
			if (j != myBookings[i].tickets.Size() - 1) {
				ofs << "&";
			}
		}
		if (i != myBookings.Size() - 1) {
			ofs << endl;
		}
	}
	ofs.close();

	isChanged = false;
}

void AirPal::saveFile() {
	if (loadedFile == "")
		saveAsFile();
	else
		saveFileWorker(loadedFile);
	refreshMainWindow();
}



void AirPal::saveAsFile() {
	QString fileName = QFileDialog::getSaveFileName(this,
		tr("Save User Terminal"), "",
		tr("AirPal User Profile (*.apl);;All Files (*)"));
	//ui.myBookingsSubtitle->setText(fileName);

	//fileName contains the path of the file to be accessed. Use it to load the User
	//into the application
	if (fileName == "")
		return;

	loadedFile = fileName.toStdString();
	saveFileWorker(loadedFile);
	refreshMainWindow();

}

// -------------------- Query dialog functionality
void AirPal::openThisQuery() {
	
	MyCurrentQuery.tickets.clear();
	CityNode* cursor = currentQueryResults[ui.searchResultsList->currentRow()];

	string Source;


	//Extract first ticket, because it's a little special
	if (cursor != nullptr) {
		Source = cursor->CityName;
		cursor = cursor->next;
		if (cursor != nullptr) {
			Ticket currentTicket(Source, cursor->CityName, cursor->Ticket_price, cursor->Flying_time, cursor->Landing_time, cursor->Date_of_travel, cursor->Name_of_airline);
			MyCurrentQuery.tickets.enqueue(currentTicket);
			Source = cursor->CityName;
			cursor = cursor->next;
		}	
	}
	while (cursor)
	{
		Ticket currentTicket(Source,cursor->CityName, cursor->Ticket_price, cursor->Flying_time, cursor->Landing_time, cursor->Date_of_travel, cursor->Name_of_airline);
		MyCurrentQuery.tickets.enqueue(currentTicket);
		Source = cursor->CityName;
		cursor = cursor->next;
	}
	
	MyQuery dialog(this->MyCurrentQuery, this);
	int dialogCode = dialog.exec();
	if (dialogCode == dialog.Accepted) {
		buyThisTicket();
	}
}

void AirPal::buyThisTicket() {
	MyCurrentQuery.setNewID();
	myBookings.enqueue(MyCurrentQuery);
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
	if (this->currentQueryResults.Size() < 20)//hardcoding 20 as page_length
		ui.nextButton->setDisabled(1);
	else
		ui.nextButton->setDisabled(0);
}

void AirPal::refreshpageSubtitle() {
	int offset = pageNumber * 20; //pageLength is constant 20 for now
	ui.searchResultsSubtitle->setText(QString::fromStdString("Displaying " + to_string(offset) + " to " + to_string(this->currentQueryResults.Size())));
}

void AirPal::refreshBookings() {
	this->ui.bookingsList->clear();
	for (int i = 0; i < myBookings.Size(); i++) {
		ui.bookingsList->addItem(QString::fromStdString(AirSearch.dictionary.getAbbreviation(myBookings[i].tickets.begin()->src) + " to " + AirSearch.dictionary.getAbbreviation(myBookings[i].tickets.end()->dest) + ", " + myBookings[i].tickets.begin()->date.getStringDate()));
		//ui.bookingsList->addItem(QString::fromStdString(myBookings[i].tickets.begin()->src + " to " + myBookings[i].tickets.end()->dest + ", " + myBookings[i].tickets.begin()->date.getStringDate()));
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

	//Load existing bookings here
	
	this->source = "";
	this->destination = "";
	this->pageNumber = 0;
	//myBookings.enqueue(booking2);


	// initialize dictionary here
	//searchIndex.CreateDictionary();


	//train ML model here
	//.....
	
	completer = nullptr;

	//Put them into the list
	refreshBookings();

}
