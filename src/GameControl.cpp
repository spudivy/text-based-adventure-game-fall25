#include <string>
#include <iostream>

#include "GameControl.hpp"

GameControl::GameControl()
            : player(""),
              cmd(&player, &phase1),
              phase1(),
              phase2(),
              phase3(),
              phase4() {}

GameControl::~GameControl() {}

void GameControl::getName() {
    std::string playerName = player.enterName();
    player.setName(playerName);
}

void GameControl::initialize() {
    getName();
    cmd.gameDescription();
    std::cout << "\nType 'help' for more commands.\n";
    std::cout << std::endl;
    cmd.getEnvironment()->printDescription(player.getCurrentRoom());
    std::cout << "\nWhat would you like to do?" << std::endl << "> ";
}

void GameControl::transition() {
    std::string victoryMessage =
        cmd.getEnvironment()->victoryCondition(player.getCurrentRoom());

    if (!victoryMessage.empty()) {
        if (cmd.getEnvironment() == &phase1) {
            cmd.setEnvironment(&phase2);
            player.setCurrentRoom(phase2.getStartingRoom());
            cmd.getEnvironment()->printDescription(player.getCurrentRoom());
        } else if (cmd.getEnvironment() == &phase2) {
            cmd.setEnvironment(&phase3);
            player.setCurrentRoom(phase3.getStartingRoom());
            cmd.getEnvironment()->printDescription(player.getCurrentRoom());
        } else if (cmd.getEnvironment() == &phase3) {
            cmd.setEnvironment(&phase4);
            player.setCurrentRoom(phase4.getStartingRoom());
            cmd.getEnvironment()->printDescription(player.getCurrentRoom());
        } else {
            std::cout << "Game Over!\n";
            cmd.quitGame();
        }
    }
}

void GameControl::run() {
    std::string line = "";
    while (line != "end" && line != "quit" && line != "exit") {
        std::getline(std::cin, line);
        if (!line.empty())
            cmd.executeCommand(line);
        transition();
        std::cout << "\n> ";
    }
}

void GameControl::start() {
    initialize();
    run();
}
