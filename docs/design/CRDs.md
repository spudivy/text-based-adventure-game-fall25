### Exceptions
**Responsibility:** Class that inherits from std::runtime_error and is used to throw errors.

### Player
**Responsibility:** Represents the player entity, manages inventory and position on the map.

**Key Methods:**
- 'getName()' - gets the players name.
- 'getPosition()' - gets what room the player is in.
- 'createinventory()' - creates an empty vector to store items.

### Items
**Responsibility:** Creates item objects and sets them around the map in various positions.

**Key Methods:**
- 'setItems()' - sets items in various positions across the map.
- need 'giveItems()' - gives the player the item after certain conditions are met. 

### HelpMenu
**Responsibility:** Lists Commands or hints when requested by player input.

**Key Methods:**
- 'listCommands()' - displays all the inputs the player can use in a given room.
- 'quitGame()' - ends the program.
- 'restartGame()' - resets all variables and initializes everything and starts the program from the beginning.
- 'getHint()' - get a hint based on what room you are in.

### NPC
**Responsibility:** Create NPC character and control the actions they can take.

**Key Methods:**
- 'talk(phase:unsigned)' - checks what phase it is and then calls that to see what to display to terminal, then displays it.
- 'giveItems()' - allows NPC to give the player any items they have.
- 'makeP_one()' - Sets up the dialogue prompts for phase 1
- 'makeP_two()' - Sets up the dialogue prompts for phase 2
- 'makeP_three()' - Sets up the dialogue prompts for phase 3
- 'makeP_four()' - Sets up the dialogue prompts for phase 4

### Command
**Responsibility:** Controls all the actions the player can take.

**Key Methods:**
- 'move(direction:string)' - moves the player in the given direction.

### Puzzles
**Responsibility:** Creates and controls the puzzles.

**Key Methods:**
- 'setPuzzles()' - Initializes the puzzles
- 'getPuzzles(phase:unsigned, position:unsigned)' - Gives puzzles based on what phase and room the player is in.

###  GameEnviroment
**Responsibility:** Sets up the enviroments of the game

### PhaseOne
**Responsibility:** Sets up the enviroment for phase one, I.E., dialogues, descriptions, win conditions.

**Key Methods:**
- 'printDescription()' - prints a description of the area the player is in.
- 'victoryCondition()' - ends the game in a victory when certain conditions are met.
- need 'loseCondition()' - ends the game in a loss when certain conditions are met.

### PhaseTwo
**Responsibility:** Sets up the enviroment for phase two, I.E., dialogues, descriptions, win conditions.

**Key Methods:**
- 'printDescription()' - prints a description of the area the player is in.
- 'victoryCondition()' - ends the game in a victory when certain conditions are met.
- need 'loseCondition()' - ends the game in a loss when certain conditions are met.

### PhaseThree
**Responsibility:** Sets up the enviroment for phase three, I.E., dialogues, descriptions, win conditions.

**Key Methods:**
- 'printDescription()' - prints a description of the area the player is in.
- 'victoryCondition()' - ends the game in a victory when certain conditions are met.
- need 'loseCondition()' - ends the game in a loss when certain conditions are met.

### PhaseFour
**Responsibility:** Sets up the enviroment for phase four, I.E., dialogues, descriptions, win conditions.

**Key Methods:**
- 'printDescription()' - prints a description of the area the player is in.
- 'victoryCondition()' - ends the game in a victory when certain conditions are met.
- need 'loseCondition()' - ends the game in a loss when certain conditions are met.