#include "../include/HPCSimulator.h"
#include "../include/AbstractScheduler.h"
#include "../include/User.h"
#include "../include/Student.h"
#include "../include/Researcher.h"
#include "../include/weekendEvent.h"
#include "../include/Group.h"
#include <cmath>

void HPCSimulator::start() {
    auto* scheduler = new Scheduler();

	events = new ListQueue();
    int numberOfWeeks = 4;
    auto *weekendBegin = new WeekendBegin(numberOfWeeks, scheduler);
    auto *weekendEnd = new WeekendEnd(numberOfWeeks, scheduler);
    insert(weekendBegin);
    insert(weekendEnd);

	/* Create the generator, queue, and simulator */
	/* Connect them together. */
	std::vector<Node*> nodes;
    for (int i = 0; i < JobsSizes::TotalNumberOfNodes ; ++i) {
        nodes.push_back(new Node());
    }

	auto *curriculum1 = new Curriculum(50,20);
    auto *curriculum2 = new Curriculum(4000,120);
     auto *group1= new Group(4000);

	auto* user1 = new Student(curriculum1);
	auto* user2 = new Student(curriculum1);
	auto* user3 = new Student(curriculum2);
	auto* researcher1 =new Researcher(group1);
	auto* researcher2 =new Researcher(group1);

	researcher1->addIndividualGrant(1000);

    cout<<" End User initialisation"<<std::endl;
	user1->addScheduler(scheduler);
	user2->addScheduler(scheduler);
	user3->addScheduler(scheduler);
	researcher1->addScheduler(scheduler);
	researcher2->addScheduler(scheduler);
    cout<<" End User initialisation"<<std::endl;
    for (auto &node : nodes) {
        scheduler->addFreeNode(this, node);
        node->addScheduler(scheduler);
    }
	/* Start the generator by creating one customer immediately */

	insert(user1);
	insert(user2);
	insert(user3);
	insert(researcher1);
	insert(researcher2);
    cout<<"users inserted"<<std::endl;
	// execute the events

	doAllEvents();

	// free the memory, note that events is freed in the base class destructor
    for (int i = 0; i < nodes.size() ; ++i) {
        Node* node = nodes.back();
        nodes.pop_back();
        delete node;
    }
    delete curriculum1;
	delete curriculum2;
	delete scheduler;
	delete user1;
	delete user2;
	delete user3;
	delete researcher1;
	delete researcher2;
	delete weekendBegin;
	delete weekendEnd;


}




	

