# Minesweeper
This application recreates the game Minewsweeper. All of the Logic is implemented using the C++ Standard Library and all of the Visuals are implemented using SFML. Features include Random Board Generation, Preloaded Board States, Debugging Mode, and a Bomb Counter. All User Interaction is done through either Left or Right Mouse Clicks.
# How it Works
The Board is a class which stores a 2-D Array of Tiles. Tiles are a struct which store the Surrounding Bomb Count, Pointers to their 8 Neighbors, and variables to check whether they're a Bomb, Flag, and/or Revealed.

### Interaction is processed by: 
1) Repeatedly Checking for User Input
2) Updating the Board State (if Necessary)
3) Redrawing the Board

### Example:
The user left clicks on an unrevealed tile. The code recognizes the left click event, tells the board that it has been left clicked, and provides the coordinates of the click. The board checks if the click was in a valid location and updates the conditions of that tile. The board will then be redrawn with the updated information.
# How to Run
The game works by downloading all files, including the folders, and running `main.cpp`. You will also have to download [SFML](https://www.sfml-dev.org/download.php).
