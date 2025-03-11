// #include <iostream>
// #include <cmath>
// #include <list>
// #include <vector>
// #include <algorithm>

// class Vector2
// {
//     int x, y;
// public:
//     Vector2(int _x, int _y) : x(_x), y(_y) {}
//     Vector2() = default;
//     Vector2 operator +(const Vector2& other) {
//         Vector2 temp;
//         temp.x = this->x + other.x;
//         temp.y = this->y + other.y;
//         return temp;
//     }
//     int getX() const { return x; }
//     int getY() const { return y; }

//     friend class Map;
// };

// struct Node
// {
//     Vector2 position;
//     int G, H, F;
//     Node* parent = nullptr;

//     Node() = default;
//     Node(const Node& other) = default;
//     Node(Vector2 pos):position(pos) {};

//     void calc(const Vector2& endPos) {
//         H = static_cast<int>((abs(static_cast<double>(position.getX() - endPos.getX())) + abs(static_cast<double>(position.getY() - endPos.getY()))));
//         G = parent ? parent->G + 1 : 1;
//         F = G + H;
//     }

//     bool operator==(const Node& other) const {
//         return (position.getX() == other.position.getX() && position.getY() == other.position.getY()); 
//     }
//     bool operator!=(const Node& other) const {
//         return !(*this == other);
//     }
//     bool operator<(const Node& other)  const {
//         return(F < other.F);
//     }
// };

// class Map
// {
//     std::vector<char> data;
//     int size;
// public:
//     Map() = default;
//     Map(int _size) : size(_size) {
//         data.resize(size * size);
//         for (int i = 0; i < size * size; ++i) data[i] = '.';
//     }
//     void display() const{
//         for (int i = 1; i <= size * size; ++i) {
//             std::cout << data[i - 1] << " ";
//             if (!(i % size)) std::cout << "\n";
//         }
//     }
//     bool getIfInDanger(Vector2 position) const {
//         if (position.y < 0) position.y = 0;
//         if (position.x < 0) position.x = 0;
//         if (position.y >= 20) position.y = size - 1;
//         if (position.x >= 20) position.x = size - 1;
//         return(data[position.getX() + (position.getY() * size)] == 'X');
//     }
//     void setElement(char&& asda, Vector2 position) {
//         data[position.getX() + (position.getY() * size)] = asda;
//     }
// };

// class Solver
// {
//     Vector2 startPos, endPos;
//     std::vector<Vector2> directions;
//     Map map;
// public:
//     Solver(Vector2 _startPos, Vector2 _endPos, int size) : startPos(_startPos), endPos(_endPos){
//         Map temp(size);
//         map = temp;

//         map.setElement('X', Vector2(14, 15));
//         map.setElement('X',Vector2(15,15));
//         map.setElement('X', Vector2(16, 15));
//         map.setElement('X', Vector2(16, 14));
//         map.setElement('X', Vector2(16, 13));
//         map.setElement('X', Vector2(16, 12));
//         map.setElement('X', Vector2(15, 12));
//         map.setElement('X', Vector2(14, 12));
//         map.setElement('X', Vector2(13, 12));
//         map.setElement('X', Vector2(12, 12));
//         map.setElement('X', Vector2(12, 13));
//         map.setElement('X', Vector2(9, 13));
//         map.setElement('X', Vector2(11, 13));
//         map.setElement('X', Vector2(10, 13));
//         map.setElement('X', Vector2(12, 14));
//         map.setElement('X', Vector2(12, 15));

//         directions.resize(8);
//         directions[0] = Vector2(-1, 1);
//         directions[1] = Vector2(-1, 0);
//         directions[2] = Vector2(-1, -1);
//         directions[3] = Vector2(0, 1);
//         directions[4] = Vector2(0, -1);
//         directions[5] = Vector2(1, 1);
//         directions[6] = Vector2(1, 0);
//         directions[7] = Vector2(1, -1);
//     }
//     bool aStar() {
//         Node startNode(startPos);
//         Node goalNode(Vector2(endPos.getX(), endPos.getY()));

//         if (map.getIfInDanger(startNode.position) || map.getIfInDanger(goalNode.position)) {
//             std::cout << "Either the start of this map is obstructed or so is the end.";
//             return false;
//         }

