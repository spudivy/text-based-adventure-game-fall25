#include <string>
#include <vector>
#include <iostream>

#include "Item.hpp"
#include "Exceptions.hpp"
#include "Player.hpp"
#include "NPC.hpp"
#include "GameEnvironment.hpp"

NPC::NPC() : NPCName(""), dialogue(), index(0) {}


NPC::NPC(std::string name, std::vector<std::string> dial)
  : NPCName(name), dialogue(dial), index(0) {}


NPC::~NPC() {}

std::string NPC::getNPCName() const {
    return NPCName;
}

std::string NPC::getNPCDialogue() const {
    return dialogue[index];
}

void NPC::setNPCDialogue(int roomID) {
  if (index != dialogue.size() - 1) {
    index += 1;
  } else {
    index = 0;
  }
}
