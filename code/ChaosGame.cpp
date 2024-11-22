#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace sf;
using namespace std;

int main()
{
    // Seed the random number generator
    srand(static_cast<unsigned int>(time(nullptr)));

    // Create a video mode object and window
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Chaos Game!!", Style::Default);

    // Vectors to store vertices and points
    vector<Vector2f> vertices;
    vector<Vector2f> points;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (vertices.size() < 3)
                    {
                        // Add vertices
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                        cout << "Vertex added at: (" << event.mouseButton.x << ", " << event.mouseButton.y << ")" << endl;
                        if (vertices.size() == 3)
                        {
                            cout << "Click a fourth point to start the algorithm." << endl;
                        }
                    }
                    else if (points.empty())
                    {
                        // Add the initial starting point
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                        cout << "Starting point added at: (" << event.mouseButton.x << ", " << event.mouseButton.y << ")" << endl;
                        cout << "Watch the fractal being generated!" << endl;
                    }
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        // Update points for the fractal
        if (!points.empty())
        {
            for (int i = 0; i < 100; ++i) // Generate multiple points per frame
            {
                int randomIndex = rand() % vertices.size();
                Vector2f randomVertex = vertices[randomIndex];
                Vector2f lastPoint = points.back();

                // Calculate midpoint
                Vector2f newPoint((lastPoint.x + randomVertex.x) / 2, (lastPoint.y + randomVertex.y) / 2);
                points.push_back(newPoint);
            }
        }

        // Draw everything
        window.clear();

        // Draw vertices
        for (const auto& vertex : vertices)
        {
            CircleShape vertexShape(5);
            vertexShape.setFillColor(Color::Blue);
            vertexShape.setPosition(vertex.x - 5, vertex.y - 5);
            window.draw(vertexShape);
        }

        // Draw fractal points
        for (const auto& point : points)
        {
            CircleShape pointShape(2);
            pointShape.setFillColor(Color::Red);
            pointShape.setPosition(point.x - 1, point.y - 1);
            window.draw(pointShape);
        }

        window.display();
    }

    return 0;
}