//         std::list<Node> openList;
//         std::list<Node> closedList;

//         startNode.calc(endPos);
//         openList.push_back(startNode);

//         while (!openList.empty()) {
//             auto current = Node(*std::min_element(openList.begin(), openList.end()));

//             current.calc(endPos);

//             closedList.push_back(current);
//             openList.remove(current);
//             if (current == goalNode) break;

//             for (auto& direction : directions) {
//                 Node successor(direction + current.position);

//                 if (map.getIfInDanger(successor.position) || successor.position.getX() > 20 - 1 || 
//                     successor.position.getY() > 20 - 1 || successor.position.getX() < 0 || 
//                     successor.position.getY() < 0 ||
//                     std::find(closedList.begin(), closedList.end(), successor) != closedList.end()) {
//                     continue;
//                 }

//                 successor.calc(endPos);

//                 auto inOpen = std::find(openList.begin(), openList.end(), successor);
//                 if (inOpen == openList.end()) {
//                     successor.parent = &closedList.back();
//                     successor.calc(endPos);

//                     openList.push_back(successor);
//                 }
//                 else
//                     if (successor.G < inOpen->G) successor.parent = &closedList.back();
//             }
//         }

//         if (!openList.size()) {
//             std::cout << "No path has been found\n";
//             return false;
//         }

//         auto inClosed = std::find(closedList.begin(), closedList.end(), goalNode);
//         if (inClosed != closedList.end()) {
//             while (*inClosed != startNode) {
//                 map.setElement('Y',inClosed->position);
//                 *inClosed = *inClosed->parent;
//             }
//         }

//         map.display();
//         return true;
//     }
// };

// int main()
// {
//     Solver solve(Vector2(0,0),Vector2(19,19), 20);
//     solve.aStar();
// }
// #include <iostream>
// #include <vector>
// #include <queue>
// #include <unordered_set>
// #include <cmath>
// #include <functional>
// #include <algorithm>  // For std::reverse

// // Define a structure for the node
// struct Node {
//     int x, y;        // Node position
//     float g, h, f;   // Costs: g (path cost), h (heuristic), f (g + h)
//     Node* parent;    // Pointer to the parent node

//     Node(int x, int y) : x(x), y(y), g(0), h(0), f(0), parent(nullptr) {}

//     // For the priority queue, we need to define the comparison operator based on f value.
//     bool operator>(const Node& other) const {
//         return f > other.f;
//     }

//     // Equality comparison for checking presence in the open list
//     bool operator==(const Node& other) const {
//         return x == other.x && y == other.y;
//     }

//     // Hash function for unordered_set (used in openListSet)
//     struct Hash {
//         size_t operator()(const Node* node) const {
//             return std::hash<int>()(node->x) ^ std::hash<int>()(node->y);
//         }
//     };
// };

// // Calculate heuristic (Manhattan distance for grid-based A* search)
// float heuristic(const Node* a, const Node* b) {
//     return std::abs(a->x - b->x) + std::abs(a->y - b->y);
// }

// // Reconstruct the path from the goal to the start
// std::vector<Node*> reconstructPath(Node* goal) {
//     std::vector<Node*> path;
//     Node* current = goal;
//     while (current != nullptr) {
//         path.push_back(current);
//         current = current->parent;
//     }
//     std::reverse(path.begin(), path.end());  // Reverse the path to get it from start to goal
//     return path;
// }

// // A* algorithm implementation
// std::vector<Node*> AStar(Node* start, Node* goal, const std::vector<std::vector<int>>& grid) {
//     // Open list (priority queue) - ordered by f value
//     std::priority_queue<Node*, std::vector<Node*>, std::greater<Node*>> openList;

//     // Set to track nodes in the open list
//     std::unordered_set<Node*, Node::Hash> openListSet;

//     // Closed list (set of visited nodes)
//     std::unordered_set<Node*, Node::Hash> closedList;

//     // Initialize start node
//     start->g = 0;
//     start->h = heuristic(start, goal);
//     start->f = start->g + start->h;
//     openList.push(start);
//     openListSet.insert(start);

//     // Direction vectors for 4 possible moves (up, down, left, right)
//     std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

