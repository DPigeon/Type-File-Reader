
#include <iostream>
#include "Date.h"

using namespace std;

Date::Date(){

}

Date::Date(int y, int m, int d) {
    day = d;
    month = m;
    year = y ;
}

int Date::getDay(){
	return day;
}

int Date::getMonth(){
	return month;
}

int Date::getYear(){
	return year;
}

Date::~Date() {

}

ostream& operator<<(ostream& out, const Date &d){
	out << d.year << '-' << d.month << '-' << d.day;
	return out;
}
