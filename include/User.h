#ifndef SUPERCOMPUTERSIMULATION_USER_H
#define SUPERCOMPUTERSIMULATION_USER_H

#include "AbstractScheduler.h"

/**
* Generate a stream of jobs for 8.0 time units.
*/
class User : public Event {
protected:
    Scheduler* scheduler;
    int num; // number of customers generated
public:
    User(double time = 0.0);
    User(const User& g) = delete;
    User& operator=(const User& g) = delete;
    void execute(AbstractSimulator* simulator);
    void addScheduler(Scheduler* scheduler) { this->scheduler = scheduler; }
};
#endif //SUPERCOMPUTERSIMULATION_USER_H