//     while (!openList.empty()) {
//         Node* current = openList.top();
//         openList.pop();
//         openListSet.erase(current);  // Remove the node from the open list set

//         // If we reached the goal, reconstruct the path
//         if (current == goal) {
//             return reconstructPath(current);
//         }

//         // Move the current node to the closed list
//         closedList.insert(current);

//         // Explore neighbors
//         for (auto& direction : directions) {
//             int newX = current->x + direction.first;
//             int newY = current->y + direction.second;

//             // Check if the new position is within bounds and walkable (0 indicates open space)
//             if (newX >= 0 && newX < grid.size() && newY >= 0 && newY < grid[0].size() && grid[newX][newY] == 0) {
//                 Node* neighbor = new Node(newX, newY);

//                 // If the neighbor is in the closed list, skip it
//                 if (closedList.find(neighbor) != closedList.end()) {
//                     continue;
//                 }

//                 // Calculate the tentative g value
//                 float tentativeG = current->g + 1; // Assuming uniform cost of 1 between nodes

//                 // If the neighbor is not in the open list or we found a shorter path
//                 if (openListSet.find(neighbor) == openListSet.end() || tentativeG < neighbor->g) {
//                     neighbor->g = tentativeG;
//                     neighbor->h = heuristic(neighbor, goal);
//                     neighbor->f = neighbor->g + neighbor->h;
//                     neighbor->parent = current;

//                     // Add the neighbor to the open list and set
//                     openList.push(neighbor);
//                     openListSet.insert(neighbor);
//                 }
//             }
//         }
//     }

//     return {}; // Return an empty path if no solution is found
// }

// int main() {
//     // Define the grid (0 = open space, 1 = obstacle)
//     std::vector<std::vector<int>> grid = {
//         {0, 0, 0, 0, 0},
//         {0, 1, 1, 0, 0},
//         {0, 0, 0, 1, 0},
//         {0, 1, 1, 1, 0},
//         {0, 0, 0, 0, 0}
//     };

//     // Define start and goal nodes
//     Node* start = new Node(0, 0);
//     Node* goal = new Node(4, 4);

//     // Call A* to find the path
//     std::vector<Node*> path = AStar(start, goal, grid);

//     // Print the result path
//     if (!path.empty()) {
//         std::cout << "Path found:\n";
//         for (auto* node : path) {
//             std::cout << "(" << node->x << ", " << node->y << ")\n";
//         }
//     } else {
//         std::cout << "No path found.\n";
//     }

//     // Clean up memory
//     delete start;
//     delete goal;

//     return 0;
// }



#include <bits/stdc++.h>
using namespace std;

#define ROW 9
#define COL 10

// Creating a shortcut for int, int pair type
typedef pair<int, int> Pair;

// Creating a shortcut for pair<int, pair<int, int>> type
typedef pair<double, pair<int, int> > pPair;

// A structure to hold the necessary parameters
struct cell {
    // Row and Column index of its parent
    // Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
    int parent_i, parent_j;
    // f = g + h
    double f, g, h;
};

// A Utility Function to check whether given cell (row, col) is a valid cell or not.
bool isValid(int row, int col)
{
    // Returns true if row number and column number is in range
    return (row >= 0) && (row < ROW) && (col >= 0)
           && (col < COL);
}

// A Utility Function to check whether the given cell is blocked or not
bool isUnBlocked(int grid[][COL], int row, int col)
{
    // Returns true if the cell is not blocked else false
    if (grid[row][col] == 1)
        return (true);
    else
        return (false);
}

// A Utility Function to check whether destination cell has been reached or not
bool isDestination(int row, int col, Pair dest)
{
    if (row == dest.first && col == dest.second)
        return (true);
    else
        return (false);
}

// A Utility Function to calculate the 'h' heuristics.
double calculateHValue(int row, int col, Pair dest)
{
    // Return using the distance formula
    return ((double)sqrt((row - dest.first) * (row - dest.first)+ (col - dest.second) * (col - dest.second)));
}

