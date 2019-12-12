#include "../include/User.h"

User::User(double time) : Event(time) { userId = ++numOfUsers; }// Used to be numOfJobs = 0;

int User::numOfJobs = 0;
int User::numOfUsers = 0;

/**
Inspired by Generator
 A user is generating Jobs for the HPC
*/
void User::execute(AbstractSimulator *simulator) {
    std::random_device rd;     // only used once to initialise (seed) engine
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni(1, 3); // guaranteed unbiased //TODO : check it is lower than instantaneous cap
    Event::execute(simulator);
    double executionTime = Random::exponential(10);
    int numberOfNodes = uni(rng);

    if (currentlyUsedNumberOfNodes + numberOfNodes <= instantaneousMaxNumberOfNodes) {
        // keep the simulator going until next planned job is too large
        if (budgetLeft() - ((executionTime * scheduler->costPerHourPerNode()) * numberOfNodes) >= 0) {

            // patients arrive on average one every 5 mins (12 per hour)
            Job *job = new Job(++User::numOfJobs);
            job->setSubmittingTime(time);
            job->setNumberOfNodes(numberOfNodes);
            job->setExecutionTime(executionTime);
            job->setUser(this);
            std::cout << "Job " << job->getId() << " submitted at time " << convertTime(time) << " by User " << userId
                      << "\n";
            std::cout << "Job " << job->getId() << " requires " << job->getNumberOfNodes() << " nodes\n";

            // insert the customer into the queue
            scheduler->insert(simulator, job, this);

            time += Random::exponential(12);

            simulator->insert(this);
            budget -= (executionTime * scheduler->costPerHourPerNode()) * numberOfNodes;
            currentlyUsedNumberOfNodes += numberOfNodes;
            std::cout << "User " << userId << " is using " << currentlyUsedNumberOfNodes << " out of "
                      << instantaneousMaxNumberOfNodes << "\n";
        } else {
            std::cout << "User " << userId << " has not enough budget left for is next job. Budget left : "
                      << budgetLeft() << " / Next Job : " << convertTime(executionTime) << " on " << numberOfNodes
                      << " Nodes \n";
        }
    } else {
        time += Random::exponential(12);
        std::cout << "User " << userId << " has not enough instantaneous nodes for this job. \n"
                  << "User will try to submit an other job at :"<< convertTime(time)<<". \n"
                  << "New Nodes required : " << numberOfNodes << "/ currently used nodes :"
                  << currentlyUsedNumberOfNodes << "/ max :" << instantaneousMaxNumberOfNodes << "\n";

        simulator->insert(this);
    }

}

double User::budgetLeft() {
    return budget;
}

int User::getUserId() const {
    return userId;
}


