#include "../include/Simulator.h"
#include <cmath>

Event::Event(double time) { this->time = time; }

bool Event::lessThan(Comparable* y) {
	Event* e = (Event*)y;
	return time < e->time;
}

void Event::execute(AbstractSimulator* simulator) 
{ 
	std::cout << std::endl <<"Time is " << convertTime(simulator->now()) << "\n";
}

double Event::getTime() { return time; }



Simulator::Simulator() { time = 0.0; }

double Simulator::now() {
	return time;
}

void Simulator::doAllEvents() {
	Event* e;
	while ((e = (Event*)events->removeFirst()) != 0) {
		time = e->getTime();
		e->execute(this);
	}
}
