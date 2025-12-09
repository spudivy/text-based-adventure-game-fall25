#include "GameEnvironment.hpp"

#include <iostream>
#include <algorithm>
#include <limits>
#include <cstdlib>

#include "Item.hpp"
#include "Player.hpp"
#include "NPC.hpp"
#include "Puzzles.hpp"

GameEnvironment::GameEnvironment() : startRoom(0) {}

void GameEnvironment::printDescription(int roomID) const {
  if (!isValidRoom(roomID)) {
    std::cout << "Invalid room.\n";
    return;
  }

  std::cout << rooms[roomID].description << "\n";
}

int GameEnvironment::getStartingRoom() const {
  return startRoom;
}

bool GameEnvironment::isValidRoom(int id) const {
  return (id >= 0 && id < static_cast<int>(rooms.size()));
}

int GameEnvironment::getNextRoom(int currentRoom,
                      const std::string& direction) const {
  if (!isValidRoom(currentRoom))
    return -1;

  auto it = rooms[currentRoom].exits.find(direction);
  if (it != rooms[currentRoom].exits.end()) {
    const Exit& exit = it->second;
    if (exit.isLocked) {
      if (!rooms[currentRoom].puzzle.getPuzzleType().empty()) {
        std::cout << "Door is puzzle locked.\n";
        return -1;
      } else {
        std::cout << "Door is locked.\n";
        return -1;
      }
    }
    return exit.roomID;
  }
  return -1;
}

void GameEnvironment::inspectRoom(int roomID) const {
  if (isValidRoom(roomID)) {
      if (!rooms[roomID].item.getItemName().empty()) {
        std::cout << "There is a "
                  << rooms[roomID].item.getItemName() << " in this room.\n";
      } else {
        std::cout << "There are no items in this room.\n";
      }
      if (!rooms[roomID].npc.getNPCName().empty()) {
        std::cout << "Someone named "
                  << rooms[roomID].npc.getNPCName() << " is in this room.\n";
      } else {
        std::cout << "There are no NPCs in this room.\n";
      }
  }
}

void GameEnvironment::removeItem(int roomID, const std::string& itemName) {
  if (isValidRoom(roomID)) {
    if (!rooms[roomID].item.getItemName().empty()
        && rooms[roomID].item.getItemName() == itemName) {
      std::cout << rooms[roomID].item.getItemName() << " grabbed.\n";
      rooms[roomID].item = Item("", "");
    } else {
        std::cout << "There are no items to pick up." << std::endl;
    }
  }
}

Item* GameEnvironment::getItem(int roomID, const std::string& itemName) {
  if (isValidRoom(roomID)) {
    if (!rooms[roomID].item.getItemName().empty()
        && rooms[roomID].item.getItemName() == itemName)
      return &rooms[roomID].item;
  }
  return nullptr;
}

Item* GameEnvironment::useItem(int roomID, const std::string& itemName) {
  if (isValidRoom(roomID)) {
    for (auto& exit : rooms[roomID].exits) {
      Exit& currentExit = exit.second;
      if (currentExit.isLocked && itemName == currentExit.requiredItem) {
        std::cout << "You used the " << itemName << ".\nDoor unlocked!\n";
        currentExit.isLocked = false;
        break;
      }
    }
  }
  return nullptr;
}

NPC* GameEnvironment::getNPC(int roomID, const std::string& NPCName) {
  if (isValidRoom(roomID)) {
    if (!rooms[roomID].npc.getNPCName().empty()
        && rooms[roomID].npc.getNPCName() == NPCName)
      return &rooms[roomID].npc;
  }
  return nullptr;
}

