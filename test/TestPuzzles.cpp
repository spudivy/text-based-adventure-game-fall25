
#include <vector>
#include <map>

#include "gtest/gtest.h"

#include "Puzzles.hpp"
#include "Exceptions.hpp"

TEST(TestPuzzles, defaultConstructorTest) {
    Puzzles* test = new Puzzles();
    EXPECT_EQ(test->getPuzzleType(), "");
    delete test;
}

TEST(TestPuzzles, paramaterConstructorTest) {
    Puzzles* test = new Puzzles("riddle");
    EXPECT_EQ(test->getPuzzleType(), "riddle");

    Puzzles* test1 = new Puzzles("anagram");
    EXPECT_EQ(test1->getPuzzleType(), "anagram");

    Puzzles* test2 = new Puzzles("chess");
    EXPECT_EQ(test2->getPuzzleType(), "chess");

    Puzzles* test3 = new Puzzles("RPS");
    EXPECT_EQ(test3->getPuzzleType(), "RPS");

    delete test;
    delete test1;
    delete test2;
    delete test3;
}

TEST(TestPuzzles, setRandomNumTest) {
    Puzzles* test = new Puzzles();
    int num1 = test->setRandomNum(10000);
    Puzzles* test1 = new Puzzles();
    int num2 = test1->setRandomNum(10000);

    if (num1 == num2)
        num1++;

    EXPECT_NE(num1, num2);

    delete test;
    delete test1;
}

TEST(TestPuzzles, riddlePuzzleTest) {
    Puzzles* test = new Puzzles("riddle");

    std::stringstream input("");
    std::streambuf* cin_backup = std::cin.rdbuf(input.rdbuf());
    testing::internal::CaptureStdout();
    EXPECT_FALSE(test->riddlePuzzle());
    std::string output = testing::internal::GetCapturedStdout();
    std::cin.rdbuf(cin_backup);
    delete test;
}

TEST(TestPuzzles, anagramPuzzleTest) {
    Puzzles* test = new Puzzles("anagram");

    std::stringstream input("");
    std::streambuf* cin_backup = std::cin.rdbuf(input.rdbuf());
    testing::internal::CaptureStdout();
    EXPECT_FALSE(test->anagramPuzzle());
    std::string output = testing::internal::GetCapturedStdout();
    std::cin.rdbuf(cin_backup);
    delete test;
}

TEST(TestPuzzles, chessPuzzleTest) {
    Puzzles* test = new Puzzles("chess");

    std::stringstream input("");
    std::streambuf* cin_backup = std::cin.rdbuf(input.rdbuf());
    testing::internal::CaptureStdout();
    EXPECT_FALSE(test->chessPuzzle());
    std::string output = testing::internal::GetCapturedStdout();
    std::cin.rdbuf(cin_backup);
    delete test;
}

TEST(TestPuzzles, checkPuzzleCorrect) {
    Puzzles test;
    std::vector<std::pair<std::string, std::string>> P;
    std::pair<std::string, std::string> QA;

    QA.first = "Question";
    QA.second = "Answer";

    P.push_back(QA);
    testing::internal::CaptureStdout();
    EXPECT_TRUE(test.checkPuzzle("Answer", P, 0));
    EXPECT_FALSE(test.checkPuzzle("Question", P, 0));
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "You solved the puzzle!\nIncorrect.\n");
}

TEST(TestPuzzles, checkIfRPSIsWorking) {
    Puzzles test;
    std::map<int, std::string> rps;
    int won, lost;

    rps[1] = "Rock";
    rps[2] = "Paper";
    rps[3] = "Sciccors";

    won = 0;
    lost = 1;
    testing::internal::CaptureStdout();
    EXPECT_FALSE(test.checkRPS(2, 1, won, lost, rps));
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "match lost\nyou chose: Rock\nstan chose: "
        "Paper\nYOU LOST THE FIGHT!!\n");

    won = 1;
    lost = 0;
    testing::internal::CaptureStdout();
    EXPECT_TRUE(test.checkRPS(3, 1, won, lost, rps));
    std::string output1 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output1, "match won\nyou chose: Rock\nstan chose: "
        "Sciccors\nYOU WON THE FIGHT!!\n");

    won = 1;
    lost = 0;
    testing::internal::CaptureStdout();
    EXPECT_TRUE(test.checkRPS(1, 2, won, lost, rps));
    std::string output2 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output2, "match won\nyou chose: Paper\nstan chose: "
        "Rock\nYOU WON THE FIGHT!!\n");

    won = 0;
    lost = 1;
    testing::internal::CaptureStdout();
    EXPECT_FALSE(test.checkRPS(3, 2, won, lost, rps));
    std::string output3 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output3, "match lost\nyou chose: Paper\nstan chose: "
        "Sciccors\nYOU LOST THE FIGHT!!\n");


    won = 0;
    lost = 1;
    testing::internal::CaptureStdout();
    EXPECT_FALSE(test.checkRPS(1, 3, won, lost, rps));
    std::string output4 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output4, "match lost\nyou chose: Sciccors\nstan chose: "
        "Rock\nYOU LOST THE FIGHT!!\n");

    won = 1;
    lost = 0;
    testing::internal::CaptureStdout();
    EXPECT_TRUE(test.checkRPS(2, 3, won, lost, rps));
    std::string output5 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output5, "match won\nyou chose: Sciccors\nstan chose: "
        "Paper\nYOU WON THE FIGHT!!\n");

    testing::internal::CaptureStdout();
    EXPECT_TRUE(test.checkRPS(2, 2, won, lost, rps));
    std::string output6 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output6, "match tied\nyou chose: Paper\nstan chose: "
        "Paper\nYOU WON THE FIGHT!!\n");
}


TEST(TestPuzzles, checkIfRPSIncorrect) {
    Puzzles test;

    std::map<int, std::string> rps;
    int won, lost;

    rps[1] = "Rock";
    rps[2] = "Paper";
    rps[3] = "Sciccors";

    won = 0;
    lost = 1;
    testing::internal::CaptureStdout();
    EXPECT_EQ(test.checkRPS(0, 0, won, lost, rps), false);
    std::string output = testing::internal::GetCapturedStdout();
}
