#include "TransitDialog.h"

TransitDialog::TransitDialog(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);

	this->directFlight->setChecked(directbool);
	this->connectingFlight->setChecked(indirectbool);
	this->transit->setCurrentText(QString::fromStdString(transitSelection));
}

void TransitDialog::toggleParams_DIRECT() {
	if (this->directFlight->isChecked()) {
		directbool = true;
	}
	else {
		directbool = false;
	}

}

void TransitDialog::toggleParams_INDIRECT() {
	if (this->connectingFlight->isChecked()) {
		indirectbool = true;
	}
	else {
		indirectbool = false;
	}
}

void TransitDialog::toggleParams_TRANSIT() {
	transitSelection = this->transit->currentText().toStdString();
}

TransitDialog::~TransitDialog()
{
}
