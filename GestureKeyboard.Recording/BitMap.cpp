#include "Bitmap.h"

using namespace std;

BitMap::BitMap()
{
	this->width = width;
	this->height = height;
	this->imgBuffer = new char[bmpInfoHeader.rawBitmapDataSize]{ 0x00 };
}

char* BitMap::getBmpBuffer()
{
	return this->imgBuffer;
}

void BitMap::setPixel(int x, int y, uint8_t b, uint8_t g, uint8_t r)
{
	int bufferPosition = ((x + (y * this->width)) * BITMAP_PIXEL_SIZE);
	this->imgBuffer[bufferPosition] = b;
	this->imgBuffer[bufferPosition+1] = g;
	this->imgBuffer[bufferPosition+2] = r;
}

int BitMap::getBufferSize()
{
	return this->bmpInfoHeader.rawBitmapDataSize;
}

int BitMap::getWidth()
{
	return this->width;
}

int BitMap::getHeight()
{
	return this->height;
}

void BitMap::writeToFile(const char* fileName)
{
	std::ofstream fout(fileName, ios::binary);

	fout.write((char*)&bmpHeader, 14);
	fout.write((char*)&bmpInfoHeader, 40);

	fout.write(imgBuffer, bmpInfoHeader.rawBitmapDataSize);

	fout.close();
}
