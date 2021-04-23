#ifndef MAZEGAME_H
#define MAZEGAME_H

#include <iostream>
#include <cstdlib>			//use for dynamic memory management
#include <unistd.h>			//to use sleep function
#include <stdio.h>			//getchar from user
#include <ctime>			//used in random number generator 
#include <termios.h>		//terminal setting
#include<math.h>
#include<stdlib.h>			//header file for Standard Library
#include<string.h>

#define row 15				//the maze size is 15x15
#define column 15
bool flag = false;          //T/F flag to determine whether the maze is solvable
bool slow = false;          //flag for time delay

using namespace std;

int maze[row][column];		//creat a 2D int array to store the maze
int pmove =0;				//initialize player's move equals to 0
int mazecopy[row][column];		//a copy of the maze, for path-search use
int dir[4][2]={{1,0},{0,1},{-1,0},{0,-1}};	//define four directions for path-search use

#endif
