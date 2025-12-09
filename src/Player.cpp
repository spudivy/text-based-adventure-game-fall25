#include <string>
#include <vector>
#include <iostream>

#include "Player.hpp"
#include "Item.hpp"
#include "Exceptions.hpp"
#include "HelpMenu.hpp"
#include "NPC.hpp"
#include "Command.hpp"

Player::Player() {
    this->playerName = "";
    this->currentRoom = 0;
}

Player::Player(std::string name) {
    this->playerName = name;
    this->currentRoom = 0;
}

Player::~Player() {}

std::string Player::enterName() {
    std::string n;
    std::cout << "What is your name?\n> ";
    getline(std::cin, n);
    return n;
}

void Player::setName(const std::string& name) {
    this->playerName = name;
}

std::string Player::getName() {
    return playerName;
}

void Player::setCurrentRoom(int newRoom) {
    currentRoom = newRoom;
}

int Player::getCurrentRoom() {
    return currentRoom;
}

int Player::getCurrentPhase() {
    return currentPhase;
}

void Player::initializeInventory(const Item& item) {
    inventory.clear();
    inventory.push_back(item);
}

void Player::addToInventory(const Item& item) {
    inventory.push_back(item);
    std::cout << item.getItemName() << " has been added to your inventory.\n";
}

void Player::removeFromInventory(const std::string& item) {
    for (unsigned i = 0; i < inventory.size(); ++i) {
        if (inventory[i].getItemName() == item) {
            inventory.erase(inventory.begin() + i);
            std::cout << item << " has been removed from your inventory.\n";
            return;
        }
    }
}

void Player::displayInventory() const {
    if (inventory.empty()) {
        std::cout << "Nothing in your inventory.\n";
        return;
    }

    std::cout << "Inventory:\n";
    for (unsigned i = 0; i < inventory.size(); ++i) {
        std::cout << "- " << inventory[i].getItemName() << ": "
                    << inventory[i].getItemDescription() << "\n";
    }
}

bool Player::hasItem(const std::string& itemName) const {
    for (unsigned i = 0; i < inventory.size(); ++i) {
        if (inventory[i].getItemName() == itemName) {
            return true;
        }
    }
    return false;
}

Item* Player::getItem(const std::string& itemName) {
        for (unsigned i = 0; i < inventory.size(); ++i) {
            if (inventory[i].getItemName() == itemName) {
                return &inventory[i];
            }
        }
    return nullptr;
}

