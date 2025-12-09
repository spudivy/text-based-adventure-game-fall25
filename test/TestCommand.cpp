#include "Command.hpp"
#include "Player.hpp"
#include "GameEnvironment.hpp"
#include "Exceptions.hpp"
#include "gtest/gtest.h"

TEST(TestCommand, executeCommandCorrect) {
    Player* player = new Player();
    GameEnvironment* env = new PhaseTwo();
    player->setCurrentRoom(env->getStartingRoom());
    Command* cmd = new Command(player, env);

    testing::internal::CaptureStdout();
    cmd->executeCommand("move north");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find(
        "You move forward into the alley way, "
        "there's a couple criminals around "
        "as well as a dumpster further north, "
        "looks like you'll need a key though."), std::string::npos);

    testing::internal::CaptureStdout();
    cmd->executeCommand("inspect");
    std::string output2 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output2, "There are no items in this room."
        "\nSomeone named lanky lee is in this room.\n");


    testing::internal::CaptureStdout();
    cmd->executeCommand("inventory");
    std::string output3 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output3, "Nothing in your inventory.\n");

    player->setCurrentRoom(2);
    testing::internal::CaptureStdout();
    cmd->executeCommand("grab rusty key");
    std::string output5 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output5, "rusty key has been added to your inventory."
        "\nrusty key grabbed.\n");

    player->setCurrentRoom(3);
    testing::internal::CaptureStdout();
    cmd->executeCommand("use rusty key");
    std::string output7 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output7, "You used the rusty key.\nDoor unlocked!\n");

    player->setCurrentRoom(0);
    testing::internal::CaptureStdout();
    cmd->executeCommand("talk to lost child");
    std::string output9 = testing::internal::GetCapturedStdout();
    EXPECT_NE(output9.find(
        "Hello sir have you seen my father? He hasn't come home for days "
        "and I'm really worried about him."), std::string::npos);

    testing::internal::CaptureStdout();
    cmd->executeCommand("solve");
    std::string output11 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output11, "There are no puzzles in this room.\n");

    testing::internal::CaptureStdout();
    cmd->executeCommand("help");
    std::string output12 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output12, "Command List:\n"
                 "- Move: Allows you to move."
                 " Type north/south/east/west to go in a certain direction.\n"
                 "    - [move north/south/east/west]\n"
                 "- Inventory: Take a look at the items in your inventory.\n"
                 "    - [inventory]\n"
                 "- Inspect: Inspect what's in the room.\n"
                 "    - [inspect]\n"
                 "- Grab: Pick up an item and place it in your inventory.\n"
                 "    - [grab (item name)]\n"
                 "- Use: Use an item that you select.\n"
                 "    - [use (item name)]\n"
                 "- Solve: Allows you to solve a riddle.\n"
                 "    - [solve]\n"
                 "- Talk: Communicate with those in the room.\n"
                 "    - [talk to (name)]\n"
                 "- Look: Examine the room you are in.\n"
                 "    - [look]\n"
                 "- Help: Access the help menu.\n"
                 "    - [help]\n"
                 "- Quit/Exit/End: Ends the game.\n"
                 "    - [quit/end/exit]\n");

    player->setCurrentRoom(env->getStartingRoom());
    testing::internal::CaptureStdout();
    cmd->executeCommand("look");
    std::string output13 = testing::internal::GetCapturedStdout();
    EXPECT_NE(output13.find(
        "You stand in the main square of Port City. "
        "You see a large gate to the west. "
        "To the north there's a dark alleyway "
        "probably teeming with criminals. "
        "To the east is the docks - you see a few cabins nearby."),
        std::string::npos);

    delete player;
    delete cmd;
    delete env;
}

TEST(TestCommand, executeCommandIncorrect) {
    Player* player = new Player();
    GameEnvironment* env = new PhaseOne();
    player->setCurrentRoom(env->getStartingRoom());
    Command* cmd = new Command(player, env);

    testing::internal::CaptureStdout();
    cmd->executeCommand("invalid");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Please enter a valid command.\n");
    delete player;
    delete cmd;
    delete env;
}

TEST(TestCommand, moveCommandCorrect) {
    Player* player = new Player();
    GameEnvironment* env = new PhaseTwo();
    player->setCurrentRoom(env->getStartingRoom());
    Command* cmd = new Command(player, env);

    testing::internal::CaptureStdout();
    cmd->moveCommand("move east");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find(
        "You stand on the rickety dock, there's a few shacks nearby. "
        "If you walk any further east, you would fall off the dock. "
        "One shack to the north catches your eye."), std::string::npos);
    delete player;
    delete cmd;
    delete env;
}

