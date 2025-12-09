#include "Command.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

#include "GameEnvironment.hpp"
#include "NPC.hpp"
#include "Player.hpp"
#include "HelpMenu.hpp"

Command::Command(Player* p, GameEnvironment* env) : player(p), gameEnv(env) {}

Command::~Command() {}

std::vector<std::string> Command::parseInput(const std::string& input) const {
  std::stringstream ss(input);
  std::string word;
  std::vector<std::string> parsedInput;

  while (ss >> word) {
    parsedInput.push_back(toLowerCase(word));
  }

  return parsedInput;
}

std::string Command::toLowerCase(const std::string& input) const {
  std::string lower = input;
  for (unsigned i = 0; i < lower.length(); ++i) {
    lower[i] = std::tolower(static_cast<unsigned char>(lower[i]));
  }
  return lower;
}

void Command::executeCommand(const std::string& input) {
  auto parsedInput = parseInput(input);
  if (parsedInput.empty()) return;
  std::string action = parsedInput[0];

  if (action == "move" || action == "yes" || action == "no")
    moveCommand(input);
  else if (action == "inspect")
    inspectCommand();
  else if (action == "inventory")
    inventoryCommand(input);
  else if (action == "grab")
    grabCommand(input);
  else if (action == "use")
    useCommand(input);
  else if (action == "talk")
    talkCommand(input);
  else if (action == "solve" || action == "fight")
    solveCommand();
  else if (action == "help")
    helpCommand();
  else if (action == "look")
    lookCommand();
  else if (action == "end" || action == "quit" || action == "exit")
    quitGame();
  else
    std::cout << "Please enter a valid command.\n";
}

void Command::moveCommand(const std::string& input) {
  auto parsedInput = parseInput(input);
  if (parsedInput.empty()) return;
  if (input == "yes" || input == "no") {
    movePlayer(parsedInput[0]);
    return;
  } else if (parsedInput.size() <= 1) {
    std::cout << "Must include a direction to move.\n";
    return;
  }
  std::string direction  = "";
  for (int i = 1; i < parsedInput.size(); i++) {
    direction += parsedInput[i];
    if (i != (parsedInput.size()-1))
      direction += " ";
  }
  movePlayer(direction);
}

void Command::inventoryCommand(const std::string& input) {
  auto parsedInput = parseInput(input);
  if (parsedInput.empty()) return;
  if (parsedInput.size() > 1) {
    std::cout << "\nToo many inputs for inventory command.\n";
    return;
  }
  player->displayInventory();
}

void Command::inspectCommand() {
  int currentRoom = player->getCurrentRoom();
  gameEnv->inspectRoom(currentRoom);
}

void Command::grabCommand(const std::string& input) {
  auto parsedInput = parseInput(input);
  if (parsedInput.empty()) return;
  if (parsedInput.size() <= 1) {
    std::cout << "Select an item to pick up.\n";
    return;
  }

  std::string itemName = "";
  for (int i = 1; i < parsedInput.size(); i++) {
    itemName += parsedInput[i];
    if (i != (parsedInput.size()-1))
      itemName += " ";
  }

  int currentRoom = player->getCurrentRoom();
  Item* roomItem = gameEnv->getItem(currentRoom, itemName);
  if (roomItem != nullptr) {
    player->addToInventory(*roomItem);
    gameEnv->removeItem(currentRoom, itemName);
  } else {
    std::cout << "There is no " << itemName << " in this room.\n";
  }
}

void Command::useCommand(const std::string& input) {
  auto parsedInput = parseInput(input);
  if (parsedInput.empty()) return;
  if (parsedInput.size() <= 1) {
    std::cout << "\nSpecify item to use.\n";
    return;
  }

  std::string itemName = "";
  for (int i = 1; i < parsedInput.size(); i++) {
    itemName += parsedInput[i];
    if (i != (parsedInput.size()-1))
      itemName += " ";
  }

  int currentRoom = player->getCurrentRoom();
  Item* roomItem = player->getItem(itemName);
  if (roomItem != nullptr) {
    gameEnv->useItem(currentRoom, itemName);
  } else {
    std::cout << "\nYou do not have a " << itemName
              << " in your inventory.\n";
  }
}

void Command::talkCommand(const std::string& input) {
  auto parsedInput = parseInput(input);
  if (parsedInput.empty()) return;
  if (parsedInput.size() <= 1) {
    std::cout << "\nTalk to who?\n";
    return;
  }

  std::string NPCName = "";
  for (int i = 2; i < parsedInput.size(); i++) {
    NPCName += parsedInput[i];
    if (i != (parsedInput.size()-1))
      NPCName += " ";
  }

  int currentRoom = player->getCurrentRoom();
  NPC* npc = gameEnv->getNPC(currentRoom, NPCName);
  if (npc != nullptr) {
    std::cout << (npc->getNPCDialogue()) << "\n";
    npc->setNPCDialogue(currentRoom);
  } else {
    std::cout << "There is nobody in this room.";
  }
}

void Command::solveCommand() {
  int currentRoom = player->getCurrentRoom();
  Puzzles* p = gameEnv->solvePuzzle(currentRoom);
  if (p != nullptr)
    std::cout << "Door unlocked!\n";
  return;
}

void Command::helpCommand() {
  HelpMenu help;
  help.listCommands();
}

void Command::lookCommand() {
  gameEnv->printDescription(player->getCurrentRoom());
}

void Command::movePlayer(const std::string& direction) {
  if (player == nullptr || gameEnv == nullptr) {
    std::cout << "Game not properly initialized.\n";
    return;
  }

  int currentRoom = player->getCurrentRoom();
  int nextRoom = gameEnv->getNextRoom(currentRoom, direction);

  if (nextRoom == -1) {
    std::cout << "You can't go that way.\n";
    return;
  }

  //updates player position
  player->setCurrentRoom(nextRoom);

  //prints new room description
  gameEnv->printDescription(nextRoom);

  //check victory condition for this phase
  std::string vc = gameEnv->victoryCondition(nextRoom);
  if (!vc.empty()) {
    std::cout << vc << "\n";
  } else if (gameEnv->loseCondition(nextRoom)) {
    std::cout << "You died!!!!!\n";
    quitGame();
  }
}

void Command::setEnvironment(GameEnvironment* env) { gameEnv = env; }

GameEnvironment* Command::getEnvironment() const {
  return gameEnv;
}

void Command::quitGame() {
  std::exit(0);
}

void Command::gameDescription() {
  std::cout
      << "\nCongrats on beating The Spicy Pepper Eating Contest "
      << player->getName()
      << ", you managed to eat the spiciest pepper on earth! "
      << "Here is you first place ribbo... OH MY GOD is that S'tan?\n";
}
