#pragma once

#include "Simulator.h"
#include "ListQueue.h"
#include "random.h"
#include "Queue.h"
#include <list>
#include <cmath>
class Scheduler;

/**
* A server that holds a customer for an exponentially distributed amout of time
* and releases it.
*/
class Node : public Event {
private:
	Job* jobBeingExecuted;
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
	void insert(AbstractSimulator* simulator, Job* job);
	void printMessage();
	void getStats() const;
};
