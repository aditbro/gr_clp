#include "Shape.h"

Shape::Shape() {

}

Shape::Shape(Line* lines, int num_line) {
	this->lines.assign(lines, lines + num_line);
}

Shape::Shape(std::vector<Line> lines) {
	this->lines = std::vector<Line>(lines);
	this->set_line_color(Color(255, 255, 255));
	this->set_shape_color(Color(255, 255, 255));
}

void Shape::add_line(Line l) {
	this->lines.push_back(l);
}

int Shape::del_line(int line_idx) {
	if (line_idx > this->get_num_of_lines()) {
		return 1;
	}
	else {
		this->lines.erase(this->lines.begin() + line_idx);
		return 0;
	}
}

Line* Shape::get_line(int line_idx) {
	return &this->lines.at(line_idx);
}

std::vector<Line> Shape::get_lines() {
	return this->lines;
}

int Shape::get_num_of_lines() {
	return this->lines.size();
}

void Shape::set_line_color(Color c) {
	this->line_color = c;
}

Color Shape::get_line_color() {
	return this->line_color;
}

void Shape::set_shape_color(Color c) {
	this->shape_color = c;
}

Color Shape::get_shape_color() {
	return this->shape_color;
}

Point Shape::get_lowest_point() {
	Point highest_point = Point(-1, -1);
	Point p1;
	Point p2;

	for (Line l : this->lines) {
		p1 = l.getP1();
		p2 = l.getP2();

		if (p1.getX() > highest_point.getX()) {
			highest_point = p1;
		}

		if (p2.getX() > highest_point.getX()) {
			highest_point = p2;
		}
	}

	return highest_point;
}

Point Shape::get_highest_point() {
	Point lowest_point = Point(1, 1);
	Point p1;
	Point p2;

	for (Line l : this->lines) {
		p1 = l.getP1();
		p2 = l.getP2();

		if (p1.getX() < lowest_point.getX()) {
			lowest_point = p1;
		}

		if (p2.getX() < lowest_point.getX()) {
			lowest_point = p2;
		}
	}

	return lowest_point;
}

Point Shape::get_leftmost_point() {
	Point leftmost_point = Point(1, 1);
	Point p1;
	Point p2;

	for (Line l : this->lines) {
		p1 = l.getP1();
		p2 = l.getP2();

		if (p1.getY() < leftmost_point.getY()) {
			leftmost_point = p1;
		}

		if (p2.getY() < leftmost_point.getY()) {
			leftmost_point = p2;
		}
	}

	return leftmost_point;
}

Point Shape::get_rightmost_point() {
	Point rightmost_point = Point(0, 0);
	Point p1;
	Point p2;

	for (Line l : this->lines) {
		p1 = l.getP1();
		p2 = l.getP2();

		if (p1.getY() > rightmost_point.getY()) {
			rightmost_point = p1;
		}

		if (p2.getY() > rightmost_point.getY()) {
			rightmost_point = p2;
		}
	}

	return rightmost_point;
}