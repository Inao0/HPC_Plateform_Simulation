#include "../include/AbstractScheduler.h"


Scheduler::Scheduler() {
    jobs = new  std::list<Job*>();
}

Scheduler::~Scheduler() {
    delete jobs;
}

void Scheduler::insert(class AbstractSimulator * simulator, class Job * job) {
    if( jobs->size()==0 && freeNodes.size()>=job->getNumberOfNodes() ){
        for (int i = 0; i < job->getNumberOfNodes(); ++i) {
            Node* node = freeNodes.front();
            freeNodes.pop();
            node->insert(simulator,job);
        }
    } else{
        jobs->push_back(job);
    }
}
void Scheduler::addNode(class AbstractSimulator * simulator, class Node * node) {
    this->freeNodes.push(node);
    Job* nextJob = jobs->front();
    while ( nextJob !=NULL && freeNodes.size()>=nextJob->getNumberOfNodes() ){
        for (int i = 0; i < nextJob->getNumberOfNodes(); ++i) {
            Node* node = freeNodes.front();
            freeNodes.pop();
            node->insert(simulator,nextJob);
        }
        jobs->pop_front();
        nextJob = jobs->front();
    }
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
    void addNode(Node* node) {this->freeNodes.push(node);}

};

*/