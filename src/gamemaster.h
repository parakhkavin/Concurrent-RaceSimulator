/**
 @file
 @author Kavin Parakh <kkp56@drexel.edu>
 @date 11/05/2023
 @section Description
*/

#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <utility>


/**
 @class GameMaster
 @brief Manages the race by controlling dice rolls and racer progress.
 @section Description

 The GameMaster class is responsible for managing the dice rolls, keeping track of the race's progress,
 and determining when the race has finished.
 
 */
class GameMaster {
private:
    int racersCount;
    std::thread gameMasterThread;
    static std::mutex queueMutex;
    static std::condition_variable queueCondVar;
    static std::queue<int> diceRollsQueue;
    static bool raceFinished;
    static std::vector<std::pair<int, std::thread::id>> finishOrder; // Pair of finish time and racer ID
    static int finishCounter;
    mutable std::mutex finishMutex;

public:
    /**
      @brief Constructor for GameMaster class.
      @param racers Number of racers in the race.
     */
    GameMaster(int racers);

    /**
      @brief Starts the game master thread.
     */
    void start();

    /**
      @brief Joins the game master thread.
     */
    void join();

    /**
      @brief The function run by the game master thread to manage the race.
      @param racers Number of racers in the race.
     */
    static void gameMasterThreadFunction(int racers);

    /**
      @brief Retrieves the next dice roll for a racer.
      @return int The value of the dice roll.
     */
    static int getDiceRoll();

    /**
      @brief Notifies the master that a racer has finished.
      @param threadID The thread ID of the racer that finished.
     */
    void notifyFinish(std::thread::id threadID);

    /**
      @brief Prints the results of the race.
     */
    void printResults() const;
};

#endif
