#include "../include/AbstractJob.h"
#include "../include/User.h"


/*RESOURCE from stackoverflow https://stackoverflow.com/questions/7803345/how-to-randomly-select-a-class-to-instantiate-without-using-switch
 * about generating randomly one of the different subclasses */
int AbstractJob::jobCounter = 0;

AbstractJob::AbstractJob() {
    id = ++jobCounter;
}

template<typename T>
AbstractJob *CreateJob() { return new T(); }


CreateJobFn create[] =
        {
                &CreateJob<LargeJob>,
                &CreateJob<MediumJob>,
                &CreateJob<MediumJob>//,
                //&CreateJob<HugeJob>
        };

const size_t fncount = sizeof(create) / sizeof(*create);

AbstractJob *CreateRandomJob() {
    return create[rand() % fncount](); //forward the call
}

void LargeJob::insertIn(AbstractSimulator *simulator,Scheduler *scheduler) {
    scheduler->insertLargeJob(simulator,this);
}

void MediumJob::insertIn(AbstractSimulator *simulator,Scheduler *scheduler) {
    scheduler->insertMediumJob(simulator,this);
}

void HugeJob::insertIn(AbstractSimulator *simulator,Scheduler *scheduler) {
    scheduler->insertHugeJob(simulator,this);
}


int LargeJob::maxNumberOfNode = 4;
double LargeJob::maximumTime = 16;

void LargeJob::tryToExecute(AbstractSimulator *simulator, Scheduler *scheduler) {
    scheduler->tryToExecuteNextLargeJob(simulator);
}

int MediumJob::maxNumberOfNode = 2;
double MediumJob::maximumTime = 8;

void MediumJob::tryToExecute(AbstractSimulator *simulator, Scheduler *scheduler) {
    scheduler->tryToExecuteNextMediumJob(simulator);
}

int HugeJob::maxNumberOfNode = 6;
double HugeJob::maximumTime = 64;


