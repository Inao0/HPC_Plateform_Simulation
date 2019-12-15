#ifndef _QUEUE
#define _QUEUE

/*#include "Node.h"*/

#include <limits>
#include "AbstractScheduler.h"
#include "HPCParameters.h"
#include "HPCSimulator.h"

/*class JobQueue;*/

class User;
class HPCSimulator;
class AbstractScheduler;

// the Customer class (in this example patients)
class AbstractJob {
protected:

    int id;   // job id
    double submittingTime = 0; // job scheduling time
    double completionTime = 0;    // job waiting time
    double executionDuration = 0;  // job execution time
    int numberOfNodes = 0;
    User *user = nullptr;
    static int jobCounter;

    void generateRandomTime(double minTime, double maxTime);


public:
    AbstractJob();

    virtual ~AbstractJob() {};

    int getId() const { return id; }

    double getSubmittingTime() const { return submittingTime; }

    double getCompletionTime() const { return completionTime; }

    double getExecutionDuration() const { return executionDuration; }

    int getNumberOfNodes() { return (numberOfNodes); };

    AbstractJob &setSubmittingTime(double time) {
        submittingTime = time;
        return *this;
    }

    AbstractJob &setCompletionTime(double time) {
        completionTime = time;
        return *this;
    }

    AbstractJob &setExecutionTime(double time) {
        executionDuration = time;
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

    virtual void insertIn(AbstractSimulator *simulator, AbstractScheduler *scheduler) = 0;

    virtual int maxNodes() = 0;

    virtual double maxTime() = 0;

    virtual string getType() = 0;

    virtual void tryToExecute(AbstractSimulator *simulator, AbstractScheduler *scheduler) = 0;

    friend bool operator<(const AbstractJob &l, const AbstractJob &r) {
        return l.priority()
               < r.priority(); // keep the same order
    }

    double priority() const;

    virtual void generateRandomRequirements() = 0;

    virtual bool isGpuJob() { return false; };

    virtual void registerAsFinishedJob(HPCSimulator *pSimulator) = 0;
};

class LargeJob : public AbstractJob {
private:
    string type = "Large";
public:
    void insertIn(AbstractSimulator *simulator, AbstractScheduler *scheduler);

    int maxNodes() { return HPCParameters::largeMaxNumberOfNode; };

    double maxTime() { return HPCParameters::largeMaximumTime; };

    void tryToExecute(AbstractSimulator *simulator, AbstractScheduler *scheduler);

    string getType() { return type; };

    void generateRandomRequirements();

    void registerAsFinishedJob(HPCSimulator *pSimulator);
};


class MediumJob : public AbstractJob {
private:
    string type = "Medium";
public:

    void insertIn(AbstractSimulator *simulator, AbstractScheduler *scheduler);

    int maxNodes() { return HPCParameters::mediumMaxNumberOfNode; };

    double maxTime() { return HPCParameters::mediumMaximumTime; };

    string getType() { return type; };

    /*
     * Assume that the job that you are trying to execute is the first in his queue
     */
    void tryToExecute(AbstractSimulator *simulator, AbstractScheduler *scheduler);

    void generateRandomRequirements();

    void registerAsFinishedJob(HPCSimulator *pSimulator);
};

class SmallJob : public AbstractJob {
private:
    string type = "Small";
public:

    void insertIn(AbstractSimulator *simulator, AbstractScheduler *scheduler);

    int maxNodes() { return HPCParameters::smallMaxNumberOfNode; };

    double maxTime() { return HPCParameters::smallMaximumTime; };

    /*
     * Assume that the job that you are trying to execute is the first in his queue
     */
    void tryToExecute(AbstractSimulator *simulator, AbstractScheduler *scheduler);

    string getType() { return type; };

    void generateRandomRequirements();

    void registerAsFinishedJob(HPCSimulator *pSimulator);

};


class HugeJob : public AbstractJob {
private:
    string type = "Huge";
public:
    void insertIn(AbstractSimulator *simulator, AbstractScheduler *scheduler);

    int maxNodes() { return HPCParameters::hugeMaxNumberOfNode; };

    double maxTime() { return HPCParameters::hugeMaximumTime; };

    string getType() { return type; };

    void tryToExecute(AbstractSimulator *simulator, AbstractScheduler *scheduler);

    void generateRandomRequirements();

    void registerAsFinishedJob(HPCSimulator *pSimulator);
};

class GpuJob : public AbstractJob {
private:
    string type = "Gpu";
public:

    void insertIn(AbstractSimulator *simulator, AbstractScheduler *scheduler);

    int maxNodes() { return HPCParameters::gpuMaxNumberOfNode; };

    double maxTime() { return HPCParameters::gpuMaximumTime; };

    /*
     * Assume that the job that you are trying to execute is the first in his queue
     */
    void tryToExecute(AbstractSimulator *simulator, AbstractScheduler *scheduler);

    string getType() { return type; };

    void generateRandomRequirements();

    bool isGpuJob() override { return true; };

    void registerAsFinishedJob(HPCSimulator *pSimulator);
};


typedef AbstractJob *(*CreateJobFn)();

AbstractJob *CreateRandomJob(const bool permissions[5]);

#endif
