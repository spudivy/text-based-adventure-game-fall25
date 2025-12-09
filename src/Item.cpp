#include <string>
#include <iostream>

#include "Item.hpp"
#include "Player.hpp"
#include "NPC.hpp"
#include "GameEnvironment.hpp"

Item::Item() {
    this->itemName = "";
    this->itemDescription = "";
}

Item::Item(std::string name, std::string description) {
    this->itemName = name;
    this->itemDescription = description;
}

Item::~Item() {}

std::string Item::getItemName() const {
    return itemName;
}

std::string Item::getItemDescription() const {
    return itemDescription;
}
