#ifndef GAMEENVIRONMENT_H_INCLUDED
#define GAMEENVIRONMENT_H_INCLUDED

#include <string>
#include <vector>
#include <map>
#include <utility>

#include "Item.hpp"
#include "NPC.hpp"
#include "Puzzles.hpp"

/**
 * @class GameEnvironment GameEnvironment.hpp "GameEnvironment.hpp"
 * @brief Abstract class representing game phase (level/map).
 */
class GameEnvironment {
 public:
 /**
  * @brief Default Constructor.
  * @details Initializes the game at room 0.
  */
  GameEnvironment();

 /**
  * @brief Destructor.
  */
  virtual ~GameEnvironment() = default;

  std::string getHint(std::string input);

 /**
  * @brief Checks if player has won/lost or if nothing happened.
  * @param [in] roomID ID of the room the player is in.
  * @return Victory string
  */
  virtual std::string victoryCondition(int roomID) = 0;

 /**
  * @brief Checks if player has lost or if nothing happened.
  * @param [in] roomID ID of the room the player is in.
  */
  virtual bool loseCondition(int roomID) = 0;

 /**
  * @brief Struct that creates the exit conditions.
  */
  struct Exit {
    int roomID;
    bool isLocked = false;
    std::string requiredItem = "";
  };

 /**
  * @brief Struct that creates a room, containing the qualities of how it works.
  */
  struct Room {
      std::string description = "NA";
      std::map<std::string, Exit> exits; //exits["north"] = 1
      Item item;
      NPC npc;
      Puzzles puzzle;
  };

 /**
  * @brief Prints description of specified room.
  * @param [in] roomID ID of the room.
  */
  void printDescription(int roomID) const;

 /**
  * @brief Returns the starting room for the phase.
  * @return The index of the starting room.
  */
  int getStartingRoom() const;

 /**
  * @brief Check if a room exists in this phase.
  * @param [in] id ID of the room the player is in.
  * @return True if the room index is valid, false if not.
  */
  bool isValidRoom(int id) const;

 /**
  * @brief Attempts to move from one room to another.
  * @param [in] currentRoom The room the player is currently in.
  * @param [in] direction The direction the player typed.
  * @return ID of the next room.
  */
  int getNextRoom(int currentRoom, const std::string& direction) const;

 /**
  * @brief Inspects rooms for NPCs and Items.
  * @param [in] roomID The room number the player is in.
  */
  void inspectRoom(int roomID) const;

 /**
  * @brief Removes an item from a room.
  * @param [in] roomID The room number the player is in.
  * @param [in] itemName The name of the item being removed.
  */
  void removeItem(int roomID, const std::string& itemName);

 /**
  * @brief Prints the list of items in a room to interact with.
  * @param [in] roomID The room number the player is in.
  */
  Item* getItem(int roomID, const std::string& itemName);

 /**
  * @brief Prints the list of items in a room to interact with.
  * @param [in] roomID The room number the player is in.
  */
  Item* useItem(int roomID, const std::string& itemName);

 /**
  * @brief Gets the NPC that corresponds with the room number.
  * @param [in] roomID The room number the player is in.
  * @param NPCName The name of the NPC to get.
  * @return The NPC that resides in that room.
  */ 
  NPC* getNPC(int roomID, const std::string&NPCName);

 /**
  * @brief Solves any type of puzzle.
  * @param [in] roomID The room number the player is in.
  * @return Address of the room.
  */ 
  Puzzles* solvePuzzle(int roomID);

  Puzzles* getPuzzle(int roomID);

  const std::vector<Room>& getRooms() const { return rooms; }



 protected:
    std::vector<Room> rooms;
    int startRoom = 0;
};

/**
 * @class PhaseOne GameEnvironment.hpp "GameEnvironment.hpp"
 * @brief Interface that creates and initializes phase one.
 */
class PhaseOne : public GameEnvironment {
 public:
 /**
  * @brief Default Constructor.
  * @details Initializes all of the rooms in Phase One.
  */
  PhaseOne();

 /**
  * @brief Destructor.
  */
  ~PhaseOne() override = default;

 /**
  * @brief Alerts the player that they are in the final phase for that room.
  * @param [in] roomID The room number the player is in.
  * @return A string indicated that the player has made it to the final room.
  */
  std::string victoryCondition(int roomID) override;

 /**
  * @brief Checks if the player has lost the game.
  * @details Dependent on phase number the player is in.
  * @param [in] roomID The room number the player is in.
  */
  bool loseCondition(int roomID) override;
};

/**
 * @class PhaseTwo GameEnvironment.hpp "GameEnvironment.hpp"
 * @brief Interface that creates and initializes phase two.
 */
class PhaseTwo : public GameEnvironment {
 public:
 /**
  * @brief Default Constructor.
  * @details Initializes all of the rooms in Phase Two.
  */
  PhaseTwo();

 /**
  * @brief Destructor.
  */
  ~PhaseTwo() override = default;

 /**
  * @brief Alerts the player that they are in the final phase for that room.
  * @param [in] roomID The room number the player is in.
  * @return A string indicated that the player has made it to the final room.
  */
  std::string victoryCondition(int roomID) override;

 /**
  * @brief Checks if the player has lost the game.
  * @details Dependent on phase number the player is in.
  * @param [in] roomID The room number the player is in.
  */
  bool loseCondition(int roomID) override;
};

/**
 * @class PhaseThree GameEnvironment.hpp "GameEnvironment.hpp"
 * @brief Interface that creates and initializes phase three.
 */
class PhaseThree : public GameEnvironment {
 public:
 /**
  * @brief Default Constructor.
  * @details Initializes all of the rooms in Phase Three.
  */
  PhaseThree();

 /**
  * @brief Destructor.
  */
  ~PhaseThree() override = default;

 /**
  * @brief Alerts the player that they are in the final phase for that room.
  * @param [in] roomID The room number the player is in.
  * @return A string indicated that the player has made it to the final room.
  */
  std::string victoryCondition(int roomID) override;

 /**
  * @brief Checks if the player has lost the game.
  * @details Dependent on phase number the player is in.
  * @param [in] roomID The room number the player is in.
  */
  bool loseCondition(int roomID) override;
};

/**
 * @class PhaseFour GameEnvironment.hpp "GameEnvironment.hpp"
 * @brief Interface that creates and initializes phase four.
 */
class PhaseFour : public GameEnvironment {
 public:
 /**
  * @brief Default Constructor.
  * @details Initializes all of the rooms in Phase Four.
  */
  PhaseFour();

 /**
  * @brief Destructor.
  */
  ~PhaseFour() override = default;

 /**
  * @brief Alerts the player that they are in the final phase for that room.
  * @param [in] roomID The room number the player is in.
  * @return A string indicated that the player has made it to the final room.
  */
  std::string victoryCondition(int roomID) override;

 /**
  * @brief Checks if the player has lost the game.
  * @details Dependent on phase number the player is in.
  * @param [in] roomID The room number the player is in.
  */
  bool loseCondition(int roomID) override;
};

#endif //GAMEENVIRONMENT_H_INCLUDED
