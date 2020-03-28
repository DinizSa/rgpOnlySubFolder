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
#include "inventory.h"

int main()
{
    enum EnumGameMode {MODE_TITLE, MODE_LOCAL_MAP, MODE_INVENTORY};

    int enumGameMode = EnumGameMode::MODE_LOCAL_MAP;
    int gameModePreviousFrame = enumGameMode;

    // Initialization of shared ressources between levels
    sf::RenderWindow window(sf::VideoMode(800, 600), "Window");
    window.setFramerateLimit(60);
    Assets::get().LoadTextures();
    Assets::get().SetNameDynamicMap("DynMap_WildOne");


    Creature* pPlayer = new cCreature_Player("Bandido", 400, 450);
    cDynamicMap* currentDynamicMap = new cDynamicMap_One;
    currentDynamicMap->populateDynamics(pPlayer);

    //cQuest::addQuest(new cQuest_Base);
    cQuest::addQuest(make_shared<cQuest_Base>());

    // Inventory mode
    cInventory inventory;


     while (window.isOpen())
    {

         switch (enumGameMode)
         {
         case EnumGameMode::MODE_LOCAL_MAP: {
             // If dynamicMap changed
             if (currentDynamicMap->getName() != Assets::get().GetNameDynamicMap()) {
                 if ("DynMap_WildOne" == Assets::get().GetNameDynamicMap())
                     currentDynamicMap = new cDynamicMap_One;
                 else if ("DynMap_WildOneTrip" == Assets::get().GetNameDynamicMap())
                     currentDynamicMap = new cDynamicMap_OneTrip;
                 currentDynamicMap->populateDynamics(pPlayer);
             }

             // Events
             sf::Event event;
             while (window.pollEvent(event))
             {
                 if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                     window.close();
                 else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) 
                     enumGameMode = EnumGameMode::MODE_INVENTORY;
                 else
                     if (cScriptProcessor::Get().getUserControlEnabled())
                         currentDynamicMap->handleInputs(event);

             }

             // Update
             currentDynamicMap->update();
             cTextDrawer::get().setHealth(pPlayer->getHealth(), pPlayer->getMaxHealth());

             // Display
             window.clear(sf::Color(0, 0, 0, 255));
             currentDynamicMap->draw(&window);
             window.display();
             gameModePreviousFrame = EnumGameMode::MODE_LOCAL_MAP;
             break;
         }

         case EnumGameMode::MODE_INVENTORY: {

             sf::RectangleShape background;

             // If comes from other game mode
             if (gameModePreviousFrame != enumGameMode) {
                 inventory.update((vector<cItem*>*)(pPlayer->getAllItems()));
                background.setFillColor(sf::Color(20, 20, 20, 255));
                background.setSize(sf::Vector2f(800.f, 600.f));
             }

             // Events
             sf::Event event;
             while (window.pollEvent(event))
             {
                 if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                     window.close();
                 else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
                     enumGameMode = EnumGameMode::MODE_LOCAL_MAP;
                 else
                     inventory.handleInputs(event);
             }



             // Display
             window.clear(sf::Color(0, 0, 0, 255));
             window.draw(background);
             inventory.draw(window);
             cTextDrawer::get().setTitle("INVENTORY");
             cTextDrawer::get().drawText_InventaryMode(&window);
             window.display();
             gameModePreviousFrame = EnumGameMode::MODE_INVENTORY;
             break;
         }
         case EnumGameMode::MODE_TITLE: {
             
         }
         default:
             break;
         }

    }

     // Cleanup
     delete pPlayer;
     delete currentDynamicMap;

    return 0;
}
