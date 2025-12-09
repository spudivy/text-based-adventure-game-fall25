#include "Puzzles.hpp"

#include <cmath>
#include <ctime>
#include <iostream>
#include <string>
#include <utility>

#include "GameEnvironment.hpp"

Puzzles::Puzzles() {
  this->puzzleType = "";
}

Puzzles::Puzzles(std::string type) {
  this->puzzleType = type;
  setPuzzles();
}

Puzzles::~Puzzles() {}

void Puzzles::setPuzzles() {
  if (puzzleType == "riddle")
    setRiddles();
  else if (puzzleType == "anagram")
    setAnagrams();
  else if (puzzleType == "chess")
    setChess();
  else if (puzzleType == "RPS")
    setRPS();
}

std::string Puzzles::getPuzzleType() const {
  return puzzleType;
}

int Puzzles::setRandomNum(int number) {
  double time = clock();
  double sinValue = std::sin(time);
  int value = static_cast<int>((sinValue + 1) * 2.5);
  if (number == 5) {
    return (value % number);
  } else {
  return ((value % number) + 1);
  }
}

// pair: Riddle[].first = question, Riddle[].second = answer
void Puzzles::setRiddles() {
  std::string Q;  // Riddle Question
  std::string A;  // Riddle Answer

  Q = "What five-letter word becomes shorter when you add two letters to it?\n";
  A = "short";
  riddles.push_back({Q, A});

  Q = "What breaks as soon as you say its name?\n";
  A = "silence";
  riddles.push_back({Q, A});

  Q = "What word begins with E and ends with E, but only has one letter?\n";
  A = "envelope";
  riddles.push_back({Q, A});

  Q = "If you drop a yellow hat in the Red Sea, what does it become?\n";
  A = "wet";
  riddles.push_back({Q, A});

  Q = "What kind of lion never roars?\n";
  A = "dandelion";
  riddles.push_back({Q, A});
}

bool Puzzles::riddlePuzzle() {
  int randNum = setRandomNum(riddles.size());

  std::cout << "This is a Riddle Puzzle!\n";

  std::cout << riddles[randNum].first;
  std::string ans;
  std::cin >> ans;

  return checkPuzzle(ans, riddles, randNum);
}

// pair: Anagram[].first = question, Anagram[].second = answer
void Puzzles::setAnagrams() {
  std::string Q;  // Anagram Question
  std::string A;  // Anagram Answer

  Q = "Solve the Anagram: stressed\n";
  A = "desserts";
  anagrams.push_back({Q, A});

  Q = "Solve the Anagram: elbow\n";
  A = "below";
  anagrams.push_back({Q, A});

  Q = "Solve the Anagram: night\n";
  A = "thing";
  anagrams.push_back({Q, A});

  Q = "Solve the Anagram: listen\n";
  A = "silent";
  anagrams.push_back({Q, A});

  Q = "Solve the Anagram: dusty\n";
  A = "study";
  anagrams.push_back({Q, A});
}

bool Puzzles::anagramPuzzle() {
  int randNum = setRandomNum(anagrams.size());

  std::cout << "This is an Anagram Puzzle!\n";

  std::cout << anagrams[randNum].first;
  std::string ans;
  std::cin >> ans;

  return checkPuzzle(ans, anagrams, randNum);
}

void Puzzles::setRPS() {
  rps[1] = "Rock";
  rps[2] = "Paper";
  rps[3] = "Scissors";
}

bool Puzzles::RPS() {
  std::cout << "Play Rock, Paper, Scissors with Stan. Whoever wins 2 matches "
               "will be the winner\n";

  int matchwin = 0, matchlose = 0, pick;
  bool flag;
  while (matchlose != 2) {
    int randNum = setRandomNum(3);

    std::cout << "\nPick your weapon (1 = rock, 2 = paper, 3 = scissors): ";
    std::cin >> pick;

    flag = checkRPS(randNum, pick, matchwin, matchlose, rps);

    if (matchwin == 2) {
      break;
    }
  }
  return flag;
}

