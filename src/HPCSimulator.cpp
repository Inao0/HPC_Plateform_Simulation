#include "../include/HPCSimulator.h"
#include "../include/AbstractScheduler.h"
#include "../include/User.h"
#include "../include/Student.h"
#include <cmath>

void HPCSimulator::start() {

	events = new ListQueue();

	/* Create the generator, queue, and simulator */
	/* Connect them together. */
	Node* node1 = new Node();
    Node* node2 = new Node();
    Node* node3 = new Node();
	Scheduler* scheduler = new Scheduler();
	Curriculum *curriculum1 = new Curriculum(1.5,3);
    Curriculum *curriculum2 = new Curriculum(80,4);

	Student* user1 = new Student(curriculum1);
	Student* user2 = new Student(curriculum2);
	Student* user3 = new Student(curriculum2);


	user1->addScheduler(scheduler);
	user2->addScheduler(scheduler);
	user3->addScheduler(scheduler);
    scheduler->addFreeNode(this, node1);
    scheduler->addFreeNode(this, node2);
    scheduler->addFreeNode(this, node3);
	node1->addScheduler(scheduler);
	node2->addScheduler(scheduler);
	node3->addScheduler(scheduler);
	/* Start the generator by creating one customer immediately */
	insert(user1);
	insert(user2);
	insert(user3);

	// execute the events
	doAllEvents();

	node1->getStats();
	node2->getStats();

	// free the memory, note that events is freed in the base class destructor
	delete node1;
	delete node2;
	delete node3;
	delete curriculum1;
	delete curriculum2;
	delete scheduler;
	delete user1;
	delete user2;
	delete user3;


}




	

