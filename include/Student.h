//
// Created by inao on 12/12/2019.
//

#ifndef SUPERCOMPUTERSIMULATION_STUDENT_H
#define SUPERCOMPUTERSIMULATION_STUDENT_H


#include "User.h"
#include "Curriculum.h"

class Student : public User {
private:
    Curriculum* curriculum;
public:
    Student(Curriculum* curriculum, double time = 0.0);

    Student(const Student &g) = delete;

    Student &operator=(const Student &g) = delete;

};


#endif //SUPERCOMPUTERSIMULATION_STUDENT_H