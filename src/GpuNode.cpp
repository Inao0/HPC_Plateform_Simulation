#include "../include/GpuNode.h"
#include <cmath>
#include "../include/AbstractScheduler.h"
#include "../include/User.h"
#include "../include/AbstractJob.h"


// convert the time in seconds to hrs, mins, secs
string convertTime(double t) {
	// current time value is decimal in hours, so multiply by 3600 to get seconds and round
	int time = static_cast<int>(round(t * 3600));

	// convert seconds to hrs, mins, secs
	int hour = time / 3600;
	time = time % 3600;
	int min = time / 60;
	time = time % 60;
	int sec = time;

	string s = to_string(hour) + "hrs:" + to_string(min) + "mins:" + to_string(sec) + "secs";
	return s;
}



GpuNode::GpuNode() : Event() {
	jobBeingExecuted = nullptr;
	serviceTime = waitingTime = 0.0;
	waitingTimeQueue = 0.0;
	num = 0;
	queueSize = 0;
}

GpuNode& GpuNode::addScheduler(class Scheduler* scheduler) {
	this->scheduler = scheduler;
	return *this;
}

// compute the average statistics
void GpuNode::getStats() const {
	std::cout << "average service time is " << convertTime(serviceTime / num) << "\n";
	std::cout << "average waiting time is " << convertTime(waitingTime / num) << "\n";
	std::cout << "average waiting time queue is " << convertTime(waitingTimeQueue / num) << "\n";
	std::cout << "average queue size is " << static_cast<double>(queueSize) / num << "\n";
}


/**
* The customer's service is completed so print a message.
* If the queue is not empty, get the next customer.
*/
void GpuNode::execute(AbstractSimulator* simulator) {
	Event::execute(simulator);
	printMessage();
	(jobBeingExecuted->getUser())->reduceNumberOfCurrentlyUsedNodeBy(1);
	jobBeingExecuted = nullptr;
	addFreeNodeToScheduler(simulator);
}

void GpuNode::addFreeNodeToScheduler(AbstractSimulator* simulator) {
	scheduler->addFreeNode(simulator, this);
}
void ReservedForGpuJobNode::addFreeNodeToScheduler(AbstractSimulator* simulator) {
	scheduler->addFreeGpuNode(simulator, this);
}



bool GpuNode::isAvailable() {
	return (jobBeingExecuted == 0);
}

/**
* Start a customer's service.  The simulator must be passed in
* as a parameter so that this can  schedule the time
* when this server will be done with the customer.
*/
void GpuNode::insert(AbstractSimulator* simulator, AbstractJob* job) {
	if (jobBeingExecuted != nullptr) {
		/* Should never reach here */
		std::cout << "Error: I am busy serving someone else" << "\n";
	}
	jobBeingExecuted = job;
	// service time is set at average 15 patients per hour
	time = simulator->now() + job->getExecutionTime();//Random::exponential(15)
	simulator->insert(this);
	num++;
}


void GpuNode::printMessage() {
	std::cout << "Finished executing " << jobBeingExecuted->getId() << " (" << jobBeingExecuted->getType() << ") at time " << convertTime(time) << "\n";
	std::cout << "Execution time was " << convertTime(jobBeingExecuted->getExecutionTime()) << "\n";
	std::cout << "Job waiting time " << convertTime(time - jobBeingExecuted->getSubmittingTime()) << "\n";
	std::cout << "Job waiting time in queue "
		<< convertTime(time - jobBeingExecuted->getExecutionTime() - jobBeingExecuted->getSubmittingTime())
		<< "\n";

	// update the various times and queue size so we can calcualte averages at the end
	serviceTime += jobBeingExecuted->getExecutionTime();
	waitingTime += time - jobBeingExecuted->getSubmittingTime();
	waitingTimeQueue += time - jobBeingExecuted->getExecutionTime() - jobBeingExecuted->getSubmittingTime();
	//queueSize += queue->size();
}