Puzzles* GameEnvironment::solvePuzzle(int roomID) {
  if (isValidRoom(roomID)) {
    for (auto& exit : rooms[roomID].exits) {
        Exit& currentExit = exit.second;
        int nextRoomID = currentExit.roomID;
        std::string type = rooms[roomID].puzzle.getPuzzleType();
        if (currentExit.isLocked && type == "riddle") {
          if (rooms[roomID].puzzle.riddlePuzzle()) {
            currentExit.isLocked = false;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return &rooms[nextRoomID].puzzle;
          } else {
            return nullptr;
          }
        }
        if (currentExit.isLocked && type == "anagram") {
          if (rooms[roomID].puzzle.anagramPuzzle()) {
            currentExit.isLocked = false;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return &rooms[nextRoomID].puzzle;
          } else {
            return nullptr;
          }
        }
        if (currentExit.isLocked && type == "chess") {
          if (rooms[roomID].puzzle.chessPuzzle()) {
            currentExit.isLocked = false;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return &rooms[nextRoomID].puzzle;
          } else {
            return nullptr;
          }
        }
        if (currentExit.isLocked && type == "RPS") {
          if (rooms[roomID].puzzle.RPS()) {
            currentExit.isLocked = false;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return &rooms[nextRoomID].puzzle;
          } else {
            return nullptr;
          }
        }
      }
  }
  std::cout << "There are no puzzles in this room.\n";
  return nullptr;
}

//------------------------------------------
//Phase One
//------------------------------------------

PhaseOne::PhaseOne() {
  rooms.resize(3);
  startRoom = 0;
  rooms[0].description =
    "S'tan, the ruler of hell just crashed your Contest! "
    "You may want to talk to him.";
  rooms[0].npc = NPC("s'tan", {
                      "So... you're the loser who thinks they can handle "
                      "spicy peppers huh? " "Well I hate to break it to "
                      "you but theres someone you haven't beat yet "
                      "and that person is ME S'tan, ruler of Hell "
                      "and I challenge you to try my spiciest pepper, "
                      "whaddya say, yes or no?"});
  rooms[0].exits["yes"] = {2};
  rooms[0].exits["no"] = {1};

  rooms[1].description =
    "You walk away while the shame slowly eats at your soul.";

  rooms[2].description =
    "The pepper burns your throat, it's so hot that your "
    "breath catches fire and in panic you accidentally burn your mother!";
}

std::string PhaseOne::victoryCondition(int roomID) {
  if (roomID == 2)
    return "Hoho! The weakling has courage... too bad your mother was "
           "in the crossfire BAHAHA! See you never LOSER! \n"
           "A few months after the incident you hear of a certain man "
           "in Port City that could help you get into hell to take "
           "revenge on S'tan, with your mother still "
           "in the hospital, you head out.\n";
  return "";
}

bool PhaseOne::loseCondition(int roomID) {
  if (roomID == 1) {
    std::cout << "Seems the wuss isn't what we "
                 "all thought he was, dissapointing.\n";
    return true;
  }
  return false;
}

//------------------------------------------
//PhaseTwo
//------------------------------------------

