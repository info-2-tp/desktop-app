#include "job.h"
#include <ctime>

Job::Job(unsigned long id, std::string name, unsigned int height, unsigned int quantity, State state, Priority priority) {
    this->id = id;
    this->name = name;
    this->height = height;
    this->quantity = quantity;
    this->state = state;
    this->priority = priority;
    this->remaining_quantity = quantity;
    this->date = time(nullptr);
}
