#pragma once

#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QCompleter>
//#include <QDebug>

#include "ui_AirPal.h"

#include "Queue.h"
#include "MyTicket.h"
#include "MyQuery.h"
#include "TransitDialog.h"
#include "QueryEngine.h"
#include "OpenProfile.h"

enum PRIORITIES {
	OPTION1 = 1,
	OPTION2 = 2,
	BOTH = 3
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

	//data variables for transit dialog
	int param_directOrIndirect;
	string transitLocation;

	//current MyQuery
	Booking MyCurrentQuery;

	AirPal(QWidget *parent = Q_NULLPTR);

private:
	Ui::AirPalClass ui;

private slots:
	void openFileWorker();
	void saveFileWorker(string theFile);
	void on_searchButton_clicked();
	void on_addTransitsbutton_clicked();
	void analyzeText1();

public slots:
	

	void refreshsearchResultsList();								// clears the search list
	void populateSearchList(Vector<CityNode*>);						// fills the search list

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