// A Utility Function to trace the path from the source to destination
void tracePath(cell cellDetails[][COL], Pair dest)
{
    printf("\nThe Path is ");
    int row = dest.first;
    int col = dest.second;

    stack<Pair> Path;

    while (!(cellDetails[row][col].parent_i == row
             && cellDetails[row][col].parent_j == col)) {
        Path.push(make_pair(row, col));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }

    Path.push(make_pair(row, col));
    while (!Path.empty()) {
        pair<int, int> p = Path.top();
        Path.pop();
        printf("-> (%d,%d) ", p.first, p.second);
    }

    return;
}

// A Function to find the shortest path between a given source cell to a destination cell according to A* Search Algorithm
void aStarSearch(int grid[][COL], Pair src, Pair dest)
{
    // If the source is out of range
    if (isValid(src.first, src.second) == false) {
        printf("Source is invalid\n");
        return;
    }

    // If the destination is out of range
    if (isValid(dest.first, dest.second) == false) {
        printf("Destination is invalid\n");
        return;
    }

    // Either the source or the destination is blocked
    if (isUnBlocked(grid, src.first, src.second) == false
        || isUnBlocked(grid, dest.first, dest.second)
               == false) {
        printf("Source or the destination is blocked\n");
        return;
    }

    // If the destination cell is the same as source cell
    if (isDestination(src.first, src.second, dest)
        == true) {
        printf("We are already at the destination\n");
        return;
    }

    // Create a closed list and initialise it to false which means that no cell has been included yet This closed list is implemented as a boolean 2D array
    bool closedList[ROW][COL];
    memset(closedList, false, sizeof(closedList));

    // Declare a 2D array of structure to hold the details of that cell
    cell cellDetails[ROW][COL];

    int i, j;

    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }

    // Initialising the parameters of the starting node
    i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;

    /*
     Create an open list having information as-
     <f, <i, j>>
     where f = g + h,
     and i, j are the row and column index of that cell
     Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
     This open list is implemented as a set of pair of
     pair.*/
    set<pPair> openList;

    // Put the starting cell on the open list and set its 'f' as 0
    openList.insert(make_pair(0.0, make_pair(i, j)));

    // We set this boolean value as false as initially the destination is not reached.
    bool foundDest = false;

    while (!openList.empty()) {
        pPair p = *openList.begin();

        // Remove this vertex from the open list
        openList.erase(openList.begin());

        // Add this vertex to the closed list
        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;

        /*
         Generating all the 8 successor of this cell

             N.W   N   N.E
               \   |   /
                \  |  /
             W----Cell----E
                  / | \
                /   |  \
             S.W    S   S.E

         Cell-->Popped Cell (i, j)
         N -->  North       (i-1, j)
         S -->  South       (i+1, j)
         E -->  East        (i, j+1)
         W -->  West           (i, j-1)
         N.E--> North-East  (i-1, j+1)
         N.W--> North-West  (i-1, j-1)
         S.E--> South-East  (i+1, j+1)
         S.W--> South-West  (i+1, j-1)*/

        // To store the 'g', 'h' and 'f' of the 8 successors
        double gNew, hNew, fNew;

        //----------- 1st Successor (North) ------------

        // Only process this cell if this is a valid one
        if (isValid(i - 1, j) == true) {
            // If the destination cell is the same as the current successor
            if (isDestination(i - 1, j, dest) == true) {
                // Set the Parent of the destination cell
                cellDetails[i - 1][j].parent_i = i;
                cellDetails[i - 1][j].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
            // If the successor is already on the closed list or if it is blocked, then ignore it. Else do the following
            else if (closedList[i - 1][j] == false && isUnBlocked(grid, i - 1, j)== true) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i - 1, j, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to the open list. 
                // Make the current square the parent of this square.
                // Record the f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, 
                // Check to see if this path to that square is better, using 'f' cost as the measure.
                if (cellDetails[i - 1][j].f == FLT_MAX || cellDetails[i - 1][j].f > fNew) {
                    openList.insert(make_pair(fNew, make_pair(i - 1, j)));
                    // Update the details of this cell
                    cellDetails[i - 1][j].f = fNew;
                    cellDetails[i - 1][j].g = gNew;
                    cellDetails[i - 1][j].h = hNew;
                    cellDetails[i - 1][j].parent_i = i;
                    cellDetails[i - 1][j].parent_j = j;
                }
            }
        }

        //----------- 2nd Successor (South) ------------

        // Only process this cell if this is a valid one
        if (isValid(i + 1, j) == true) {
            // If the destination cell is the same as the
            // current successor
            if (isDestination(i + 1, j, dest) == true) {
                // Set the Parent of the destination cell
                cellDetails[i + 1][j].parent_i = i;
                cellDetails[i + 1][j].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i + 1][j] == false
                     && isUnBlocked(grid, i + 1, j)
                            == true) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i + 1, j, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i + 1][j].f == FLT_MAX
                    || cellDetails[i + 1][j].f > fNew) {
                    openList.insert(make_pair(
                        fNew, make_pair(i + 1, j)));
                    // Update the details of this cell
                    cellDetails[i + 1][j].f = fNew;
                    cellDetails[i + 1][j].g = gNew;
                    cellDetails[i + 1][j].h = hNew;
                    cellDetails[i + 1][j].parent_i = i;
                    cellDetails[i + 1][j].parent_j = j;
                }
            }
        }

        //----------- 3rd Successor (East) ------------

        // Only process this cell if this is a valid one
        if (isValid(i, j + 1) == true) {
            // If the destination cell is the same as the
            // current successor
            if (isDestination(i, j + 1, dest) == true) {
                // Set the Parent of the destination cell
                cellDetails[i][j + 1].parent_i = i;
                cellDetails[i][j + 1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }

            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i][j + 1] == false
                     && isUnBlocked(grid, i, j + 1)
                            == true) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j + 1, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i][j + 1].f == FLT_MAX
                    || cellDetails[i][j + 1].f > fNew) {
                    openList.insert(make_pair(
                        fNew, make_pair(i, j + 1)));

                    // Update the details of this cell
                    cellDetails[i][j + 1].f = fNew;
                    cellDetails[i][j + 1].g = gNew;
                    cellDetails[i][j + 1].h = hNew;
                    cellDetails[i][j + 1].parent_i = i;
                    cellDetails[i][j + 1].parent_j = j;
                }
            }
        }

        //----------- 4th Successor (West) ------------

        // Only process this cell if this is a valid one
        if (isValid(i, j - 1) == true) {
            // If the destination cell is the same as the
            // current successor
            if (isDestination(i, j - 1, dest) == true) {
                // Set the Parent of the destination cell
                cellDetails[i][j - 1].parent_i = i;
                cellDetails[i][j - 1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }

            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i][j - 1] == false
                     && isUnBlocked(grid, i, j - 1)
                            == true) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j - 1, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i][j - 1].f == FLT_MAX
                    || cellDetails[i][j - 1].f > fNew) {
                    openList.insert(make_pair(
                        fNew, make_pair(i, j - 1)));

                    // Update the details of this cell
                    cellDetails[i][j - 1].f = fNew;
                    cellDetails[i][j - 1].g = gNew;
                    cellDetails[i][j - 1].h = hNew;
                    cellDetails[i][j - 1].parent_i = i;
                    cellDetails[i][j - 1].parent_j = j;
                }
            }
        }

        //----------- 5th Successor (North-East)
        //------------

        // Only process this cell if this is a valid one
        if (isValid(i - 1, j + 1) == true) {
            // If the destination cell is the same as the
            // current successor
            if (isDestination(i - 1, j + 1, dest) == true) {
                // Set the Parent of the destination cell
                cellDetails[i - 1][j + 1].parent_i = i;
                cellDetails[i - 1][j + 1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }

            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i - 1][j + 1] == false
                     && isUnBlocked(grid, i - 1, j + 1)
                            == true) {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i - 1, j + 1, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i - 1][j + 1].f == FLT_MAX
                    || cellDetails[i - 1][j + 1].f > fNew) {
                    openList.insert(make_pair(
                        fNew, make_pair(i - 1, j + 1)));

                    // Update the details of this cell
                    cellDetails[i - 1][j + 1].f = fNew;
                    cellDetails[i - 1][j + 1].g = gNew;
                    cellDetails[i - 1][j + 1].h = hNew;
                    cellDetails[i - 1][j + 1].parent_i = i;
                    cellDetails[i - 1][j + 1].parent_j = j;
                }
            }
        }

        //----------- 6th Successor (North-West)
        //------------

        // Only process this cell if this is a valid one
        if (isValid(i - 1, j - 1) == true) {
            // If the destination cell is the same as the
            // current successor
            if (isDestination(i - 1, j - 1, dest) == true) {
                // Set the Parent of the destination cell
                cellDetails[i - 1][j - 1].parent_i = i;
                cellDetails[i - 1][j - 1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }

            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i - 1][j - 1] == false
                     && isUnBlocked(grid, i - 1, j - 1)
                            == true) {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i - 1, j - 1, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i - 1][j - 1].f == FLT_MAX
                    || cellDetails[i - 1][j - 1].f > fNew) {
                    openList.insert(make_pair(
                        fNew, make_pair(i - 1, j - 1)));
                    // Update the details of this cell
                    cellDetails[i - 1][j - 1].f = fNew;
                    cellDetails[i - 1][j - 1].g = gNew;
                    cellDetails[i - 1][j - 1].h = hNew;
                    cellDetails[i - 1][j - 1].parent_i = i;
                    cellDetails[i - 1][j - 1].parent_j = j;
                }
            }
        }

        //----------- 7th Successor (South-East)
        //------------

        // Only process this cell if this is a valid one
        if (isValid(i + 1, j + 1) == true) {
            // If the destination cell is the same as the
            // current successor
            if (isDestination(i + 1, j + 1, dest) == true) {
                // Set the Parent of the destination cell
                cellDetails[i + 1][j + 1].parent_i = i;
                cellDetails[i + 1][j + 1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }

            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i + 1][j + 1] == false
                     && isUnBlocked(grid, i + 1, j + 1)
                            == true) {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i + 1, j + 1, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i + 1][j + 1].f == FLT_MAX
                    || cellDetails[i + 1][j + 1].f > fNew) {
                    openList.insert(make_pair(
                        fNew, make_pair(i + 1, j + 1)));

                    // Update the details of this cell
                    cellDetails[i + 1][j + 1].f = fNew;
                    cellDetails[i + 1][j + 1].g = gNew;
                    cellDetails[i + 1][j + 1].h = hNew;
                    cellDetails[i + 1][j + 1].parent_i = i;
                    cellDetails[i + 1][j + 1].parent_j = j;
                }
            }
        }

        //----------- 8th Successor (South-West)
        //------------

        // Only process this cell if this is a valid one
        if (isValid(i + 1, j - 1) == true) {
            // If the destination cell is the same as the
            // current successor
            if (isDestination(i + 1, j - 1, dest) == true) {
                // Set the Parent of the destination cell
                cellDetails[i + 1][j - 1].parent_i = i;
                cellDetails[i + 1][j - 1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }

            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i + 1][j - 1] == false
                     && isUnBlocked(grid, i + 1, j - 1)
                            == true) {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i + 1, j - 1, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i + 1][j - 1].f == FLT_MAX
                    || cellDetails[i + 1][j - 1].f > fNew) {
                    openList.insert(make_pair(
                        fNew, make_pair(i + 1, j - 1)));

                    // Update the details of this cell
                    cellDetails[i + 1][j - 1].f = fNew;
                    cellDetails[i + 1][j - 1].g = gNew;
                    cellDetails[i + 1][j - 1].h = hNew;
                    cellDetails[i + 1][j - 1].parent_i = i;
                    cellDetails[i + 1][j - 1].parent_j = j;
                }
            }
        }
    }

    // When the destination cell is not found and the open list is empty, 
    // then we conclude that we failed to reach the destination cell. 
    // This may happen when the there is no way to destination cell (due to blockages)
    if (foundDest == false)
        printf("Failed to find the Destination Cell\n");

    return;
}

// Driver program to test above function
int main()
{
    /* Description of the Grid-
     1--> The cell is not blocked
     0--> The cell is blocked    */
    int grid[ROW][COL]
        = { { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
            { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
            { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
            { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
            { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
            { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
            { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
            { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
            { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 } };

    // Source is the left-most bottom-most corner
    Pair src = make_pair(8, 0);

    // Destination is the left-most top-most corner
    Pair dest = make_pair(0, 0);

    aStarSearch(grid, src, dest);

    return (0);
}