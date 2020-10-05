#pragma once

#include<iostream>
#include<cstring>
#include<sstream>
using namespace std;

class Date
{
private:
	int Year;
	int Month;
	int Day;
public:
	Date(string date);
	Date() :Month(0), Day(0), Year(0) {}
	Date(const int& day, const int& month, const int& year) : Month(month), Day(day), Year(year) { }

	Date operator=(string str) {
		stringstream geek(str);
		char temp;
		geek >> Day;
		geek >> temp;
		geek >> Month;
		geek >> temp;
		geek >> Year;
		return *this;
	}
	Date operator=(const Date& d);
	bool operator>(Date& d);
	bool operator>=(Date& d);
	bool operator<(Date& d);
	bool operator!=(Date& d);
	bool operator==(Date& d);
	void operator--(int ignored) {
		if (Day == 1) {
			if (Month == 1) {
				Year--;
				Month = 12;
				Day = 30;
			}
			else {
				Month--;
				Day = 30;
			}
		}
		else
			Day--;
	}
	void operator++(int ignoreds) {
		if (Day == 30) {
			if (Month == 12) {
				Year++;
				Month = 1;
				Day = 1;
			}
			else {
				Month++;
				Day = 1;
			}
		}
		else
			Day++;
	}
	int getDay()const;
	int getMonth()const;
	int getYear()const;
	string getStringDate()const;
};