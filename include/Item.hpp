#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include <string>
#include <vector>

/**
 * @class Item Item.hpp "Item.hpp"
 * @brief Interface that creates and stores items.
 */
class Item {
 public:
 /**
  * @brief Default Constructor.
  * @details Initializes the item information to an empty string.
  */
  Item();

 /**
  * @brief item Constructor
  * @param [in] itemName the name of the item.
  * @param [in] itemDescription the description of the item.
  */
  Item(std::string itemName, std::string itemDescription);

 /**
  * @brief Destructor.
  */
  ~Item();

 /**
  * @brief Gets the name of the item.
  * @return The item's name.
  */
  std::string getItemName() const;

 /**
  * @brief Gets the description of the item.
  * @return The item's description.
  */
  std::string getItemDescription() const;

 protected:
  std::string itemName, itemDescription;
};

#endif // ITEM_H_INCLUDED
