#include "../include/User.h"

User::User(double time) : Event(time) { userId = ++numOfUsers; }// Used to be numOfJobs = 0;


int User::numOfUsers = 0;

/**
Inspired by Generator
 A user is generating Jobs for the HPC
*/
void User::execute(AbstractSimulator *simulator) {
    std::random_device rd;     // only used once to initialise (seed) engine
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    Event::execute(simulator);
    AbstractJob *job = CreateRandomJob();
    job->generateRandomRequirements();
    if (currentlyUsedNumberOfNodes + job->getNumberOfNodes() <= instantaneousMaxNumberOfNodes) {
        // keep the simulator going until next planned job is too large
        if (budgetLeft() - ((job->getExecutionTime() * scheduler->costPerHourPerNode()) * job->getNumberOfNodes()) >= 0) {

            // patients arrive on average one every 5 mins (12 per hour)

            job->setSubmittingTime(time);
            job->setUser(this);
            std::cout << job->getType() << "job " << job->getId() << " submitted at time " << convertTime(time) << " by User " << userId
                      << "\n";
            std::cout << "Job " << job->getId() << " requires " << job->getNumberOfNodes() << " nodes\n";

            // insert the customer into the queue
            job->insertIn(simulator, scheduler);
            removeFromBudget( (job->getExecutionTime() * scheduler->costPerHourPerNode()) * job->getNumberOfNodes());

            time += Random::exponential(12);

            simulator->insert(this);

            currentlyUsedNumberOfNodes += job->getNumberOfNodes();
            std::cout << "User " << userId << " is using " << currentlyUsedNumberOfNodes << " out of "
                      << instantaneousMaxNumberOfNodes << "\n"
                      <<" Budget left " << convertTime(budgetLeft())<<"\n";
        } else {
            std::cout << "User " << userId << " has not enough budget left for is next job. Budget left : "
                      << budgetLeft() << " / Next Job : " << convertTime(job->getExecutionTime()) << " on " << job->getNumberOfNodes()
                      << " Nodes \n";
        }
    } else {
        time += Random::exponential(12);
        std::cout << "User " << userId << " has not enough instantaneous nodes for this job. \n"
                  << "User will try to submit an other job at :" << convertTime(time) << ". \n"
                  << "New Nodes required : " << job->getNumberOfNodes() << "/ currently used nodes :"
                  << currentlyUsedNumberOfNodes << "/ max :" << instantaneousMaxNumberOfNodes << "\n"
                <<" Budget left " << convertTime(budgetLeft())<<"\n";;

        simulator->insert(this);
    }

}

double User::budgetLeft() {
    return budget;
}

int User::getUserId() const {
    return userId;
}

void User::removeFromBudget(double amountToRemove) {
    budget -= amountToRemove;
}


