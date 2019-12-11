#ifndef _QUEUE
#define _QUEUE

/*#include "Node.h"*/

/*class JobQueue;*/

// the Customer class (in this example patients)
class Job {
private:
    int id;   // job id
    double submittingTime; // job scheduling time
    double waitingTime;    // job waiting time
    double executionTime=0;  // job execution time
    int numberOfNodes;
public:
    Job() = default;

    Job(int Id) : id(Id) {}

    int getId() const { return id; }

    double getSubmittingTime() const { return submittingTime; }

    double getWaitingTime() const { return waitingTime; }

    double getExecutionTime() const { return executionTime; }


    int getNumberOfNodes() { return (numberOfNodes); };

    Job &setSubmittingTime(double time) {
        submittingTime = time;
        return *this;
    }

    Job &setWaitingTime(double time) {
        waitingTime = time;
        return *this;
    }

    Job &setExecutionTime(double time) {
        executionTime = time;
        return *this;
    }

    Job &setNumberOfNodes(int nbNodes) {
        numberOfNodes = nbNodes;
        return *this;
    };
};

/*
class JobQueue {
    /**
    * Use the std::list to implement a FIFO queue.
    *//*
private:
    std::list<Job *> *jobs;
    Node *node;
public:
    JobQueue();

    JobQueue(const JobQueue &jobQueue) = delete;

    JobQueue &operator=(const JobQueue &jobQueue) = delete;

    ~JobQueue();

    /**
    * Add a customer to the queue.
    * If the server is available (which also implies this queue is empty),
    * pass the customer on to the server.
    * Otherwise add the customer to the queue.
    *//*
    void insert(AbstractSimulator *simulator, Job *job);

    /**
    * return the first customer in the queue
    *//*
    Job *remove();

    void addNode(Node *node) { this->node = node; }

    int size();

};*/


#endif
