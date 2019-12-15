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

class Scheduler {
private:
    std::list<MediumJob *> *mediumJobs{};//maybe should use a heap for ordering according to priority maybe heaps for different jobs and then take the one with the highest priority ?
	std::list<SmallJob*>* smallJobs{};
	std::list<LargeJob *> *largeJobs{}; //maybe should use a heap for ordering according to priority maybe heaps for different jobs and then take the one with the highest priority ?
    std::list<HugeJob *> *hugeJobs{}; //maybe should use a heap for ordering according to priority maybe heaps for different jobs and then take the one with the highest priority ?
	std::list<GpuJob*>* gpuJobs{};
	std::queue<Node *> freeMediumNodes; //reserved for medium nodes
	std::queue<Node*> freeSmallNodes;
	std::queue<Node*> freeGpuNodes;
	std::queue<Node *> freeNodes;
    double const costOneHourOneNode = 1;
    double const costOneHourOneGPUNode = 1.1;

public:

    /* Do not take into account week-end*/
    void tryToExecuteNextLargeJob(AbstractSimulator* simulator);
    void tryToExecuteNextMediumJob(AbstractSimulator* simulator);
	void tryToExecuteNextSmallJob(AbstractSimulator* simulator);
    void tryToExecuteNextHugeJobs(AbstractSimulator *simulator);
	void tryToExecuteNextGpuJob(AbstractSimulator* simulator);

	void tryToExecuteNextNonGpuJobShortEnough (AbstractSimulator *simulator);

    Scheduler();
    Scheduler(const Scheduler &scheduler) = delete;
    Scheduler &operator=(const Scheduler &scheduler) = delete;
    ~Scheduler();

    void addFreeNode(AbstractSimulator *simulator, Node *node);
    void addFreeMediumNode(AbstractSimulator *simulator, ReservedForMediumJobNode* node);
	void addFreeSmallNode(AbstractSimulator* simulator, ReservedForSmallJobNode* node);
	void addFreeGpuNode(AbstractSimulator* simulator, GpuNode* node);

    double costPerHourPerNode();
    double costPerHourPerGpuNode();

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
