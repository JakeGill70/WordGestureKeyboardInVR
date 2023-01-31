#include "Bitmap.h"

// Holy cow look at that, I added a comment!
// What do you think about that?

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

// top and bottom should really be uint12_t, but that isn't a value, and working with bitfields got to be very cumbersome.
// Just make sure that the value of both doesn't exceed 4095, i.e. 2^12 - 1
void BitMap::setPixel(int bufferPosition, uint16_t top, uint16_t bottom)
{
	uint32_t combined = top;
	combined = combined << 12;
	combined = combined | bottom;

	uint8_t* const byteArray = reinterpret_cast<uint8_t*>(&combined);

	uint8_t b = byteArray[0];
	uint8_t g = byteArray[1];
	uint8_t r = byteArray[2];

	this->imgBuffer[bufferPosition] = b;
	this->imgBuffer[bufferPosition + 1] = g;
	this->imgBuffer[bufferPosition + 2] = r;
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
