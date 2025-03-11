// #include <bits/stdc++.h>
// using namespace std;

// const int N = 1e5+10;
// const int INF = 1e9+10;

// vector<pair<int, int>> g[N];
// vector<int> parent(N, -1);

// void dijkstra(int source, int target) {
//     vector<int> vis(N, 0);
//     vector<int> dist(N, INF);
//     set<pair<int, int>> st;
//     st.insert({0, source});
//     dist[source] = 0;

//     while (!st.empty()) {
//         auto node = *st.begin();
//         int v = node.second;
//         int v_dist = node.first;
//         st.erase(st.begin());

//         if (vis[v]) continue;
//         vis[v] = 1;

//         for (auto child : g[v]) {
//             int child_v = child.first;
//             int wt = child.second;

//             if (dist[v] + wt < dist[child_v]) {
//                 dist[child_v] = dist[v] + wt;
//                 parent[child_v] = v;
//                 st.insert({dist[child_v], child_v});
//             }
//         }
//     }

//     if (dist[target] == INF) {
//         cout << "No path from node " << source << " to node " << target << "." << endl;
//     } else {
//         cout << "Shortest path distance from node " << source << " to node " << target << ": " << dist[target] << endl;

//         stack<int> path;
//         for (int v = target; v != -1; v = parent[v]) {
//             path.push(v);
//         }

//         cout << "Path: ";
//         while (!path.empty()) {
//             cout << path.top() << " ";
//             path.pop();
//         }
//         cout << endl;
//     }
// }

// ------------------------------------------------ On graph 


// #include <bits/stdc++.h>
// using namespace std;

// class Dijkstra {
// public:
//     // Accept a const pointer to graph and number of nodes
//     void initializeGraph(const vector<pair<int, int>>* input_graph, int n) {
//         graph = input_graph;  
//         num_nodes = n;
//     }

//     void findShortestPath(int source, int target) {
//         vector<int> dist(num_nodes + 1, INT_MAX);   // Distance from source to each node
//         vector<int> parent(num_nodes + 1, -1);      // To reconstruct the path
//         vector<bool> visited(num_nodes + 1, false); // To keep track of visited nodes

//         priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
//         pq.push({0, source}); // {cost, node}
//         dist[source] = 0;

//         while (!pq.empty()) {
//             int current_node = pq.top().second;
//             int current_dist = pq.top().first;
//             pq.pop();

//             if (visited[current_node]) continue; // Skip if already processed
//             visited[current_node] = true;

//             // Process neighbors
//             for (const auto& neighbor : graph[current_node]) {
//                 int neighbor_node = neighbor.first;
//                 int edge_weight = neighbor.second;

//                 if (dist[current_node] + edge_weight < dist[neighbor_node]) {
//                     dist[neighbor_node] = dist[current_node] + edge_weight;
//                     parent[neighbor_node] = current_node;
//                     pq.push({dist[neighbor_node], neighbor_node});
//                 }
//             }
//         }

//         // If there's no path to the target
//         if (dist[target] == INT_MAX) {
//             cout << "No path from node " << source << " to node " << target << endl;
//             return;
//         }

//         // Print shortest path distance
//         cout << "Shortest path distance from node " << source << " to node " << target << ": " << dist[target] << endl;

//         // Reconstruct and print the path
//         stack<int> path;
//         for (int node = target; node != -1; node = parent[node]) {
//             path.push(node);
//         }

//         cout << "Path: ";
//         while (!path.empty()) {
//             cout << path.top() << " ";
//             path.pop();
//         }
//         cout << endl;
//     }

// private:
//     const vector<pair<int, int>>* graph;  // Now graph is a const pointer
//     int num_nodes;                        // Total number of nodes
// };

// int main() {
//     int n = 10, m = 15;

//     vector<pair<int, int>> graph[n + 1]; // Graph initialized with n+1 (1-based index)

