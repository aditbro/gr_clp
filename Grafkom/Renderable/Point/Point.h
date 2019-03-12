#ifndef POINT_H
#define POINT_H

class Point {
private:
	double x;
	double y;

public:
	Point();
	Point(double x, double y);
	
	double getX();
	void setX(double x);

	double getY();
	void setY(double y);
};


#endif
