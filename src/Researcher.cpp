#include "../include/Researcher.h"

Researcher::Researcher(Group* group, double time) : User(time), group(group) {
	budget = curriculum->getGrantsInNodeHour();
	individualGrantPerUser = group->getIndividualGrantsPerResearcherInNodes();
}