PhaseTwo::PhaseTwo() {
  rooms.resize(14);
  startRoom = 0;
  rooms[0].description =
    "You stand in the main square of Port City. "
    "You see a large gate to the west. "
    "To the north there's a dark alleyway "
    "probably teeming with criminals. "
    "To the east is the docks - you see a few cabins nearby.";
  rooms[0].npc = NPC("lost child", {
    "Hello sir have you seen my father? He hasn't come home for days "
    "and I'm really worried about him.",
    "He was a spirit medium... he was talking about a way to "
    "create a portal to hell before he got lost. "
    "If you find him I'm sure he'll help you! ",
    "What are you waiting for? Go save him!"});
  rooms[0].exits["east"] = {1};
  rooms[0].exits["north"] = {3};
  rooms[0].exits["west"] = {5};

  rooms[1].description =
    "You stand on the rickety dock, there's a few shacks nearby. "
    "If you walk any further east, you would fall off the dock. "
    "One shack to the north catches your eye.";
  rooms[1].exits["east"] = {12};
  rooms[1].exits["north"] = {2};
  rooms[1].exits["west"] = {0};

  rooms[12].description =
    "You walked off the docks, dum dum.";

  rooms[2].description =
    "This cabin seems to have belonged to some spirit medium. "
    "In the corner you see a crystal. For some reason "
    "you want to move to the crystal";
  rooms[2].item = Item("rusty key",
                       "A small rusty key");
  rooms[2].exits["to crystal"] = {13};
  rooms[2].exits["south"] = {1};

  rooms[13].description =
    "The crystal doesn't do anything, and yet, "
    "you feel like you can see something take shape "
    "it makes you uncomfortable, you want to move back";
  rooms[13].exits["back"] = {2};

  rooms[3].description =
    "You move forward into the alley way, there's a couple criminals around "
    "as well as a dumpster further north, looks like you'll need a key though.";
  rooms[3].npc = NPC("lanky lee", {
    "I would rob you! Too bad I'm lanky!",
    "I was so lanky I threw out my trading pass!"});
  rooms[3].exits["north"] = {4, true, "rusty key"};
  rooms[3].exits["south"] = {0};

  rooms[4].description =
    "A putrid smell emanates from the dumpster";
  rooms[4].item = Item("trading pass",
                       "A trading pass covered in garbage, probably useable.");
  rooms[4].exits["south"] = {0};

  rooms[5].description =
    "Going west, you approach a towering city wall, "
    "with a man guarding the gate";
  rooms[5].npc = NPC("ivan", {
    "You'll need a trading pass to get through.",
    "Man... I could go for a donut."});
  rooms[5].exits["east"] = {0};
  rooms[5].exits["west"] = {6, true, "trading pass"};

  rooms[6].description =
    "Inside the city gate is a vast street market. "
    "There's plenty of stalls for any kind of business. ";
  rooms[6].npc = NPC("shady merchant", {
    "I know what you seek... head north and you shall find it there.",
    "Leave me, I have business to attend to.",
    "Buzz off!"});
  rooms[6].exits["east"] = {5};
  rooms[6].exits["north"] = {7};

  rooms[7].description =
    "Entering the underground market you are met with winding paths "
    "and unsavory company.";
  rooms[7].npc = NPC("shady slim", {
    "You know Lanky? He's my cousin. If you tight with him you aight with me",
    "Just move to the bookshelf and you'll find what you want."});
  rooms[7].exits["to bookshelf"] = {10};
  rooms[7].exits["north"] = {8};
  rooms[7].exits["east"] = {9};

  rooms[8].description =
    "It's just an empty storage room";
  rooms[8].item = Item("family portrait",
    "A picture of a father and son, he seems familiar...");
  rooms[8].exits["south"] = {7};

  rooms[9].description =
    "The smell of death is strong in this room, yet it appears empty.";
  rooms[9].npc = NPC("blood butcher", {
    "I don't know why the guys all call me that, I'm just the chef.",
    "Are you supposed to be in here?"});
  rooms[9].exits["west"] = {7};

  rooms[10].description =
    "Walking to the bookshelf you find a secret passage! "
    "Inside is a man as well as some sophisticated calculations "
    "on the wall.";
  rooms[10].npc = NPC("spirit medium", {
    "I've been waiting for you! The spirits said you would arrive "
    "so I found a safe space away from my son in order to create "
    "this portal for you.",
    "Just move to the portal and you'll wind up in hell! "
    "As long as you can solve my riddle that is"});
  rooms[10].puzzle = Puzzles("riddle");
  rooms[10].exits["to portal"] = {11, true};

  rooms[11].description =
    "The portal sucks you in! You can't stand the pressure "
    "and you black out.";
}

std::string PhaseTwo::victoryCondition(int roomID) {
  if (roomID == 11) {
    return "The smell of death and decay wakes you up.";
  }
  return "";
}

bool PhaseTwo::loseCondition(int roomID) {
  if (roomID == 12)
    return true;
  return false;
}

//------------------------------------------
//PhaseThree
//------------------------------------------

