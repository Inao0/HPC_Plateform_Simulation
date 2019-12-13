#ifndef SUPERCOMPUTERSIMULATION_USER_H
#define SUPERCOMPUTERSIMULATION_USER_H

#include <unordered_set>
#include "AbstractScheduler.h"

/**
* Generate a stream of jobs for 8.0 time units.
*/
class User : public Event {
protected:
    double budget = 1;
    int instantaneousMaxNumberOfNodes = 4;
    int currentlyUsedNumberOfNodes = 0;
    Scheduler *scheduler;
    static int numOfUsers;
    int userId;
public:
    int getUserId() const;

    User(double time = 0.0);

    User(const User &g) = delete;

    User &operator=(const User &g) = delete;

    void execute(AbstractSimulator *simulator);

    void addScheduler(Scheduler *scheduler) { this->scheduler = scheduler; };

    double budgetLeft();

    void reduceNumberOfCurrentlyUsedNodeBy(int numberOfNodes) {
        currentlyUsedNumberOfNodes -= numberOfNodes;
    };

};

#endif //SUPERCOMPUTERSIMULATION_USER_H
