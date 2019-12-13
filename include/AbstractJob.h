#ifndef _QUEUE
#define _QUEUE

/*#include "Node.h"*/

#include <limits>
#include "AbstractScheduler.h"

/*class JobQueue;*/

class User;

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

    virtual void insertIn(AbstractSimulator* simulator, Scheduler *scheduler) = 0;

    virtual int maxNodes() = 0;

    virtual double maxTime() = 0;

    virtual string getType() = 0;

    virtual void tryToExecute(AbstractSimulator *simulator, Scheduler *scheduler) = 0;

};

class LargeJob : public AbstractJob {
private:
    static int maxNumberOfNode; //TODO adapt to number of Node in the HPC plateform
    static double maximumTime;

public:
    virtual void insertIn(AbstractSimulator *simulator, Scheduler *scheduler);

    int maxNodes() { return maxNumberOfNode; };

    double maxTime() {
        return maximumTime;
    };

    string getType() { return "Large"; };

    virtual void tryToExecute(AbstractSimulator *simulator, Scheduler *scheduler) ;
};


class MediumJob : public AbstractJob {
private:
    static int maxNumberOfNode; //TODO adapt to number of Node in the HPC plateform
    static double maximumTime;
    string type = "Medium";
public:

    void insertIn(AbstractSimulator *simulator, Scheduler *scheduler);

    int maxNodes() {
        return maxNumberOfNode;
    };

    double maxTime() {
        return maximumTime;
    };

    string getType() { return "Medium"; };
    /*
     * Assume that the job that you are trying to execute is the first in his queue
     */
    virtual void tryToExecute(AbstractSimulator *simulator, Scheduler *scheduler);
};

class SmallJob : public AbstractJob {
private:
	static int maxNumberOfNode; //TODO adapt to number of Node in the HPC plateform
	static double maximumTime;
	string type = "Small";
public:

	void insertIn(AbstractSimulator* simulator, Scheduler* scheduler);

	int maxNodes() {
		return maxNumberOfNode;
	};

	double maxTime() {
		return maximumTime;
	};

	string getType() { return "Small"; };
	/*
	 * Assume that the job that you are trying to execute is the first in his queue
	 */
	virtual void tryToExecute(AbstractSimulator* simulator, Scheduler* scheduler);
};





class HugeJob : public AbstractJob {
private:
    static int maxNumberOfNode; //TODO adapt to number of Node in the HPC plateform
    static double maximumTime; // From friday 5 pm to monday 9am
    string type = "Huge";
public:
    void insertIn(AbstractSimulator *simulator, Scheduler *scheduler);

    int maxNodes() {
        maxNumberOfNode = 6;
        return maxNumberOfNode;
    };

    double maxTime() {
        maximumTime = 64;
        return maximumTime;
    };

    string getType() { return "Huge"; };
};

typedef AbstractJob *(*CreateJobFn)();

AbstractJob *CreateRandomJob();

#endif
