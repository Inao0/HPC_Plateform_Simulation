#include "../include/AbstractJob.h"
#include "../include/User.h"


/*RESOURCE from stackoverflow https://stackoverflow.com/questions/7803345/how-to-randomly-select-a-class-to-instantiate-without-using-switch
 * about generating randomly one of the different subclasses */

template<typename T>
AbstractJob *CreateJob() { return new T(); }


CreateJobFn create[] =
        {
                &CreateJob<LargeJob>,
                &CreateJob<MediumJob>,
                &CreateJob<MediumJob>,
                &CreateJob<HugeJob>
        };

const size_t fncount = sizeof(create) / sizeof(*create);

AbstractJob *CreateRandomJob() {
    return create[rand() % fncount](); //forward the call
}

void LargeJob::insertIn(Scheduler *scheduler) {
    scheduler->insertLargeJob(this);

}

void MediumJob::insertIn(Scheduler *scheduler) {
    scheduler->insertMediumJob(this);
}

void HugeJob::insertIn(Scheduler *scheduler) {
    scheduler->insertHugeJob(this);
}


int LargeJob::maxNumberOfNode = 4;
double LargeJob::maximumTime = 16;

int MediumJob::maxNumberOfNode = 2;
double MediumJob::maximumTime = 8;

int HugeJob::maxNumberOfNode = 6;
double HugeJob::maximumTime = 64;