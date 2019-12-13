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
    std::list<MediumJob *> *mediumJobs{}; //maybe should use a heap for ordering according to priority maybe heaps for different jobs and then take the one with the highest priority ?
    std::list<LargeJob *> *largeJobs{}; //maybe should use a heap for ordering according to priority maybe heaps for different jobs and then take the one with the highest priority ?
    std::list<HugeJob *> *hugeJobs{}; //maybe should use a heap for ordering according to priority maybe heaps for different jobs and then take the one with the highest priority ?
    std::queue<Node *> freeMediumNodes; //reserved for medium nodes
    std::queue<Node *> freeNodes;
    std::queue<Node *> freeHugeNodes; //only for the weekend
    double const costOneHourOneNode = 1;

public:

    void tryToExecuteNextLargeJob(AbstractSimulator* simulator);
    void tryToExecuteNextMediumJob(AbstractSimulator* simulator);
    Scheduler();
    Scheduler(const Scheduler &scheduler) = delete;
    Scheduler &operator=(const Scheduler &scheduler) = delete;
    ~Scheduler();

    void addFreeNode(AbstractSimulator *simulator, Node *node);
    void addFreeMediumNode(AbstractSimulator *simulator, ReservedForMediumJobNode* node);

    double costPerHourPerNode();

    AbstractJob* nextJob();

    void insertMediumJob(AbstractSimulator *simulator, MediumJob *job);
    void insertLargeJob(AbstractSimulator *simulator, LargeJob *job);
    void insertHugeJob(AbstractSimulator *simulator, HugeJob *job) {
        hugeJobs->push_back(job);
    };//TODO à implémenter pour de vrai

};

#endif //SUPERCOMPUTERSIMULATION_ABSTRACTSCHEDULER_H

