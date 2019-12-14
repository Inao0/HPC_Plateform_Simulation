#pragma once

#include <vector>
#include "Simulator.h"
#include "Group.h"
#include "Curriculum.h"
#include "User.h"

class HPCSimulator : public Simulator {
private:
    std::vector<User*> users;
public:
	HPCSimulator() = default;
	void initialisation (string filename);
	void start();
};


