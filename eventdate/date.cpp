#include <iostream>
#include <string>
#include "date.h"

using namespace std;



void Date::setDate(int d, int m, int y) {
    if (d < 1 || d > 31 || m < 1 || m > 12 || y < 1) {
        cout << "You entered an invalid date. Date must be within the range of 1 to 31, month must be within 1 to 12, and the year cannot be less than or equal to 0." << endl;
        return;
    }

    day = d;
    month = m;
    year = y;
}
void Date::printDate(int day, int month, int year) {

    cout << "Date: " << day << "/" << month << "/" << year << endl;

}
int Date::getDay()
{
    return day;
}

int Date::getMonth()
{
    return month;
}

int Date::getYear()
{
    return year;
}
