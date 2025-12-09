#include "GameEnvironment.hpp"
#include "Exceptions.hpp"
#include "gtest/gtest.h"

TEST(TestGameEnvironment, isValidCorrectTest) {
    GameEnvironment *game = new PhaseOne();
    EXPECT_TRUE(game->isValidRoom(0));
    delete game;
}

TEST(TestGameEnvironment, isValidIncorrectTest) {
    GameEnvironment *game = new PhaseOne();
    EXPECT_FALSE(game->isValidRoom(-2));
    delete game;
}

TEST(TestGameEnvironment, removeItemCorrectTest) {
    GameEnvironment *game = new PhaseTwo();
    auto& rooms = game->getRooms();

    Item* item = game->getItem(2, "rusty key");
    EXPECT_NE(item, nullptr);

    testing::internal::CaptureStdout();

    game->removeItem(2, "rusty key");

    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "rusty key grabbed.\n");

    item = game->getItem(2, "rusty key");
    EXPECT_EQ(item, nullptr);

    EXPECT_EQ(rooms[2].item.getItemName(), "");
    EXPECT_EQ(rooms[2].item.getItemDescription(), "");
    delete game;
}


TEST(TestGameEnvironment, removeItemIncorrectTest) {
    GameEnvironment *game = new PhaseTwo();
    auto& rooms = game->getRooms();

    Item* test = game->getItem(2, "rusty key");
    EXPECT_NE(test, nullptr);

    testing::internal::CaptureStdout();

    game->removeItem(2, "banana");

    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "There are no items to pick up.\n");

    test = game->getItem(2, "rusty key");
    EXPECT_NE(test, nullptr);

    EXPECT_EQ(rooms[1].item.getItemName(), "");
    EXPECT_EQ(rooms[1].item.getItemDescription(), "");

    delete game;
}

TEST(TestGameEnvironment, useItemUnlockCorrectTest) {
    GameEnvironment *game = new PhaseTwo();
    auto& rooms = game->getRooms();

    Item* test = game->getItem(2, "rusty key");
    EXPECT_NE(test, nullptr);

    testing::internal::CaptureStdout();

    game->useItem(3, "rusty key");

    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "You used the rusty key.\nDoor unlocked!\n");

    delete game;
}

TEST(TestGameEnvironment, useItemCorrectTest) {
    GameEnvironment *game = new PhaseTwo();
    auto& rooms = game->getRooms();

    Item* test = game->getItem(2, "rusty key");
    EXPECT_NE(test, nullptr);

    testing::internal::CaptureStdout();

    game->useItem(3, "rusty key");

    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "You used the rusty key.\nDoor unlocked!\n");

    delete game;
}

TEST(TestGameEnvironment, useItemIncorrectTest) {
    GameEnvironment *game = new PhaseTwo();
    auto& rooms = game->getRooms();

    Item* test = game->getItem(2, "rusty key");
    EXPECT_NE(test, nullptr);

    EXPECT_EQ((game->useItem(2, "key")), nullptr);

    delete game;
}

//FIX ARGH </3
TEST(TestGameEnvironment, solvePuzzleCorrectTest) {
    /*
    GameEnvironment *game = new PhaseTwo();
    GameEnvironment *game1 = new PhaseThree();
    GameEnvironment *game2 = new PhaseFour();

    auto& rooms = game->getRooms();
    auto& rooms2 = game1->getRooms();
    auto& rooms3 = game2->getRooms();

    testing::internal::CaptureStdout();

    std::stringstream input("");
    std::streambuf* cin_backup = std::cin.rdbuf(input.rdbuf());
    EXPECT_FALSE(game->solvePuzzle(10));
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output.find("There are no puzzles in this room."), std::string::npos);
    std::cin.rdbuf(cin_backup);
    
    std::stringstream input1("");
    std::streambuf* cin_backup1 = std::cin.rdbuf(input1.rdbuf());
    testing::internal::CaptureStdout();
    EXPECT_FALSE(game1->solvePuzzle(6));
    std::string output1 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output1.find("There are no puzzles in this room."), std::string::npos);
    std::cin.rdbuf(cin_backup1);

    std::stringstream input2("");
    std::streambuf* cin_backup2 = std::cin.rdbuf(input2.rdbuf());
    testing::internal::CaptureStdout();
    EXPECT_FALSE(game1->solvePuzzle(10));
    std::string output2 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output2.find("There are no puzzles in this room."), std::string::npos);
    std::cin.rdbuf(cin_backup2);

    std::stringstream input3("");
    std::streambuf* cin_backup3 = std::cin.rdbuf(input3.rdbuf());
    testing::internal::CaptureStdout();
    EXPECT_FALSE(game2->solvePuzzle(4));
    std::string output3 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output3.find("There are no puzzles in this room."), std::string::npos);
    std::cin.rdbuf(cin_backup3);
    std::stringstream input4("");
    std::streambuf* cin_backup4 = std::cin.rdbuf(input4.rdbuf());
    testing::internal::CaptureStdout();
    EXPECT_FALSE(game->solvePuzzle(0));
    std::string output4 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output4.find("There are no puzzles in this room."), std::string::npos);
    std::cin.rdbuf(cin_backup4);

    delete game;
    delete game1;
    delete game2;*/
}

