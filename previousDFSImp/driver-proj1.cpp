/**
* file: driver-proj1.cpp
 * author: Aubrey Bedford
 * course: CSI 3334
 * assignment: Project 1 -- Maze Solver
 * due date: September 12, 2025
 * version 1.3
 *
 * This file is the driver for the Maze Solver program which will take a maze
 * from standard input and find whether, or not, it has a solution. It
 * utilizes a depth first search algorithm to find the solution.
 *
 */

#include <iostream>
#include "location-proj1.h"
#include "maze-proj1.h"
#include "stack-proj1.h"


/* main
 *  parameters:
 *      argc -- the number of arguments from the command line
 *      argv -- the command line argument values
 *  return value: 0 (indicating a successful run)
 *
 *  Currently designated for testing each function of the location
 *  class
 */
int main (int argc, char *argv[]) {

  Maze puzzle;
  LocationStack locStack;
  bool solved = false;


  cin >> puzzle;

  //Starting Location is at the top
  locStack.push(puzzle.getStartLocation());

  //If the start and the end are the same, it will immediately go to print
  if (puzzle.isEndLocation(puzzle.getStartLocation())) {
    solved = true;
  }

  while (!locStack.isEmpty() && !solved) {
    Location m = locStack.getTop(), neighbor;

    if (m.iterationDone()) {
      locStack.pop();
    }
    else {
      do {
        neighbor = m.iterationCurrent();
        m.iterationAdvance();
        locStack.pop();
        locStack.push(m);
        if (puzzle.isValidLocation(neighbor) && !locStack.isOn(neighbor)) {
          locStack.push(neighbor);
        }
        //Checks if m has a valid neighbor or that the current has changed
      } while (!m.iterationDone() && locStack.getTop() == m);
      if (puzzle.isEndLocation(locStack.getTop())) {
        solved = true;
      }
    }
  }

  if (solved) {
    cout << "Solution found" << endl;
    cout << locStack;
  }
  else {
    cout << "No solution" << endl;
  }


  return 0;
}