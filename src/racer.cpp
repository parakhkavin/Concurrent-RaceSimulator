/**
 @file
 @author Kavin Parakh <kkp56@drexel.edu>
 @date 11/05/2023
 @section Description
*/

#include "racer.h"
#include "gamemaster.h"
#include <iostream>
#include <mutex>
#include <random>
#include <chrono>
#include <thread>

std::mutex ioMutex;

// Racer constructor
Racer::Racer(int id, GameMaster& gm) : id(id), distance(0), gameMaster(gm) {}


void Racer::start() {
    racerThread = std::thread(&Racer::run, this);
}

void Racer::join() {
    if (racerThread.joinable()) {
        racerThread.join();
    }
}

void Racer::run() {
    {
        std::unique_lock<std::mutex> lk(ioMutex); // Lock the mutex for I/O operations
        std::cout << "Thread " << std::this_thread::get_id() << " has left the gate.\n";
    }

    // Source: // Source: https://www.geeksforgeeks.org/stdmt19937-class-in-cpp/#
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> sleepTime(0, 2000);

    while (distance < 20) {
        int roll = GameMaster::getDiceRoll();
        distance += roll;

        {
            std::unique_lock<std::mutex> lk(ioMutex); // Lock the mutex for I/O operations
            std::cout << "Thread " << std::this_thread::get_id() << " moved forward " << roll << " spaces.\n";

            if (distance >= 20) {
                std::cout << "Thread " << std::this_thread::get_id() << " has crossed the finish line.\n";
                gameMaster.notifyFinish(std::this_thread::get_id()); // Pass the thread id
                break; // Exit the loop since the racer has finished
            }
        } // Mutex automatically releases here due to the scope of unique_lock


        // Source: https://stackoverflow.com/questions/49071285/sleep-vs-sleep-for
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime(gen)));
    }
}


int Racer::getDistance() const {
    return distance;
}

int Racer::getID() const {
    return id;
}
