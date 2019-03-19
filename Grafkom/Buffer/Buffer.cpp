#include "Buffer.h"

Buffer::Buffer() {

}

Buffer::Buffer(char* buffer, int width, int height) {
	this->buffer = buffer;
	this->width = width;
	this->height = height;
}

int Buffer::getWidth() {
	return this->width;
}

int Buffer::getHeight() {
	return this->height;
}

void Buffer::draw_color(Color col, Point p) {
	if (this->is_point_in_buffer(p)) {
		int i = (int)(p.getX());
		int j = (int)(p.getY());

		if (col.equals(Color(0, 0, 0))) {
			return;
		}
		else {
			this->buffer[(this->width * i + j) * 4] = col.getBlue();
			this->buffer[(this->width * i + j) * 4 + 1] = col.getGreen();
			this->buffer[(this->width * i + j) * 4 + 2] = col.getRed();
			this->buffer[(this->width * i + j) * 4 + 3] = 0;
		}
	}
}

Color Buffer::get_color_at_point(Point p) {
	Color c;
	if (this->is_point_in_buffer(p)) {
		int i = (int)(p.getX());
		int j = (int)(p.getY());
		
		c.setBlue(this->buffer[(this->width * i + j) * 4]);
		c.setGreen(this->buffer[(this->width * i + j) * 4 + 1]);
		c.setRed(this->buffer[(this->width * i + j) * 4 + 2]);

		return c;
	}
	else {
		c = Color(-1, -1, -1);
	}

	return c;
}

int Buffer::is_point_in_buffer(Point p) {
	bool is_x_in_buffer = p.getX() < this->height && p.getX() >= 0;
	bool is_y_in_buffer = p.getY() < this->width && p.getY() >= 0;

	return (is_x_in_buffer && is_y_in_buffer);
}

void Buffer::draw_to_buffer(Buffer* buff, Point init) {
	if (this->getHeight() + init.getX() > buff->getHeight() || this->getWidth() + init.getY() > buff->getWidth()) {
		return;
	}

	Color temp;
	for (int i = 0; i < this->getHeight(); i++) {
		for (int j = 0; j < this->getWidth(); j++) {
			Point src = Point(i, j);
			Point dest = Point(i + init.getX(), j + init.getY());

			temp = this->get_color_at_point(src);
			buff->draw_color(temp, dest);
		}
	}
}