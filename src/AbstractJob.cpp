#include "../include/AbstractJob.h"
#include "../include/User.h"
#include "../include/random.h"
#include "../include/JobsSizes.h"

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
                &CreateJob<HugeJob>,
				&CreateJob<GpuJob>

        };


const size_t fncount = sizeof(create) / sizeof(*create);

AbstractJob *CreateRandomJob(const bool permissions[5]) {
    std::vector <int> proportionsWithPermissions= {0,0,0,0,0};
    for (int i = 0; i < 5; ++i) {
        if (permissions[i]){
            proportionsWithPermissions[i]=JobsSizes::jobTypeProportions[i];
        }
    }
    std::random_device randomDevice;
    std::mt19937 randomGenerator(randomDevice());
    std::discrete_distribution<int> distribution (proportionsWithPermissions.begin(),proportionsWithPermissions.end());

    return create[ distribution (randomGenerator)](); //forward the call
}

void LargeJob::insertIn(AbstractSimulator *simulator, AbstractScheduler *scheduler) {
    scheduler->insertLargeJob(simulator, this);
}

void MediumJob::insertIn(AbstractSimulator *simulator, AbstractScheduler *scheduler) {
    scheduler->insertMediumJob(simulator, this);
}

void SmallJob::insertIn(AbstractSimulator *simulator, AbstractScheduler *scheduler) {
    scheduler->insertSmallJob(simulator, this);
}

void GpuJob::insertIn(AbstractSimulator* simulator, AbstractScheduler* scheduler) {
	scheduler->insertGpuJob(simulator, this);
}

void HugeJob::insertIn(AbstractSimulator *simulator, AbstractScheduler *scheduler) {
    scheduler->insertHugeJob(simulator, this);
}


void AbstractJob::generateRandomTime(double minTime, double maxTime) {
    double timeMean = 0.5 * (minTime + maxTime);
    double timeStddev = (maxTime - minTime) / 6;
    do {
        executionDuration = Random::normalDouble(timeMean, timeStddev);
    } while (minTime > executionDuration || maxTime < executionDuration);
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

void HugeJob::tryToExecute(AbstractSimulator *simulator, AbstractScheduler *scheduler) {
    //TODO justify this properly . Should never be called. Huge
}

void LargeJob::tryToExecute(AbstractSimulator *simulator, AbstractScheduler *scheduler) {
    scheduler->tryToExecuteNextLargeJob(simulator);
}

void GpuJob::tryToExecute(AbstractSimulator* simulator, AbstractScheduler* scheduler) {
    scheduler->tryToExecuteNextGpuJob(simulator);
}

void MediumJob::tryToExecute(AbstractSimulator *simulator, AbstractScheduler *scheduler) {
    scheduler->tryToExecuteNextMediumJob(simulator);
}

void SmallJob::tryToExecute(AbstractSimulator *simulator, AbstractScheduler *scheduler) {
    scheduler->tryToExecuteNextSmallJob(simulator);
}


void GpuJob::registerAsFinishedJob(HPCSimulator *simulator){
    simulator->registerFinishedGpuJobs(this);
}
void SmallJob::registerAsFinishedJob(HPCSimulator *simulator){
    simulator->registerFinishedSmallJobs(this);
}
void MediumJob::registerAsFinishedJob(HPCSimulator *simulator){
    simulator->registerFinishedMediumJobs(this);
}
void LargeJob::registerAsFinishedJob(HPCSimulator *simulator){
    simulator->registerFinishedLargeJobs(this);
}
void HugeJob::registerAsFinishedJob(HPCSimulator *simulator) {
    simulator->registerFinishedHugeJobs(this);
}


