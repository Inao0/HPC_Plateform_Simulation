
#pragma once

#include <iostream>
#include <string>
using namespace std;

class AbstractSimulator;

class Comparable {
public:
	virtual bool lessThan(Comparable* y) = 0;
	virtual ~Comparable() {}
};


class AbstractEvent : public Comparable {
public:
	virtual void execute(AbstractSimulator* simulator) = 0;
};


class OrderedSet {
public:
	virtual void insert(Comparable* x) = 0;
	virtual Comparable* removeFirst() = 0;
	virtual int size() = 0;
	virtual Comparable* remove(Comparable* x) = 0;
	virtual ~OrderedSet() { }
};
    

class AbstractSimulator {
protected:
	OrderedSet* events;
public:
	AbstractSimulator();
	void insert(AbstractEvent* e); 
	virtual void doAllEvents() = 0;
	virtual double now() = 0;
	virtual ~AbstractSimulator();
    int eventsSize();//added function
};

