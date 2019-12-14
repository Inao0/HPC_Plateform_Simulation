#include <algorithm>
#include "../include/AbstractScheduler.h"
#include "../include/User.h"


/*
 * Assuming that the simulation start at Monday 9 AM.
 */
bool isDuringWeekend(double time) {
    const double numberOfHourInTheWeek = 168;
    const double startingWeekendTime = 104;
    double mod = fmod(time, numberOfHourInTheWeek);
    return (mod > startingWeekendTime);
}


Scheduler::Scheduler() {
    mediumJobs = new std::list<MediumJob *>;
    smallJobs = new std::list<SmallJob *>;
    largeJobs = new std::list<LargeJob *>;
    hugeJobs = new std::list<HugeJob *>;
    gpuJobs = new std::list<GpuJob *>;

}


void Scheduler::addFreeMediumNode(AbstractSimulator *simulator, ReservedForMediumJobNode *node) {
    this->freeMediumNodes.push(node);
    if (!isDuringWeekend(simulator->now()) && !isDuringWeekend(simulator->now() + JobsSizes::mediumMaximumTime)) {
        tryToExecuteNextMediumJob(simulator);
    }
}

void Scheduler::addFreeSmallNode(AbstractSimulator *simulator, ReservedForSmallJobNode *node) {
    this->freeSmallNodes.push(node);
    if (!isDuringWeekend(simulator->now()) && !isDuringWeekend(simulator->now() + JobsSizes::smallMaximumTime)) {
        tryToExecuteNextSmallJob(simulator);
    }
}

void Scheduler::addFreeGpuNode(AbstractSimulator *simulator, GpuNode *node) {
    this->freeGpuNodes.push(node);
    if (gpuJobs->front() != nullptr && isDuringWeekend(simulator->now() + gpuJobs->front()->maxTime())) {// TODO MODIFY{
        tryToExecuteNextGpuJob(simulator);
    }
}

void Scheduler::addFreeNode(class AbstractSimulator *simulator, class Node *node) {
    this->freeNodes.push(node);
    AbstractJob *job;
    if (!isDuringWeekend(simulator->now()) && !isDuringWeekend(simulator->now() + JobsSizes::largeMaximumTime)) {
        job = nextJob();
        if (job != nullptr) {
            job->tryToExecute(simulator, this);
            return;
        }
    } else if (!isDuringWeekend(simulator->now()) &&
               !isDuringWeekend(simulator->now() + JobsSizes::mediumMaximumTime)) {
        if (mediumJobs->empty() || (!smallJobs->empty() && *(smallJobs->front()) < *(mediumJobs->front()))) {
            tryToExecuteNextSmallJob(simulator);
            return;
        }
        tryToExecuteNextMediumJob(simulator);
        return;
    } else if (!isDuringWeekend(simulator->now()) && !isDuringWeekend(simulator->now() + JobsSizes::smallMaximumTime)) {
        tryToExecuteNextSmallJob(simulator);
    }
}

double Scheduler::costPerHourPerNode() {
    return (costOneHourOneNode);
}


void Scheduler::insertMediumJob(AbstractSimulator *simulator, MediumJob *job) {
    if (!isDuringWeekend(simulator->now()) && mediumJobs->empty() &&
        !isDuringWeekend(simulator->now() + JobsSizes::mediumMaximumTime)) {
        mediumJobs->push_back(job);
        tryToExecuteNextMediumJob(simulator);
    } else {
        mediumJobs->push_back(job);
    }
}

void Scheduler::insertSmallJob(AbstractSimulator *simulator, SmallJob *job) {
    if (!isDuringWeekend(simulator->now()) && smallJobs->empty() &&
        !isDuringWeekend(simulator->now() + JobsSizes::smallMaximumTime)) {
        smallJobs->push_back(job);
        tryToExecuteNextSmallJob(simulator);
    } else {
        smallJobs->push_back(job);
    }
}

void Scheduler::insertGpuJob(AbstractSimulator *simulator, GpuJob *job) {
    if (gpuJobs->empty()) {
        gpuJobs->push_back(job);
        tryToExecuteNextGpuJob(simulator);
    } else {
        gpuJobs->push_back(job);
    }
}


void Scheduler::insertLargeJob(class AbstractSimulator *simulator, class LargeJob *job) {
    if (!isDuringWeekend(simulator->now()) && largeJobs->empty() &&
        !isDuringWeekend(simulator->now() + JobsSizes::largeMaximumTime)) {
        largeJobs->push_back(job);
        tryToExecuteNextLargeJob(simulator);
    } else {
        largeJobs->push_back(job);
    }
}

void Scheduler::insertHugeJob(AbstractSimulator *simulator, HugeJob *job) {
    hugeJobs->push_back(job);
}

