#pragma once

#include <vector>
#include "Simulator.h"
#include "Group.h"
#include "Curriculum.h"
#include "User.h"

class GpuJob;
class SmallJob;
class MediumJob;
class LargeJob;
class HugeJob;
class User;

class HPCSimulator : public Simulator {
private:
    std::vector<User*> users;
    std::vector<GpuJob*> finishedGpuJobs;
    std::vector<SmallJob*> finishedSmallJobs;
    std::vector<MediumJob*> finishedMediumJobs;
    std::vector<LargeJob*> finishedLargeJobs;
    std::vector<HugeJob*> finishedHugeJobs;
    double initialUsersBudget=0;

public:
	HPCSimulator() = default;
	void initialisation (string filename);
	void start();

    void registerFinishedGpuJobs(GpuJob *pJob);

    void registerFinishedSmallJobs(SmallJob *pJob);

    void registerFinishedMediumJobs(MediumJob *pJob);

    void registerFinishedLargeJobs(LargeJob *pJob);

    void registerFinishedHugeJobs(HugeJob *pJob);

    void printResults();
};


