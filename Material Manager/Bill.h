#pragma once
#include <string>
#include "Billdetails_list.h"
using namespace std;
struct Date
{
	int day, month, year;

	void get_date(string data)
	{
		string d = string(1, data[0]) + string(1, data[1]);    //
		string m = string(1, data[3]) + string(1, data[4]);
		string y = string(1, data[6]) + string(1, data[7]) + string(1, data[8]) + string(1, data[9]);
		//	d = data[0] + data[1];   // SAI   -  se chuyen thanh so vd A => 65
		day = atoi(d.c_str());
		month = atoi(m.c_str());
		year = atoi(y.c_str());
	}
	bool before_day(Date& date)
	{
		if(this->year<date.year)
		{
			return true;
		}
		else if(this->year==date.year&&this->month<date.month)
		{
			return true;
		}
		else if(this->year==date.year&&this->month==date.month&&this->day<date.day)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};
struct Bill
{
	string ID;
	Date date;
	string Type;
	Billdetails_list* billbetail_list_ptr = nullptr;
};
