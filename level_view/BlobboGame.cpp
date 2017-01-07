#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>

#include "BlobboGame.h"
#include "ToolUtils.h"
#include "SFMLFrontend.h"

namespace Blobbo
{
	const char * Game::getLevelData()
	{
		return const_cast<char *>(this->levelData);
	}

	void Game::loadLevelFromFile(const std::string path)
	{
		std::ifstream file;
		file.open(path, std::ios::ate | std::ios::binary);

		size_t length = file.tellg();
		size_t length_packed = length - blevHeaderSize;

		char *source = new char[length];

	    file.seekg(0, std::ios::beg);
	    file.read(source, length);
	    file.close();

	    // It looks like all official blobbo maps start with the signature 0x7FFF
	    const unsigned short *signature = reinterpret_cast<unsigned short *>(&source[0]);
	    if(signature[0] != 0xFF7F && length == 640) {
	    	this->levelData = source;
	    	return;
	    }

	    char *packed = &source[blevHeaderSize];
	    char *unpacked = new char[mapWidth * mapHeight];

	    // Decrypt the level data
	    char next_encode;
	    char encode = source[15];

	    for(int i = 0; i < length_packed; i++) {
	    	next_encode = packed[i];
	        packed[i] ^=  encode;
	        encode = next_encode;
	    }

	    Toolbox::ToolUtils::UnpackBits((unsigned char *)packed, (unsigned char *)unpacked, length_packed);
	    
	    this->levelData = unpacked;
	    delete[] source;
	}

    void Game::loadLevelBuiltin(short id)
    {
    	std::stringstream pathBuilder;
	    pathBuilder << "../levels/" << std::setw(5) << std::setfill('0') << id << ".blev";
	    this->loadLevelFromFile(pathBuilder.str());
    }
}