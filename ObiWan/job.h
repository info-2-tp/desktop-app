#ifndef JOB_H
#define JOB_H

#include <string>
#include <iostream>

using namespace std;

enum State { LOADED, READY, IN_PROGRESS, COMPLETED, CANCELED };
enum Measure { CM, MM };
enum Priority { LOW, MEDIUM, HIGH };
class Job {
public:
    Job(unsigned long id, string name, unsigned int height, unsigned int quantity, time_t date, unsigned int remaining_quantity, unsigned int reserved = 0, Measure measure = CM, State state = LOADED, Priority priority = MEDIUM);
    Job(string name, unsigned int height, unsigned int quantity, time_t date, Measure measure = CM, State state = LOADED, Priority priority = MEDIUM);
private:
    unsigned long id;
    string name;
    unsigned int height;
    Measure measure;
    unsigned int quantity;
    State state;
    unsigned int remaining_quantity;
    unsigned int reserved;
    time_t date;
    Priority priority;

    string stateToString();
    string priorityToString();
    string measureToString();

public:
    friend ostream & operator << (ostream& out, Job& job);
    bool operator == (Job job);
    bool isEquals(Job job);
    string toString();

    unsigned long getId();
    string getName();
    unsigned int getHeight();
    unsigned int getHeightInMillis();
    Measure getMeasure();
    unsigned int getQuantity();
    State getState();
    unsigned int getRemaining_quantity();
    unsigned int getAvailable_quantity();
    unsigned int getReserved();
    time_t getDate();
    Priority getPriority();
};

#endif // JOB_H
