#ifndef SUPERCOMPUTERSIMULATION_ABSTRACTSCHEDULER_H
#define SUPERCOMPUTERSIMULATION_ABSTRACTSCHEDULER_H

#include <queue>
#include "../include/Node.h"
#include "../include/Queue.h"
#include <list>



class Scheduler {
private:
    std::list<Job *> * jobs; //maybe should use a heap for ordering according to priority maybe heaps for different jobs and then take the one with the highest priority ?
    std::queue<Node *> freeNodes;

public:
    Scheduler();

    Scheduler(const Scheduler &scheduler) = delete;

    Scheduler &operator=(const Scheduler &scheduler) = delete;

    ~Scheduler();

    void insert(AbstractSimulator *simulator, Job *job);

    /**
     * return the first customer in the queue
    */
    Job *nextJob();

    void addNode(AbstractSimulator *simulator, Node *node);

    double costPerHourPerNode();

    double const costOneHourOneNode = 1;
};

#endif //SUPERCOMPUTERSIMULATION_ABSTRACTSCHEDULER_H

