#include <bits/stdc++.h>

/*


//  matrix


const int N = 10;
int graph[N][N];

int main(){
    int n,m; ///number of vertices and edge;
    int matrix[n+1][n+1];
    for(int i=0; i<m ; i++){
        int vertex1 ,vertex2;
        cin>>vertex1;
        cin>>vertex2;
        matrix[vertex1][vertex2] ==1;
        matrix[vertex2][vertex1] ==1;


    }


    return 0;
}

*/

// space complexity O(v+e); very optimal for the space complelixty;
// v2

#include <iostream>
#include <vector>
using namespace std;

class Graph
{
public:
    Graph(int vertices)
    {
        num_vertex = vertices;
        adjList.resize(vertices);
        visited.resize(vertices);
        vertex_levels.resize(vertices); // Resize the vector to have 'vertices' number of vectors and visited array
    }

    void addEdge(int u, int v)
    {
        adjList[u].push_back(v); // Add v to the list of neighbors for u
        adjList[v].push_back(u); // Add u to the list of neighbors for v (if graph is undirected)
    }

    void displayGraph()
    {
        for (int i = 0; i < adjList.size(); i++)
        {
            cout << "Vertex " << i << ": ";
            for (int neighbor : adjList[i])
            {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    void dfs(int vertex)
    {
        // Take action on the vertex after entering the vertex
        cout << "Entering vertex " << vertex << endl;
        if (visited[vertex] == 1)
            return; // If already visited, stop recursion
        visited[vertex] = 1;

        // Explore all the adjacent vertices (children)
        for (int child : adjList[vertex])
        {
            cout << "Parent: " << vertex << " Child: " << child << endl;

            // Take the action on the child before entering it
            if (visited[child] == 1)
            {
                continue; // Skip if child is already visited
            }

            dfs(child); // Recursive DFS call on the child

            // Take the action after exiting the child node (post-processing)
            cout << "Exiting child " << child << " from parent " << vertex << endl;
        }

        // Take the action on the vertex before exiting it
        cout << "Exiting vertex " << vertex << endl;
    }

    void bfs(int start_vertex)
    {
        // Reset the visited array before performing BFS
        fill(visited.begin(), visited.end(), 0);
        fill(vertex_levels.begin(), vertex_levels.end(), -1);
        vertex_levels[start_vertex] = 1;
        queue<int> q;              // Declare a queue to store the vertices to visit
        q.push(start_vertex);      // Start BFS from the given start_vertex
        visited[start_vertex] = 1; // Mark the start vertex as visited

        cout << "BFS Traversal starting from vertex " << start_vertex << ": "<<std::endl;

        while (!q.empty())
        {
            int curr_vertex = q.front(); // Get the front vertex from the queue
            q.pop();                     // Remove it from the queue

            cout << "Vertex: " << curr_vertex << " (Level: " << vertex_levels[curr_vertex] << ")" << endl;

            // Explore all the adjacent vertices (neighbors)
            for (int child_vertex : adjList[curr_vertex])
            {
                if (visited[child_vertex] != 1)
                {                              // If the child has not been visited
                    q.push(child_vertex);      // Add it to the queue
                    visited[child_vertex] = 1; // Mark it as visited
                    vertex_levels[child_vertex] = vertex_levels[curr_vertex]+1;
                }
            }
        }

        cout << endl; // Print a newline after BFS traversal
    }

private:
    int num_vertex;
    vector<vector<int>> adjList; // A vector of vectors to store the adjacency list
    vector<int> visited;         // visited array;
    vector<int> vertex_levels;  // level of the vertex
};

// dfs in the matrix formate
void dfs(vector<vector<int>> &v, vector<vector<int>> &visited, int i, int j)
{
    if (i < 0 || j < 0)
        return;
    if (i >= v.size() || j >= v[0].size())
        return;
    if (visited[i][j] == 1)
        return;
    visited[i][j] = 1;

    std::cout << "the value if " << i << "  " << j << " " << v[i][j] << std::endl;

    dfs(v, visited, i - 1, j);
    dfs(v, visited, i, j - 1);
    dfs(v, visited, i + 1, j);
    dfs(v, visited, i, j + 1);
}

int main()
{
    Graph g(15);

    // Adding edges to make the graph more complex
    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 6);
    g.addEdge(3, 4);
    g.addEdge(3, 7);
    g.addEdge(4, 5);
    g.addEdge(5, 6);
    g.addEdge(5, 8);
    g.addEdge(6, 9);
    g.addEdge(7, 8);
    g.addEdge(8, 10);
    g.addEdge(9, 11);
    g.addEdge(10, 12);
    g.addEdge(11, 13);
    g.addEdge(12, 14);
    g.addEdge(13, 14);

    // g.displayGraph(); // display the graph with for loop in  vector to vector

    /*  Vertex 0: 1 4
        Vertex 1: 0 2 3 5
        Vertex 2: 1 6
        Vertex 3: 1 4
        Vertex 4: 0 3 7
        Vertex 5: 1
        Vertex 6: 2 7
        Vertex 7: 6 4
    */
     //g.dfs(1);

    //    vector<vector<int>>v(10,vector<int>(10,0));
    //    srand(time(0));

    //    for(int i=0; i<10; i++){
    //     for(int j=0; j<10; j++){
    //         v[i][j] = rand() % 2;
    //         std::cout<<v[i][j];
    //     }
    //     std::cout<<endl;
    //    }
    //     vector<vector<int>>visited(10,vector<int>(10,0));
    //     dfs(v,visited,0,0);

    //     for(int i=0; i<10; i++){
    //     for(int j=0; j<10; j++){

    //         std::cout<<visited[i][j];
    //     }
    //     std::cout<<endl;
    //    }

    // g.bfs(0);

    return 0;
}