AbstractJob *Scheduler::nextJob() {
    std::vector<AbstractJob *> nextJobs;
    MediumJob *nextMediumJob;
    if (!mediumJobs->empty()) { //TODO Improve
        nextJobs.push_back(mediumJobs->front());
    }
    if (!largeJobs->empty()) {
        nextJobs.push_back(largeJobs->front());
    }
    if (!gpuJobs->empty()) {
        nextJobs.push_back(gpuJobs->front());
    }
    if (!smallJobs->empty()) {
        nextJobs.push_back(smallJobs->front());
    }

    if (nextJobs.empty()) {
        return nullptr;
    }
    auto nextJobIt = max_element(std::begin(nextJobs), std::end(nextJobs));
    return *nextJobIt;
}

void Scheduler::tryToExecuteNextLargeJob(AbstractSimulator *simulator) { //TODO : IMPROVE
    LargeJob *nextLargeJob = largeJobs->front();
    if (nextLargeJob != nullptr && freeNodes.size() >= nextLargeJob->getNumberOfNodes()) {
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
    if (nextMediumJob != nullptr && freeMediumNodes.size() >= nextMediumJob->getNumberOfNodes()) {
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


void Scheduler::tryToExecuteNextGpuJob(AbstractSimulator *simulator) {
    AbstractJob *nextGPUJob = gpuJobs->front();
    if (nextGPUJob != nullptr && freeGpuNodes.size() >= nextGPUJob->getNumberOfNodes()) {
        for (int i = 0; i < nextGPUJob->getNumberOfNodes(); ++i) {
            Node *node = freeNodes.front();
            freeNodes.pop();
            node->insert(simulator, nextGPUJob);
        }
        gpuJobs->pop_front();
    }

}

void Scheduler::tryToExecuteNextSmallJob(AbstractSimulator *simulator) { //TODO : IMPROVE
    AbstractJob *nextSmallJob = smallJobs->front();
    if (nextSmallJob != nullptr && freeSmallNodes.size() >= nextSmallJob->getNumberOfNodes()) {
        for (int i = 0; i < nextSmallJob->getNumberOfNodes(); ++i) {
            Node *node = freeSmallNodes.front();
            freeSmallNodes.pop();
            node->insert(simulator, nextSmallJob);
        }
        smallJobs->pop_front();
        return;
    } else if (nextSmallJob != nullptr &&
               (freeSmallNodes.size() + freeNodes.size()) >= nextSmallJob->getNumberOfNodes() &&
               nextSmallJob == nextJob()) {
        for (int i = 0; i < nextSmallJob->getNumberOfNodes(); ++i) {
            if (!freeSmallNodes.empty()) {
                Node *node = freeSmallNodes.front();
                freeSmallNodes.pop();
                node->insert(simulator, nextSmallJob);
            } else {
                if (!freeNodes.empty()) {
                    Node *node = freeNodes.front();
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

/* Try to launch as many huge jobs as possible */
void Scheduler::tryToExecuteNextHugeJobs(AbstractSimulator *simulator) {
    int previousHugeQueueSize;
    do {
        previousHugeQueueSize = hugeJobs->size();
        AbstractJob *nextHugeJob = hugeJobs->front();
        int totalNumberOfNodesAvailable = freeNodes.size() + freeMediumNodes.size() + freeSmallNodes.size();//TODO GPU
        if (nextHugeJob != nullptr && nextHugeJob->getNumberOfNodes() < totalNumberOfNodesAvailable) {
            for (int i = 0; i < nextHugeJob->getNumberOfNodes(); ++i) {
                Node *node;
                if (!freeSmallNodes.empty()) {
                    node = freeSmallNodes.front();
                    freeSmallNodes.pop();
                } else if (!freeMediumNodes.empty()) {
                    node = freeMediumNodes.front();
                    freeMediumNodes.pop();
                } else {
                    node = freeNodes.front();
                    freeNodes.pop();
                }
                node->insert(simulator, nextHugeJob);
            }
            hugeJobs->pop_front();
        }
    } while (previousHugeQueueSize > hugeJobs->size());
}

void Scheduler::tryToExecuteNextJobs(AbstractSimulator *simulator) {
    int previousNumberOfJobWaiting;
    do {
        previousNumberOfJobWaiting = totalOfNonHugeJobsWaiting();
        if (nextJob() != nullptr) {
            nextJob()->tryToExecute(simulator, this);
        }
    } while (previousNumberOfJobWaiting > totalOfNonHugeJobsWaiting());
}

int Scheduler::totalOfNonHugeJobsWaiting() {
    return smallJobs->size() + mediumJobs->size() + largeJobs->size();
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
