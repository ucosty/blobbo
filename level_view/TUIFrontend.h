
#ifndef BLOBBO_TUIFRONTEND_H
#define BLOBBO_TUIFRONTEND_H

#include "IFrontend.h"
#include "BlobboGame.h"

namespace Blobbo
{

    class TUIFrontend : private IFrontend
    {
        private:
            // Game Instance
            Game *gameInstance;

        public:
            TUIFrontend(Game &instance);
            virtual void renderFrame();
            virtual void processEvents();
    };

}

#endif
