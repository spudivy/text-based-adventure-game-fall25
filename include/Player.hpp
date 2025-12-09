#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <string>
#include <vector>

#include "Item.hpp"
#include "HelpMenu.hpp"
#include "NPC.hpp"
#include "Command.hpp"

/**
 * @class Player Player.hpp "Player.hpp"
 * @brief Interface that creates a player.
 */
class Player {
 public:
 /**
  * @brief Default Constructor.
  * @details Sets the name and the current room number.
  */
  Player();

 /**
  * @brief Player Constructor.
  * @param [in] name The name of the player.
  */
  Player(std::string name);

 /**
  * @brief Destructor.
  */
  ~Player();

 /**
  * @brief Prompts user to enter Name.
  */
  std::string enterName();

 /**
  * @brief Sets the name to the input name
  * @param [in] name The name of the player.
  */
  void setName(const std::string& name);

 /**
  * @brief Gets the name of the player.
  * @return The player's name.
  */
  std::string getName();

 /**
  * @brief Sets the value of the new room.
  * @param [in] newRoom The room the player has moved to.
  */ 
  void setCurrentRoom(int newRoom);

 /**
  * @brief Gets the current position of the player.
  * @return Player's current position.
  */
  int getCurrentRoom();

 /**
  * @brief Gets the current position of the player.
  * @return Player's current position.
  */
  int getCurrentPhase();

 /**
  * @brief Creates an invetory for the player.
  * @param [in] item Pointer to items that the player can pick up.
  */
  void initializeInventory(const Item& item);

 /**
  * @brief Adds an item to the player's inventory.
  * @param [in] item The name of the item to add.
  */ 
  void addToInventory(const Item& item);

 /**
  * @brief Removes an item from the player's inventory.
  * @param [in] item The name of the item to remove.
  */ 
  void removeFromInventory(const std::string& item);

 /**
  * @brief Displays the player's inventory.
  */ 
  void displayInventory() const;

 /**
  * @brief Checks if a player has a certain item in their inventory.
  * @param [in] itemName The name of the item to check.
  * @return True if the player has the item, false otherwise.
  */ 
  bool hasItem(const std::string& itemName) const;

 /**
  * @brief The player can grab an item from their inventory to use.
  * @param [in] itemName The name of the item to get.
  * @return A pointer to the item.
  */ 
  Item* getItem(const std::string&itemName);

 private:
  int currentRoom;
  int currentPhase = 1;
  std::string playerName;
  std::vector<Item> inventory;
};

#endif // PLAYER_H_INCLUDED
