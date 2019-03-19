#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "Line/Line.h"
#include "Point/Point.h"
#include "Shape/Shape.h"
#include "Properties/Color/Color.h"

class Renderable {
protected:
	Point location;
	Shape shape;

public:
	Renderable();
	Renderable(Shape* sh, Point loc);

	Shape* get_shape();
	Point* get_location();

	void set_location(Point p);
};

#endif // !RENDERABLE_H
