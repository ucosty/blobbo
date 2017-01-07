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
const unsigned short tile_size = 16;
const unsigned int level_min = 128;
const unsigned int level_max = 155;

struct HexCharStruct
{
    unsigned char c;
    HexCharStruct(unsigned char _c) : c(_c) { }
};

inline std::ostream& operator<<(std::ostream& o, const HexCharStruct& hs)
{
    return (o << std::setw(2) << std::setfill('0') << std::hex << (int)hs.c);
}

inline HexCharStruct hex(unsigned char _c)
{
    return HexCharStruct(_c);
}

void hexOutput(char* input, int length, int width)
{
    unsigned int value = 0;
    for (int i = 0; i < length; i++)
    {
        std::cout << hex(input[i]) << ' ';
        if ((i + 1) % width == 0) std::cout << std::endl;
    }
    std::cout << std::endl;
}

char *loadBlevResource(std::string filename)
{

    std::ifstream file;
    file.open(filename, std::ios::ate | std::ios::binary);
    size_t length = file.tellg();
    char *source = new char[length];
    file.seekg(0, std::ios::beg);
    file.read(source, length);
    file.close();

    char *encrypted = &source[16];
    char *unpacked = new char[640];

    size_t length_packed = length - 16;

    // It looks like all official blobbo maps start with the signature 0x7FFF
    const unsigned short *signature = reinterpret_cast<unsigned short *>(&source[0]);
    if(signature[0] != 0xFF7F && length == 640) {
        return source;
    }

    char encode = source[15], nextencode;
    for(int i = 0; i < length_packed; i++) {
        nextencode = encrypted[i];
        encrypted[i] ^= encode;
        encode = nextencode;
    }

    Toolbox::ToolUtils::UnpackBits((unsigned char *)encrypted, (unsigned char *)unpacked, length_packed);

    delete[] source;
    return unpacked;
}

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