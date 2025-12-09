#include "Player.hpp"
#include "Exceptions.hpp"
#include "gtest/gtest.h"

TEST(TestPlayer, defaultConstructorTest) {
    Player* player = new Player();
    EXPECT_EQ(player->getName(), "");
    EXPECT_EQ(player->getCurrentRoom(), 0);
    delete player;
}

TEST(TestPlayer, paramaterConstructorTest) {
    Player* player = new Player("bob");
    EXPECT_EQ(player->getName(), "bob");
    EXPECT_EQ(player->getCurrentRoom(), 0);
    delete player;
}

TEST(TestPlayer, enterNameTest) {
    Player* player = new Player();
    std::stringstream input("bob");
    std::streambuf* cin_backup = std::cin.rdbuf(input.rdbuf());

    testing::internal::CaptureStdout();
    std::string name = player->enterName();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "What is your name?\n> ");

    EXPECT_EQ(name, "bob");
    std::cin.rdbuf(cin_backup);
    delete player;
}

TEST(TestPlayer, setNameTest) {
    Player* player = new Player();

    player->setName("bob");
    EXPECT_EQ(player->getName(), "bob");
    EXPECT_NE(player->getName(), "anna");
    delete player;
}

TEST(TestPlayer, setCurrentRoomTest) {
    Player* player = new Player();

    player->setCurrentRoom(2);
    EXPECT_EQ(player->getCurrentRoom(), 2);
    EXPECT_NE(player->getCurrentRoom(), 4);
    delete player;
}

TEST(TestPlayer, initializeInventoryTest) {
    Player* player = new Player();
    Item item("key", "a small key");

    player->initializeInventory(item);
    EXPECT_TRUE(player->hasItem("key"));
    EXPECT_FALSE(player->hasItem("banana"));
    delete player;
}

TEST(TestPlayer, addToInventoryTest) {
    Player* player = new Player();
    Item item("key", "a small key");

    testing::internal::CaptureStdout();
    player->addToInventory(item);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(player->hasItem("key"));
    EXPECT_NE(output.find("key has been added to your inventory.\n"),
              std::string::npos);

    EXPECT_TRUE(player->hasItem("key"));
    EXPECT_FALSE(player->hasItem("banana"));
    delete player;
}

TEST(TestPlayer, removeFromInventoryTest) {
    Player* player = new Player();
    Item item("key", "a small key");

    testing::internal::CaptureStdout();
    player->addToInventory(item);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(player->hasItem("key"));
    EXPECT_NE(output.find("key has been added to your inventory.\n"),
              std::string::npos);

    testing::internal::CaptureStdout();
    player->removeFromInventory("key");
    std::string output1 = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(player->hasItem("key"));
    EXPECT_NE(output1.find("key has been removed from your inventory.\n"),
              std::string::npos);

    delete player;
}

TEST(TestPlayer, displayInventoryTest) {
    Player* player = new Player();
    Item item("key", "a small key");

    testing::internal::CaptureStdout();
    player->addToInventory(item);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(player->hasItem("key"));
    EXPECT_NE(output.find("key has been added to your inventory.\n"),
              std::string::npos);

    testing::internal::CaptureStdout();
    player->displayInventory();
    std::string output1 = testing::internal::GetCapturedStdout();
    EXPECT_NE(output1.find("Inventory:\n"), std::string::npos);
    EXPECT_NE(output1.find("- key"), std::string::npos);

    delete player;
}

TEST(TestPlayer, hasItemInInventoryTest) {
    Player* player = new Player();
    Item item("key", "a small key");

    testing::internal::CaptureStdout();
    player->addToInventory(item);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(player->hasItem("key"));
    EXPECT_NE(output.find("key has been added to your inventory.\n"),
              std::string::npos);

    EXPECT_TRUE(player->hasItem("key"));
    EXPECT_FALSE(player->hasItem("banana"));

    Item* itemGrabbed = player->getItem("key");

    EXPECT_NE(itemGrabbed, nullptr);
    EXPECT_EQ(itemGrabbed->getItemName(), "key");

    delete player;
}
