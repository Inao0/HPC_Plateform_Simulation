#ifndef SUPERCOMPUTERSIMULATION_CURRICULUM_H
#define SUPERCOMPUTERSIMULATION_CURRICULUM_H


class Curriculum {
    const double cumulativeCapPerStudentInNodeHour;
    const int instantaneousCapPerStudentInNodes;
public:
    int getInstantaneousCapInNode() { return instantaneousCapPerStudentInNodes; };

    double getCumulativeCapInNodeHour() { return cumulativeCapPerStudentInNodeHour;};

    Curriculum(double cumulativeCap, int instantaneousCap) : cumulativeCapPerStudentInNodeHour(cumulativeCap),
                                                             instantaneousCapPerStudentInNodes(instantaneousCap) {};
    Curriculum()=delete;
};


#endif //SUPERCOMPUTERSIMULATION_CURRICULUM_H
