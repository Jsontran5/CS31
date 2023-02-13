#include <iostream>
#include <string>
#include <vector>
#include "event.h"
#include "date.h"

using namespace std;

int main() {
    string eventName;
    string sponsor;
    int startHour, endHour, day, month, year;
    Date* date;
    Date da;
    int option;
    vector<Event> events;
    //cout << "What would you like to do? (1.Add an Event 2.Cancel Event 3.List all Events 4.Exit the program):  ";
   // cin >> option;
   // cin.ignore();


    do {
        cout << "What would you like to do? (1.Add an Event 2.Cancel Event 3.List all Events 4.Exit the program):  ";
        cin >> option;
        cin.ignore();
        if (option == 1) {
            cout << "What is the event name? " << endl;
            getline(cin, eventName);
            cout << "Who is the sponsor? " << endl;
            getline(cin, sponsor);
            cout << "Enter the date with spaces in between the numbers(MM DD YYYY): " << endl;
            cin >> month >> day >> year;
            da.setDate(day, month, year);

            date = &da;

            cout << "Enter the hour it starts and ends(0-23) separated by a space: " << endl;
            cin >> startHour;

            cin >> endHour;
            cin.ignore();

            Event newEvent(eventName, sponsor, startHour, endHour, date);

            bool oFlag = false;

            for (int i = 0; i < events.size(); i++) {
                if (events[i].hasOverlap(newEvent) && i != (events.size()-1)) {
                    oFlag = true;
                    cout << "Your event is overlapping with an existing event. Please try again. " << endl;
                    cout << "Here is the existing event: " << endl;
                    events[i].printEvent(events[i]);
                    break;
                }
            }
            if (!oFlag) {
                events.push_back(newEvent);
            }
            
        }
        else if (option == 2) {
            string eventCancel;
            cout << "Enter the event you want to cancel: ";
            cin >> eventCancel;

            for (int i = 0; i < events.size(); i++) {
                if (events[i].getEventName() == eventCancel) {
                    events.erase(events.begin() + i);
                    cout << eventCancel << " has been canceled" << endl;
                    break;
                }
            }
        }
        else if (option == 3) {
            cout << "List of Events: " << endl;
            for (int i = 0; i < events.size(); i++) {
                events[i].printEvent(events[i]);
            }
        }
        else if (option == 4) {
            cout << "You have exited the program." << endl;
            exit(0);
        }
        else {
            cout << "Option invalid. Please try again." << endl;
        }

    }while (option != 4);
    
}