//     vector<tuple<int, int, int>> edges = {
//         {1, 2, 5}, {1, 3, 2}, {1, 4, 1}, {2, 4, 3}, {2, 5, 2},
//         {3, 5, 4}, {3, 6, 7}, {4, 6, 1}, {4, 7, 6}, {5, 7, 8},
//         {5, 8, 3}, {6, 8, 5}, {6, 9, 2}, {7, 10, 6}, {8, 10, 4}
//     };

//     // Build graph (adjacency list)
//     for (auto& edge : edges) {
//         int x, y, wt;
//         tie(x, y, wt) = edge;
//         graph[x].push_back({y, wt});
//         graph[y].push_back({x, wt});
//     }

//     Dijkstra dijkstra;
//     dijkstra.initializeGraph(graph, n);

//     int source = 1;
//     int target = 10;

//     dijkstra.findShortestPath(source, target);

//     return 0;
// }


// #include <bits/stdc++.h>
// using namespace std;

// class Dijkstra {
// public:
//     void initializeGrid(int n, int m) {
//         rows = n;
//         cols = m;
//         dist.resize(n, vector<int>(m, INT_MAX));  // Initialize distance matrix with infinity
//         parent.resize(n, vector<pair<int, int>>(m, {-1, -1}));  // Initialize parent matrix for path reconstruction
//         visited.resize(n, vector<bool>(m, false));  // To keep track of visited nodes
//     }

//     void findShortestPath(int start_x, int start_y, int target_x, int target_y) {
//         // Directions for moving in 4 possible ways (up, down, left, right)
//         vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1},{-1, -1}, {1, 1}, {1, -1}, {-1, 1}};

//         priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
//         pq.push({0, start_x, start_y}); // {distance, x, y}
//         dist[start_x][start_y] = 0;

//         while (!pq.empty()) {
//             int current_dist, x, y;
//             tie(current_dist, x, y) = pq.top();
//             pq.pop();

//             if (visited[x][y]) continue; // Skip if already visited
//             visited[x][y] = true;

//             // If we reach the target, stop
//             if (x == target_x && y == target_y) {
//                 break;
//             }

//             // Explore neighbors (4 directions)
//             for (auto& dir : directions) {
//                 int nx = x + dir.first, ny = y + dir.second;

//                 if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) { // Check if inside the grid
//                     int new_dist = current_dist + 1; // All edges have weight 1

//                     if (new_dist < dist[nx][ny]) {
//                         dist[nx][ny] = new_dist;
//                         parent[nx][ny] = {x, y};
//                         pq.push({new_dist, nx, ny});
//                     }
//                 }
//             }
//         }

//         // If we reach the target
//         if (dist[target_x][target_y] == INT_MAX) {
//             cout << "No path from (" << start_x << "," << start_y << ") to (" << target_x << "," << target_y << ")\n";
//             return;
//         }

//         cout << "Shortest path distance from (" << start_x << "," << start_y << ") to (" << target_x << "," << target_y << "): " << dist[target_x][target_y] << endl;

//         // Reconstruct and print the path
//         stack<pair<int, int>> path;
//         pair<int, int> p = {target_x, target_y};
//         while (p != make_pair(start_x, start_y)) {
//             path.push(p);
//             p = parent[p.first][p.second];
//         }
//         path.push({start_x, start_y});

//         cout << "Path: ";
//         while (!path.empty()) {
//             pair<int, int> cell = path.top();
//             path.pop();
//             cout << "(" << cell.first << ", " << cell.second << ") ";
//         }
//         cout << endl;
//     }

// private:
//     int rows, cols;  // Grid dimensions
//     vector<vector<int>> dist;  // Distance matrix
//     vector<vector<pair<int, int>>> parent;  // Parent matrix for path reconstruction
//     vector<vector<bool>> visited;  // Visited matrix
// };

// int main() {
//     int n = 10, m = 5; // Grid dimensions (5x5)

