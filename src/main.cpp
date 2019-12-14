
#include "../include/HPCSimulator.h"

int main() {
    cout << " HPC simulator initialisation" << std::endl;
    HPCSimulator b;
    b.initialisation("../data/InputDataExample.txt");
    cout << " Starting" << std::endl;
    b.start();
    return 0;
}
