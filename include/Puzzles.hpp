#ifndef PUZZLES_H_INCLUDED
#define PUZZLES_H_INCLUDED

#include <string>
#include <utility>
#include <vector>
#include <map>

/**
 * @class Puzzles Puzzles.hpp "Puzzles.hpp"
 * @brief Interface that creates and stores puzzles.
 */
class Puzzles {
 public:
 /**
  * @brief Default Constructor.
  * @details Initializes the game at room 0.
  */ 
  Puzzles();

 /**
  * @brief Puzzles Constructor.
  * @param [in] type The name of the puzzle.
  */
  Puzzles(std::string type);

  /**
   * @brief Destructor.
   */
  ~Puzzles();

 /**
  * @brief Sets the puzzle type depending on the name of.
  * @details Dependent on the name of the puzzle.
  */
  void setPuzzles();

 /**
  * @brief Retrieves the puzzle type.
  */
  std::string getPuzzleType() const;

  /**
   * @brief A helper function to generate a random number.
   * @param [in] number Is used as an indicator to which
   * range of numbers to use.
   * @details This function is used to generate numbers
   * from 0 - 4 (Riddles, Anagrams, Chess) or 1 - 3 (RPS) 
   * @return A random integer from the given range.
   */
  int setRandomNum(int number);

  /**
   * @brief Sets the riddles for the game.
   * pair of riddle and answer.
   */
  void setRiddles();

  /**
   * @brief Asks a riddle and prmopt user to answer. 
   * @details checkPuzzle() is used to check if they
   * answered the riddle correctly
   * @return Boolean: true if user answer is correct, false otherwise.
   */
  bool riddlePuzzle();

  /**
   * @brief Sets the anagrams in a vector.
   * vector is a collection of pair of
   * anagrams and their answer
   */
  void setAnagrams();

  /**
   * @brief Asks to solve an anagram, prompts the user 
   * to enter their answer.
   * @details checkPuzzle() is used to check if they
   * answered the anagram correctly
   * @return Boolean: true if anagram is solved, false otherwise;
   */
  bool anagramPuzzle();

  /**
   * @brief Initializes a vector of pairs for a 
   * mate in one question.
   */
  void setChess();

  /**
   * @brief Prompts the user to solve the Mate in One
   * chess problem.
   * @details checkPuzzle() is used to verify if the user's
   * answer is correct.
   * @return Boolean: true if the solved it, false otherwise.
   */
  bool chessPuzzle();

  /**
   * @brief Sets a Map for Rock, Paper, and Scissors
   * with their correponding number.
   */
  void setRPS();

  /**
   * @brief Prompts the user to play Rock, Paper, and Scissors
   * with Stan.
   * @details checkRPS() is used to keep track of the matches
   * @return Boolean: true if they won, false otherwise.
   */
  bool RPS();

  /**
   * @brief A helper function that compares if 
   * the given answer matches with the right answer.
   * @details This function is used in riddlePuzzle(), 
   * anagramPuzzle(), and chessPuzzle().
   * @param [in] string, int, vector are used 
   * for the comparison. 
   * @returns Boolean: true if they match, false otherwise.
   */
  bool checkPuzzle(std::string, std::vector<std::pair<std::string,
                  std::string>>, int);

  /**
   * @brief A helper function that compares rock, paper, and scissors.
   * from the user input and the random number.
   * @details This function is used in RPS() to check
   * whether the user is winning or losing.
   * @return Boolean: true if they won, false otherwise.
   */             
  bool checkRPS(int, int, int&, int&, std::map<int, std::string>);

 private:
  bool win;
  std::string puzzleType;
  int puzzleNum;
  std::vector<std::pair<std::string, std::string>> riddles;
  std::vector<std::pair<std::string, std::string>> anagrams;
  std::map<int, std::string> rps;  // 1 = rock, 2 = paper, 3 = scissors
  std::vector<std::pair<std::string, std::string>> chess;
};

#endif  // PUZZLES_H_INCLUDED
