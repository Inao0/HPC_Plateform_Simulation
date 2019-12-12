#include "../include/HPCSimulator.h"
#include "../include/AbstractScheduler.h"
#include "../include/User.h"
#include <cmath>

void HPCSimulator::start() {

	events = new ListQueue();

	/* Create the generator, queue, and simulator */
	/* Connect them together. */
	Node* node1 = new Node();
    Node* node2 = new Node();
    Node* node3 = new Node();
	Scheduler* scheduler = new Scheduler();
	User* user = new User();

	user->addScheduler(scheduler);
	scheduler->addNode(this, node1);
	scheduler->addNode(this, node2);
	scheduler->addNode(this, node3);
	node1->addScheduler(scheduler);
	node2->addScheduler(scheduler);
	node3->addScheduler(scheduler);
	/* Start the generator by creating one customer immediately */
	insert(user);

	// execute the events
	doAllEvents();

	node1->getStats();
	node2->getStats();

	// free the memory, note that events is freed in the base class destructor
	delete node1;
	delete node2;
	delete scheduler;
	delete user;

}




	