TEST(TestCommand, moveCommandIncorrect) {
    Player* player = new Player();
    GameEnvironment* env = new PhaseOne();
    player->setCurrentRoom(env->getStartingRoom());
    Command* cmd = new Command(player, env);

    testing::internal::CaptureStdout();
    cmd->moveCommand("move west");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "You can't go that way.\n");

    testing::internal::CaptureStdout();
    cmd->moveCommand("move");
    std::string output1 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output1, "Must include a direction to move.\n");

    delete player;
    delete cmd;
    delete env;
}

TEST(TestCommand, movePlayerEmptyTest) {
    Player* player = nullptr;
    GameEnvironment* env = nullptr;
    Command* cmd = new Command(player, env);

    testing::internal::CaptureStdout();
    cmd->moveCommand("move north");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Game not properly initialized.\n"),
              std::string::npos);
    delete player;
    delete cmd;
    delete env;
}

TEST(TestCommand, inventoryCommandCorrect) {
    Player* player = new Player();
    GameEnvironment* env = new PhaseOne();
    player->setCurrentRoom(env->getStartingRoom());
    Command* cmd = new Command(player, env);

    testing::internal::CaptureStdout();
    cmd->inventoryCommand("inventory");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Nothing in your inventory.\n");
    delete player;
    delete cmd;
    delete env;
}

TEST(TestCommand, inventoryCommandIncorrect) {
    Player* player = new Player();
    GameEnvironment* env = new PhaseOne();
    player->setCurrentRoom(env->getStartingRoom());
    Command* cmd = new Command(player, env);

    testing::internal::CaptureStdout();
    cmd->inventoryCommand("inventory blabla");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "\nToo many inputs for inventory command.\n");
    delete player;
    delete cmd;
    delete env;
}

TEST(TestCommand, inspectCommandCorrect) {
    Player* player = new Player();
    GameEnvironment* env = new PhaseTwo();
    player->setCurrentRoom(env->getStartingRoom());
    Command* cmd = new Command(player, env);

    testing::internal::CaptureStdout();
    cmd->inspectCommand();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output,
        "There are no items in this room."
        "\nSomeone named lost child is in this room.\n");
    delete player;
    delete cmd;
    delete env;
}

TEST(TestCommand, grabCommandCorrect) {
    Player* player = new Player();
    GameEnvironment* env = new PhaseTwo();
    player->setCurrentRoom(2);
    Command* cmd = new Command(player, env);

    testing::internal::CaptureStdout();
    cmd->grabCommand("grab rusty key");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "rusty key has been added to your inventory."
        "\nrusty key grabbed.\n");

    player->setCurrentRoom(4);
    testing::internal::CaptureStdout();
    cmd->grabCommand("grab trading pass");
    std::string output1 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output1, "trading pass has been added to your inventory."
        "\ntrading pass grabbed.\n");

    delete player;
    delete cmd;
    delete env;
}

TEST(TestCommand, grabCommandIncorrect) {
    Player* player = new Player();
    GameEnvironment* env = new PhaseOne();
    player->setCurrentRoom(env->getStartingRoom());
    Command* cmd = new Command(player, env);

    testing::internal::CaptureStdout();
    cmd->grabCommand("grab banana");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "There is no banana in this room.\n");

    testing::internal::CaptureStdout();
    cmd->grabCommand("grab");
    std::string output1 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output1, "Select an item to pick up.\n");

    delete player;
    delete cmd;
    delete env;
}

TEST(TestCommand, useCommandCorrect) {
    Player* player = new Player();
    GameEnvironment* env = new PhaseTwo();
    player->setCurrentRoom(2);
    Command* cmd = new Command(player, env);

    testing::internal::CaptureStdout();
    cmd->grabCommand("grab rusty key");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "rusty key has been added to your inventory."
        "\nrusty key grabbed.\n");

    player->setCurrentRoom(3);
    testing::internal::CaptureStdout();
    cmd->useCommand("use rusty key");
    std::string output1 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output1, "You used the rusty key.\nDoor unlocked!\n");

    delete player;
    delete cmd;
    delete env;
}

TEST(TestCommand, useCommandIncorrect) {
    Player* player = new Player();
    GameEnvironment* env = new PhaseOne();
    player->setCurrentRoom(env->getStartingRoom());
    Command* cmd = new Command(player, env);

    testing::internal::CaptureStdout();
    cmd->useCommand("use banana");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "\nYou do not have a banana in your inventory.\n");

    testing::internal::CaptureStdout();
    cmd->useCommand("use");
    std::string output1 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output1, "\nSpecify item to use.\n");

    delete player;
    delete cmd;
    delete env;
}

TEST(TestCommand, talkCommandCorrect) {
    Player* player = new Player();
    GameEnvironment* env = new PhaseTwo();
    player->setCurrentRoom(0);
    Command* cmd = new Command(player, env);

    testing::internal::CaptureStdout();
    cmd->talkCommand("talk to lost child");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find(
        "Hello sir have you seen my father? He hasn't come home for days "
        "and I'm really worried about him."), std::string::npos);
    delete player;
    delete cmd;
    delete env;
}

