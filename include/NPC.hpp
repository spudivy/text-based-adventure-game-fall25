#ifndef NPC_H_INCLUDED
#define NPC_H_INCLUDED

#include <string>
#include <vector>

/**
 * @class NPC NPC.hpp "NPC.hpp"
 * @brief Interface that creates various NPCs.
 */
class NPC {
 public:
 /**
  * @brief Default Constructor.
  * @details Initializes name to an empty string and index to 0.
  */
  NPC();

 /**
  * @brief Item Constructor.
  * @param [in] name The name of the item.
  * @param [in] dialogue The description of the item.
  */
  NPC(std::string name, std::vector<std::string> dialogue);

 /**
  * @brief Destructor.
  */
  ~NPC();

 /**
  * @brief Gets the name of the item.
  * @return The item's name.
  */
  std::string getNPCName() const;

 /**
  * @brief Gets the description of the item.
  * @return The item's description.
  */
  std::string getNPCDialogue() const;

 /**
  * @brief Gets the description of the item.
  * @return The item's description.
  */
  void setNPCDialogue(int roomID);

 protected:
  std::string NPCName;
  int index;
  std::vector<std::string> dialogue;
};

#endif // NPC_H_INCLUDED

