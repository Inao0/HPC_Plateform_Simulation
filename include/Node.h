#pragma once

#include "Simulator.h"
#include "ListQueue.h"
#include "random.h"
#include <list>
#include <cmath>


class Scheduler;
class User;
class AbstractJob;
/**
* A server that holds a customer for an exponentially distributed amout of time
* and releases it.
*/
class Node : public Event {
protected:
	AbstractJob* jobBeingExecuted;
    /*JobQueue* queue;*/
    Scheduler* scheduler;
	double serviceTime;
	double waitingTime;
	double waitingTimeQueue;
	int queueSize;
	int num;

public:
	Node();
	Node(const Node& node) = delete;
	Node& operator=(const Node& node) = delete;

	Node& addScheduler(Scheduler* scheduler);
	void execute(AbstractSimulator* simulator);
	bool isAvailable();

    /**
    * Start a customer's service.  The simulator must be passed in
    * as a parameter so that this can  schedule the time
    * when this server will be done with the customer.
    */
	void insert(AbstractSimulator* simulator, AbstractJob* job);
	void printMessage();
	void getStats() const;
	virtual void addFreeNodeToScheduler(AbstractSimulator *Simulator);
};

class ReservedForMediumJobNode : public Node {
public:
    void addFreeNodeToScheduler(AbstractSimulator *simulator) override;
};

class ReservedForSmallJobNode : public Node {
public:
    void addFreeNodeToScheduler(AbstractSimulator *simulator) override;
};

class GpuNode : public Node {
public:
    void addFreeNodeToScheduler(AbstractSimulator* Simulator) override;
};
