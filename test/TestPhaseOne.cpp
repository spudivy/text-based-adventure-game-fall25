#include <string>
#include <cstdlib>

#include "GameEnvironment.hpp"
#include "Exceptions.hpp"
#include "gtest/gtest.h"

TEST(TestPhaseOne, constructionTest) {
    GameEnvironment* test = new PhaseOne();
    const auto& rooms = test->getRooms();
    EXPECT_EQ(rooms[0].description,
                  "S'tan, the ruler of hell just crashed your Contest! "
    "You may want to talk to him.");
    delete test;
}

TEST(TestPhaseOne, victoryConditionCorrect) {
    GameEnvironment* test = new PhaseOne();
    std::string expect =
           "Hoho! The weakling has courage... too bad your mother was "
           "in the crossfire BAHAHA! See you never LOSER! \n"
           "A few months after the incident you hear of a certain man "
           "in Port City that could help you get into hell to take "
           "revenge on S'tan, with your mother still "
           "in the hospital, you head out.\n";
    EXPECT_EQ(test->victoryCondition(2), expect);
    delete test;
}

TEST(TestPhaseOne, victoryConditionIncorrect) {
    GameEnvironment* test = new PhaseOne();
    EXPECT_EQ(test->victoryCondition(5), "");
    delete test;
}

TEST(TestPhaseOne, loseConditionCorrect) {
    GameEnvironment* test = new PhaseOne();
    EXPECT_TRUE(test->loseCondition(1));
    delete test;
}

TEST(TestPhaseOne, loseConditionIncorrect) {
    GameEnvironment* test = new PhaseOne();
    EXPECT_FALSE(test->loseCondition(4));
    delete test;
}

