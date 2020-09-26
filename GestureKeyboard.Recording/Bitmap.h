#pragma once
#ifndef BITMAP_H
#define BITMAP_H

// By default, values are set to assume 35x35 bitmap image using 24-bit color depth

// Code tutorial from the following:
// https://dev.to/muiz6/c-how-to-write-a-bitmap-image-from-scratch-1k6m

#include <cstdint> // for specific size integers
#include <fstream> // for file handling

#define BITMAP_HEADER_FORMAT_SIZE 14
#define BITMAP_HEADER_META_SIZE 40
#define BITMAP_HEADER_TOTAL_SIZE 54 // BITMAP_HEADER_FORMAT_SIZE + BITMAP_HEADER_META_SIZE

#define BITMAP_PIXEL_SIZE 3

class BitMap
{
public:
    BitMap(int width, int height);
    char* getBmpBuffer();
    void setPixel(int x, int y, Pixel& pixel);
    void setPixel(int x, int y, uint8_t b, uint8_t g, uint8_t r);
    int getBufferSize();
    int getWidth();
    int getHeight();
    Pixel getPixel(int x, int y);
private:
    BmpHeader bmpHeader;
    BmpInfoHeader bmpInfoHeader;
    char* bmpBuffer;
    int width;
    int height;
    int bufferSize;
};

struct BmpHeader {
    char bitmapSignatureBytes[2] = { 'B', 'M' }; // Magic Values, unique to the format
    uint32_t sizeOfBitmapFile = BITMAP_HEADER_TOTAL_SIZE + 3675; // total size is the sum of size of meta data (14 + 40 = 54 bytes) and size of pixels (35 * 35 * 3 = 3675, each pixel is of 3 bytes in 24 bit bitmap file)
    uint32_t reservedBytes = 0; // Magic value
    uint32_t pixelDataOffset = BITMAP_HEADER_TOTAL_SIZE; // 54 is the size of all the meta data
};

struct BmpInfoHeader {
    uint32_t sizeOfThisHeader = BITMAP_HEADER_META_SIZE;
    int32_t width = 35; // in pixels
    int32_t height = 35; // in pixels
    uint16_t numberOfColorPlanes = 1; // must be 1, magic value
    uint16_t colorDepth = BITMAP_PIXEL_SIZE * 8; // 8 bits per byte, typically this will be 24-bit using 3 byes for channels rgb 
    uint32_t compressionMethod = 0; // Magic value
    uint32_t rawBitmapDataSize = 0; // generally ignored
    int32_t horizontalResolution = 3780; // in pixel per meter, magic value
    int32_t verticalResolution = 3780; // in pixel per meter, magic value
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

#endif