#include "Date.h"


Date::Date(string date)
{
	stringstream geek(date);
	char temp;
	geek >> Day;
	geek >> temp;
	geek >> Month;
	geek >> temp;
	geek >> Year;
}

int Date::getDay()const { return Day; }
int Date::getMonth()const { return Month; }
int Date::getYear()const { return Year; }

Date Date::operator=(const Date& d)
{
	Year = d.getYear();
	Month = d.getMonth();
	Day = d.getDay();
	return *this;
}

string Date::getStringDate()const
{
	string strdate = "";
	strdate += to_string(Day) + "/" + to_string(Month) + "/" + to_string(Year) + "\0";
	return strdate;
}

bool Date::operator>(Date& d)
{
	if (Year > d.Year)
	{
		return true;
	}
	else if (Year == d.Year && Month > d.Month)
	{
		return true;
	}
	else if (Year == d.Year && Month == d.Month && Day > d.Day)
	{
		return true;
	}
	return false;
}

bool Date::operator<(Date& d)
{
	if (Year < d.Year)
	{
		return true;
	}
	else if (Year == d.Year && Month < d.Month)
	{
		return true;
	}
	else if (Year == d.Year && Month == d.Month && Day < d.Day)
	{
		return true;
	}
	return false;
}

bool Date::operator>=(Date& d)
{
	if (*this < d)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Date::operator!=(Date& d)
{
	if (Year != d.Year)
	{
		return true;
	}
	else if (Year == d.Year && Month != d.Month)
	{
		return true;
	}
	else if (Year == d.Year && Month == d.Month && Day != d.Day)
	{
		return true;
	}
	return false;
}

bool Date::operator==(Date& d)
{
	if (Year == d.Year && Month == d.Month && Day == d.Day)
	{
		return true;
	}
	else
	{
		return false;
	}
}
