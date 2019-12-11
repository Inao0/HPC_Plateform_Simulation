#include "../include/User.h"

User::User(double time) : Event(time) { num = 0; }

/**
Inspired by Generator
 A user is generating Jobs for the HPC
*/
void User::execute(AbstractSimulator* simulator) {
    Event::execute(simulator);
    // patients arrive on average one every 5 mins (12 per hour)
    Job* job = new Job(++num);
    job->setSubmittingTime(time);
    job->setNumberOfNodes(2);
    job->setExecutionTime(Random::exponential(1));
    std::cout << "Job " << job->getId() << " submitted at time " << convertTime(time) << "\n";
    // insert the customer into the queue
    scheduler->insert(simulator, job);

    time += Random::exponential(12);

    // keep the simulator going until 8 hours is reached
    if (time < 0.5) {
        simulator->insert(this);
    }
}


