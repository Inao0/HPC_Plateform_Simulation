#include "../include/Student.h"

Student::Student(Curriculum* curriculum, double time) : User(time), curriculum(curriculum) {
    budget = curriculum->getCumulativeCapInNodeHour();
    instantaneousMaxNumberOfNodes = curriculum->getInstantaneousCapInNode();
}
