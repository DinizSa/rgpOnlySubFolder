#include "inputHandler.h"
#include "dynamic.h"
#include "SFML/Window.hpp"

InputHandler::InputHandler() {
    this->bPressedLeft = false;
    this->bPressedRight = false;
    this->bPressedUp = false;
    this->bPressedDown = false;
}

InputHandler::~InputHandler() {

}

void InputHandler::pollEvents(sf::RenderWindow* window, Dynamic* controlled) {
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window->close();
        // Movement pressed
        
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::A)
                this->bPressedLeft = true;
            if (event.key.code == sf::Keyboard::D)
                this->bPressedRight = true;
            if (event.key.code == sf::Keyboard::W)
                this->bPressedUp = true;
            if (event.key.code == sf::Keyboard::S)
                this->bPressedDown = true;
        }

        // Movement released
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::A)
                this->bPressedLeft = false;
            if (event.key.code == sf::Keyboard::D)
                this->bPressedRight = false;
            if (event.key.code == sf::Keyboard::W)
                this->bPressedUp = false;
            if (event.key.code == sf::Keyboard::S)
                this->bPressedDown = false;
        }
    }

    if(bPressedLeft)
        controlled->addVelocityNormalizedX(-1.f);
    if (bPressedRight)
        controlled->addVelocityNormalizedX(1.f);
    if (bPressedUp)
        controlled->addVelocityNormalizedY(-1.f);
    if (bPressedDown)
        controlled->addVelocityNormalizedY(1.f);

}