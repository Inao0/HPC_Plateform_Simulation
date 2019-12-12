#include "../include/User.h"

User::User(double time) : Event(time) { num = 0; }

/**
Inspired by Generator
 A user is generating Jobs for the HPC
*/
void User::execute(AbstractSimulator *simulator) {
    std::random_device rd;     // only used once to initialise (seed) engine
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni(1, 3); // guaranteed unbiased
    Event::execute(simulator);
    double executionTime = Random::exponential(10);
    int numberOfNodes = uni(rng);

    // keep the simulator going until next planned job is too large
    if (budgetLeft() - ((executionTime * scheduler->costPerHourPerNode())* numberOfNodes)>= 0) {

        // patients arrive on average one every 5 mins (12 per hour)
        Job *job = new Job(++num);
        job->setSubmittingTime(time);
        job->setNumberOfNodes(numberOfNodes);
        job->setExecutionTime(executionTime);
        std::cout << "Job " << job->getId() << " submitted at time " << convertTime(time) << "\n";
        std::cout << "Job " << job->getId() << " requires " << job->getNumberOfNodes() << " nodes\n";
        // insert the customer into the queue
        scheduler->insert(simulator, job);

        time += Random::exponential(12);

        simulator->insert(this);
        budget -=  (executionTime * scheduler->costPerHourPerNode())*numberOfNodes;
    } else {
        std::cout << "User has not enough budget left for is next job. Budget left : " << budgetLeft() << " / Next Job : " << convertTime(executionTime) << " on " << numberOfNodes<<" Nodes \n";
    }
}

double User::budgetLeft() {
    return budget;
}