void Puzzles::setChess() {
  std::string Q;  // Chess Question
  std::string A;  // Chess Answer

  Q = "\nWhite is lowercase and black is Uppercase, checkmate black in 1. "
    "\n"
    "  a b c d e f g h\n"
    "8 K . . . Q . . R\n"
    "7 P P q R . . . .\n"
    "6 . . . . . . . .\n"
    "5 . . . . . . . .\n"
    "4 . p . H b . . .\n"
    "3 p . . . . . . .\n"
    "2 . . . . . . p .\n"
    "1 . k r . . . . r\n";
  A = "bb7";
  chess.push_back({Q, A});

  Q = "\nWhite is lowercase and black is Uppercase, checkmate black in 1. "
      "\n"
      "  a b c d e f g h\n"
      "8 . . . . . . K .\n"
      "7 . . . . . P P P\n"
      "6 P . . . . . . .\n"
      "5 p . . . . . . .\n"
      "4 . . . . . B . .\n"
      "3 . . . . . . . p\n"
      "2 . R . . . p p .\n"
      "1 . . . r . . k .\n";
  A = "rd8";
  chess.push_back({Q, A});

  Q = "\nWhite is lowercase and black is Uppercase, checkmate black in 1. "
    "\n"
    "  a b c d e f g h\n"
    "8 R . B Q K B . R\n"
    "7 P P P P . P P P\n"
    "6 . . H . . H . .\n"
    "5 . . . q . . . .\n"
    "4 . . b . p . . .\n"
    "3 . . . . . . . .\n"
    "2 p b . . . p p p\n"
    "1 r h . . k . h r\n";
  A = "qf7";
  chess.push_back({Q, A});

  Q = "\nWhite is lowercase and black is Uppercase, checkmate black in 1. "
    "\n"
    "  a b c d e f g h\n"
    "8 . K . R . . . .\n"
    "7 . . P . . . P Q\n"
    "6 q P . . . . . .\n"
    "5 . . . . h . p P\n"
    "4 . . . . . . . p\n"
    "3 . . k . . . . .\n"
    "2 . . . . . . . .\n"
    "1 . . . R . . r .\n";
  A = "hc6";
  chess.push_back({Q, A});

  Q = "\nWhite is lowercase and black is Uppercase, checkmate black in 1. "
    "\n"
    "  a b c d e f g h\n"
    "8 . . . . . . K .\n"
    "7 . . . . . P P P\n"
    "6 . . . . . . . .\n"
    "5 q . . . . . . .\n"
    "4 . . . . . h . .\n"
    "3 . . . . . . p .\n"
    "2 . . P h . . . p\n"
    "1 . . . . k . . B\n";
  A = "qd8";
  chess.push_back({Q, A});
}

bool Puzzles::chessPuzzle() {
  int randNum = setRandomNum(chess.size());

  std::cout << "This is a Chess: Mate in One Puzzle!\n";
  std::cout << "The answer format should be in standard algebraic notation "
               "(ex: qd4) H = knight\n";

  std::cout << chess[randNum].first;
  std::string ans;
  std::cin >> ans;

  return checkPuzzle(ans, chess, randNum);
}

bool Puzzles::checkPuzzle(std::string ans, std::vector<std::pair<std::string,
                    std::string>> puzzle, int number) {
    if (ans == puzzle[number].second) {
        puzzle.erase(puzzle.begin() + number);
        std::cout << "You solved the puzzle!\n";
        return true;
    }   else {
        std::cout << "Incorrect.\n";
        return false;
    }
}

bool Puzzles::checkRPS(int randNum, int pick, int& matchwin,
    int& matchlose, std::map<int, std::string> rps) {

    if ((pick == 1) && (randNum == 2)) {
      std::cout << "match lost\n";
      std::cout << "you chose: " << rps[pick];
      std::cout << "\nstan chose: " << rps[randNum];
      ++matchlose;
    } else if ((pick == 1) && (randNum == 3)) {
      std::cout << "match won\n";
      std::cout << "you chose: " << rps[pick];
      std::cout << "\nstan chose: " << rps[randNum];
      ++matchwin;
    } else if ((pick == 2) && (randNum == 1)) {
      std::cout << "match won\n";
      std::cout << "you chose: " << rps[pick];
      std::cout << "\nstan chose: " << rps[randNum];
      ++matchwin;
    } else if ((pick == 2) && (randNum == 3)) {
      std::cout << "match lost\n";
      std::cout << "you chose: " << rps[pick];
      std::cout << "\nstan chose: " << rps[randNum];
      ++matchlose;
    } else if ((pick == 3) && (randNum == 1)) {
      std::cout << "match lost\n";
      std::cout << "you chose: " << rps[pick];
      std::cout << "\nstan chose: " << rps[randNum];
      ++matchlose;
    } else if ((pick == 3) && (randNum == 2)) {
      std::cout << "match won\n";
      std::cout << "you chose: " << rps[pick];
      std::cout << "\nstan chose: " << rps[randNum];
      ++matchwin;
    } else {
      std::cout << "match tied\n";
      std::cout << "you chose: " << rps[pick];
      std::cout << "\nstan chose: " << rps[randNum];
    }

    if (matchwin == 2) {
      std::cout << "\nYOU WON THE FIGHT!!\n";
      return true;
    } else if (matchlose == 2) {
      std::cout << "\nYOU LOST THE FIGHT!!\n";
      return false;
    }
  return false;
}
