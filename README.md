# RandomMazeGenerator
This is a homework assignment from a data structures class taken during my time in community college. The objective was to produce a randomly generated maze that starts in the upper left hand corner of the screen and ends in the lower right hand corner.  The objective was to combine several different types of data structures we had learned in the summer course such as Stacks, Queues, and Disjoint Sets (union find). Additionally I had to use algorithms such as Depth-First search and Breadth-First search to find the exit of the maze. An optional objective was to use C++ and compile it from the command line using g++.



# Compiling Instructions
1. To compile on Linux use:

	`g++ -std=c++11 main.cpp -o Douglas_Christopher_prog4`
	

2. To execute:

   There are two ways to do this:
	1) without a file
	
	  `./Douglas_Christopher_prog4`
	  
	  It will ask you for the size, n, and generate a random maze that is n by n units long.
	  After making the maze the program will then display the path
	   
	2) with a file
	 
	  `./Douglas_Christopher_prog4 <INPUT_FILE.TXT>`
		
	  It will take one file as input, turn it into a maze, and solve it.

# Input file explanation
First value to be read in, n, will be the length of the sides of the maze.
there will then need to be n squared more lines. Each line will contain a 1 or 0 representing an opening in the top, bottom, left, and right. All 1s and 0s must be separated by a space
