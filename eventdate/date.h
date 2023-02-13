#ifndef DATE_H
#define DATE_H

#pragma once

class Date
{
public:
    void setDate(int d, int m, int y);
    void  printDate(int day, int month, int year);
    int getDay();
    int getMonth();
    int getYear();


private:
    int day;
    int month;
    int year;

};

#endif