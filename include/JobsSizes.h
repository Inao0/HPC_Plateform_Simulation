//
// Created by inao on 13/12/2019.
//

#ifndef SUPERCOMPUTERSIMULATION_JOBSSIZES_H
#define SUPERCOMPUTERSIMULATION_JOBSSIZES_H


class JobsSizes {
public:
    static const int TotalNumberOfNodes = 128;

    const static int smallMaxNumberOfNode = 1;
    constexpr static double smallMaximumTime = 2;

    const static int mediumMaxNumberOfNode = 0.1*TotalNumberOfNodes;
    constexpr static double mediumMaximumTime = 8;

    const static int largeMaxNumberOfNode = 0.5*TotalNumberOfNodes;
    constexpr static double largeMaximumTime = 16;

    const static int hugeMaxNumberOfNode = TotalNumberOfNodes;
    constexpr static double hugeMaximumTime = 64;


};


#endif //SUPERCOMPUTERSIMULATION_JOBSSIZES_H
