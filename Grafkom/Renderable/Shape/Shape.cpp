#include "Shape.h"

Shape::Shape() {

}

Shape::Shape(Line* lines, int num_line) {
	this->lines.assign(lines, lines + num_line);
}

Shape::Shape(std::vector<Line> lines) {
	this->lines = std::vector<Line>(lines);
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

Line Shape::get_line(int line_idx) {
	return this->lines.at(line_idx);
}

int Shape::get_num_of_lines() {
	return this->lines.size();
}

void Shape::set_line_color(Color c) {
	this->line_color = c;
}

void Shape::set_shape_color(Color c) {
	this->shape_color = c;
}