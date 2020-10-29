# GameOfLife
Simple, text based cellular automaton application. Supports randomized begin state and file loading

## How to run
### Using CMake
1. Clone repository
2. Enter GameOfLife directory <code>cd GameOfLife</code>
3. Create build directory inside:
   <code>mkdir build</code>
4. Go to build:
   <code>cd build</code>
5. Create cmake files
   <code>cmake ..</code>
6. Build
   <code>make</code>
7. Enjoy!
   <code>./Game_of_Life</code>
### Using Visual Studio
1. Clone repository
2. Open <code>*.sln</code> file 
3. <code>Ctrl+Shift+B</code> to build
4. <code>Ctrl+F5</code> to run


After launching you select if you want to create a new board, in which case you enter the board size and the simulation starts. 
Or you have an option to load a board state.

\* represent live Cells, # dead ones.

#### Creating own board states save files.
Board state has to follow the following:
1. First two numbers are width and height of a board
2. Zeros are dead cells
3. Ones are live cells
4. Total number of zeros and ones has to match given width*height of the board 

## Plans for the future:
1. Saving board state
2. Move from text based to graphic based

### App in action:
[![](http://img.youtube.com/vi/cdUo8_2b6M8/0.jpg)](https://youtu.be/cdUo8_2b6M8 "App in action")

[App in action](https://youtu.be/cdUo8_2b6M8)
