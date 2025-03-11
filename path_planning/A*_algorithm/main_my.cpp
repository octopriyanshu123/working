#include <bits/stdc++.h>
using namespace std;

#define ROW 10
#define COL 10

typedef pair<int, int> Pair;
typedef pair<double, pair<int, int>> pPair;

struct cell
{
    int parent_i;
    int parent_j;
    double f;
    double g;
    double h;
};

// helper function
bool isValid(int row_index, int col_index)
{
    return row_index >= 0 && row_index < ROW && col_index >= 0 && col_index < COL;
}

bool isUnBlocked(int grid[ROW][COL], int row_index, int col_index)
{
    return grid[row_index][col_index] == 1;
}

bool isDestination(Pair first_pair, Pair sec_pair)
{
    return first_pair.first == sec_pair.first && first_pair.second == sec_pair.second;
}

// A Utility Function to calculate the 'h' heuristics.
double calculateHValue(int row, int col, Pair dest)
{
    return sqrt((row - dest.first) * (row - dest.first) + (col - dest.second) * (col - dest.second));
}

void tracePath(cell cellDetails[ROW][COL], Pair dest)
{
    printf("The path is: ");
    int row = dest.first;
    int col = dest.second;
    stack<Pair> path;

    while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col))
    {
        path.push(make_pair(row, col));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }

    path.push(make_pair(row, col));
    while (!path.empty())
    {
        Pair p = path.top();
        path.pop();
        printf("-> (%d,%d) ", p.first, p.second);
    }
    printf("\n");
}

void astar(int grid[ROW][COL], Pair src, Pair dest)
{
    if (!isValid(src.first, src.second) || !isValid(dest.first, dest.second))
    {
        printf("Source or Destination is out of range\n");
        return;
    }

    if (!isUnBlocked(grid, src.first, src.second) || !isUnBlocked(grid, dest.first, dest.second))
    {
        std::cout<<isUnBlocked(grid, dest.first, dest.second);
        printf("Source or Destination is blocked\n");
        return;
    }

    if (isDestination(src, dest))
    {
        printf("We are already at the destination\n");
        return;
    }

    bool closedList[ROW][COL];
    memset(closedList, false, sizeof(closedList));

    cell cellDetails[ROW][COL];
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }

    int i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;

    set<pPair> openList;
    openList.insert(make_pair(0.0, make_pair(i, j)));
    bool foundDest = false;

    vector<Pair> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {1, 1}, {1, -1}, {-1, 1}};

    while (!openList.empty())
    {
        pPair p = *openList.begin();
        openList.erase(openList.begin());

        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;

        double gNew, hNew, fNew;

        for (Pair direction : directions)
        {
            int new_i = i + direction.first;
            int new_j = j + direction.second;

            if (isValid(new_i, new_j) && !closedList[new_i][new_j] && isUnBlocked(grid, new_i, new_j))
            {
                if (isDestination(make_pair(new_i, new_j), dest))
                {
                    cellDetails[new_i][new_j].parent_i = i;
                    cellDetails[new_i][new_j].parent_j = j;
                    printf("The destination cell is found\n");
                    tracePath(cellDetails, dest);
                    foundDest = true;
                    return;
                }

                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(new_i, new_j, dest);
                fNew = gNew + hNew;

                if (cellDetails[new_i][new_j].f == FLT_MAX || cellDetails[new_i][new_j].f > fNew)
                {
                    openList.insert(make_pair(fNew, make_pair(new_i, new_j)));
                    cellDetails[new_i][new_j].f = fNew;
                    cellDetails[new_i][new_j].g = gNew;
                    cellDetails[new_i][new_j].h = hNew;
                    cellDetails[new_i][new_j].parent_i = i;
                    cellDetails[new_i][new_j].parent_j = j;
                }
            }
        }
    }

    if (!foundDest)
        printf("Failed to find the Destination Cell\n");
}

int main()
{
    int grid[ROW][COL] = {
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 0, 1, 1, 1, 0, 1, 1},
        {1, 1, 1, 0, 1, 1, 0, 1, 0, 1},
        {0, 0, 1, 0, 1, 0, 0, 0, 0, 1},
        {1, 1, 1, 0, 1, 1, 1, 0, 1, 0},
        {1, 0, 1, 1, 1, 1, 0, 1, 0, 0},
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 1, 0, 0, 1},
        {1, 1, 0, 0, 0, 1, 0, 0, 1, 1}};
    
    Pair src = make_pair(0, 0);
    Pair dest = make_pair(9, 9);
    
    astar(grid, src, dest);
    return 0;
}
