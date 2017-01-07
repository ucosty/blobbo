#include <iostream>
#include <iomanip>

#include "TUIFrontend.h"

void hexOutput(char* input, int length, int width);

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

namespace Blobbo
{
	TUIFrontend::TUIFrontend(Game &instance)
	{
		this->gameInstance = &instance;
	}

	void TUIFrontend::processEvents()
	{
	}

	void TUIFrontend::renderFrame()
	{
		const char *level = this->gameInstance->getLevelData();

		unsigned char row[Blobbo::mapHeight][Blobbo::mapWidth];

		unsigned int linear = 0;
		for(int x = 0; x < Blobbo::mapWidth; x++)
		{
			for(int y = 0; y < Blobbo::mapHeight; y++)
			{
				row[y][x] = level[linear++];
			}
		}


	    for(int y = 0; y < Blobbo::mapHeight; y++)
	    {
	    	for(int x = 0; x < Blobbo::mapWidth; x++)
	    	{
	    		unsigned char block = row[y][x];

	    		if(block > 0 && block <= 0x1E) {
	    			std::cout << "\033[1;42;97m" << ' ' << (char)(block + 0x40) << ' ';

	    		} else if(block >= 0xe0 && block <= 0xec) {
	    			int number = block - 0xe0;
	    			std::cout << "\033[1;42;97m" << ' ' << (char)(number + 0x30) << ' ';
	    		} else {
	    			switch(block)
		    		{
		    			case 0:
		    				std::cout << "\033[49;0m"  << "   ";
	    					break;
		    			case 0x20:
		    				std::cout << "\033[100m"  << "   ";
		    				break;
		    			case 0x26:
		    				std::cout << "\033[49;0m"  << " \\ ";
		    				break;
		    			case 0x27:
		    				std::cout << "\033[49;0m"  << " / ";
		    				break;
		    			case 0x28:
		    				std::cout << "\033[91;41m"  << "/#\\";
		    				break;
		    			case 0x29:
		    				std::cout << "\033[46m"  << "_=_";
		    				break;
		    			case 0x2F:
		    				std::cout << "\033[46m"  << "\\-_";
		    				break;
		    			case 0x39:
		    				std::cout << "\033[46m"  << "<=>";
		    				break;
		    			case 0xC0:
		    				std::cout << "\033[101m" << "(0)";
		    				break;
		    			case 0xC2:
		    				std::cout << "\033[101m" << "<--";
		    				break;
		    			case 0xC3:
		    				std::cout << "\033[101m" << "-->";
		    				break;
		    			case 0x70:
		    				std::cout << "\033[33;103m" << " @ ";
	    					break;
		    			case 0x80:
		    				std::cout << "\033[104m" << "[=]";
	    					break;
		    			default:
		    				std::cout << "\033[49;0m" << ' ' << hex(row[y][x]);

		    		}
	    		}
    			std::cout << "\033[49;0m";
	    	}
	    	std::cout << std::endl;
	    }

	    std::cout << "\033[49;0m" << std::endl;
	}
}