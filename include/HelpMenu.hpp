#ifndef HELPMENU_H_INCLUDED
#define HELPMENU_H_INCLUDED

/**
 * @class HelpMenu HelpMenu.hpp "HelpMenu.hpp"
 * @brief Interface that stores the help command information.
 */
class HelpMenu {
 public:
 /**
  * @brief Default Constructor.
  */
  HelpMenu();

 /**
  * @brief Destructor.
  */
  ~HelpMenu();

 /**
  * @brief Lists the commands that the player can activate.
  */
  void listCommands();
};

#endif // HELPMENU_H_INCLUDED