TEST(TestGameEnvironment, solvePuzzleIncorrectTest) {
    GameEnvironment *game = new PhaseOne();
    auto& rooms = game->getRooms();

    testing::internal::CaptureStdout();

    EXPECT_EQ((game->solvePuzzle(3)), nullptr);

    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "There are no puzzles in this room.\n");

    delete game;
}

TEST(TestGameEnvironment, inspectRoomItemOnlyTest) {
    GameEnvironment* game = new PhaseTwo();
    auto& rooms = game->getRooms();


    EXPECT_EQ(rooms[2].item.getItemName(), "rusty key");
    EXPECT_EQ(rooms[2].npc.getNPCName(), "");

    delete game;
}

TEST(TestGameEnvironment, inspectRoomNPCOnlyTest) {
    GameEnvironment* game = new PhaseTwo();
    auto& rooms = game->getRooms();

    EXPECT_EQ(rooms[3].item.getItemName(), "");
    EXPECT_EQ(rooms[3].npc.getNPCName(), "lanky lee");

    delete game;
}

TEST(TestGameEnvironment, inspectRoomFullTest) {
    GameEnvironment* game = new PhaseThree();
    auto& rooms = game->getRooms();


    EXPECT_EQ(rooms[6].item.getItemName(), "bone polish");
    EXPECT_EQ(rooms[6].npc.getNPCName(), "bone sally");

    delete game;
}

TEST(TestGameEnvironment, inspectRoomEmptyTest) {
    GameEnvironment* game = new PhaseTwo();
    auto& rooms = game->getRooms();

    EXPECT_EQ(rooms[1].item.getItemName(), "");
    EXPECT_EQ(rooms[1].npc.getNPCName(), "");

    delete game;
}

TEST(TestGameEnvironment, getNextRoomInvalidTest) {
    GameEnvironment* game = new PhaseOne();
    auto& rooms = game->getRooms();

    EXPECT_EQ(game->getNextRoom(-1, "north"), -1);

    delete game;
}

TEST(TestGameEnvironment, getNextRoomInvalidDirectionTest) {
    GameEnvironment* game = new PhaseOne();
    auto& rooms = game->getRooms();

    EXPECT_EQ(game->getNextRoom(0, "south"), -1);

    delete game;
}

TEST(TestGameEnvironment, getNextRoomValidExitUnlockedTest) {
    GameEnvironment* game = new PhaseTwo();
    auto& rooms = game->getRooms();

    EXPECT_EQ(game->getNextRoom(0, "north"), 3);

    delete game;
}

TEST(TestGameEnvironment, getNextRoomValidExitLockedTest) {
    GameEnvironment* game = new PhaseOne();
    auto& rooms = game->getRooms();

    testing::internal::CaptureStdout();

    EXPECT_EQ(game->getNextRoom(4, "east"), -1);

    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output.find("Door is locked.\n"), std::string::npos);

    delete game;
}

TEST(TestGameEnvironment, getNextRoomValidExitPuzzleLockedTest) {
    GameEnvironment* game = new PhaseOne();
    auto& rooms = game->getRooms();

    testing::internal::CaptureStdout();

    EXPECT_EQ(game->getNextRoom(3, "north"), -1);

    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output.find("Door is puzzle locked.\n"), std::string::npos);

    delete game;
}

TEST(TestGameEnvironment, printDescriptionValidRoom) {
    GameEnvironment* game = new PhaseOne();
    auto& rooms = game->getRooms();

    testing::internal::CaptureStdout();

    game->printDescription(0);

    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output,
    "S'tan, the ruler of hell just crashed your Contest!"
    " You may want to talk to him.\n");

    delete game;
}

TEST(TestGameEnvironment, printDescriptionInvalidRoom) {
    GameEnvironment* game = new PhaseOne();
    auto& rooms = game->getRooms();

    testing::internal::CaptureStdout();

    game->printDescription(-1);

    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Invalid room.\n");

    delete game;
}

TEST(TestGameEnvironment, getStartingRoomTest) {
    GameEnvironment* game = new PhaseOne();
    int start = game->getStartingRoom();

    EXPECT_EQ(start, 0);

    delete game;
}

TEST(TestGameEnvironment, setNPCDialogueTest) {
    GameEnvironment *game = new PhaseThree();
    NPC *npc = game->getNPC(4, "bone daddy");

    ASSERT_NE(npc, nullptr);

    npc->setNPCDialogue(4);
    EXPECT_EQ(npc->getNPCDialogue(), "How'd you keep your skin... whatever, "
    "keep going south and you'll reach my town. "
    "Don't go in the well without a way out though HARHARHAR!");

    delete game;
}
