#pragma once

#include <QDialog>
#include <string>
#include "ui_TransitDialog.h"


static int directbool = true; 
static int indirectbool = true;
static std::string transitSelection = "Any Transit";

class TransitDialog : public QDialog, public Ui::TransitDialog
{
	Q_OBJECT

public:
	TransitDialog(QWidget *parent = Q_NULLPTR);
	~TransitDialog();

public slots:
	void toggleParams_DIRECT();
	void toggleParams_INDIRECT();
	void toggleParams_TRANSIT();

};
