#include "inputHandler.h"
#include "dynamic.h"
#include "SFML/Window.hpp"

InputHandler::InputHandler() {

}

InputHandler::~InputHandler() {

}

void InputHandler::pollEvents(sf::RenderWindow* window, Dynamic* controlled) {
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window->close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            controlled->addVelocityNormalizedX(-1.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            controlled->addVelocityNormalizedX(1.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            controlled->addVelocityNormalizedY(-1.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            controlled->addVelocityNormalizedY(1.f);

    }
}