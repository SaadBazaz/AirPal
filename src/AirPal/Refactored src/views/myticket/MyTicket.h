#pragma once

#include <QDialog>
#include "ui_MyTicket.h"
#include "Booking.h"

class MyTicket : public QDialog, public Ui::MyTicket
{
	Q_OBJECT

public:
	MyTicket(QWidget *parent = Q_NULLPTR);
	MyTicket( Booking thisBooking, QWidget *parent = Q_NULLPTR);
	void setLabels();
	~MyTicket();
};
