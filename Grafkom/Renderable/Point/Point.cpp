#include "Point.h"

Point::Point() {
	this->setX(0);
	this->setY(0);
}

Point::Point(double x, double y) {
	this->setX(x);
	this->setY(y);
}

double Point::getX() {
	return this->x;
}

void Point::setX(double x) {
	this->x = x;
}

double Point::getY() {
	return this->y;
}

void Point::setY(double y) {
	this->y = y;
}