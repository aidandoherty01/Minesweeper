# Minesweeper
This application recreates the game Minewsweeper. All of the Logic is implemented using the C++ Standard Library and all of the Visuals are implemented using SFML. Features include Random Board Generation, Preloaded Board States, Debugging Mode, and a Bomb Counter. All User Interaction is done through either Left or Right Mouse Clicks.
# How it Works
The Board is stored as a 2-D Array of Tiles.
=> Tiles are a structure 
### Interaction is processed by: 
1) Repeatedly Checking for User Input
2) Updating the Board State (if Necessary)
3) Redrawing the Board
Example:
  A user Left Clicks on an Unrevealed Tile. The code recognizes the left click event, tells the board that it has been left clicked, and provides the coordinates of the click. The board checks if the click was in a valid location (in this case it was), up
