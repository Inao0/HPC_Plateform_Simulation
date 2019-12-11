#include "../include/AbstractSimulator.h"

AbstractSimulator::AbstractSimulator()  {}

void AbstractSimulator::insert(AbstractEvent* e) {
	events->insert(e);
}

AbstractSimulator::~AbstractSimulator() { 
	delete events; 
}

