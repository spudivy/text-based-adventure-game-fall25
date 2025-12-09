#include <string>
#include <cstdlib>

#include "GameEnvironment.hpp"
#include "Exceptions.hpp"
#include "gtest/gtest.h"

TEST(TestPhaseFour, constructionTest) {
    GameEnvironment* test = new PhaseFour();
    const auto& rooms = test->getRooms();
    EXPECT_EQ(rooms[0].description,
                  "You stand in the grand hallway of S'tans castle. "
    "He must be compensating for something. "
    "You have to move forward.");
    delete test;
}

TEST(TestPhaseFour, victoryConditionCorrect) {
    GameEnvironment* test = new PhaseFour();
    std::string expect = "Congratulations you win!";
    EXPECT_EQ(test->victoryCondition(6), expect);
    delete test;
}

TEST(TestPhaseFour, victoryConditionIncorrect) {
    GameEnvironment* test = new PhaseFour();
    EXPECT_EQ(test->victoryCondition(5), "");
    delete test;
}

TEST(TestPhaseFour, loseConditionCorrect) {
    GameEnvironment* test = new PhaseFour();
    EXPECT_FALSE(test->loseCondition(5));
    delete test;
}
