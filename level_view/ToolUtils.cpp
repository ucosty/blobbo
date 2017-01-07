#include <cstddef>
#include "ToolUtils.h"
#include <iostream>
namespace Toolbox
{
    void ToolUtils::UnpackBits(unsigned char *source, unsigned char *destination, size_t &size)
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
};
