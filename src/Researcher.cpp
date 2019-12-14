#include "../include/Researcher.h"

Researcher::Researcher(Group* group, double time) : User(time), group(group) {
	budget = group->getGrantsInNodeHour();
	individualGrantPerUser = group->getIndividualGrantsPerResearcherInNodes();
}
