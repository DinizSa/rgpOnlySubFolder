#include <SFML/Graphics.hpp>
#include "assets.h"
#include "entity.h"
#include "maps.h"
#include "creature.h"
#include "inputHandler.h"
#include "timer.h"
#include "scriptProcessor.h"
#include "command_MoveTo.h"
#include "commands.h"
#include "textDrawer.h"
#include "command_Talk.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Window");
    window.setFramerateLimit(60);
    Timer timer;

    Assets::get().LoadTextures();
    InputHandler inputHandler;
    Maps mapOne("map1.txt", "MapTransp", window.getSize().x, window.getSize().y);
    Maps mapTwo("map2.txt", "MapTranspFucked", window.getSize().x, window.getSize().y);
    Maps* pCurrentMap = &mapTwo;
    //Creature player("EarthBender", 50, 50, 0, 0, 34, 34, 1, 1, 1, 100, 2);
    Creature player("PackMan", 400, 450, 0, 0, 34, 34, 1, 1, 1, 100, 1);
    Creature coelho("FireLady", 550, 500, 0, 0, 34, 34, 1, 1, 1, 50, 1);
    Interactive magicFlower("RedFlowers", 700, 450, 34, 34);

    cTextDrawer textDrawer;
    cCommand_Talk commandTalkConv00(&textDrawer, "hi", "Hey! ", 1000, sf::Color::Red);
    cCommand_Talk commandTalkConv01(&textDrawer, "hiBack", "Hi! ", 1000, sf::Color::Blue);

    // Commands
    cScriptProcessor scriptProcessor;
    cCommand_MoveTo comandToMove(&coelho, player.getPosX(), player.getPosY());
    scriptProcessor.AddCommand(&comandToMove);
    scriptProcessor.AddCommand(&commandTalkConv00);
    scriptProcessor.AddCommand(&commandTalkConv01);

    vector<Dynamic*> vDynamic;
    vDynamic.push_back(&player);
    vDynamic.push_back(&coelho);
    vDynamic.push_back(&magicFlower);


    while (window.isOpen())
    {
        // Update
        timer.updateTimer();
        scriptProcessor.ProcessCommands(timer.getMsSinceLastFrame());
        if(scriptProcessor.getUserControlEnabled())
            inputHandler.pollEvents(&window, &vDynamic, &player);

        for (int i = 0; i < vDynamic.size(); i++)
            vDynamic[i]->update(&timer, &mapOne, &vDynamic, window.getSize().x, window.getSize().y);

        // Display
        window.clear(sf::Color(0,0,0,255));
        //// Draw map & dynamic objects
        pCurrentMap->draw(&window);
        for (int i = 0; i < vDynamic.size(); i++)
            vDynamic[i]->draw(&window);
        textDrawer.drawText(&window);

        window.display();
    }

    return 0;
}