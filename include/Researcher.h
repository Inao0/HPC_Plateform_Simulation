
#ifndef SUPERCOMPUTERSIMULATION_RESEARCHER_H
#define SUPERCOMPUTERSIMULATION_RESEARCHER_H


#include "User.h"
#include "Group.h"

class Researcher : public User {
private:
    Group *group;
public:
    Researcher() = delete;

    Researcher(Group *group);

    Researcher(Group *group, double meanTimeBetweenTwoJobs);

    Researcher(Group *group, double meanTimeBetweenTwoJobs, double firstJobTime);

    Researcher(const Researcher &g) = delete;

    Researcher &operator=(const Researcher &g) = delete;

    void addIndividualGrant(double grantInNodeHours) { budget += grantInNodeHours;};

    double budgetLeft() override;

    void removeFromBudget(double amountToRemove) override;

};


#endif //SUPERCOMPUTERSIMULATION_RESEARCHER_H
