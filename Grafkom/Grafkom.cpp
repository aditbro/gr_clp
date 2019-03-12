// Grafkom.cpp : Defines the entry point for the application.
//

#include "Grafkom.h"

using namespace std;

int main()
{
	Point p = Point(1, 2);

	cout << p.getX() << " " << p.getY() << endl;

	Line l = Line(Point(0, 0), Point(1, 1));

	cout << l.getP1().getX() << l.getP2().getX() << endl;

	Shape s = Shape();
	s.add_line(Line(Point(0, 0), Point(10, 0)));
	s.add_line(Line(Point(10, 0), Point(10, 10)));
	s.add_line(Line(Point(10, 10), Point(0, 10)));
	s.add_line(Line(Point(0, 10), Point(0, 0)));
	s.set_line_color(Color(255, 255, 255));
	s.set_shape_color(Color(255, 0, 255));

	for (int i = 0; i < s.get_num_of_lines(); i++) {
		cout << s.get_line(i).getP1().getX() << s.get_line(i).getP2().getX() << endl;
	}

	char d;
	cin >> d;
}
