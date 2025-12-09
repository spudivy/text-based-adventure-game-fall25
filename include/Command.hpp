#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

#include <string>
#include <vector>

//forward commit so buildTests works
class Player;
class GameEnvironment;

/**
 * @class Command Command.hpp "Command.hpp"
 * @brief Interface that holds the player's movements.
 */
class Command {
 public:
 /**
  * @brief Constructor.
  * @param [in] p Reference to the player object.
  * @param [in] env Reference to the game environment.
  */
  Command(Player* p, GameEnvironment* env);

 /**
  * @brief Destructor.
  */
  ~Command();

 /**
  * @brief Reads and executes a command entered by the player.
  * @param [in] input The command input (e.g. "move north").
  */
  void executeCommand(const std::string& input);

 /**
  * @brief Helper function to move the player.
  * @param [in] input The command input.
  */
  void moveCommand(const std::string& input);

 /**
  * @brief Helper function to view the player's inventory.
  * @param [in] input The command input.
  */
  void inventoryCommand(const std::string& input);

 /**
  * @brief Helper function to view what's in a room.
  */
  void inspectCommand();

 /**
  * @brief Helper function for the player to grab an item.
  * @param [in] input The command input.
  */
  void grabCommand(const std::string& input);

 /**
  * @brief Helper function for the player to use an item.
  * @param [in] input The command input.
  */
  void useCommand(const std::string& input);

 /**
  * @brief Helper function for the player to talk to an NPC.
  * @param [in] input The command input.
  */
  void talkCommand(const std::string& input);

 /**
  * @brief Helper function for the player to solve a puzzle.
  */  
  void solveCommand();

 /**
  * @brief Helper function for the player to access the help menu.
  */
  void helpCommand();

 /**
  * @brief Helper function for the player to look in a room.
  */
  void lookCommand();

 /**
  * @brief Function that allows the player to move.
  * @param [in] direction Direction the player wants to move in.
  */
  void movePlayer(const std::string& direction);

 /**
  * @brief Changes the game's phase.
  * @param [in] env Pointer to a new phase.
  */
  void setEnvironment(GameEnvironment* env);

 /**
  * @brief Gets the environment that the player is in.
  * @return A pointer to the environment the player resides in.
  */
  GameEnvironment* getEnvironment() const;

 /**
  * @brief Function to quit the game and automatically lose.
  */
  void quitGame();

 /**
  * @brief Prints out the description of the whole game.
  */
  void gameDescription();

 private:
  Player* player;
  GameEnvironment* gameEnv;

 /**
  * @brief Parses the input command into individual words.
  * @param [in] input The command input string.
  * @return A vector of words from the command.
  */
  std::vector<std::string> parseInput(const std::string& input) const;

 /**
  * @brief Converts all text to lowercase.
  * @param [in] input The input to be changed.
  * @return The input string in lowercase.
  */
  std::string toLowerCase(const std::string& input) const;
};

#endif //COMMAND_H_INCLUDED
