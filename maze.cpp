#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include "mazeclass.h"

int main(int argc, char *argv[])
{
    try
    {
        if (argc != 3 && argc != 4)
        {
            throw std::invalid_argument("Please provide rows and columns as arguments.");
        }

        int numRows, numCols;
        int seed;

        if (argc == 3)
        {
            numRows = std::stoi(argv[1]);
            numCols = std::stoi(argv[2]);
            seed = time(nullptr);
        }
        else
        {
            numRows = std::stoi(argv[1]);
            numCols = std::stoi(argv[2]);
            seed = std::stoi(argv[3]);
        }

        if (numRows <= 0 || numCols <= 0)
        {
            throw std::invalid_argument("Rows and columns must be positive integers.");
        }

        Maze maze(numRows, numCols);

        srand(seed);

        maze.generateMaze();
        maze.findPath(0, 0, numRows - 1, numCols - 1);
        maze.printMaze();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}