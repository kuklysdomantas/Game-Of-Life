# Game of Life

This project is a C++ implementation of Conway's Game of Life. The game simulates cellular automata, where cells on a grid live, die, or multiply based on simple rules. The program reads a set of initial cell coordinates from a `.txt` file and allows users to observe the evolution of the cells over time. It is worth mentioning that this was my project in University.


## Features

- **Grid-based simulation**: The game runs on a two-dimensional grid where each cell can either be alive or dead.
- **Customizable Initial State**: The program reads the initial live cell coordinates from a provided `.txt` file. You can modify this file to create your own initial configurations.
- **Step-by-step Simulation**: Users can observe the changes in cell states across generations, where cells are updated based on the four rules of Conway's Game of Life.
- **Executable File**: A pre-compiled `.exe` file is provided for immediate execution without the need to compile the code.

## Rules of Conway's Game Of Life
1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
2. Any live cell with two or three live neighbours lives on to the next generation.
3. Any live cell with more than three live neighbours dies, as if by overpopulation.
4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

## How to Run the Game

1. Download the files from this git repository.
2. Run the **Game_Of_Life.exe** file.
3. Select the number of processes.
4. Select if you want to run the initial state from file or write it with hand. If you want to run the initial state from file, then write "**r**" and type the file name with .txt (in this case "random.txt"). If you want to write by hand, then just select the number of cells and type the coordinates.
5. Press "**y**" if you want to start the game. If you press the button "**n**", then it exits the `.exe` file.
6. Enjoy the game! Once the game is finished the `.exe` file is exited.

## Potential Future Improvements
- Supporting larger grids and faster computations.
- Allowing for more interactive control, such as pausing, resetting, and step-by-step execution.

## More information
If you want to find more information regarding this, you can find it in `https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life`. There is an explanation about all the examples of the patterns in the game. 
