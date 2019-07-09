#ifndef JOB_H
#define JOB_H

#include <string>
#include <iostream>

using namespace std;

enum State { LOADED, READY, IN_PROGRESS, COMPLETED, CANCELED };
enum Measure { CM, MM };
enum Priority { MEDIUM, HIGH, LOW };
class Job {
public:
    Job(unsigned long id, string name, unsigned int height, unsigned int quantity, time_t date, Measure measure = CM, State state = LOADED, Priority priority = MEDIUM);
        Job(string name, unsigned int height, unsigned int quantity, time_t date, Measure measure = CM, State state = LOADED, Priority priority = MEDIUM);
private:
    unsigned long id;
    string name;
    unsigned int height;
    Measure measure;
    unsigned int quantity;
    State state;
    unsigned int remaining_quantity;
    time_t date;
    Priority priority;

    string stateToString();
    string priorityToString();
    string measureToString();

public:
    friend ostream & operator << (ostream& out, Job& job);
    string toString();

    unsigned long getId();
    string getName();
    unsigned int getHeight();
    Measure getMeasure();
    unsigned int getQuantity();
    State getState();
    unsigned int getRemaining_quantity();
    time_t getDate();
    Priority getPriority();
};

#endif // JOB_H
