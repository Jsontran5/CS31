#ifndef EVENT_H
#define EVENT_H

#pragma once

#include <string>
#include "date.h"
using namespace std;

class Event
{

public:
    void printEvent(Event e);
    bool hasOverlap(Event other);
    Date* getDate() const;
    Event(string name, string spon, int sH, int eH, Date* eD);
    void checkTime(int sH, int eH);
    string getEventName();
    string getSponsor();
    int getStartHour();
    int getEndHour();
    //Date getDate();
private:

    Date* eventDate;
    string eventName;
    string sponsor;
    int startHour;
    int endHour;

};

#endif