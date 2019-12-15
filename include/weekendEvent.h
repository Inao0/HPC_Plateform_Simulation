//
// Created by inao on 13/12/2019.
//

#ifndef SUPERCOMPUTERSIMULATION_WEEKENDEVENT_H
#define SUPERCOMPUTERSIMULATION_WEEKENDEVENT_H


#include "Simulator.h"
#include "AbstractScheduler.h"

class WeekendBegin : public Event {
private:
    AbstractScheduler *scheduler;
    const double numberOfHoursInAWeek = 168;
    const double numberOfHoursBeforeWeekEnd = 104;
public:
    void execute(AbstractSimulator *simulator) override;
    WeekendBegin(AbstractScheduler *scheduler);
};

class WeekendEnd : public Event {
private:
    AbstractScheduler *scheduler;
    const double numberOfHoursInAWeek = 168;
    const double numberOfHoursBeforeWeekEnd = 168;
public:
    void execute(AbstractSimulator *simulator) override;
    WeekendEnd(AbstractScheduler *scheduler);
};



#endif //SUPERCOMPUTERSIMULATION_WEEKENDEVENT_H
