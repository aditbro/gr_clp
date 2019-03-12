#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include "../Line/Line.h"
#include "../Properties/Color/Color.h"

class Shape {
protected:
	std::vector<Line> lines;
	Color shape_color;
	Color line_color;

public:
	Shape();
	Shape(Line* lines, int num_line);
	Shape(std::vector<Line> lines);

	void add_line(Line l);
	int del_line(int line_idx);

	Line get_line(int line_idx);
	int get_num_of_lines();

	void set_line_color(Color c);
	void set_shape_color(Color c);
};

#endif // !SHAPE_H
