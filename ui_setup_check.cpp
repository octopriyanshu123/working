// #include <SFML/Graphics.hpp>

// int main() {
//     sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Test");

//     while (window.isOpen()) {
//         sf::Event event;
//         while (window.pollEvent(event)) {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }

//         window.clear();
//         window.display();
//     }

//     return 0;
// }


// run g++ -o my_program my_program.cpp -lsfml-graphics -lsfml-window -lsfml-system



#include <SFML/Graphics.hpp>

int main()
{
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Line Example");

    // Create a VertexArray for the line (2 vertices for a straight line)
    sf::VertexArray line(sf::Lines, 2);

    // Set the positions of the two vertices (start and end points)
    line[0].position = sf::Vector2f(100, 100);  // Start point
    line[1].position = sf::Vector2f(700, 500);  // End point

    // Set the color of the line
    line[0].color = sf::Color::Red;    // Color of the start point
    line[1].color = sf::Color::Blue;   // Color of the end point

    // Main loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window
        window.clear(sf::Color::White);

        // Draw the line
        window.draw(line);

        // Display the contents of the window
        window.display();
    }

    return 0;
}

