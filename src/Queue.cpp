#include "../include/Queue.h"
#include "../include/User.h"


/*JobQueue::JobQueue() {
    jobs = new std::list<Job*>();
}

// delete the queue of customers
JobQueue::~JobQueue() {
    delete jobs;
}


/**
* Add a customer to the queue.
* If the server is available (which also implies this queue is empty),
* pass the customer on to the server.
* Otherwise add the customer to the queue.
*//*
void JobQueue::insert(AbstractSimulator* simulator, Job* job) {
    if (node->isAvailable()) {
        node->insert(simulator, job);
    }
    else {
        jobs->push_back(job);
    }
}

/**
* return the first customer in the queue
*//*
Job* JobQueue::remove() {
    Job* job = jobs->front();
    jobs->pop_front();
    return job;
}

int JobQueue::size() {
    return jobs->size();
}
*/