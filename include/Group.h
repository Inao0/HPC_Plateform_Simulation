#ifndef SUPERCOMPUTERSIMULATION_CURRICULUM_H
#define SUPERCOMPUTERSIMULATION_CURRICULUM_H


class Group {
	const double cumulativeCapPerGroupInNodeHour;
	const int individualGrantsPerResearcherInNodes;
public:
	int getIndividualGrantsPerResearcherInNodes() { return individualGrantsPerResearcherInNodes; };

	double getGrantsInNodeHour() { return cumulativeCapPerGroupInNodeHour; };

	Group(double cumulativeCap, int individualCap) : cumulativeCapPerGroupInNodeHour(cumulativeCap),
		individualGrantsPerResearcherInNodes(individualCap) {};
	Group() = delete;
};