#include "../include/HPCSimulator.h"
#include "../include/AbstractScheduler.h"
#include "../include/User.h"
#include "../include/Student.h"
#include "../include/Researcher.h"
#include "../include/weekendEvent.h"
#include "../include/Group.h"
#include <cmath>
#include <fstream>

void HPCSimulator::start() {
    auto *scheduler = new Scheduler();

    events = new ListQueue();
//TODO change this crap
    int numberOfWeeks = 8;
    auto *weekendBegin = new WeekendBegin(numberOfWeeks, scheduler);
    auto *weekendEnd = new WeekendEnd(numberOfWeeks, scheduler);
    insert(weekendBegin);
    insert(weekendEnd);

    /* Create the generator, queue, and simulator */
    /* Connect them together. */
    std::vector<Node *> nodes;
    for (int i = 0; i < JobsSizes::TotalNumberOfNodes; ++i) {
        nodes.push_back(new Node());
    }
    for (auto &node : nodes) {
        scheduler->addFreeNode(this, node);
        node->addScheduler(scheduler);
    }
    for (User *user : users) {
        user->addScheduler(scheduler);
        insert(user);
    }
    cout<<users.size()<< " users inserted in the timeline \n";
    doAllEvents();

    // free the memory, note that events is freed in the base class destructor
    for (int i = 0; i < nodes.size(); ++i) {
        Node *node = nodes.back();
        nodes.pop_back();
        delete node;
    }
    for (int i = 0; i < users.size(); ++i) {
        User *user = users.back();
        users.pop_back();
        delete user;
    }
    delete weekendBegin;
    delete weekendEnd;

}

void HPCSimulator::initialisation(string filename) {
    cout << "Initialising simulation from file \n";
    std::ifstream inputStream(filename);
    std::string line = "";
    getline(inputStream, line);
    //research group parsing
    while (line != "----") {
        unsigned long firstMeaningfullcharacter = line.find_first_not_of(" \t");
        if (firstMeaningfullcharacter == string::npos || line[firstMeaningfullcharacter] == '#') {
            getline(inputStream, line);
            continue;
        } else {
            double commonBudget;
            double averageTimeBetweenJobs;
            bool permissions[5];
            int numberOfResearchers;
            std::vector<double> individualGrants;

            //budget line:
            commonBudget = std::stod(line.substr(line.find(' ') + 1, line.size() - 1));
            auto *group = new Group(commonBudget);

            // permission line :
            getline(inputStream, line);
            int indexFirstSpace = line.find(' ');
            for (int i = 0; i < 5; ++i) {
                permissions[i] = ('1' == line[indexFirstSpace + 1 + 2 * i]);
            }

            //Average Time Between Two Jobs line
            getline(inputStream, line);
            averageTimeBetweenJobs = std::stod(line.substr(line.find(' ') + 1, line.size() - 1));

            //Get Individual Grant
            getline(inputStream, line);
            int indexNextSpaceIndex = line.find(' ');
            if (indexNextSpaceIndex != line.npos) {
                std::string grantsString = (line.substr(line.find(' ') + 1, line.size() - 1));
                if (grantsString.find_first_not_of(" \t") != grantsString.npos) {
                    while (!grantsString.empty()) {
                        individualGrants.push_back(std::stod(grantsString.substr(0, grantsString.find(' '))));
                        if (grantsString.find(' ') == grantsString.npos) {
                            grantsString = "";
                        } else {
                            grantsString = grantsString.substr(grantsString.find(' ') + 1, grantsString.npos - 1);
                        }

                    }
                }
            }

            // Number of researchers line
            getline(inputStream, line);
            numberOfResearchers = std::stoi(line.substr(line.find(' ') + 1, line.size() - 1));

            for (int j = 0; j < numberOfResearchers; ++j) {
                auto *researcher = new Researcher(group, averageTimeBetweenJobs);
                if (j < individualGrants.size()) {
                    researcher->addIndividualGrant(individualGrants[j]);
                }
                users.push_back(researcher);
            }

            cout << " Group : " << commonBudget << ',' << permissions[0] << permissions[1] << permissions[2]
                 << permissions[3] << permissions[4] << ',' << averageTimeBetweenJobs << "," << numberOfResearchers
                 << "\n";
            getline(inputStream, line);
        }
    }
    getline(inputStream, line);
    //Curriculums parsing
    while (line != "----") {
        unsigned long firstMeaningfullcharacter = line.find_first_not_of(" \t");
        if (firstMeaningfullcharacter == string::npos || line[firstMeaningfullcharacter] == '#') {
            getline(inputStream, line);
            continue;
        } else {
            double cummulativeCap;
            int instantanousCap;
            double averageTimeBetweenJobs;
            bool permissions[5];
            int numberOfStudents;
            std::vector<double> individualGrants;

            //cumulative cap line
            cummulativeCap = std::stod(line.substr(line.find(' ') + 1, line.size() - 1));

            // instantaneous cap line
            getline(inputStream, line);
            instantanousCap = std::stoi(line.substr(line.find(' ') + 1, line.size() - 1));

            auto *curriculum = new Curriculum(cummulativeCap, instantanousCap);

            // permission line :
            getline(inputStream, line);
            int indexFirstSpace = line.find(' ');
            for (int i = 0; i < 5; ++i) {
                permissions[i] = ('1' == line[indexFirstSpace + 1 + 2 * i]);
            }

            //Average Time Between Two Jobs line
            getline(inputStream, line);
            averageTimeBetweenJobs = std::stod(line.substr(line.find(' ') + 1, line.size() - 1));

            // Number of students line
            getline(inputStream, line);
            numberOfStudents = std::stoi(line.substr(line.find(' ') + 1, line.size() - 1));


            for (int j = 0; j < numberOfStudents; ++j) {
                users.push_back(new Student(curriculum, averageTimeBetweenJobs));
            }

            cout << " Curriculum : " << cummulativeCap << "," << instantanousCap << ',' << permissions[0]
                 << permissions[1] << permissions[2]
                 << permissions[3] << permissions[4] << ',' << averageTimeBetweenJobs << "," << numberOfStudents
                 << "\n";
            getline(inputStream, line);
        }
    }
}




	

