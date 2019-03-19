#include "Renderer.h"
#include <cstdlib>
#include <queue>
#include <iostream>

// Helper function declarations
int get_line_direction(Point bp1, Point bp2);
Point get_point_inside(Renderable* rd, Buffer* buff);
bool is_point_inside(Point p, Renderable* rd, Buffer* buff);
bool is_in_clipping_plane(Renderable& rd, double size_i, double size_j, Point init);
Renderable clip_shape(Renderable& rd, double size_i, double size_j, Point init);
Line clip_line(Line ln, double size_i, double size_j, Point init);

Point Renderer::get_buffer_point(Point p, Buffer* buff) {
	Point buffer_point;
	buffer_point.setX((int)(p.getX() * buff->getHeight()));
	buffer_point.setY((int)(p.getY() * buff->getWidth()));

	return buffer_point;
}

void Renderer::Render_renderable_to_buffer(Renderable* rd, Buffer* buff) {
	if (rd->get_shape()->get_num_of_lines() > 1) {
		for (int i = 0; i < rd->get_shape()->get_num_of_lines(); i++) {
			Renderer::Render_line_to_buffer(rd->get_shape()->get_line(i), *rd->get_location(), rd->get_shape()->get_line_color(), buff);
		}
		////std::cout << std::endl;

		Renderer::Render_color(rd, buff);
	}
	else {
		for (int i = 0; i < rd->get_shape()->get_num_of_lines(); i++) {
			Renderer::Render_line_to_buffer(rd->get_shape()->get_line(i), *rd->get_location(), rd->get_shape()->get_line_color(), buff);
		}
	}
}

void Renderer::Render_color(Renderable* rd, Buffer* buff) {
	Point initial_drawing_point = get_point_inside(rd, buff);	

	std::queue<Point> point_queue = std::queue<Point>();
	point_queue.push(initial_drawing_point);
	Point p;
	int i, j;
	Color shape_color = rd->get_shape()->get_shape_color();
	Color line_color = rd->get_shape()->get_line_color();

	while (!point_queue.empty()) {
		p = point_queue.front();
		i = p.getX();
		j = p.getY();

		if (!buff->get_color_at_point(p).equals(shape_color) 
			&& !buff->get_color_at_point(p).equals(line_color)
			&& i >= 0 && i < buff->getHeight() 
			&& j >= 0 && j < buff->getWidth()) 
		{
			buff->draw_color(shape_color, p);
			point_queue.push(Point(i + 1, j));
			point_queue.push(Point(i, j + 1));
			point_queue.push(Point(i - 1, j));
			point_queue.push(Point(i, j - 1));
		}

		point_queue.pop();
	}
}

Point get_point_inside(Renderable* rd, Buffer* buff) {
	Point init = *rd->get_location();

	double top = rd->get_shape()->get_highest_point().getX();
	double bottom = rd->get_shape()->get_lowest_point().getX();

	double leftmost = rd->get_shape()->get_leftmost_point().getY();
	double rightmost = rd->get_shape()->get_rightmost_point().getY();

	Point check_point = Renderer::get_buffer_point(Point(init.getX()+(top + bottom) / 2, init.getY()+(leftmost + rightmost) / 2), buff);

	return check_point;
}

void Renderer::Render_line_to_buffer(Line* ln, Point init, Color col, Buffer* buff) {
	Point p1 = Renderer::get_buffer_point(ln->getP1(), buff);
	Point p2 = Renderer::get_buffer_point(ln->getP2(), buff);
	init = Renderer::get_buffer_point(init, buff);
	//std::cout << p1.getX() << "," << p1.getY() << " " << p2.getX() << "," << p2.getY() << std::endl;

	Point p_start;
	Point p_end;
	int i, j, di, dj, end;

	int line_direction = get_line_direction(p1, p2);

	if (line_direction == 1 || line_direction == 2) {
		p_start = p1;
		p_end = p2;
	}
	else {
		p_end = p1;
		p_start = p2;
	}

	if (line_direction % 2 == 1) {
		dj = (int)p_end.getY() - p_start.getY();
		di = (int)p_end.getX() - p_start.getX();
		j = (int)p_start.getY(), i = p_start.getX();
		end = (int)p_end.getY();
	}
	else {
		dj = (int)p_end.getX() - p_start.getX();
		di = (int)p_end.getY() - p_start.getY();
		j = (int)p_start.getX(), i = p_start.getY();
		end = (int)p_end.getX();
	}

	//drawing the line
	int adjust_i = (di < 0 ? -1 : 1);

	di = abs(di);
	dj = abs(dj);
	int p = 2 * di - dj;
	for (; j <= end; j++) {
		if (line_direction % 2 == 1) {
			buff->draw_color(col, Point(i + init.getX(), j + init.getY()));
		}
		else {
			buff->draw_color(col, Point(j + init.getX(), i + init.getY()));

		}
		if (p < 0) {
			p = p + 2 * di;
		}
		else {
			i = i + adjust_i;
			p = p + 2 * di - (2 * dj);
		}
	}
}

