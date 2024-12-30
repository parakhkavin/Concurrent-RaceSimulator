/**
 @file
 @author Kavin Parakh <kkp56@drexel.edu>
 @date 11/05/2023
 @section Description

 This program simulates a race between multiple racers, each represented by a thread.
 The progress of each racer is determined by dice rolls managed by the GameMaster.

*/

#include "racer.h"
#include "gamemaster.h"
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <thread>


/**
 @brief Main function to start the race simulation.
 
 This function initializes the GameMaster and all Racers, starts their threads, and
 waits for the race to finish before printing the results.
  
 @param argc The argument count.
 @param argv The argument vector, expects the number of racers as the second argument.
 @return int Returns 0 on successful execution, 1 on error.
 
*/
int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <number_of_racers>\n";
        return 1;
    }

    int racers = std::stoi(argv[1]);
    if (racers <= 0) {
        std::cerr << "Error: The number of threads must be strictly larger than 0.\n";
        return 1;
    }

    std::cout << "Starting Race with " << racers << " threads.\n";

    // Initialize the GameMaster and racers
    GameMaster master(racers);

    //Source: https://stackoverflow.com/questions/16894400/how-to-declare-stdunique-ptr-and-what-is-the-use-of-it
    std::vector<std::unique_ptr<Racer>> racerObjects;
    for (int i = 0; i < racers; ++i) {
        racerObjects.emplace_back(std::make_unique<Racer>(i, master));
    }

    // Start all racer threads
    master.start();
    for (auto& r : racerObjects) {
        r->start();
    }

    // Wait for all threads to finish
    master.join();
    for (auto& r : racerObjects) {
        r->join();
    }

    // Print race results
    std::cout << "Race finished. Results:\n";
    master.printResults();

    return 0;
}
