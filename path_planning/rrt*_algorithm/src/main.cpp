#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>

int window_size = 1000;
const int gridSize = 50;
int step_size = 5;
struct Point
{
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y)
    {
    }

    double distance(const Point &other) const
    {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }

    Point moveTowards(const Point &target, double step_size)
    {
        double dist = distance(target);
        if (dist < step_size)
        {
            return target;
        }
        double ratio = step_size / dist;
        double xNew = x + (target.x - x) * ratio;
        double yNew = y + (target.y - y) * ratio;
        return Point(xNew, yNew);
    }
};
std::vector<Point> tree;

Point nearestNeighbor(const Point& sample) {
        Point nearest = tree[0];  
        double min_distance = nearest.distance(sample); 

        for (const auto& node : tree) {
            double dist = node.distance(sample);
            if (dist < min_distance) {  
                nearest = node;
                min_distance = dist;
            }
        }
        return nearest;  
    }
Point randomSample()
{
    int x = rand()% gridSize; 
    int y = rand()% gridSize;
    std::cout<<x<<" x y "<<y<<std::endl;
    return Point(x, y);                                              
}
void printTree() {
        std::cout << "Tree Nodes:" << std::endl;
        for (const auto& node : tree) {
            std::cout << "(" << node.x << ", " << node.y << ")" << std::endl;
        }
    }

void rrt(std::vector<std::vector<sf::Color>> &grid, int gridSize, int i, int j, sf::Vector2f src_point, sf::Vector2f desr_point)
{

Point goal;
Point start;
start.x = src_point.x;
start.y = src_point.y;
goal.x = desr_point.x;
goal.y = desr_point.y;

    // Point start =(src_point.x, src_point.y);
    // Point goal =(desr_point.x, desr_point.y);


    tree.push_back(start); 
    //tree.push_back(goal);

    int reached_to_gole = false;
    int num_iterations = 0;
    while(!reached_to_gole){
    num_iterations++;
    Point curr_random_point = randomSample();
    // int x = curr_random_point.x;
    // int y = curr_random_point.y;
    //grid[x][y] = sf::Color(128, 128, 128, 255);
    if(curr_random_point.x > 50 || curr_random_point.x<0 || curr_random_point.y>50 ||curr_random_point.y<0) return;
    Point nearest = nearestNeighbor(curr_random_point);
    Point new_node = nearest.moveTowards(curr_random_point,step_size);
    tree.push_back(new_node);
    if(new_node.distance(goal)<step_size){
                reached_to_gole = true;
                std::cout<<"reatched to gole "<<num_iterations<<std::endl;
                //printTree();
            }
    sf::Vector2i curr_point{new_node.x, new_node.y};
    double x = new_node.x;
    double y = new_node.y;
    grid[x][y] = sf::Color::Blue;
    
}
     //printTree();
    return;
}

void drawLineBetweenPoints(sf::RenderWindow &window, const sf::Vector2f &start, const sf::Vector2f &end, int cellSize) {
    sf::VertexArray line(sf::Lines, 2);
    sf::Vertex startVertex(sf::Vector2f(start.x * cellSize + cellSize / 2, start.y * cellSize + cellSize / 2), sf::Color::Yellow);
    sf::Vertex goalVertex(sf::Vector2f(end.x * cellSize + cellSize / 2, end.y * cellSize + cellSize / 2), sf::Color::Yellow);
    
    line[0] = startVertex;
    line[1] = goalVertex;
    
    window.draw(line);
}

int main()
{

    sf::RenderWindow window(sf::VideoMode(window_size, window_size), "50x50 Grid");

    // const int gridSize = 50;
    const int cellSize = window_size / gridSize;
    int click_count = 0;
    sf::Vector2f first_click{-1, -1};
    sf::Vector2f second_click{-1, -1};

    std::vector<std::vector<sf::Color>> grid(gridSize, std::vector<sf::Color>(gridSize, sf::Color::White));

    sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
    cell.setOutlineColor(sf::Color::Black);
    cell.setOutlineThickness(1);
    sf::VertexArray line(sf::Lines, 2);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (click_count != 3)
                        click_count++;

                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    int col = mousePos.x / cellSize;
                    int row = mousePos.y / cellSize;

                    if (row < gridSize && col < gridSize)
                    {
                        std::cout << "Cell clicked: (" << row << ", " << col << ")\n";
                        if (click_count == 1)
                        {
                            grid[row][col] = sf::Color::Red;
                            first_click = {row, col};
                        }
                        else if (click_count == 2)
                        {
                            grid[row][col] = sf::Color::Green;
                            second_click = {row, col};
                        }
                        else
                        {
                            // Start DFS from the first clicked point
                            line[0].position = first_click;  // Start point
                            line[1].position = second_click;
                            line[0].color = sf::Color::Red;    // Color of the start point
                            line[1].color = sf::Color::Blue; 
                            rrt(grid, gridSize, first_click.x, first_click.y, first_click, second_click);
                        }
                    }
                }
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    // Reset the grid and click count
                    grid = std::vector<std::vector<sf::Color>>(gridSize, std::vector<sf::Color>(gridSize, sf::Color::White));
                    click_count = 0;
                    std::vector<Point> newTree;
                    tree = newTree;
                    std::cout << "Grid reset\n";
                }
            }
        }

        window.clear(sf::Color::Black);

        // Draw the grid with updated colors
        for (int row = 0; row < gridSize; ++row)
        {
            for (int col = 0; col < gridSize; ++col)
            {
                cell.setFillColor(grid[row][col]);
                cell.setPosition(col * cellSize, row * cellSize);
                window.draw(cell);
            }
        }
        window.draw(line);


        window.display();
    }

    return 0;
}
