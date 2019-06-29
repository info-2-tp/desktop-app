#ifndef JOB_H
#define JOB_H

#include <string>

enum State { LOADED, READY, IN_PROGRESS, COMPLETED, CANCELED };
enum Measure { CM, MM };
enum Priority { HIGH, MEDIUM, LOW };
class Job {
public:
    Job(unsigned long id, std::string name, unsigned int height, unsigned int quantity, time_t date, Measure measure = CM, State state = LOADED, Priority priority = MEDIUM);
private:
    unsigned long id;
    std::string name;
    unsigned int height;
    Measure measure;
    unsigned int quantity;
    State state;
    unsigned int remaining_quantity;
    time_t date;
    Priority priority;
};

#endif // JOB_H
