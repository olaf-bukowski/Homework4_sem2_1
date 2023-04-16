#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

class CustomRectangleShape : public sf::RectangleShape {
public:
    CustomRectangleShape(const sf::Vector2f &size) :
        sf::RectangleShape(size),
        speed(150.f)
    {
        srand(static_cast<unsigned int>(time(nullptr)));

        int r = rand() % 256;
        int g = rand() % 256;
        int b = rand() % 256;

        setFillColor(sf::Color(r, g, b));
        setOutlineThickness(2.f);
        setOutlineColor(sf::Color::White);
    }

    void moveInDirection(const sf::Time &elapsed, const sf::Keyboard::Key &key) {
        sf::Vector2f movement(0.f, 0.f);
        float distance = speed * elapsed.asSeconds();

        if (key == sf::Keyboard::Left) {
            movement.x -= distance;
        }
        else if (key == sf::Keyboard::Right) {
            movement.x += distance;
        }
        else if (key == sf::Keyboard::Up) {
            movement.y -= distance;
        }
        else if (key == sf::Keyboard::Down) {
            movement.y += distance;
        }

        sf::Vector2f newPosition = getPosition() + movement;

                if (isWithinBounds(newPosition)) {
                    move(movement);
                }
    }

    bool isClicked(sf::Vector2i &mouse_position) const {
        sf::FloatRect boundingBox = getGlobalBounds();
        return boundingBox.contains(static_cast<sf::Vector2f>(mouse_position));
    }
    bool isWithinBounds(const sf::Vector2f &position) const {
            sf::FloatRect boundingBox = getGlobalBounds();
            sf::FloatRect windowBox(0.f, 0.f, static_cast<float>(windowSize.x), static_cast<float>(windowSize.y));
            return windowBox.contains(position) && windowBox.contains(position + sf::Vector2f(boundingBox.width, boundingBox.height));
        }

    void setWindowSize(const sf::Vector2u &size) {
            windowSize = size;
    }

private:
    float speed;
    sf::Vector2u windowSize;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Moving rectangle");

    CustomRectangleShape rect(sf::Vector2f(140.f, 140.f));
    rect.setPosition(100.f, 100.f);
    rect.setWindowSize(window.getSize());

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                rect.moveInDirection(sf::seconds(3.f / 60.f), event.key.code);
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
                if (rect.isClicked(mouse_position)) {
                    int r = rand() % 256;
                    int g = rand() % 256;
                    int b = rand() % 256;

                    rect.setFillColor(sf::Color(r, g, b));
                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(rect);
        window.display();
    }

    return 0;
}
