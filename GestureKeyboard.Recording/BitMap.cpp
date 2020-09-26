#include "Bitmap.h"

using namespace std;

BitMap::BitMap(int width, int height)
{
	this->width = width;
	this->height = height;
	this->bufferSize = BITMAP_HEADER_TOTAL_SIZE + (width * height * BITMAP_PIXEL_SIZE);
	this->bmpHeader.sizeOfBitmapFile = this->bufferSize;
	this->bmpInfoHeader.width = (uint32_t)width;
	this->bmpInfoHeader.height = (uint32_t)height;
	this->bmpBuffer = new char[this->bufferSize]{ 0x00 };
}

char* BitMap::getBmpBuffer()
{
	return this->bmpBuffer;
}

void BitMap::setPixel(int x, int y, Pixel& pixel)
{
	setPixel(x, y, pixel.blue, pixel.green, pixel.red);
}

void BitMap::setPixel(int x, int y, uint8_t b, uint8_t g, uint8_t r)
{
	int bufferPosition = ((x + (y * this->width)) * BITMAP_PIXEL_SIZE) + BITMAP_HEADER_TOTAL_SIZE;
	this->bmpBuffer[bufferPosition] = b;
	this->bmpBuffer[bufferPosition+1] = g;
	this->bmpBuffer[bufferPosition+2] = r;
}

int BitMap::getBufferSize()
{
	return this->bufferSize;
}

int BitMap::getWidth()
{
	return this->width;
}

int BitMap::getHeight()
{
	return this->height;
}

Pixel BitMap::getPixel(int x, int y)
{
	int bufferPosition = ((x + (y * this->width)) * BITMAP_PIXEL_SIZE) + BITMAP_HEADER_TOTAL_SIZE;
	uint32_t  b = this->bmpBuffer[bufferPosition];
	uint32_t  g = this->bmpBuffer[bufferPosition + 1];
	uint32_t  r = this->bmpBuffer[bufferPosition + 2];
	return Pixel(b, g, r);
}
