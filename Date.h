
#ifndef DATE_H_
#define DATE_H_

#include <iostream>

using namespace std;

class Date {
	public:
		Date();
		Date(int, int, int);   // sets day, month, year
		virtual ~Date();
		int getDay();
		int getMonth();
		int getYear();
		friend ostream& operator<<(ostream& out, const Date &d); //used for the reserved file by writing everything back
	private:
		int day;
		int month;
		int year;
};
#endif /* DATE_H_ */
