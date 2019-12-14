#include "../include/AbstractJob.h"
#include "../include/User.h"
#include "../include/random.h"

/*RESOURCE from stackoverflow https://stackoverflow.com/questions/7803345/how-to-randomly-select-a-class-to-instantiate-without-using-switch
 * about generating randomly one of the different subclasses */
int AbstractJob::jobCounter = 0;

AbstractJob::AbstractJob() {
    id = ++jobCounter;
}

double AbstractJob::priority() const {
    return (-submittingTime);
}

template<typename T>
AbstractJob *CreateJob() { return new T(); }

CreateJobFn create[] =
        {
                &CreateJob<LargeJob>,
                &CreateJob<MediumJob>,
                &CreateJob<SmallJob>,
                &CreateJob<MediumJob>,
                &CreateJob<HugeJob>,
				&CreateJob<GpuJob>

        };


const size_t fncount = sizeof(create) / sizeof(*create);

AbstractJob *CreateRandomJob() {
    return create[rand() % fncount](); //forward the call
}

void LargeJob::insertIn(AbstractSimulator *simulator, Scheduler *scheduler) {
    scheduler->insertLargeJob(simulator, this);
}

void MediumJob::insertIn(AbstractSimulator *simulator, Scheduler *scheduler) {
    scheduler->insertMediumJob(simulator, this);
}

void SmallJob::insertIn(AbstractSimulator *simulator, Scheduler *scheduler) {
    scheduler->insertSmallJob(simulator, this);
}

void GpuJob::insertIn(AbstractSimulator* simulator, Scheduler* scheduler) {
	scheduler->insertGpuJob(simulator, this);
}

void HugeJob::insertIn(AbstractSimulator *simulator, Scheduler *scheduler) {
    scheduler->insertHugeJob(simulator, this);
}


void AbstractJob::generateRandomTime(double minTime, double maxTime) {
    double timeMean = 0.5 * (minTime + maxTime);
    double timeStddev = (maxTime - minTime) / 6;
    do {
        executionTime = Random::normalDouble(timeMean, timeStddev);
    } while (minTime > executionTime || maxTime < executionTime);
}

//TODO : ASSUMPTION on minimum limits
void LargeJob::generateRandomRequirements() {
    generateRandomTime(JobsSizes::mediumMaximumTime, JobsSizes::largeMaximumTime);
    numberOfNodes = JobsSizes::mediumMaxNumberOfNode +
                    Random::binomialInt(JobsSizes::largeMaxNumberOfNode - JobsSizes::mediumMaxNumberOfNode, 0.5);
}

void HugeJob::generateRandomRequirements() {
    generateRandomTime(JobsSizes::largeMaximumTime, JobsSizes::hugeMaximumTime);
    numberOfNodes = JobsSizes::largeMaxNumberOfNode +
                    Random::binomialInt(JobsSizes::hugeMaxNumberOfNode - JobsSizes::largeMaxNumberOfNode, 0.5);
}

void MediumJob::generateRandomRequirements() {
    generateRandomTime(JobsSizes::smallMaximumTime, JobsSizes::mediumMaximumTime);
    numberOfNodes = JobsSizes::smallMaxNumberOfNode +
                    Random::binomialInt(JobsSizes::mediumMaxNumberOfNode - JobsSizes::smallMaxNumberOfNode, 0.5);
}
void SmallJob::generateRandomRequirements() {
    generateRandomTime(0, JobsSizes::smallMaximumTime);
    numberOfNodes = 1+Random::binomialInt(JobsSizes::smallMaxNumberOfNode-1, 0.5);
}

void GpuJob::generateRandomRequirements() {
	generateRandomTime(0, JobsSizes::gpuMaximumTime);
	numberOfNodes = 1 + Random::binomialInt(JobsSizes::gpuMaxNumberOfNode-1, 0.5);
}

void HugeJob::tryToExecute(AbstractSimulator *simulator, Scheduler *scheduler) {
    //TODO justify this properly . Should never be called. Huge
}

void LargeJob::tryToExecute(AbstractSimulator *simulator, Scheduler *scheduler) {
    scheduler->tryToExecuteNextLargeJob(simulator);
}

void GpuJob::tryToExecute(AbstractSimulator* simulator, Scheduler* scheduler) {
    scheduler->tryToExecuteNextGpuJob(simulator);
}

void MediumJob::tryToExecute(AbstractSimulator *simulator, Scheduler *scheduler) {
    scheduler->tryToExecuteNextMediumJob(simulator);
}


void SmallJob::tryToExecute(AbstractSimulator *simulator, Scheduler *scheduler) {
    scheduler->tryToExecuteNextSmallJob(simulator);
}


