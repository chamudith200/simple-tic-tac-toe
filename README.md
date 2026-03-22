# Simple TIc-Tac-Toe
A simple tic-tac-toe game using c language

### Requierements
* GCC compiler
* Linux or MacOS (or Windows with MinGW)

### How to build and run
to build,
``` bash
gcc main.c -o tictactoe
```
then to run,
```
./tictactoe
```

### How to play
The game will ask,
``` text
Player 1 playing.
Enter: row col
Enter: 
```
Player need to enter the row and column in order divided by a space,
``` text
Enter: 1 2
```
This will draw the player's symbol in the coresponding cell.
If there's a winning move the winner will be seleced and the the game will stop.
``` text
Enter: 3 2
O X . 
. X .
. X O

Player 1 has won!!!
```
