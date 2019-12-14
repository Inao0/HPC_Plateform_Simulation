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
    double meanTimeToNextJob = 4;// by default a user will try to generate a job every 4 hours

public:
    double getMeanTimeToNextJob() const;

    void setMeanTimeToNextJob(double meanTimeToNextJob);

    int getUserId() const;

    User();

    User(double meanTimeBetweenToJobs);

    User(double meanTimeBetweenToJobs, double firstJobTime);

    User(const User &g) = delete;

    User &operator=(const User &g) = delete;

    void execute(AbstractSimulator *simulator);

    void addScheduler(Scheduler *scheduler) { this->scheduler = scheduler; };

    double budgetLeft();

    void removeFromBudget(double amountToRemove);

    void reduceNumberOfCurrentlyUsedNodeBy(int numberOfNodes) {
        currentlyUsedNumberOfNodes -= numberOfNodes;
    };

};

#endif //SUPERCOMPUTERSIMULATION_USER_H
