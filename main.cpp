#include <SFML/Graphics.hpp>
#include "assets.h"
#include "entity.h"
#include "maps.h"
#include "creature.h"
#include "timer.h"
#include "scriptProcessor.h"
#include "command.h"
#include "textDrawer.h"
#include "dynamicMap.h"

int main()
{

    // Initialization of shared ressources between levels
    sf::RenderWindow window(sf::VideoMode(800, 600), "Window");
    window.setFramerateLimit(60);
    Assets::get().LoadTextures();
    Assets::get().LoadDynamicMaps();

    Assets::get().SetNameDynamicMap("DynMap_WildOne");
    cDynamicMap* currentDynamicMap = Assets::get().GetCurrentDynamicMap();

    Creature* pPlayer = new Creature("PackMan", 400, 450, 1, 1, 1, 100, 2.0f);
    currentDynamicMap->setpPlayer(pPlayer);

     while (window.isOpen())
    {
         // If dynamicMap changed
         if (currentDynamicMap != Assets::get().GetCurrentDynamicMap()) {
             currentDynamicMap = Assets::get().GetCurrentDynamicMap();
             currentDynamicMap->setpPlayer(pPlayer);
         }

        // Events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
            else
                if (currentDynamicMap->isAcceptingInputs())
                    currentDynamicMap->handleInputs(event);
            
        }

        // Update
        currentDynamicMap->update();

        // Display
        window.clear(sf::Color(0,0,0,255));
        currentDynamicMap->draw(&window);
        window.display();
    }


    return 0;
}