PhaseThree::PhaseThree() {
  rooms.resize(15);
  startRoom = 0;

  rooms[0].description =
    "You stand high atop the mountain peak, you hear "
    "the screams of your fellow man all around you. "
    "the only path down is west.";
  rooms[0].exits["west"] = {1};

  rooms[1].description =
    "Descending the mountain a bit, you come to a halt, "
    "the only way down is to fall off the cliff to the west. "
    "there doesn't seem like a way back. ";
  rooms[1].npc = NPC("sinner", {
    "A new arrival huh? I've been here too long now, "
    "terrified of heights you see...",
    "There's a small passage up north with a great view if you're "
    "scared too.",
    "might as well jump, you're already dead."});
  rooms[1].exits["north"] = {2};
  rooms[1].exits["west"] = {3};

  rooms[2].description =
    "Sneaking through a crack in the wall takes you to a small ledge. "
    "There's a beautiful view of S'tan's palace in the distance.";
  rooms[2].item = Item("crumpled note",
    "A small note, all you can read is: 'move beyond in the royal chamber...'");
  rooms[2].exits["south"] = {1};

  rooms[3].description =
    "You fall for about 30 seconds before "
    "landing with suprisingly little pain. "
    "The only path out is south.";
  rooms[3].exits["south"] = {4};

  rooms[4].description =
    "You approach a clearing, in the distance is a small town.";
  rooms[4].npc = NPC("bone daddy", {
    "How'd you keep your skin... whatever, "
    "keep going south and you'll reach my town. "
    "Don't go in the well without a way out though HARHARHAR!"});
  rooms[4].exits["south"] = {5};
  rooms[4].exits["north"] = {3};

  rooms[5].description =
    "A big sign 'Bone Zone' greets you at the entrance of town. "
    "There's a store to the north a path to the east, "
    "and a well in the town center. "
    "Do skeletons need to drink?";
  rooms[5].npc = NPC("bone boy", {
    "Did you see my dad on the way down?! He likes taking hikes "
    "to meet all the new dead people!",
    "I like going east to the crypt, but I can never get past "
    "that door...",
    "Later loser! Don't get stuck in the well!"});
  rooms[5].exits["to well"] = {8};
  rooms[5].exits["north"] = {6};
  rooms[5].exits["east"] = {9};

  rooms[6].description =
    "A skeleton store with your basic essentials, "
    "Bone Polish, Sphaghetti, Bone Broth, Calcium Supplements. "
    "You see a sign for a deep tissue massage, it's dusty.";
  rooms[6].npc = NPC("bone sally", {
    "If you're here for the massage just move to the back, "
    "you'll have to figure out the password, "
    "but we've got nothing else for your kind.",
    "Buy something or leave."});
  rooms[6].item = Item("bone polish",
    "This doesn't seem like it'll be useful...");
  rooms[6].puzzle = Puzzles("anagram");
  rooms[6].exits["to back"] = {7, true};
  rooms[6].exits["south"] = {5};

  rooms[7].description =
    "A massage parlour that hasn't been used in ages. "
    "It seems to have been converted to a storage room. "
    "Move back to leave.";
  rooms[7].item = Item("rope",
    "This could get you out of a tight spot.");
  rooms[7].exits["back"] = {6};

  rooms[8].description =
    "You've entered the well, hopefully you have a way to move up.";
  rooms[8].item = Item("crypt key",
    "A key in the shape of a skeleton");
  rooms[8].exits["up"] = {5, true, "rope"};

  rooms[9].description =
    "You stand at a cross road, to the north is a spooky crypt, "
    "with a keyhole in the shape of a skull. "
    "To the east is S'tans castle, the path is "
    "blocked by an ornate gate";
  rooms[9].exits["north"] = {10, true, "crypt key"};
  rooms[9].exits["east"] = {14, true, "gilded key"};
  rooms[9].exits["west"] = {5};

  rooms[10].description =
    "The crypt is dark and damp, skeletons line the wall. "
    "To the north is a door with a puzzle lock. "
    "To the west you spot a room full of riches! Who left this unlocked!?";
  rooms[10].puzzle = Puzzles("chess");
  rooms[10].exits["west"] = {11};
  rooms[10].exits["south"] = {9};
  rooms[10].exits["north"] = {12, true};

  rooms[11].description =
    "Of course it was a trap, this treasure would have "
    "been long gone by now.";

  rooms[12].description =
    "A grand chapel is before you, beautiful skullptures are all around. "
    "In the center is a gilded key. "
    "The door locks behind you.";
  rooms[12].item = Item("gilded key",
    "A beautifully crafted key made of gold.");
  rooms[12].npc = NPC("skullpture", {
    "You've been trapped by your greed, youll never escape from here!",
    "Ahhhh I'm just playing, go east to the exit."});
  rooms[12].exits["east"] = {9};
  rooms[12].exits["beyond"] = {13};

  rooms[13].description =
    "you've moved beyond reality, you feel like moving back any second.";
  rooms[13].item = Item("spectral key",
    "This key is beyond reality, someone must not want it used...");
  rooms[13].exits["back"] = {12};

  rooms[14].description =
    "You've finally made it into S'tans Castle!";
}


