#include "Line.h"

Line::Line() {
	this->setP1(Point());
	this->setP2(Point());
}

Line::Line(Point p1, Point p2) {
	this->setP1(p1);
	this->setP2(p2);
}

Point Line::getP1() {
	return this->p1;
}

void Line::setP1(Point p) {
	this->p1 = p;
}

Point Line::getP2() {
	return this->p2;
}

void Line::setP2(Point p) {
	this->p2 = p;
}