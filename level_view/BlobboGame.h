
#ifndef _BLOBBO_GAME_H
#define _BLOBBO_GAME_H

#include <string>
#include <vector>
#include <map>

namespace Blobbo
{
	const unsigned short mapWidth = 32;
	const unsigned short mapHeight = 20;
	const unsigned short tileSize = 16;

	const unsigned short blevHeaderSize = 16;

    class Game
    {
    private:
        std::string currentLevelName;
        char * levelData;

    public:
    	void loadLevelFromFile(const std::string path);
        void loadLevelBuiltin(short id);

        const char *getLevelData();
    };
};

#endif
