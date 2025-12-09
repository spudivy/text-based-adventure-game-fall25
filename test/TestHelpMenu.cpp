#include "HelpMenu.hpp"
#include "Exceptions.hpp"
#include "gtest/gtest.h"

TEST(TestHelpMenu, listCommandsTest) {
    HelpMenu *help = new HelpMenu();

    testing::internal::CaptureStdout();

    help->listCommands();

    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output,
        "Command List:\n"
                 "- Move: Allows you to move."
                 " Type north/south/east/west to go in a certain direction.\n"
                 "    - [move north/south/east/west]\n"
                 "- Inventory: Take a look at the items in your inventory.\n"
                 "    - [inventory]\n"
                 "- Inspect: Inspect what's in the room.\n"
                 "    - [inspect]\n"
                 "- Grab: Pick up an item and place it in your inventory.\n"
                 "    - [grab (item name)]\n"
                 "- Use: Use an item that you select.\n"
                 "    - [use (item name)]\n"
                 "- Solve: Allows you to solve a riddle.\n"
                 "    - [solve]\n"
                 "- Talk: Communicate with those in the room.\n"
                 "    - [talk to (name)]\n"
                 "- Look: Examine the room you are in.\n"
                 "    - [look]\n"
                 "- Help: Access the help menu.\n"
                 "    - [help]\n"
                 "- Quit/Exit/End: Ends the game.\n"
                 "    - [quit/end/exit]\n");
    delete help;
}
