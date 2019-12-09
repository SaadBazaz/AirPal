#pragma once

#include <QDialog>
#include "ui_MyQuery.h"
#include "Booking.h"

class MyQuery : public QDialog, public Ui::MyQuery
{
	Q_OBJECT

public:
	MyQuery(QWidget *parent = Q_NULLPTR);
	MyQuery(Booking thisBooking, QWidget *parent = Q_NULLPTR);
	~MyQuery();
};
