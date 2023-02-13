#include <iostream>
#include <string>
#include <vector>
#include "event.h"
#include "date.h"
string Event::getEventName() {
    return eventName;
}
string Event::getSponsor() {
    return sponsor;
}
int Event::getStartHour() {
    return startHour;
}
int Event::getEndHour() {
    return endHour;
}
Date* Event::getDate() const {
    return eventDate;
}

Event::Event(string name, string spon, int sH, int eH, Date* eD) 
{
    eventName = name;
    sponsor = spon;

    checkTime(sH, eH);

    eventDate = eD;

}
void Event::checkTime(int sH, int eH) {
    if (eH < sH) {
        cout << "Invalid time. Please try again. " << endl;
        exit(EXIT_FAILURE);
    }
    else {
        startHour = sH;
        endHour = eH;
    }
}
void Event::printEvent(Event e) {

    cout << "Event: " << e.getEventName() << endl;
    cout << "Sponsor: " << e.getSponsor() << endl;
    cout << "Date: " << e.eventDate->getMonth() << "/" << e.eventDate->getDay() << "/" << e.eventDate->getYear() << endl;
    cout << "Start time: " << e.startHour << endl;
    cout << "End time: " << endHour << endl;

}
bool Event::hasOverlap(Event other) {
    if (eventDate->getDay() == other.eventDate->getDay() &&
        eventDate->getMonth() == other.eventDate->getMonth() &&
        eventDate->getYear() == other.eventDate->getYear() &&
      ((startHour >= other.startHour && startHour < other.endHour) ||
            (endHour > other.startHour && endHour <= other.endHour)))
    {
        return true;
    }

    return false;
}
