#pragma once
#ifndef BITMAP_H
#define BITMAP_H

// By default, values are set to assume 35x35 bitmap image using 24-bit color depth

// Code tutorial from the following:
// https://dev.to/muiz6/c-how-to-write-a-bitmap-image-from-scratch-1k6m

#include <cstdint> // for specific size integers
#include <fstream> // for file handling

#define BITMAP_HEADER_FILE_SIZE 14
#define BITMAP_HEADER_META_SIZE 40
#define BITMAP_HEADER_TOTAL_SIZE 54 // BITMAP_HEADER_FILE_SIZE + BITMAP_HEADER_META_SIZE

#define BITMAP_PIXEL_SIZE 3

#pragma pack(1)

struct BmpHeader {
    char bitmapSignatureBytesB = 'B'; // Magic Values, unique to the format
    char bitmapSignatureBytesM = 'M'; // Magic Values, unique to the format
    uint32_t sizeOfBitmapFile = 3834; // total size is the sum of size of meta data (14 + 40 = 54 bytes) and size of pixels (35 * 35 * 3 = 3675, each pixel is of 3 bytes in 24 bit bitmap file)
    uint32_t reservedBytes = 0; // Magic value
    uint32_t pixelDataOffset = 54; // BITMAP_HEADER_TOTAL_SIZE; // 54 is the size of all the meta data
};

struct BmpInfoHeader {
    uint32_t sizeOfThisHeader = 40;
    int32_t width = 35; // in pixels
    int32_t height = 35; // in pixels
    uint16_t numberOfColorPlanes = 1; // must be 1, magic value
    uint16_t colorDepth = 24; // 8 bits per byte, typically this will be 24-bit using 3 byes for channels rgb 
    uint32_t compressionMethod = 0; // Magic value
    uint32_t rawBitmapDataSize = 3780; // Magic value
    int32_t horizontalResolution = 0; // in pixel per meter, magic value
    int32_t verticalResolution = 0; // in pixel per meter, magic value
    uint32_t colorTableEntries = 0; // magic value
    uint32_t importantColors = 0; // Magic value
} ;

struct Pixel {
    uint8_t blue = 0;
    uint8_t green = 0;
    uint8_t red = 0;
    Pixel(uint8_t b, uint8_t g, uint8_t r) {
        blue = b;
        green = g;
        red = r;
    };
};

class BitMap
{
public:
    BitMap();
    char* getBmpBuffer();
    void setPixel(int x, int y, uint8_t b, uint8_t g, uint8_t r);
    void setPixel(int bufferPosition, uint16_t top, uint16_t bottom);
    int getBufferSize();
    int getWidth();
    int getHeight();
    void writeToFile(const char* fileName);
private:
    BmpHeader bmpHeader;
    BmpInfoHeader bmpInfoHeader;
    char* imgBuffer;
    int width;
    int height;
};

#endif