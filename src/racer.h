/**
 @file
 @author Kavin Parakh <kkp56@drexel.edu>
 @date 11/05/2023
 @section Description
*/

#ifndef RACER_H
#define RACER_H

#include "gamemaster.h"
#include <thread>

/**
  @class Racer
  @brief Represents a participant in the race.
 
  Each racer runs in a separate thread, advancing in the race based on dice rolls
  provided by the GameMaster.
 */
class Racer {
    int id;
    int distance;
    std::thread racerThread;
    GameMaster& gameMaster;

public:

    /**
      @brief Constructs a new Racer object.
      @param id The identifier for the racer.
      @param gameMaster Reference to the GameMaster to interact with race logic.
     */
    Racer(int id, GameMaster& gameMaster);

    /**
      @brief Starts the racer thread.
     */
    void start();

    /**
      @brief Joins the racer thread, ensuring it has finished before continuing.
     */
    void join();

    /**
      @brief The racer's thread function, it races until the end is reached.
     */
    void run();

    /**
      @brief Retrieves the racer's current distance in the race.
      @return int The current distance the racer has covered.
     */
    int getDistance() const;

    /**
      @brief Retrieves the racer's ID.
      @return int The ID of the racer.
     */

    int getID() const;
};

#endif
