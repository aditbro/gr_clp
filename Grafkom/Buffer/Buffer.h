#ifndef BUFFER_H
#define BUFFER_H

#include "../Renderable/Properties/Color/Color.h"
#include "../Renderable/Line/Line.h"
#include "../Renderable/Point//Point.h"
#include "../Renderable/Shape/Shape.h"

class Buffer {
protected:
	char* buffer;
	int width;
	int height;

public:
	Buffer();
	Buffer(char* buffer, int width, int height);

	int getWidth();
	int getHeight();

	void draw_color(Color c, Point p);
	Color get_color_at_point(Point p);

	void draw_to_buffer(Buffer* buff, Point init);

private:
	int is_point_in_buffer(Point p);
};

#endif // !BUFFER_H
