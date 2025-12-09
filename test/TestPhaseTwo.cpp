#include <string>
#include <cstdlib>

#include "GameEnvironment.hpp"
#include "Exceptions.hpp"
#include "gtest/gtest.h"

TEST(TestPhaseTwo, constructionTest) {
    GameEnvironment* test = new PhaseTwo();
    const auto& rooms = test->getRooms();
    EXPECT_EQ(rooms[0].description,
    "You stand in the main square of Port City. "
    "You see a large gate to the west. "
    "To the north there's a dark alleyway "
    "probably teeming with criminals. "
    "To the east is the docks - you see a few cabins nearby.");
    delete test;
}

TEST(TestPhaseTwo, victoryConditionCorrect) {
    GameEnvironment* test = new PhaseTwo();
    std::string expect = "The smell of death and decay wakes you up.";
    EXPECT_EQ(test->victoryCondition(11), expect);
    delete test;
}

TEST(TestPhaseTwo, victoryConditionIncorrect) {
    GameEnvironment* test = new PhaseTwo();
    EXPECT_EQ(test->victoryCondition(5), "");
    delete test;
}

TEST(TestPhaseTwo, loseConditionCorrect) {
    GameEnvironment* test = new PhaseTwo();
    EXPECT_TRUE(test->loseCondition(12));
    delete test;
}

TEST(TestPhaseTwo, loseConditionIncorrect) {
    GameEnvironment* test = new PhaseTwo();
    EXPECT_FALSE(test->loseCondition(4));
    delete test;
}

