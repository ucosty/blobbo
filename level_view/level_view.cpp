#include <fstream>
#include <vector>
#include <iostream>
#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include <thread>

#include "ToolUtils.h"
#include "BlobboGame.h"
#include "TUIFrontend.h"
#include "SFMLFrontend.h"

const char pixmapFilename[] = "img/00128.png";
const unsigned int level_min = 128;
const unsigned int level_max = 155;

std::vector<sf::RectangleShape> tiles;
sf::Texture textures;

void loadPixmapData(sf::Texture &pixmap)
{
    pixmap.loadFromFile(pixmapFilename);
}

int main(int argc, char *argv[])
{
    unsigned int defaultLevelID = 128;
    unsigned int currentLevelID = 128;

    Blobbo::Game instance;
    Blobbo::TUIFrontend tui(instance);
    Blobbo::SFMLFrontend sfml(instance);

    instance.loadLevelBuiltin(currentLevelID);

    sf::RenderWindow *window = sfml.getWindow();

    tui.renderFrame();
    sfml.renderFrame();

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();

            if(event.type == sf::Event::KeyPressed)
            {
                switch(event.key.code)
                {
                    case sf::Keyboard::N:
                        if(currentLevelID >= level_max) break;
                        instance.loadLevelBuiltin(++currentLevelID);
                        sfml.renderFrame();
                        tui.renderFrame();
                        break;

                    case sf::Keyboard::P:
                        if(currentLevelID <= level_min) break;
                        instance.loadLevelBuiltin(--currentLevelID);
                        sfml.renderFrame();
                        tui.renderFrame();
                        break;

                    case sf::Keyboard::F:
                        currentLevelID = defaultLevelID;
                        instance.loadLevelBuiltin(currentLevelID);
                        sfml.renderFrame();
                        tui.renderFrame();
                        break;

                    case sf::Keyboard::Q:
                        window->close();
                        break;

                    default:
                        break;
                }
            }
        }
    }

    return 0;
}