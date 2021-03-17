# Group-Project

- Group No.: 177
- Group members: Jing Jingderong(3035771775), Meiwen Su(3035709277)
- Topic: Walk out a Random Maze via the shortest path


# Description
- Our game will be a maze game where player can operate a sign to move around in a random generated maze. There will be a line under the maze stating “You have moved n steps” where n is the total number of steps players have moved so far. Players can only win the game when they arrive at the exit via the shortest path.

# Game Rules
- Every time players will face a different maze (random generated solvable maze)
- Players only win when they find the exit via the shortest path (the least steps)
- There’s only one entrance and one exit
- Players can only move in four directions: upwards, downwards, leftwards, and rightwards
- Players cannot move over the block
- Players can only move one step each time
- A step back will also be counted
- In case more than one path will be considered as shortest paths (with equal step counts), as far as the player’s moves is equal to the value of least steps, they win

# Feature lists and coding element
(1)
Random solvable maze
    - code element 1. Generation of random game sets
    - code element 3. Dynamic memory management
A 20x20 maze will be randomly generated every time player starts the game. Using time as root for srand to generate random blocks and maze path. Applying dynamic memory management (delete in the first run, then new for the rest). Objects instantiated from the heap by new need to be manually freed from memory after use. Every time there’s a new maze, the maze will be stored in an array. Apply void function to make sure there will always be at least one successful path.


(2)
Maze map will be a 20x20 rectangle with walls
    - code element 2. Data structures for storing game status
The maze will be a rectangular grid so the data structure will be a 2D array. Each element of the array representing 1 row, and each element of the inner arrays representing 1 cell in that row. Cell can be either empty (movable cell) or block (non-movable cell). 
			￼

(3)
Display player’s moving status “You have moved n steps” under the bottom
    - code element 2. Data structures for storing game status
In this line, n is a variable which will increase accordingly every time player makes a move. This value is cleared at the end of each game round. We will also create a class to set player’s initial status (can only move in four directions).

(4)
Only win when the player finds the exit via shortest path
    - code element 2. Data structures for storing game status
    - code element 4. File input/output
To calculate the least steps used to find the exit, a deep finding search algorithm will be applied to the maze map. Every time the new maze map will be used as input to DFS function. Then the result of DFS will be returned to main function will compare player’s step value and DFS step value at the end.

(5)
Multiple files to execute the code
- code element 5. Program codes in multiple files
Code Outline:
  1. Program analysis
    - Create the maze class and print out the map of the maze.
    - Create the class of the person walking the maze.

  2、Program implementation
    - Map.h : set up the maze map
    - Map.cpp : constructor, initialize parameters; destructor, release dynamically requested memory space; set up a random maze map, pass parameters; print the      maze map; set up the exit of the maze
    - player.h : set the position of the character, record the number of steps the character has taken
    - player.cpp : constructor, initialize data members, console screen buffer handle, characters to be written to the console buffer; number of character cells to be written, game start function
    - Main.cpp : defines and initializes a two-dimensional array of map data, instantiated from the heap with new, and requires manual memory release after use; 














