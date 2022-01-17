# Peg Game Solver

This is the program I  wrote for my Algorithms (CS 2500) final project. The point of this project was to write a program to solve and analyze the triangular variant of Peg Solitaire. The game itself can be played with various different board shapes, but I chose the 15-peg triangular variant since these are often found at Cracker Barrel restaurants. The rules are the same regardless of the board shape.

I used recursive backtracking to simulate every possible move that can be played in order to determine solutions. I also used this to find the worst you can do when playing it. 

The following image shows the numeric labels I chose for the board.

![Board Layout](peglayout.png?raw=true "Board Layout")

## Results

These images show the output from running the program. They detail the amount of solutions that exist for any given starting hole, show the moves needed to do the worst possible, and show an example solution.

![Results](Results.png?raw=true "results")

![Results](Results2.png?raw=true "results")

This shows the amount of solutions pertaining to each starting hole. Based on this, the next time you try playing this at Cracker Barrel, you should start with one of the middle side holes. You'll have a better chance of winning!

![Solutions count](pegsolscount.png?raw=true "Solutions Count")

## Examples

Here are some example solutions found using this program.

Solution Example 1

![Solution 1](Example1.gif?raw=true "Example 1")

Solution Example 2

![Solution 2](Example2.gif?raw=true "Example 2")

Worst Possible Game Example

![Worst Possible Example](Fail.gif?raw=true "Worst Possible Example")