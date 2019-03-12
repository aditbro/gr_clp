#ifndef RENDERABLE_H
#define RENDERABLE_H

class Renderable {
protected:
	Point location;
	Shape shape;

public:
	Renderable();
	Renderable(Shape* sh, Point loc);
};

#endif // !RENDERABLE_H
