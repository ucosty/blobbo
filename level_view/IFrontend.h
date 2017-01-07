
#ifndef _BLOBBO_IFRONTEND_H
#define _BLOBBO_IFRONTEND_H

namespace Blobbo
{
	class IFrontend
    {
    public:
    	virtual ~IFrontend() {};
    	virtual void renderFrame() = 0;
    	virtual void processEvents() = 0;
    };
}

#endif
