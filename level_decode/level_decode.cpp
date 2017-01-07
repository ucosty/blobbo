#include <iostream>
#include <fstream>
#include <iomanip>

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

void hexOutput(char* input, int length)
{
	unsigned int value = 0;
	for (int i = 0; i < length; i++)
	{
		std::cout << hex(input[i]) << ' ';
		if ((i + 1) % 32 == 0) std::cout << std::endl;
	}
	std::cout << std::endl;
}

char *readFile(const char *filename, size_t &fileSize, int skip = 0)
{
	std::ifstream file;
	file.open(filename, std::ios::ate | std::ios::binary);
	fileSize = file.tellg();
	fileSize -= skip;
	char *buffer = new char[fileSize];
	file.seekg(skip, std::ios::beg);
	file.read(buffer, fileSize);
	file.close();
	return buffer;
}

void UnpackBits(unsigned char *source, unsigned char *destination, size_t &size)
{
	int src = 0, dest = 0, runLength = 0;
    size_t packed = size;
    unsigned char *pDst, *pSrc;

    while(src < packed) {
        if (source[src] >= 128) {
            // Sequence of packed bytes
            runLength = 256 - source[src] + 1;
            pSrc = &source[src + 1];
            pDst = &destination[dest];
            for (int i = 0; i < runLength; i++ ) {
                *pDst++ = *pSrc;
            }
            src += 2;
            dest += runLength;
        }
        else {
            // Sequence of unpacked bytes
            runLength = source[src] + 1;
            pSrc = &source[src + 1];
            pDst = &destination[dest];
            for(int i = 0; i < runLength; i++ ) {
                *pDst++ = *pSrc++;
            }
            src += runLength + 1;
            dest += runLength;
        }
    }
    size = dest;
}

int main(int argc, char *argv[])
{
	std::string level_file;
	size_t length, length_packed;

	if(argc != 2) {
		std::cout << "Usage: " << argv[0] << " level_file" << std::endl;
		return 1;
	}

	unsigned char *source = (unsigned char*) readFile(argv[1], length);
	unsigned char *encrypted = &source[16];
	unsigned char *unencrypted = new unsigned char[length];
	unsigned char *unpacked = new unsigned char[length];

	std::cout << "Level Encrypted" << std::endl;
	hexOutput((char *)source, length);
	std::cout << std::endl;

	length_packed = length - 16;

	unsigned char encode = source[15];
	for(int i = 0; i < length_packed; i++) {
		unencrypted[i] = encrypted[i] ^ encode;
		encode = encrypted[i];
	}

	std::cout << "Level Unencrypted" << std::endl;
	hexOutput((char *)unencrypted, length_packed);
	std::cout << std::endl;

	UnpackBits(unencrypted, unpacked, length_packed);

	std::cout << "Level Unpacked (" << std::dec << length_packed << " bytes)." << std::endl;
	hexOutput((char *)unpacked, length_packed);
	std::cout << std::endl;
}

