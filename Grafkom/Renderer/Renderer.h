#ifndef RENDERER_H
#define RENDERER_H

#include "../Buffer/Buffer.h"
#include "../Renderable/Renderable.h"
#include <vector>

class Renderer {
public:
	static void Render_renderable_to_buffer(Renderable* sh, Buffer* buffer);
	static void Render_line_to_buffer(Line* ln, Point init, Color c, Buffer* buffer);
	static Point get_buffer_point(Point renderable_point, Buffer* buffer);
	static void Render_color(Renderable* rd, Buffer* buff);
	static std::vector<Renderable> clip(std::vector<Renderable> rd, double size_i, double size_j, Point init);
};


#endif // !RENDERER_H
