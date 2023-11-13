#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>

class Cell
{
public:
    bool visited;
    bool wallUp, wallRight, wallDown, wallLeft;
    bool isPath;

    Cell()
    {
        visited = false;
        wallUp = true;
        wallRight = true;
        wallDown = true;
        wallLeft = true;
        isPath = false;
    }

    void visit() { visited = true; }
    void addToPath() { isPath = true; }
};

class Maze
{
public:
    int rows, cols;
    std::vector<std::vector<Cell>> grid;

    Maze(int numRows, int numCols) : rows(numRows), cols(numCols)
    {
        grid.resize(rows, std::vector<Cell>(cols));
    }

    bool isValid(int x, int y)
    {
        return x >= 0 && y >= 0 && x < rows && y < cols;
    }

    bool findPath(int startX, int startY, int endX, int endY)
    {
        if (startX == endX && startY == endY)
        {
            grid.at(startX).at(startY).addToPath();
            return true;
        }

        grid.at(startX).at(startY).visit();

        std::vector<int> dx = {-1, 0, 1, 0};
        std::vector<int> dy = {0, 1, 0, -1};

        for (int i = 0; i < 4; i++)
        {
            int newX = startX + dx.at(i);
            int newY = startY + dy.at(i);

            if (isValid(newX, newY) &&
                !grid.at(newX).at(newY).visited &&
                !getCellWall(startX, startY, i))
            {
                if (findPath(newX, newY, endX, endY))
                {
                    grid.at(startX).at(startY).addToPath();
                    return true;
                }
            }
        }

        return false;
    }

    bool getCellWall(int x, int y, int dir)
    {
        if (dir == 0)
            return grid.at(x).at(y).wallUp;
        if (dir == 1)
            return grid.at(x).at(y).wallRight;
        if (dir == 2)
            return grid.at(x).at(y).wallDown;
        if (dir == 3)
            return grid.at(x).at(y).wallLeft;
        return false;
    }

    void generateMaze()
    {
        std::stack<std::pair<int, int>> stack;
        int startX = 0, startY = 0;
        stack.push({startX, startY});
        grid.at(startX).at(startY).visit();

        std::vector<std::pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

        while (!stack.empty())
        {
            int x = stack.top().first, y = stack.top().second;
            stack.pop();

            std::vector<int> validDirs;

            for (int i = 0; i < 4; i++)
            {
                int newX = x + directions.at(i).first;
                int newY = y + directions.at(i).second;

                if (isValid(newX, newY) &&
                    !grid.at(newX).at(newY).visited)
                {
                    validDirs.push_back(i);
                }
            }

            if (!validDirs.empty())
            {
                stack.push({x, y});
                int randomIndex = rand() % validDirs.size();
                int dir = validDirs.at(randomIndex);

                int newX = x + directions.at(dir).first;
                int newY = y + directions.at(dir).second;

                setCellWall(x, y, dir, false);
                setCellWall(newX, newY, (dir + 2) % 4, false);

                stack.push({newX, newY});
                grid.at(newX).at(newY).visit();
            }
        }

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                grid.at(i).at(j).visited = false;
            }
        }
    }

    void setCellWall(int x, int y, int dir, bool value)
    {
        if (dir == 0)
            grid.at(x).at(y).wallUp = value;
        if (dir == 1)
            grid.at(x).at(y).wallRight = value;
        if (dir == 2)
            grid.at(x).at(y).wallDown = value;
        if (dir == 3)
            grid.at(x).at(y).wallLeft = value;
    }

    void printMaze()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                std::cout << "+";
                std::cout << (getCellWall(i, j, 0) ? "---" : "   ");
            }
            std::cout << "+" << std::endl;

            for (int j = 0; j < cols; j++)
            {
                std::cout << (getCellWall(i, j, 3) ? "|" : " ");
                std::cout << (grid.at(i).at(j).isPath ? " . " : "   ");
            }
            std::cout << "|" << std::endl;
        }

        for (int j = 0; j < cols; j++)
        {
            std::cout << "+---";
        }
        std::cout << "+" << std::endl;
    }
};
