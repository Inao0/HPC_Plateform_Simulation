//
// Created by inao on 13/12/2019.
//

#include "../include/weekendEvent.h"

void WeekendBegin::execute(AbstractSimulator *simulator) {
    Event::execute(simulator);

    std::cout << "Weekend Start" << std::endl;
    if (simulator->eventsSize()>1 || scheduler->totalOfNonHugeJobsWaiting()>0) {
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
    scheduler->tryToExecuteNextJobs(simulator);
    if (simulator->eventsSize()>0 ) {
        time += numberOfHoursInAWeek;
        if (simulator->eventsSize()==1){
            cout<<"LAST WEEK IS EMPTY \n";
        }
        simulator->insert(this);
    }


}

WeekendEnd::WeekendEnd(int numberOfWeeks, Scheduler *scheduler1) : numberOfWeeksSimulated(numberOfWeeks),
                                                                   scheduler(scheduler1) {
    time = numberOfHoursInAWeek;
}
