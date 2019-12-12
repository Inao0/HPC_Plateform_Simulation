
#ifndef SUPERCOMPUTERSIMULATION_STUDENT_H
#define SUPERCOMPUTERSIMULATION_STUDENT_H


#include "User.h"
#include "Group.h"

class Researcher : public User {
private:
	Group* group;
public:
	Researcher(Group* group ,double time = 0.0);

	Researcher(const Researcher & g) = delete;

	Researcher& operator=(const Researcher& g) = delete;

};


#endif //SUPERCOMPUTERSIMULATION_STUDENT_H
