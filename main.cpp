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
#include "quest.h"

int main()
{

    // Initialization of shared ressources between levels
    sf::RenderWindow window(sf::VideoMode(800, 600), "Window");
    window.setFramerateLimit(60);
    Assets::get().LoadTextures();
    Assets::get().SetNameDynamicMap("DynMap_WildOne");


    Creature* pPlayer = new Creature("Bandido", "PackMan", 400, 450, 1, 1, 1, 100, 2.0f);
    cDynamicMap* currentDynamicMap = new cDynamicMap_One;
    currentDynamicMap->populateDynamics(pPlayer);

    //cQuest::addQuest(new cQuest_Base);
    cQuest::addQuest(make_shared<cQuest_Base>());

     while (window.isOpen())
    {
         // If dynamicMap changed
         if (currentDynamicMap->getName() != Assets::get().GetNameDynamicMap()){
             if ("DynMap_WildOne" == Assets::get().GetNameDynamicMap())
                 currentDynamicMap = new cDynamicMap_One;
             else if ("DynMap_WildOneTrip" == Assets::get().GetNameDynamicMap())
                 currentDynamicMap = new cDynamicMap_OneTrip;
             currentDynamicMap->populateDynamics(pPlayer );
         }

        // Events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
            else 
                if (cScriptProcessor::Get().getUserControlEnabled())
                    currentDynamicMap->handleInputs(event);
            
        }

        // Update
        currentDynamicMap->update();

        // Display
        window.clear(sf::Color(0,0,0,255));
        currentDynamicMap->draw(&window);
        window.display();
    }

     // Cleanup
     delete pPlayer;
     delete currentDynamicMap;

    return 0;
}
