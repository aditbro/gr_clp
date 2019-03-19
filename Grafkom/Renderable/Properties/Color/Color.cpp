#include "Color.h"

Color::Color() {
	Color(0, 0, 0);
}

Color::Color(int r, int g, int b) {
	this->setRed(r);
	this->setGreen(g);
	this->setBlue(b);
}

void Color::setRed(int r) {
	this->r = r;
}

void Color::setGreen(int g) {
	this->g = g;
}

void Color::setBlue(int b) {
	this->b = b;
}

int Color::getRed() {
	return this->r;
}

int Color::getGreen() {
	return this->g;
}

int Color::getBlue() {
	return this->b;
}

char* Color::toPixelArray() {
	char pixelArray[4];
	pixelArray[0] = (char)b;
	pixelArray[1] = (char)g;
	pixelArray[2] = (char)r;
	pixelArray[3] = (char)0;

	return pixelArray;
}

bool Color::equals(Color c) {
	return (this->r == c.r && this->g == c.g && this->b == c.b);
}