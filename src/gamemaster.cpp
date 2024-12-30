/**
 @file
 @author Kavin Parakh <kkp56@drexel.edu>
 @date 11/05/2023
 @section Description
*/

#include "gamemaster.h"
#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <thread>

std::mutex GameMaster::queueMutex;
std::condition_variable GameMaster::queueCondVar;
std::queue<int> GameMaster::diceRollsQueue;
bool GameMaster::raceFinished = false;
std::vector<std::pair<int, std::thread::id>> GameMaster::finishOrder;
int GameMaster::finishCounter = 0;

GameMaster::GameMaster(int racers) : racersCount(racers) {}

void GameMaster::start() {
    gameMasterThread = std::thread(gameMasterThreadFunction, racersCount);
}

void GameMaster::join() {
    if (gameMasterThread.joinable()) {
        gameMasterThread.join();
    }
}

void GameMaster::gameMasterThreadFunction(int racers) {
    std::random_device rd;

    // Source: https://www.geeksforgeeks.org/stdmt19937-class-in-cpp/#
    std::mt19937 gen(rd());

    // Source: https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
    std::uniform_int_distribution<> diceRollsCount(0, 5);
    std::uniform_int_distribution<> diceRoll(1, 6);
    std::uniform_int_distribution<> sleepTime(0, 2000);

    while (!raceFinished) {
        int k = diceRollsCount(gen);
        std::unique_lock<std::mutex> lk(queueMutex);
        for (int i = 0; i < k; ++i) {
            diceRollsQueue.push(diceRoll(gen));
        }
        lk.unlock();
        queueCondVar.notify_all();

        // Source: https://stackoverflow.com/questions/49071285/sleep-vs-sleep-for
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime(gen)));

        if (finishCounter >= racers) {
            raceFinished = true;
        }
    }
}

int GameMaster::getDiceRoll() {
    std::unique_lock<std::mutex> lk(queueMutex);
    queueCondVar.wait(lk, [] { return !diceRollsQueue.empty() || raceFinished; });

    if (raceFinished) {
        return 0; // Race has finished, no more rolls.
    }

    int roll = diceRollsQueue.front();
    diceRollsQueue.pop();
    return roll;
}

void GameMaster::notifyFinish(std::thread::id threadID) {
    std::lock_guard<std::mutex> lk(finishMutex);
    finishOrder.push_back({finishCounter++, threadID});
}

void GameMaster::printResults() const {
    std::lock_guard<std::mutex> lk(finishMutex);
    int displayCount = 0;
    for (const auto &entry : finishOrder) {
        if (displayCount++ < finishOrder.size()) { 
            std::cout << displayCount << ": " << entry.second << std::endl;
        } 
        else {
            break;
        }
    }
}
