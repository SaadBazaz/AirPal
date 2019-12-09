#pragma once

#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QCompleter>

#include "ui_AirPal.h"


#include "Queue.h"
#include "MyTicket.h"
#include "MyQuery.h"
#include "QueryEngine.h"
#include "OpenProfile.h"

enum PRIORITIES {
	ALL_P = 0,
	FLIGHT_COST = 1,
	FLIGHT_TIME = 2,
	BOTH_P = 3
};

class AirPal : public QMainWindow
{
	Q_OBJECT

public:

	bool isChanged = false;

	//used Queue with date sorting... makes more logical sense 
	//for consecutive bookings

	//static array implementation for faster access
	Queue <Booking> myBookings;
	
	//string storing the current loaded file
	string loadedFile;
	
	//used Trie for NLP and spellchecking of queries
	QueryEngine AirSearch;

	//used for completion
	QCompleter *completer;
	
	//store the current page number
	int pageNumber;

	//vector of current Query Results
	Vector<CityNode*> currentQueryResults;
	
	//query params
	string source;
	string destination;
	int budget;
	Date preferredDate;
	string airline;
	int priority;

	//current MyQuery
	Booking MyCurrentQuery;

	AirPal(QWidget *parent = Q_NULLPTR);

private:
	Ui::AirPalClass ui;

private slots:
	void openFileWorker();
	void saveFileWorker(string theFile);
	void on_searchButton_clicked();
	void analyzeText1();
	void analyzeText2();

public slots:
	
	void processQuery();
	void refreshsearchResultsList();
	void populateSearchList();
	void refreshpageSubtitle();

	void nextPage();


	//refresh all data on the window incase of a file load
	void refreshMainWindow();

	void refreshUserProfile();

	void openFile();
	void triggerIsChanged();

	void saveFile();
	void saveAsFile();

	void openThisQuery();
	void buyThisTicket();

	void openAction_Documentation();


	void openThisTicket();
	void cancelThisTicket(int index);
	void refreshBookings();
};
