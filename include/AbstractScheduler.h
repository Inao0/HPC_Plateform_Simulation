#ifndef SUPERCOMPUTERSIMULATION_ABSTRACTSCHEDULER_H
#define SUPERCOMPUTERSIMULATION_ABSTRACTSCHEDULER_H

#include <queue>
#include "../include/Node.h"
#include "AbstractJob.h"
#include <list>


class User;
class MediumJob;
class LargeJob;
class HugeJob;

class Scheduler {
private:
    std::list<AbstractJob *> *jobs; //maybe should use a heap for ordering according to priority maybe heaps for different jobs and then take the one with the highest priority ?
    std::queue<Node *> freeNodes;


public:
    Scheduler();

    Scheduler(const Scheduler &scheduler) = delete;

    Scheduler &operator=(const Scheduler &scheduler) = delete;

    ~Scheduler();

    void insert(AbstractSimulator *simulator, AbstractJob *job, User *user);

    /**
     * return the first customer in the queue
    */
    AbstractJob *nextJob();

    void addFreeNode(AbstractSimulator *simulator, Node *node);

    double costPerHourPerNode();

    double const costOneHourOneNode = 1;

    void insertMediumJob(MediumJob* job){};
    void insertLargeJob(LargeJob* job){};
    void insertHugeJob(HugeJob* job){};
};

#endif //SUPERCOMPUTERSIMULATION_ABSTRACTSCHEDULER_H

