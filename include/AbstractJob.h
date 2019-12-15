#ifndef _QUEUE
#define _QUEUE

/*#include "Node.h"*/

#include <limits>
#include "AbstractScheduler.h"
#include "JobsSizes.h"

/*class JobQueue;*/

class User;

class JobsSizes;

// the Customer class (in this example patients)
class AbstractJob {
protected:

    int id;   // job id
    double submittingTime = 0; // job scheduling time
    double waitingTime = 0;    // job waiting time
    double executionTime = 0;  // job execution time
    int numberOfNodes = 0;
    User *user = nullptr;
    static int jobCounter;

    void generateRandomTime(double minTime, double maxTime);


public:
    AbstractJob();

    virtual ~AbstractJob() {};

    int getId() const { return id; }

    double getSubmittingTime() const { return submittingTime; }

    double getWaitingTime() const { return waitingTime; }

    double getExecutionTime() const { return executionTime; }

    int getNumberOfNodes() { return (numberOfNodes); };

    AbstractJob &setSubmittingTime(double time) {
        submittingTime = time;
        return *this;
    }

    AbstractJob &setWaitingTime(double time) {
        waitingTime = time;
        return *this;
    }

    AbstractJob &setExecutionTime(double time) {
        executionTime = time;
        return *this;
    }

    AbstractJob &setNumberOfNodes(int nbNodes) {
        numberOfNodes = nbNodes;
        return *this;
    };

    User *getUser() const {
        return user;
    }

    void setUser(User *user) {
        AbstractJob::user = user;
    }

    virtual void insertIn(AbstractSimulator *simulator, Scheduler *scheduler) = 0;

    virtual int maxNodes() = 0;

    virtual double maxTime() = 0;

    virtual string getType() = 0;

    virtual void tryToExecute(AbstractSimulator *simulator, Scheduler *scheduler) = 0;

    friend bool operator<(const AbstractJob &l, const AbstractJob &r) {
        return l.priority()
               < r.priority(); // keep the same order
    }

    double priority() const;

    virtual void generateRandomRequirements() = 0;

    virtual bool isGpuJob() { return false; };
};

class LargeJob : public AbstractJob {
private:
    string type = "Large";
public:
    void insertIn(AbstractSimulator *simulator, Scheduler *scheduler);

    int maxNodes() { return JobsSizes::largeMaxNumberOfNode; };

    double maxTime() { return JobsSizes::largeMaximumTime; };

    void tryToExecute(AbstractSimulator *simulator, Scheduler *scheduler);

    string getType() { return type; };

    void generateRandomRequirements();
};


class MediumJob : public AbstractJob {
private:
    string type = "Medium";
public:

    void insertIn(AbstractSimulator *simulator, Scheduler *scheduler);

    int maxNodes() { return JobsSizes::mediumMaxNumberOfNode; };

    double maxTime() { return JobsSizes::mediumMaximumTime; };

    string getType() { return type; };

    /*
     * Assume that the job that you are trying to execute is the first in his queue
     */
    void tryToExecute(AbstractSimulator *simulator, Scheduler *scheduler);

    void generateRandomRequirements();
};

class SmallJob : public AbstractJob {
private:
    string type = "Small";
public:

    void insertIn(AbstractSimulator *simulator, Scheduler *scheduler);

    int maxNodes() { return JobsSizes::smallMaxNumberOfNode; };

    double maxTime() { return JobsSizes::smallMaximumTime; };

    /*
     * Assume that the job that you are trying to execute is the first in his queue
     */
    void tryToExecute(AbstractSimulator *simulator, Scheduler *scheduler);

    string getType() { return type; };

    void generateRandomRequirements();
};


class HugeJob : public AbstractJob {
private:
    string type = "Huge";
public:
    void insertIn(AbstractSimulator *simulator, Scheduler *scheduler);

    int maxNodes() { return JobsSizes::hugeMaxNumberOfNode; };

    double maxTime() { return JobsSizes::hugeMaximumTime; };

    string getType() { return type; };

    void tryToExecute(AbstractSimulator *simulator, Scheduler *scheduler);

    void generateRandomRequirements();
};

class GpuJob : public AbstractJob {
private:
    string type = "Gpu";
public:

    void insertIn(AbstractSimulator *simulator, Scheduler *scheduler);

    int maxNodes() { return JobsSizes::gpuMaxNumberOfNode; };

    double maxTime() { return JobsSizes::gpuMaximumTime; };

    /*
     * Assume that the job that you are trying to execute is the first in his queue
     */
    void tryToExecute(AbstractSimulator *simulator, Scheduler *scheduler);

    string getType() { return type; };

    void generateRandomRequirements();

    bool isGpuJob() override { return true; };
};


typedef AbstractJob *(*CreateJobFn)();

AbstractJob *CreateRandomJob(const bool permissions[5]);

#endif
