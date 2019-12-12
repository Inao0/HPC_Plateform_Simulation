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
	User* user1 = new User();
    User* user2 = new User();

	user1->addScheduler(scheduler);
	user2->addScheduler(scheduler);
    scheduler->addFreeNode(this, node1);
    scheduler->addFreeNode(this, node2);
    scheduler->addFreeNode(this, node3);
	node1->addScheduler(scheduler);
	node2->addScheduler(scheduler);
	node3->addScheduler(scheduler);
	/* Start the generator by creating one customer immediately */
	insert(user1);
	insert(user2);

	// execute the events
	doAllEvents();

	node1->getStats();
	node2->getStats();

	// free the memory, note that events is freed in the base class destructor
	delete node1;
	delete node2;
	delete scheduler;
	delete user1;
	delete user2;

}




	