TEST(TestCommand, talkCommandIncorrect) {
    Player* player = new Player();
    GameEnvironment* env = new PhaseOne();
    player->setCurrentRoom(env->getStartingRoom());
    Command* cmd = new Command(player, env);

    testing::internal::CaptureStdout();
    cmd->talkCommand("talk to charlie");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "There is nobody in this room.");

    testing::internal::CaptureStdout();
    cmd->talkCommand("talk");
    std::string output1 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output1, "\nTalk to who?\n");

    delete player;
    delete cmd;
    delete env;
}

TEST(TestCommand, solveCommandCorrect) {
    Player* player = new Player();
    GameEnvironment* env = new PhaseOne();
    player->setCurrentRoom(env->getStartingRoom());
    Command* cmd = new Command(player, env);

    testing::internal::CaptureStdout();
    cmd->solveCommand();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "There are no puzzles in this room.\n");

    delete player;
    delete cmd;
    delete env;
}

TEST(TestCommand, helpCommandCorrect) {
    Player* player = new Player();
    GameEnvironment* env = new PhaseOne();
    player->setCurrentRoom(env->getStartingRoom());
    Command* cmd = new Command(player, env);

    testing::internal::CaptureStdout();
    cmd->helpCommand();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Command List:\n"
                 "- Move: Allows you to move."
                 " Type north/south/east/west to go in a certain direction.\n"
                 "    - [move north/south/east/west]\n"
                 "- Inventory: Take a look at the items in your inventory.\n"
                 "    - [inventory]\n"
                 "- Inspect: Inspect what's in the room.\n"
                 "    - [inspect]\n"
                 "- Grab: Pick up an item and place it in your inventory.\n"
                 "    - [grab (item name)]\n"
                 "- Use: Use an item that you select.\n"
                 "    - [use (item name)]\n"
                 "- Solve: Allows you to solve a riddle.\n"
                 "    - [solve]\n"
                 "- Talk: Communicate with those in the room.\n"
                 "    - [talk to (name)]\n"
                 "- Look: Examine the room you are in.\n"
                 "    - [look]\n"
                 "- Help: Access the help menu.\n"
                 "    - [help]\n"
                 "- Quit/Exit/End: Ends the game.\n"
                 "    - [quit/end/exit]\n");
    delete player;
    delete cmd;
    delete env;
}

TEST(TestCommand, lookCommandCorrect) {
    Player* player = new Player();
    GameEnvironment* env = new PhaseOne();
    player->setCurrentRoom(env->getStartingRoom());
    Command* cmd = new Command(player, env);

    testing::internal::CaptureStdout();
    cmd->lookCommand();
    std::string output13 = testing::internal::GetCapturedStdout();
    EXPECT_NE(output13.find(
        "S'tan, the ruler of hell just crashed your Contest! "
        "You may want to talk to him."), std::string::npos);
    delete player;
    delete cmd;
    delete env;
}

TEST(TestCommand, lookCommandIncorrect) {
    Player* player = new Player();
    GameEnvironment* env = new PhaseOne();
    player->setCurrentRoom(env->getStartingRoom());
    Command* cmd = new Command(player, env);

    testing::internal::CaptureStdout();
    cmd->lookCommand();
    std::string output13 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output13.find(
        "The pepper burns your throat, it's so hot that your "
        "breath catches fire and in panic you accidentally burn"
        "your mother!"), std::string::npos);
    delete player;
    delete cmd;
    delete env;
}

TEST(TestCommand, setEnvironmentTest) {
    GameEnvironment* env1 = new PhaseOne();
    GameEnvironment* env2 = new PhaseTwo();

    Player* player = new Player();
    Command* cmd = new Command(player, env1);

    EXPECT_EQ(cmd->getEnvironment(), env1);

    cmd->setEnvironment(env2);
    EXPECT_EQ(cmd->getEnvironment(), env2);

    delete player;
    delete cmd;
    delete env1;
    delete env2;
}

TEST(TestCommand, gameDescriptionTest) {
    GameEnvironment* env = new PhaseOne();
    Player* player = new Player("bob");
    Command* cmd = new Command(player, env);

    testing::internal::CaptureStdout();
    cmd->gameDescription();

    EXPECT_EQ(player->getName(), "bob");

    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output.find("\nCongrats on beating The Spicy Pepper"
        "Eating Contest bob, you managed to eat the spiciest pepper on earth! "
        "Here is you first place ribbo... OH MY GOD is that S'tan?\n"),
        std::string::npos);

    delete player;
    delete cmd;
    delete env;
}
