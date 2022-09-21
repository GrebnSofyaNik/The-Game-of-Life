# The-Game-of-Life
"The Game of Life" virtualization in C

***== The program src/game_of_life.c was developed in the C programming language, which is a visualization of "The Game of Life". To display graphics, only character (ASCII) graphics were used (with output to the terminal). The game Game of life has an interactive mode, with game speed setting (by changing the delay step). ==***

* ***Graphic arts***

The field is a rectangle 80 by 25 cells.
It is understood that the field is "closed on itself", for example, for the lower right square, the neighbor on the right is the lower left square, and the neighbor on the bottom is the upper right.

The initialization of the "game" state via stdin is provided. Prepared 10 initial state files for quick launch and initialization via input redirection.

## Important Notes

* The game is developed in the C language, in a structural style and works from the terminal;

> When developing the game, I was fully guided by the principles of E. Dijkstra's structured programming.