//     Dijkstra dijkstra;
//     dijkstra.initializeGrid(n, m);

//     // Example: Find shortest path from (0,0) to (4,4)
//     int start_x = 0, start_y = 0;
//     int target_x = 6, target_y = 4;

//     dijkstra.findShortestPath(start_x, start_y, target_x, target_y);

//     return 0;
// }


#include <bits/stdc++.h>
using namespace std;

class Dijkstra {
public:
    void initializeGrid(int n, int m) {
        rows = n;
        cols = m;
        
        // Initialize distance matrix with infinity
        dist.resize(n, vector<int>(m, INT_MAX));
        parent.resize(n, vector<pair<int, int>>(m, {-1, -1}));
        visited.resize(n, vector<bool>(m, false));
        
        // Initialize cost matrix with random costs (1 to 9)
        cost.resize(n, vector<int>(m));
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, 9);
        
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cost[i][j] = dis(gen);  
            }
        }
        //
    }

    void findShortestPath(int start_x, int start_y, int target_x, int target_y) {
        // Movement Vector All four direction;
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {1, 1}, {1, -1}, {-1, 1}};
        
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
        pq.push({0, start_x, start_y});
        dist[start_x][start_y] = 0;

        while (!pq.empty()) {
            int current_dist, x, y;
            tie(current_dist, x, y) = pq.top();
            pq.pop();

            if (visited[x][y]) continue;
            visited[x][y] = true;

            // If we reach the target, stop
            if (x == target_x && y == target_y) {
                break;
            }

            // Explore neighbors (all 8 directions)
            for (auto& dir : directions) {
                int nx = x + dir.first, ny = y + dir.second;

                if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) { //Check the next x and y is valid
                    int new_dist = current_dist + cost[nx][ny];  // Add the cost of the neighboring cell

                    if (new_dist < dist[nx][ny]) {
                        dist[nx][ny] = new_dist;
                        parent[nx][ny] = {x, y};
                        pq.push({new_dist, nx, ny});
                    }
                }
            }
        }

        // If we reach the target
        if (dist[target_x][target_y] == INT_MAX) {
            cout << "No path from (" << start_x << "," << start_y << ") to (" << target_x << "," << target_y << ")\n";
            return;
        }

        cout << "Shortest path distance from (" << start_x << "," << start_y << ") to (" << target_x << "," << target_y << "): " << dist[target_x][target_y] << endl;

        // Reconstruct and print the path
        stack<pair<int, int>> path;
        pair<int, int> p = {target_x, target_y};
        while (p != make_pair(start_x, start_y)) {
            path.push(p);
            p = parent[p.first][p.second];
        }
        path.push({start_x, start_y});

        cout << "Path: ";
        while (!path.empty()) {
            pair<int, int> cell = path.top();
            path.pop();
            cout << "(" << cell.first << ", " << cell.second << ") ";
        }
        cout << endl;
    }

    void printCostMatrix() {
        cout << "Cost Matrix:\n";
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << cost[i][j] << " ";
            }
            cout << endl;
        }
    }

private:
    int rows, cols;  // Grid dimensions
    vector<vector<int>> dist;  // Distance matrix
    vector<vector<pair<int, int>>> parent;  // Parent matrix for path reconstruction
    vector<vector<bool>> visited;  // Visited matrix
    vector<vector<int>> cost;  // Cost matrix with random costs
};

int main() {
    int n = 10, m = 5; // Grid dimensions (10x5)

    Dijkstra dijkstra;
    dijkstra.initializeGrid(n, m);

    // Example: Find shortest path from (0,0) to (6,4)
    int start_x = 0, start_y = 0;
    int target_x = 9, target_y = 4;

    dijkstra.printCostMatrix();  // Print the randomly generated cost matrix
    dijkstra.findShortestPath(start_x, start_y, target_x, target_y);

    return 0;
}