std::string PhaseThree::victoryCondition(int roomID) {
  if (roomID == 14) {
    return "You can't wait to get your revenge!";
  }
  return "";
}

bool PhaseThree::loseCondition(int roomID) {
  if (roomID == 11)
    return true;
  return false;
}

//------------------------------------------
//PhaseFour
//------------------------------------------

PhaseFour::PhaseFour() {
  rooms.resize(8);
  startRoom = 0;

  rooms[0].description =
    "You stand in the grand hallway of S'tans castle. "
    "He must be compensating for something. "
    "You have to move forward.";
  rooms[0].puzzle = Puzzles("riddle");
  rooms[0].exits["forward"] = {1, true};

  rooms[1].description =
    "You can sense his fear. "
    "You have to move forward.";
  rooms[1].puzzle = Puzzles("anagram");
  rooms[1].exits["forward"] = {2, true};

  rooms[2].description =
    "Revenge is so close. "
    "Move Forward.";
  rooms[2].puzzle = Puzzles("chess");
  rooms[2].exits["forward"] = {3, true};

  rooms[3].description =
    "You stand before S'tans Grand Chamber."
    "There's a door emmiting a ghostly hue to the west."
    "S'tan is right there. Move Forward";
  rooms[3].exits["forward"] = {4};
  rooms[3].exits["west"] = {7, true, "spectral key"};

  rooms[4].description =
    "There he is.";
  rooms[4].npc = NPC("s'tan", {
    "So you actually came? I didn't expect to see you till you croaked! "
    "Since you're here, I'm assuming you're looking for the Cure All Milk! "
    "Well too bad it's all mine. Unless you think you could possibly... "
    "FIGHT for it? \nIt's down south, not that you'll ever win though",
    "Quit wasting my time talking and come at me already!",
    "You scared little man?",
    "Little piss baby can't save his mommy, wah wah!"});
  rooms[4].puzzle = Puzzles("RPS");
  rooms[4].exits["south"] = {5, true};

  rooms[5].description =
    "The Holy Fridge, filled with the legendary Cure All Milk. "
    "There's a portal to earth here too.";
  rooms[5].item = Item("milk",
      "The Legendary Cure All Milk needed to save your mother.");
  rooms[5].exits["to portal"] = {6};

  rooms[6].description = "You head home and cure your mother!";

  rooms[7].description =
    "It seems to be S'tans bedroom, why would he go through "
    "so much trouble to lock it?";
  rooms[7].item = Item("undies",
      "S'tans embarassing undies, adorned with little teddie bears <3");
  rooms[7].npc = NPC("cerberus", {
    "He doesn't want to talk",
    "...",
    "...",
    "...",
    "He let's you pet him once. It's warm."});
  rooms[7].exits["east"] = {3};
}

std::string PhaseFour::victoryCondition(int roomID) {
  if (roomID == 6)
    return "Congratulations you win!";
  return "";
}

bool PhaseFour::loseCondition(int roomID) {
  return false;
}
