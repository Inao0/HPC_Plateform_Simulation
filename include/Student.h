//
// Created by inao on 12/12/2019.
//

#ifndef SUPERCOMPUTERSIMULATION_STUDENT_H
#define SUPERCOMPUTERSIMULATION_STUDENT_H


#include "User.h"
#include "Curriculum.h"

class Student : public User {
private:
    Curriculum curriculum;
public:
    Student(Curriculum curriculum, double time = 0.0) : User(time), curriculum(curriculum) {};

    Student(const Student &g) = delete;

    Student &operator=(const Student &g) = delete;

    void execute(AbstractSimulator *simulator);

    void addScheduler(Scheduler *scheduler) { this->scheduler = scheduler; };

    double budgetLeft();


};


#endif //SUPERCOMPUTERSIMULATION_STUDENT_H
