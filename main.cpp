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
#include "constants.h"

int main()
{
    enum EnumGameMode {MODE_TITLE, MODE_LOCAL_MAP, MODE_INVENTORY};

    int enumGameMode = EnumGameMode::MODE_LOCAL_MAP;
    int gameModePreviousFrame = enumGameMode;

    // Initialization of shared ressources between levels
    sf::RenderWindow window(sf::VideoMode(constants::WINDOW_WIDTH, constants::WINDOW_HEIGHT), "Window");
    window.setFramerateLimit(60);
    Assets::get().LoadTextures();
    Assets::get().SetNameDynamicMap("DynMap_WildOne");


    Creature* pPlayer = new cCreature_Player("Bandido", 400, 450);
    cDynamicMap* currentDynamicMap = new cDynamicMap_One;
    currentDynamicMap->populateDynamics(pPlayer);

    //cQuest::addQuest(new cQuest_Base);
    cQuest::addQuest(make_shared<cQuest_Base>());

    // Inventory mode
    cInventory inventory((vector<cItem*>*)(pPlayer->getAllItems()));
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
             auto centerX = pPlayer->getPosX() < (constants::VIEW_WIDTH / 2) ? max(constants::VIEW_WIDTH / 2, (int)pPlayer->getPosX()) : min((constants::WINDOW_WIDTH - constants::VIEW_WIDTH / 2) , (int)pPlayer->getPosX());
             auto centerY = pPlayer->getPosY() < (constants::VIEW_HEIGHT / 2) ? max(constants::VIEW_HEIGHT / 2, (int)pPlayer->getPosY()) : min((constants::WINDOW_HEIGHT - constants::VIEW_HEIGHT / 2) , (int)pPlayer->getPosY());
             window.setView(sf::View(sf::Vector2f(centerX, centerY), sf::Vector2f((float)constants::VIEW_WIDTH, (float)constants::VIEW_HEIGHT)));
             window.display();
             gameModePreviousFrame = EnumGameMode::MODE_LOCAL_MAP;
             break;
         }

         case EnumGameMode::MODE_INVENTORY: {

             // If comes from other game mode: Initialization
             if (gameModePreviousFrame != enumGameMode) {
                 window.setView(sf::View(sf::Vector2f(400,300), sf::Vector2f((float)constants::WINDOW_WIDTH, (float)constants::VIEW_HEIGHT)));
                gameModePreviousFrame = EnumGameMode::MODE_INVENTORY;
                cTextDrawer::get().setTitleMode("INVENTORY");
                inventory.repositionElements();
             }

             // Events
             sf::Event event;
             while (window.pollEvent(event))
             {
                 if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                     window.close();
                 else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
                     enumGameMode = EnumGameMode::MODE_LOCAL_MAP;
                 else {
                     cItem* itemConsumed = inventory.handleInputs(event); // Get consumed item
                     if (itemConsumed) {
                         itemConsumed->OnUse(pPlayer);
                         pPlayer->consumeItem(itemConsumed, 1);
                         inventory.repositionElements();
                     }
                 }
             }

             // Set text
             if (inventory.getSelectedItem())
                 cTextDrawer::get().setItemText(inventory.getSelectedItem()->getName(), inventory.getSelectedItem()->getQuantity(), inventory.getSelectedItem()->getDescription());
             else
                 cTextDrawer::get().setNoItemText();
             // Draw
             window.clear(sf::Color(30, 30, 30, 255));
             inventory.draw(window);
             cTextDrawer::get().drawText_InventaryMode(&window);
             window.display();
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
