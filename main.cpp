#include <SFML/Graphics.hpp>
#include "assets.h"
#include "entity.h"
#include "maps.h"
#include "creature.h"
#include "timer.h"
#include "scriptProcessor.h"
#include "command.h"
#include "textDrawer.h"
#include "level.h"

int main()
{

    // Initialization of shared ressources between levels
    sf::RenderWindow window(sf::VideoMode(800, 600), "Window");
    window.setFramerateLimit(60);
    Assets::get().LoadTextures();
    Assets::get().LoadMaps();
    cLevel_LevelOne level;

    while (window.isOpen())
    {
        // TODO: Events related with window shouldnt be handled in the level
        // Events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
            else
                if (level.isAcceptingInputs())
                    level.handleInputs(event);
            
        }

        // Update
        level.update();

        // Display
        window.clear(sf::Color(0,0,0,255));
        level.draw(&window);
        window.display();
    }

    return 0;
}