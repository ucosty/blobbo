
#ifndef _BLOBBO_SMFLFRONTEND_H
#define _BLOBBO_SMFLFRONTEND_H

#include <SFML/Graphics.hpp>
#include "BlobboGame.h"
#include "IFrontend.h"

namespace Blobbo
{
    class SFMLFrontend : private IFrontend
    {
	private:
        // SFML Internals
        sf::RenderWindow window;

        // Blobbo Map Rendering
        std::vector<sf::RectangleShape> tiles;
        sf::Texture pixmap;

        // Game Instance
        Game *gameInstance;

    public:
    	SFMLFrontend(Game &instance);
    	virtual void renderFrame();
        virtual void processEvents();
        sf::RenderWindow *getWindow();
    };

}

#endif
