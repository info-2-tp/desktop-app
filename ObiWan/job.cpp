#include "job.h"
#include <ctime>
#include <QDateTime>

#define DEFAULT_ID 0

Job::Job(unsigned long id, string name, unsigned int height, unsigned int quantity, time_t date, unsigned int remaining_quantity, unsigned int reserved, Measure measure, State state, Priority priority) {
    this->id = id;
    this->name = name;
    this->height = height;
    this->measure = measure;
    this->quantity = quantity;
    this->state = state;
    this->priority = priority;
    this->remaining_quantity = remaining_quantity;
    this->reserved = reserved;
    this->date = date;
}

Job::Job(string name, unsigned int height, unsigned int quantity, time_t date, Measure measure, State state, Priority priority) {
    this->id = DEFAULT_ID;
    this->name = name;
    this->height = height;
    this->measure = measure;
    this->quantity = quantity;
    this->state = state;
    this->priority = priority;
    this->remaining_quantity = quantity;
    this->reserved = 0;
    this->date = date;
}

string Job::measureToString() {
    return CM == measure ? "cm" : "mm";
}

string Job::priorityToString() {
    switch (priority) {
    case LOW: return "low";
    case MEDIUM: return "medium";
    case HIGH: return "high";
    }
    return "high";
}

string Job::stateToString() {
    switch (state) {
    case LOADED: return "loaded";
    case READY: return "ready";
    case IN_PROGRESS: return "in progress";
    case COMPLETED: return "completed";
    case CANCELED: return "canceled";
    }
    return "canceled";
}

string Job::toString() {
    return "{ id: " + to_string(id) + ", name: " + name + ", height: " + to_string(height) +
            measureToString() + ", quantity: " + to_string(quantity) + ", state: " + stateToString()  +
            ", priority: " + priorityToString() + ", remaining_quantity: " + to_string(remaining_quantity) +
            ", reserved: " + to_string(reserved) +
            ", date: " + QDateTime::fromTime_t(date).toString().toStdString() + " }";
}

ostream& operator << (ostream& out, Job& job) {
    out << job.toString();
    return out;
}

unsigned long Job::getId() {
    return id;
}
string Job::getName() {
    return name;
}
unsigned int Job::getHeight() {
    return height;
}

unsigned int Job::getHeightInMillis() {
    return measure == CM ? 10*getHeight() : getHeight();
}
Measure Job::getMeasure() {
    return measure;
}
unsigned int Job::getQuantity() {
    return quantity;
}
State Job::getState() {
    return state;
}
unsigned int Job::getRemaining_quantity() {
    return remaining_quantity;
}

unsigned int Job::getAvailable_quantity() {
    return remaining_quantity - reserved;
}

unsigned int Job::getReserved() {
    return reserved;
}
time_t Job::getDate() {
    return date;
}
Priority Job::getPriority() {
    return priority;
}

bool Job::isEquals(Job job) {
    return job.getId() == getId();
}

bool Job::operator==(Job job) {
    return isEquals(job);
}
