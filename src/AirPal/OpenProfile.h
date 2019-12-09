#pragma once

#include <QDialog>
#include "ui_OpenProfile.h"
#include <string>
#include <fstream>
using namespace std;

class OpenProfile : public QDialog, public Ui::OpenProfile
{
	Q_OBJECT

public:

	OpenProfile(QWidget *parent = Q_NULLPTR);
	string loadREADME();
	~OpenProfile();
};
