#include "OpenProfile.h"

OpenProfile::OpenProfile(QWidget *parent)
	: QDialog(parent)
{
	//setupUi(this);
	//string text = loadREADME();
	//this->readMeText->setText(QString::fromStdString(text));
}


string OpenProfile::loadREADME() {
	ifstream ifs("README.md");
	string content((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));
	return content;
}

OpenProfile::~OpenProfile()
{
}
