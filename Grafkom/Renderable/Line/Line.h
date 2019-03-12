#ifndef LINE_H
#define LINE_H

#include "../Point/Point.h"

class Line {
private:
	Point p1;
	Point p2;

public:
	Line();
	Line(Point p1, Point p2);

	Point getP1();
	void setP1(Point p);

	Point getP2();
	void setP2(Point p);
};


#endif
