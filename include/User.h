#ifndef SUPERCOMPUTERSIMULATION_USER_H
#define SUPERCOMPUTERSIMULATION_USER_H

#include "AbstractScheduler.h"

/**
* Generate a stream of jobs for 8.0 time units.
*/
class User : public Event {
protected:
    double budget = 1;
    Scheduler* scheduler;
    static int numOfJobs; // number of customers generated
    static int numOfUsers;
    int userId;
public:
    int getUserId() const;

public:
    User(double time = 0.0);
    User(const User& g) = delete;
    User& operator=(const User& g) = delete;
    void execute(AbstractSimulator* simulator);
    void addScheduler(Scheduler* scheduler) { this->scheduler = scheduler;}
    double budgetLeft();

};
#endif //SUPERCOMPUTERSIMULATION_USER_H
