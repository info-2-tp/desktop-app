#include "job.h"
#include <ctime>

Job::Job(unsigned long id, std::string name, unsigned int height, unsigned int quantity, time_t date, Measure measure, State state, Priority priority) {
    this->id = id;
    this->name = name;
    this->height = height;
    this->measure = measure;
    this->quantity = quantity;
    this->state = state;
    this->priority = priority;
    this->remaining_quantity = quantity;
    this->date = date; //time(nullptr);
}
