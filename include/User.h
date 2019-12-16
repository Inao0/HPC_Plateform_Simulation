#ifndef SUPERCOMPUTERSIMULATION_USER_H
#define SUPERCOMPUTERSIMULATION_USER_H

#include <unordered_set>
#include "AbstractScheduler.h"
#include "HPCParameters.h"
/*
* Generate a stream of jobs for 8.0 time units.
*/

class AbstractScheduler;
/**
 * User class specify  the behavior of Users.
 * Users events corresponds to a user creating a new job and trying to submit it.
 * it will re
 */
class User : public Event {
protected:
    double budget = 0;
    int instantaneousMaxNumberOfNodes = HPCParameters::TotalNumberOfNodes;
    int currentlyUsedNumberOfNodes = 0;
    AbstractScheduler *scheduler;
    static int numOfUsers;
    int userId;
    double meanTimeToNextJob = 12;// by default a user will try to generate a job every 12 hours
    bool permissions[5]={0, 0, 0, 0, 0};


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

    void addScheduler(AbstractScheduler *scheduler) { this->scheduler = scheduler; };

    virtual double budgetLeft();

    virtual void removeFromBudget(double amountToRemove);

    void reduceNumberOfCurrentlyUsedNodeBy(int numberOfNodes) {
        currentlyUsedNumberOfNodes -= numberOfNodes;
    };

    void setPermission (bool small,bool medium,bool large,bool huge,bool gpu);

};

#endif //SUPERCOMPUTERSIMULATION_USER_H
