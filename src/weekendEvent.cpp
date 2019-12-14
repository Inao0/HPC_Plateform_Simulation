//
// Created by inao on 13/12/2019.
//

#include "../include/weekendEvent.h"

void WeekendBegin::execute(AbstractSimulator *simulator) {
    Event::execute(simulator);

    std::cout << "Weekend Start" << std::endl;
    if (simulator->now() + (numberOfHoursInAWeek - numberOfHoursBeforeWeekEnd) <=
        numberOfWeeksSimulated * numberOfHoursInAWeek) {
        time += numberOfHoursInAWeek;
        simulator->insert(this);
    }
    scheduler->tryToExecuteNextHugeJobs(simulator);
}

//Assuming that you simulate at least a week
WeekendBegin::WeekendBegin(int numberOfWeeks, Scheduler *scheduler1) : numberOfWeeksSimulated(numberOfWeeks),
                                                                       scheduler(scheduler1) {
    time = numberOfHoursBeforeWeekEnd;
}

void WeekendEnd::execute(AbstractSimulator *simulator) {
    Event::execute(simulator);
    std::cout << "Weekend End" << std::endl;
    if (simulator->now() <=
        numberOfWeeksSimulated * numberOfHoursInAWeek) {
        time += numberOfHoursInAWeek;
        simulator->insert(this);
    }
    scheduler->tryToExecuteNextJobs(simulator);
}

WeekendEnd::WeekendEnd(int numberOfWeeks, Scheduler *scheduler1) : numberOfWeeksSimulated(numberOfWeeks),
                                                                   scheduler(scheduler1) {
    time = numberOfHoursInAWeek;
}