std::vector<Renderable> Renderer::clip(std::vector<Renderable> shape_list, double size_i, double size_j, Point init) {
	std::vector<Renderable> clipped_shape;
	double ratio_i = 1 / size_i;
	double ratio_j = 1 / size_j;

	for (Renderable rd : shape_list) {
		if (is_in_clipping_plane(rd, size_i, size_j, init)) {
			clipped_shape.push_back(clip_shape(rd, size_i, size_j, init));
		}
	}

	for (Renderable rd : clipped_shape) {
		Point init_location = *rd.get_location();
		init_location.setX(init_location.getX() - init.getX());
		init_location.setY(init_location.getY() - init.getY());

		rd.set_location(init_location);

		for (Line ln : rd.get_shape()->get_lines()) {
			Point prev_point = ln.getP1();
			////std::cout << "before p1 " << prev_point.getX() << "," << prev_point.getY() << std::endl;
			prev_point.setX(ratio_i * (prev_point.getX()));
			prev_point.setY(ratio_j * (prev_point.getY()));

			ln.setP1(prev_point);
			////std::cout << "p1 " << prev_point.getX() << "," << prev_point.getY() << std::endl;

			prev_point = ln.getP2();
			////std::cout << "before p2 " << prev_point.getX() << "," << prev_point.getY() << std::endl;
			prev_point.setX(ratio_i * (prev_point.getX()));
			prev_point.setY(ratio_j * (prev_point.getY()));

			////std::cout << "p2 " << prev_point.getX() << "," << prev_point.getY() << std::endl;
			ln.setP2(prev_point);
		}

		////std::cout << std::endl;
	}

	return clipped_shape;
}

Renderable clip_shape(Renderable& rd, double size_i, double size_j, Point init) {
	double leftmost = init.getY();
	double rightmost = leftmost + size_j;
	double top = init.getX();
	double bottom = top + size_i;

	Shape sh = Shape();
	sh.set_line_color(rd.get_shape()->get_line_color());
	sh.set_shape_color(rd.get_shape()->get_shape_color());
	Point p1;
	Point p2;

	for (Line ln : rd.get_shape()->get_lines()) {
		p1 = Point(ln.getP1().getX() + rd.get_location()->getX(), ln.getP1().getY() + rd.get_location()->getY());
		p2 = Point(ln.getP2().getX() + rd.get_location()->getX(), ln.getP2().getY() + rd.get_location()->getY());
		Line new_line = Line(p1, p2);
		bool line_outside = p1.getX() < top || p1.getX() > bottom || p1.getY() < leftmost || p1.getY() < rightmost;
		line_outside = line_outside || p2.getX() < top || p2.getX() > bottom || p2.getY() < leftmost || p2.getY() < rightmost;

		if (line_outside) {
			new_line = clip_line(new_line, size_i, size_j, init);
		}

		sh.add_line(new_line);
	}

	Renderable rds = Renderable(&sh, *rd.get_location());
	return rds;
}

