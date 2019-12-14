#ifndef SUPERCOMPUTERSIMULATION_GROUP_H
#define SUPERCOMPUTERSIMULATION_GROUP_H


class Group {
    double groupRessourcesAllocationInNodeHours;

public:

    double getGroupRessourcesInNodeHour() { return groupRessourcesAllocationInNodeHours; };

    void removeFromGroupRessources(
            double nodeHoursToRemove) { groupRessourcesAllocationInNodeHours -= nodeHoursToRemove; }

    Group(double cumulativeCap) : groupRessourcesAllocationInNodeHours(cumulativeCap) {};

    Group() = delete;
};

#endif //SUPERCOMPUTERSIMULATION_GROUP_H
