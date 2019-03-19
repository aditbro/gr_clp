#include "Renderable.h"

Renderable::Renderable() {

}

Renderable::Renderable(Shape* sh, Point loc) {
	this->shape = *sh;
	this->location = loc;
}

Shape* Renderable::get_shape() {
	return &this->shape;
}

Point* Renderable::get_location() {
	return &this->location;
}

void Renderable::set_location(Point p) {
	this->location = p;
}