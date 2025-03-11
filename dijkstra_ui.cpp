#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

int main() {
    int window_size = 1000;
    sf::RenderWindow window(sf::VideoMode(window_size, window_size), "50x50 Grid");

    const int gridSize = 50;
    const int cellSize = window_size / gridSize;
    int click_count = 0;
    sf::Vector2i first_click{-1, -1};
    sf::Vector2i second_click{-1, -1};
    int level = 1;

    std::vector<std::vector<sf::Color>> grid(gridSize, std::vector<sf::Color>(gridSize, sf::Color::White));

    sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
    cell.setOutlineColor(sf::Color::Black);
    cell.setOutlineThickness(1);
    sf::VertexArray line(sf::Lines);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (click_count != 3) click_count++;
                    
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    int col = mousePos.x / cellSize;
                    int row = mousePos.y / cellSize;


                    if (row < gridSize && col < gridSize) {
                        std::cout << "Cell clicked: (" << row << ", " << col << ")\n";
                        if (click_count == 1) {
                            grid[row][col] = sf::Color::Red;
                            first_click = {row, col};
                        } else if (click_count == 2) {
                            grid[row][col] = sf::Color::Green;
                            second_click = {row, col};
                        } else {
                            std::cout <<level;
                            // line.clear();
                            // line.append(sf::Vertex(sf::Vector2f(first_click.x * cellSize + cellSize / 2, first_click.y * cellSize + cellSize / 2), sf::Color::Blue));
                            // line.append(sf::Vertex(sf::Vector2f(second_click.x * cellSize + cellSize / 2, second_click.y * cellSize + cellSize / 2), sf::Color::Blue));
                            int i = first_click.x;
                            int j = first_click.y;
                            grid[i+level][j] = sf::Color::Blue;
                            grid[i][j+level] = sf::Color::Blue;
                            grid[i][j-level] = sf::Color::Blue;
                            grid[i-level][j] = sf::Color::Blue;
                            grid[i+level][j+level] = sf::Color::Blue;
                            grid[i-level][j+level] = sf::Color::Blue;
                            grid[i+level][j-level] = sf::Color::Blue;
                            grid[i-level][j-level] = sf::Color::Blue;
                            level++;


                        }
                    }
                }
                if (event.mouseButton.button == sf::Mouse::Right) {
                    grid = std::vector<std::vector<sf::Color>>(gridSize, std::vector<sf::Color>(gridSize, sf::Color::White));
                    click_count = 0;
                    level = 1;
                    std::cout << "Grid reset\n";
                }
            }
        }

        window.clear(sf::Color::Black);

        for (int row = 0; row < gridSize; ++row) {
            for (int col = 0; col < gridSize; ++col) {
                cell.setFillColor(grid[row][col]);
                cell.setPosition(col * cellSize, row * cellSize);
                window.draw(cell);
            }
        }

        if (click_count == 3) {
            window.draw(line);
        }

        window.display();
    }

    return 0;
}
