#include "../include/Researcher.h"


Researcher::Researcher(Group *group) : User(), group(group) {

}

Researcher::Researcher(Group *group, double meanTimeBetweenTwoJobs) : User(meanTimeBetweenTwoJobs), group(group) {
}

Researcher::Researcher(Group *group, double meanTimeBetweenTwoJobs, double firstJobTime) : User(meanTimeBetweenTwoJobs,
                                                                                                firstJobTime),
                                                                                           group(group) {

}

double Researcher::budgetLeft() {
    return (budget + group->getGroupRessourcesInNodeHour());
}

void Researcher::removeFromBudget(double amountToRemove) {
    double groupRessources = group->getGroupRessourcesInNodeHour();
    if (amountToRemove<groupRessources){
        group->removeFromGroupRessources(amountToRemove);
    }
    else{
        double hoursLeftForIndividualBudget = amountToRemove - groupRessources;
        group->removeFromGroupRessources(groupRessources);
        budget -= hoursLeftForIndividualBudget;
    }
}
