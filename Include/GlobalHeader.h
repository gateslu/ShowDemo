#ifndef GLOBALHEADER_H
#define GLOBALHEADER_H

#include <stdint.h>

#pragma pack (push ,1)

typedef struct { /* bmfh */
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
} BMP_FILE_HDR;

typedef struct { /* bmih */
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} BMP_INFO_HDR;

#pragma pack (pop)

#endif // GLOBALHEADER_H
