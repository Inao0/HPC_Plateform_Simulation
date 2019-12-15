#ifndef SUPERCOMPUTERSIMULATION_ABSTRACTSCHEDULER_H
#define SUPERCOMPUTERSIMULATION_ABSTRACTSCHEDULER_H

#include <queue>
#include "../include/Node.h"
#include "AbstractJob.h"
#include <list>


class User;
class MediumJob;
class SmallJob;
class LargeJob;
class HugeJob;
class GpuJob;
class Node;
class ReservedForMediumJobNode;
class ReservedForSmallJobNode;
class GpuNode;

class AbstractScheduler {
protected:
    std::list<MediumJob *> *mediumJobs{};//maybe should use a heap for ordering according to priority maybe heaps for different jobs and then take the one with the highest priority ?
    std::list<SmallJob*>* smallJobs{};
    std::list<LargeJob *> *largeJobs{}; //maybe should use a heap for ordering according to priority maybe heaps for different jobs and then take the one with the highest priority ?
    std::list<HugeJob *> *hugeJobs{}; //maybe should use a heap for ordering according to priority maybe heaps for different jobs and then take the one with the highest priority ?
    std::list<GpuJob*>* gpuJobs{};
    std::queue<Node *> freeMediumNodes; //reserved for medium nodes
    std::queue<Node*> freeSmallNodes;
    std::queue<Node*> freeGpuNodes;
    std::queue<Node *> freeNodes;

public:

    /* Do not take into account week-end*/
    virtual void tryToExecuteNextLargeJob(AbstractSimulator* simulator)=0;
    virtual void tryToExecuteNextMediumJob(AbstractSimulator* simulator)=0;
    virtual void tryToExecuteNextSmallJob(AbstractSimulator* simulator)=0;
    virtual void tryToExecuteNextHugeJobs(AbstractSimulator *simulator)=0;
    virtual void tryToExecuteNextGpuJob(AbstractSimulator* simulator)=0;

    virtual void tryToExecuteNextNonGpuJobShortEnough (AbstractSimulator *simulator)=0;

    AbstractScheduler();
    AbstractScheduler(const AbstractScheduler &scheduler) = delete;
    AbstractScheduler &operator=(const AbstractScheduler &scheduler) = delete;
    virtual ~AbstractScheduler();

    virtual void addFreeNode(AbstractSimulator *simulator, Node *node) = 0;
    virtual void addFreeMediumNode(AbstractSimulator *simulator, ReservedForMediumJobNode* node)=0;
    virtual void addFreeSmallNode(AbstractSimulator* simulator, ReservedForSmallJobNode* node)=0;
    virtual void addFreeGpuNode(AbstractSimulator* simulator, GpuNode* node)=0;


    virtual void insertMediumJob(AbstractSimulator *simulator, MediumJob *job)=0;
    virtual void insertSmallJob(AbstractSimulator* simulator, SmallJob* job)=0;
    virtual void insertLargeJob(AbstractSimulator *simulator, LargeJob *job)=0;
    virtual void insertGpuJob(AbstractSimulator* simulator, GpuJob *job)=0;
    virtual void insertHugeJob(AbstractSimulator *simulator, HugeJob *job)=0;

    virtual void tryToExecuteNextJobs(AbstractSimulator *pSimulator)=0;
    virtual int totalOfNonHugeJobsWaiting()=0;
};


class Scheduler : public AbstractScheduler {

public:

    Scheduler();

/* Do not take into account week-end*/
    void tryToExecuteNextLargeJob(AbstractSimulator* simulator);
    void tryToExecuteNextMediumJob(AbstractSimulator* simulator);
	void tryToExecuteNextSmallJob(AbstractSimulator* simulator);
    void tryToExecuteNextHugeJobs(AbstractSimulator *simulator);
	void tryToExecuteNextGpuJob(AbstractSimulator* simulator);

	void tryToExecuteNextNonGpuJobShortEnough (AbstractSimulator *simulator);

    Scheduler(const Scheduler &scheduler) = delete;
    Scheduler &operator=(const Scheduler &scheduler) = delete;

    void addFreeNode(AbstractSimulator *simulator, Node *node);
    void addFreeMediumNode(AbstractSimulator *simulator, ReservedForMediumJobNode* node);
	void addFreeSmallNode(AbstractSimulator* simulator, ReservedForSmallJobNode* node);
	void addFreeGpuNode(AbstractSimulator* simulator, GpuNode* node);

    AbstractJob* nextNonGpuJob();
    AbstractJob* nextJob();

    void insertMediumJob(AbstractSimulator *simulator, MediumJob *job);
    void insertSmallJob(AbstractSimulator* simulator, SmallJob* job);
    void insertLargeJob(AbstractSimulator *simulator, LargeJob *job);
    void insertGpuJob(AbstractSimulator* simulator, GpuJob *job);
    void insertHugeJob(AbstractSimulator *simulator, HugeJob *job) ;

    void tryToExecuteNextJobs(AbstractSimulator *pSimulator);

    int totalOfNonHugeJobsWaiting();
};

#endif //SUPERCOMPUTERSIMULATION_ABSTRACTSCHEDULER_H
