#include <string>
#include <cstdlib>

#include "GameEnvironment.hpp"
#include "Exceptions.hpp"
#include "gtest/gtest.h"

TEST(TestPhaseThree, constructionTest) {
    GameEnvironment* test = new PhaseThree();
    const auto& rooms = test->getRooms();
    EXPECT_EQ(rooms[0].description,
    "You stand high atop the mountain peak, you hear "
    "the screams of your fellow man all around you. "
    "the only path down is west.");
    delete test;
}

TEST(TestPhaseThree, victoryConditionCorrect) {
    GameEnvironment* test = new PhaseThree();
    std::string expect = "You can't wait to get your revenge!";
    EXPECT_EQ(test->victoryCondition(14), expect);
    delete test;
}

TEST(TestPhaseThree, victoryConditionIncorrect) {
    GameEnvironment* test = new PhaseThree();
    EXPECT_EQ(test->victoryCondition(5), "");
    delete test;
}

TEST(TestPhaseThree, loseConditionCorrect) {
    GameEnvironment* test = new PhaseThree();
    EXPECT_TRUE(test->loseCondition(11));
    delete test;
}

TEST(TestPhaseThree, loseConditionIncorrect) {
    GameEnvironment* test = new PhaseThree();
    EXPECT_FALSE(test->loseCondition(4));
    delete test;
}
