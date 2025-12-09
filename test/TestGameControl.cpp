#include "GameControl.hpp"
#include "Exceptions.hpp"
#include "gtest/gtest.h"

TEST(TestGameControl, defaultConstructorTest) {
    GameControl* game = new GameControl();
    ASSERT_NE(game, nullptr);
    delete game;
}

TEST(TestGameControl, startGameTest) {
    /*
    GameControl* game = new GameControl();
    testing::internal::CaptureStdout();
    game->start();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("> ") != std::string::npos);

    delete game;*/
}
