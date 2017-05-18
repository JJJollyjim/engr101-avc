#include<stdio.h>
#include<time.h>
#include<iostream>
#include"E101.h"

using namespace std;

/*
 * - A Maze has many nodes (junctions)
 * - A Node has up to 4 direct neighbours
 * - A Maze can be constructed from a txt file containing a list of nodes, with an id [A-Z] and their direct neighbours
 * - A Maze has two special nodes, entry and exit
 * - If the robot was to lose track of nodes, current node can be set to entry when camera detects a line...
 * ... and no walls to either side. The robot can then turn around and begin the maze again. (In the case of the walled maze)
 */

class Maze {
    Node nodes[];
};

struct Node {
    char identifier; // unique id of node

    // Direct neighbours
    Node north;
    Node east;
    Node south;
    Node west;

};

