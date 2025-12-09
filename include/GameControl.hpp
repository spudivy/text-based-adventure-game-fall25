#ifndef GAMECONTROL_H_INCLUDED
#define GAMECONTROL_H_INCLUDED

#include <string>
#include <iostream>

#include "Player.hpp"
#include "GameEnvironment.hpp"
#include "Command.hpp"

/**
 * @class GameControl GameControl.hpp "GameControl.hpp"
 * @brief Interface that controls how the game is run.
 */
class GameControl {
 public:
  /**
  * @brief Default Constructor.
  */
  GameControl();

 /**
  * @brief Destructor.
  */
  ~GameControl();

 /**
  * @brief Function that runs the game loop.
  * @details Uses initialize() and transition().
  */
  void start();

 private:
  Player player;
  Command cmd;
  PhaseOne phase1;
  PhaseTwo phase2;
  PhaseThree phase3;
  PhaseFour phase4;

 /**
  * @brief Gets the name of the player.
  */
  void getName();

 /**
  * @brief Sets up the game.
  * @details Utilizes getName().
  */
  void initialize();

 /**
  * @brief Handles the transitioning of phases.
  */
  void transition();

 /**
  * @brief Controls how the game input works.
  * @details Utilizes transition().
  */
  void run();
};


#endif //GAMECONTROL_H_INCLUDED
