
#include "SFMLFrontend.h"


namespace Blobbo
{
	SFMLFrontend::SFMLFrontend(Game &instance)
	{
		this->gameInstance = &instance;
		this->window.create(sf::VideoMode(512, 320), "Blobbo");
		this->pixmap.loadFromFile("img/00128.png");
	}

	void SFMLFrontend::processEvents()
	{
	}

	sf::RenderWindow *SFMLFrontend::getWindow()
	{
		return &this->window;
	}

	void SFMLFrontend::renderFrame()
	{
		// Get the current level
		const char *level = this->gameInstance->getLevelData();

		// Create a painting tile
		sf::RectangleShape shape(sf::Vector2f(tileSize, tileSize));
		shape.setTexture(&this->pixmap, false);

		// Clear the window
		this->window.clear(sf::Color(255,255,255));

		unsigned int index = 0;
		for(int x = 0; x < Blobbo::mapWidth; x++)
	    {
	        for(int y = 0; y < Blobbo::mapHeight; y++)
	        {
	            sf::Uint8 value = level[index++];
	            if(value == 0) continue;

	            unsigned int tile_x = value >> 4;
	            unsigned int tile_y = value & 0x0F;           

	            shape.setPosition(x * tileSize, y * tileSize);

	            shape.setTextureRect(sf::IntRect(
	                tile_x * tileSize,
	                tile_y * tileSize,
	                tileSize,
	                tileSize
	            ));
	            this->window.draw(shape);
	        }
	    }        
        this->window.display();
	}
}