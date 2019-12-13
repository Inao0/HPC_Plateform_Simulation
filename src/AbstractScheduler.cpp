#include "../include/AbstractScheduler.h"
#include "../include/User.h"


Scheduler::Scheduler() {
    mediumJobs = new std::list<MediumJob *>;
	smallJobs = new std::list<SmallJob*>;
    largeJobs = new std::list<LargeJob *>;
    hugeJobs = new std::list<HugeJob *>;


}


void Scheduler::addFreeMediumNode(AbstractSimulator *simulator, ReservedForMediumJobNode *node) {
    this->freeMediumNodes.push(node);
    tryToExecuteNextMediumJob(simulator);
}
void Scheduler::addFreeSmallNode(AbstractSimulator* simulator, ReservedForSmallJobNode* node) {
	this->freeSmallNodes.push(node);
	tryToExecuteNextSmallJob(simulator);
}

void Scheduler::addFreeNode(class AbstractSimulator *simulator, class Node *node) {
    this->freeNodes.push(node);
    AbstractJob *job = nextJob();
    if (job != nullptr) {
        job->tryToExecute(simulator, this);
    }
}

double Scheduler::costPerHourPerNode() {
    return (costOneHourOneNode);
}


void Scheduler::insertMediumJob(AbstractSimulator *simulator, MediumJob *job) {
    if (mediumJobs->empty()) {
        mediumJobs->push_back(job);
        tryToExecuteNextMediumJob(simulator);
    } else {
        mediumJobs->push_back(job);
    }
}
void Scheduler::insertSmallJob(AbstractSimulator* simulator, SmallJob *job) {
	if (smallJobs->empty()) {
		smallJobs->push_back(job);
		tryToExecuteNextSmallJob(simulator);
	}
	else {
		smallJobs->push_back(job);
	}
}




void Scheduler::insertLargeJob(class AbstractSimulator *simulator, class LargeJob *job) {
    if (largeJobs->empty()) {
        largeJobs->push_back(job);
        tryToExecuteNextLargeJob(simulator);
    } else {
        largeJobs->push_back(job);
    }
}

AbstractJob *Scheduler::nextJob() {
   
    MediumJob *nextMediumJob;
    if (mediumJobs->empty()) {
        nextMediumJob = nullptr;
    } else {
        nextMediumJob = mediumJobs->front();
    }
	SmallJob *nextSmallJob;
	if (smallJobs->empty()) {
		nextSmallJob = nullptr;
	}
	else {
		nextSmallJob = smallJobs->front();
	}


    LargeJob *nextLargeJob;
    if (largeJobs->empty()) {
        nextLargeJob = nullptr;
    } else {
        nextLargeJob = largeJobs->front();
    }

    if (nextMediumJob == nullptr) {
        return (nextLargeJob);
    } else if (nextLargeJob == nullptr) {
        return (nextMediumJob);
		if (nextSmallJob == nullptr) {
			return (nextMediumJob);
		}
		else if (nextMediumJob == nullptr) {
			return (nextSmallJob);


    } else {
        if (nextLargeJob->getSubmittingTime() < nextMediumJob->getSubmittingTime()) {
            return (nextLargeJob);
        }
        return (nextMediumJob);
    }
}

void Scheduler::tryToExecuteNextLargeJob(AbstractSimulator *simulator) { //TODO : IMPROVE
    LargeJob *nextLargeJob = largeJobs->front();
    if (freeNodes.size() >= nextLargeJob->getNumberOfNodes()) {
        for (int i = 0; i < nextLargeJob->getNumberOfNodes(); ++i) {
            Node *node = freeNodes.front();
            freeNodes.pop();
            node->insert(simulator, nextLargeJob);
        }
        largeJobs->pop_front();
    }
}

void Scheduler::tryToExecuteNextMediumJob(AbstractSimulator *simulator) { //TODO : IMPROVE
    AbstractJob *nextMediumJob = mediumJobs->front();
    if (nextMediumJob != NULL && freeMediumNodes.size() >= nextMediumJob->getNumberOfNodes()) {
        for (int i = 0; i < nextMediumJob->getNumberOfNodes(); ++i) {
            Node *node = freeMediumNodes.front();
            freeMediumNodes.pop();
            node->insert(simulator, nextMediumJob);
        }
        mediumJobs->pop_front();
        return;
    } else if (nextMediumJob != NULL &&
               (freeMediumNodes.size() + freeNodes.size()) >= nextMediumJob->getNumberOfNodes() &&
               nextMediumJob == nextJob()) { //TODO check for small jobs too ! CODE DUPLICATION
        for (int i = 0; i < nextMediumJob->getNumberOfNodes(); ++i) {
            if (!freeMediumNodes.empty()) {
                Node *node = freeMediumNodes.front();
                freeMediumNodes.pop();
                node->insert(simulator, nextMediumJob);
            } else {
                if (!freeNodes.empty()) {
                    Node *node = freeNodes.front();
                    freeNodes.pop();
                    node->insert(simulator, nextMediumJob);
                }
            }
        }
        mediumJobs->pop_front();
        return;
    }
}

void Scheduler::tryToExecuteNextSmallJob(AbstractSimulator* simulator) { //TODO : IMPROVE
	AbstractJob* nextSmallJob = smallJobs->front();
	if (nextSmallJob != NULL && freeSmallNodes.size() >= nextSmallJob->getNumberOfNodes()) {
		for (int i = 0; i < nextSmallJob->getNumberOfNodes(); ++i) {
			Node* node = freeSmallNodes.front();
			freeSmallNodes.pop();
			node->insert(simulator, nextSmallJob);
		}
		smallJobs->pop_front();
		return;
	}
	else if (nextSmallJob != NULL &&
		(freeSmallNodes.size() + freeNodes.size()) >= nextSmallJob->getNumberOfNodes() &&
		nextSmallJob == nextJob()) { 
		for (int i = 0; i < nextSmallJob->getNumberOfNodes(); ++i) {
			if (!freeSmallNodes.empty()) {
				Node* node = freeSmallNodes.front();
				freeSmallNodes.pop();
				node->insert(simulator, nextSmallJob);
			}
			else {
				if (!freeNodes.empty()) {
					Node* node = freeNodes.front();
					freeNodes.pop();
					node->insert(simulator, nextSmallJob);
				}
			}
		}
		smallJobs->pop_front();
		return;
	}
}




Scheduler::~Scheduler() {
    delete mediumJobs;
    delete largeJobs;
    delete hugeJobs;
	delete smallJobs;
}




/*class Scheduler {
private:
    std::list<Job*>* jobs; //maybe should use a heap for ordering according to priority maybe heaps for different jobs and then take the one with the highest priority ?
    std::queue<Node*> freeNodes;

public:

    void insert(AbstractSimulator* simulator, Job* job);

    /**
     * return the first customer in the queue
    *//*
    Job* nextJob();
    void addFreeNode(Node* node) {this->freeNodes.push(node);}

};

*/