Line clip_line(Line ln, double size_i, double size_j, Point init) {
	double leftmost = init.getY();
	double rightmost = leftmost + size_j;
	double top = init.getX();
	double bottom = top + size_i;
	
	double m = ((ln.getP1().getX() - ln.getP2().getX()) / (ln.getP1().getY() - ln.getP2().getY()));
	Point p1 = ln.getP1();
	Point p2 = ln.getP2();
	////std::cout << "p1 " << ln.getP1().getX() << "," << ln.getP1().getY() << std::endl;
	////std::cout << "p2 " << ln.getP2().getX() << "," << ln.getP2().getY() << std::endl;
	////std::cout << "m " << m << std::endl;
	if (p1.getX() < top) {
		////std::cout << "top p1 before " << p1.getX() << "," << p1.getY() << std::endl;
		p1.setX(top);
		if (dx > -0.001 && dx < 0.001) {
			p1.setY(p1.getY());
		}
		else {
			p1.setY(1 / m * (top - p2.getX()) + p2.getY());
		}
		////std::cout << "top p1 after" << p1.getX() << "," << p1.getY() << std::endl;
	}
	else if (p1.getX() > bottom) {
		////std::cout << "bottom p1 before " << p1.getX() << "," << p1.getY() << std::endl;
		p1.setX(bottom);
		if (dx > -0.001 && dx < 0.001) {
			p1.setY(p1.getY());
		}
		else {
			p1.setY(1 / m * (bottom - p2.getX()) + p2.getY());
		}
		////std::cout << "bottom p1 after " << p1.getX() << "," << p1.getY() << std::endl;
	}

	if (p1.getY() < leftmost) {
		////std::cout << "left p1 before " << p1.getX() << "," << p1.getY() << std::endl;
		p1.setY(leftmost);
		if (dy > -0.001 && dy < 0.001) {
			p1.setX(p1.getX());
		}
		else {
			p1.setX(m * (leftmost - p2.getY()) + p2.getX());
		}
		////std::cout << "bottom p1 after " << p1.getX() << "," << p1.getY() << std::endl;
	} 
	else if (p1.getY() > rightmost) {
		////std::cout << "right p1 before " << p1.getX() << "," << p1.getY() << std::endl;
		p1.setY(rightmost);
		if (dy > -0.001 && dy < 0.001) {
			p1.setX(p1.getX());
		}
		else {
			p1.setX(m * (rightmost - p2.getY()) + p2.getX());
		}
		////std::cout << "right p1 after " << p1.getX() << "," << p1.getY() << std::endl;
	}

	if (p2.getX() < top) {
		////std::cout << "top p2 before " << p2.getX() << "," << p2.getY() << std::endl;
		p2.setX(top);
		if (dx > -0.001 && dx < 0.001) {
			p2.setY(p2.getY());
		}
		else {
			p2.setY(1 / m * (top - p2.getX()) + p1.getY());
		}
		////std::cout << "top p2 after " << p2.getX() << "," << p2.getY() << std::endl;
	}
	else if (p2.getX() > bottom) {
		////std::cout << "bottom p2 before " << p2.getX() << "," << p2.getY() << std::endl;
		p2.setX(bottom);
		if (dx > -0.001 && dx < 0.001) {
			p2.setY(p2.getY());
		}
		else {
			p2.setY(1 / m * (bottom - p1.getX()) + p1.getY());
		}
		////std::cout << "bottom p2 after " << p2.getX() << "," << p2.getY() << std::endl;
	}

	if (p2.getY() < leftmost) {
		////std::cout << "left p2 before " << p2.getX() << "," << p2.getY() << std::endl;
		p2.setY(leftmost);
		if (dy > -0.001 && dy < 0.001) {
			p2.setX(p2.getX());
		}
		else {
			p2.setX(m * (leftmost - p1.getY()) + p1.getX());
		}
		////std::cout << "left p2 after " << p2.getX() << "," << p2.getY() << std::endl;
	}
	else if (p2.getY() > rightmost) {
		////std::cout << "right p2 before " << p2.getX() << "," << p2.getY() << std::endl;
		p2.setY(rightmost);
		if (dy > -0.001 && dy < 0.001) {
			p2.setX(p2.getX());
		}
		else {
			p2.setX(m * (rightmost - p1.getY()) + p1.getX());
		}
		////std::cout << "right p2 after " << p2.getX() << "," << p2.getY() << std::endl;
	}

	return Line(p1, p2);
}

bool is_in_clipping_plane(Renderable& rd, double size_i, double size_j, Point init) {
	double leftmost = init.getY();
	double rightmost = leftmost + size_j;
	double top = init.getX();
	double bottom = top + size_i;

	int p1_score = 0;
	int p2_score = 0;
	Point p1;
	Point p2;

	for (Line ln : rd.get_shape()->get_lines()) {
		p1 = Point(ln.getP1().getX() + rd.get_location()->getX(), ln.getP1().getY() + rd.get_location()->getY());
		p2 = Point(ln.getP2().getX() + rd.get_location()->getX(), ln.getP2().getY() + rd.get_location()->getY());

		if (p1.getY() < leftmost) {
			p1_score = p1_score | 1;
		}
		if (p2.getY() < leftmost) {
			p2_score = p2_score | 1;
		}

		if (p1.getY() > rightmost) {
			p1_score = p1_score | 2;
		}
		if (p2.getY() > rightmost) {
			p2_score = p2_score | 2;
		}

		if (p1.getX() < top) {
			p1_score = p1_score | 8;
		}
		if (p2.getX() < top) {
			p2_score = p2_score | 8;
		}

		if (p1.getX() > bottom) {
			p1_score = p1_score | 4;
		}
		if (p2.getX() > bottom) {
			p2_score = p2_score | 4;
		}

		if (!(p1_score & p2_score)) {
			return true;
		}

		p1_score = 0;
		p2_score = 0;
	}

	return false;
}

int get_line_direction(Point bp1, Point bp2) {
	int di = (int)(bp2.getX() - bp1.getX());
	int dj = (int)(bp2.getY() - bp1.getY());

	if (abs(dj) > abs(di)) {
		if (dj > 0) {
			return 1;
		}
		else {
			return 3;
		}
	}
	else {
		if (di > 0) {
			return 2;
		}
		else {
			return 4;
		}
	}
}

bool is_point_inside(Point checked_point, Renderable* rd, Buffer* buff) {
	return true;
};