// Grafkom.cpp : Defines the entry point for the application.
//

#include "Grafkom.h"
#include <cstdlib>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>


using namespace std;

Buffer get_image_buffer(char* dir, int width, int height) {
	int fb_fd = 0;
	int SCREEN_SIZE = width * height * 4;
	fb_fd = open(dir, O_RDWR);
	char * fb = (char*)mmap(NULL,
		SCREEN_SIZE,
		PROT_READ | PROT_WRITE, MAP_FILE | MAP_SHARED,
		fb_fd,
		0);
	Buffer b = Buffer(fb, width, height);

	return b;
}

std::vector<Renderable> get_itb_building();

int main()
{
	vector<Renderable> peta_itb = get_itb_building();
	peta_itb = Renderer::clip(peta_itb, 0.5, 0.5, Point(0.0, 0.0));
	Buffer frame_buffer = get_image_buffer("/dev/fb0", 1176, 800);

	char* mb = (char*)malloc(400 * 600 * 4);
	Buffer map_buffer = Buffer(mb, 400, 600);

	char* tb = (char*)malloc(200 * 300 * 4);
	Buffer thumbnail_buffer = Buffer(tb, 200, 300);

	for (Renderable rd : peta_itb) {
		Renderer::Render_renderable_to_buffer(&rd, &map_buffer);
		Renderer::Render_renderable_to_buffer(&rd, &thumbnail_buffer);
	}

	
	map_buffer.draw_to_buffer(&frame_buffer, Point(0, 400));
	thumbnail_buffer.draw_to_buffer(&frame_buffer, Point(150, 50));
	

	char d;
	cin >> d;
}

std::vector<Renderable> get_itb_building() {
	std::vector<Renderable> itb_map;

	Shape sipil = Shape();
	sipil.set_line_color(Color(255, 255, 255));
	sipil.set_shape_color(Color(255, 255, 255));
	sipil.add_line(Line(Point(0, 0), Point(0, 0.4)));
	sipil.add_line(Line(Point(0, 0.4), Point(0.15, 0.4)));
	sipil.add_line(Line(Point(0.15, 0.4), Point(0.15, 0.1)));
	sipil.add_line(Line(Point(0.15, 0.1), Point(0, 0)));
	Renderable map_sipil = Renderable(&sipil, Point(0.85, 0));
	itb_map.push_back(map_sipil);

	Shape seni_rupa = Shape();
	seni_rupa.set_line_color(Color(255, 255, 255));
	seni_rupa.set_shape_color(Color(255, 255, 255));
	seni_rupa.add_line(Line(Point(0, 0), Point(0, 0.4)));
	seni_rupa.add_line(Line(Point(0, 0.4), Point(0.15, 0.3)));
	seni_rupa.add_line(Line(Point(0.15, 0.3), Point(0.15, 0)));
	seni_rupa.add_line(Line(Point(0.15, 0), Point(0, 0)));
	Renderable map_seni_rupa = Renderable(&seni_rupa, Point(0.85, 0.6));
	itb_map.push_back(map_seni_rupa);

	Shape labtek = Shape();
	labtek.set_line_color(Color(255, 255, 255));
	labtek.set_shape_color(Color(255, 255, 255));
	labtek.add_line(Line(Point(0, 0), Point(0, 0.4)));
	labtek.add_line(Line(Point(0, 0.4), Point(0.05, 0.4)));
	labtek.add_line(Line(Point(0.05, 0.4), Point(0.05, 0.0)));
	labtek.add_line(Line(Point(0.05, 0.0), Point(0.0, 0.0)));
	Renderable ctim = Renderable(&labtek, Point(0.65, 0.05));
	Renderable cbar = Renderable(&labtek, Point(0.65, 0.55));

	itb_map.push_back(ctim);
	itb_map.push_back(cbar);

	Renderable labtek_v = Renderable(&labtek, Point(0.55, 0.05));
	Renderable labtek_vi = Renderable(&labtek, Point(0.485, 0.05));
	Renderable labtek_vii = Renderable(&labtek, Point(0.55, 0.55));
	Renderable labtek_viii = Renderable(&labtek, Point(0.485, 0.55));

	itb_map.push_back(labtek_v);
	itb_map.push_back(labtek_vi);
	itb_map.push_back(labtek_vii);
	itb_map.push_back(labtek_viii);

	Shape oktagon = Shape();
	oktagon.set_shape_color(Color(255, 255, 255));
	oktagon.set_line_color(Color(255, 255, 255));
	oktagon.add_line(Line(Point(0.00, 0.02), Point(0.00, 0.08)));
	oktagon.add_line(Line(Point(0.00, 0.08), Point(0.02, 0.10)));
	oktagon.add_line(Line(Point(0.02, 0.10), Point(0.06, 0.10)));
	oktagon.add_line(Line(Point(0.06, 0.10), Point(0.08, 0.08)));
	oktagon.add_line(Line(Point(0.08, 0.08), Point(0.08, 0.02)));
	oktagon.add_line(Line(Point(0.08, 0.02), Point(0.06, 0.00)));
	oktagon.add_line(Line(Point(0.06, 0.00), Point(0.02, 0.00)));
	oktagon.add_line(Line(Point(0.02, 0.00), Point(0.00, 0.02)));
	
	Renderable tvst = Renderable(&oktagon, Point(0.375, 0.35));
	Renderable gd_oktagon = Renderable(&oktagon, Point(0.285, 0.35));

	itb_map.push_back(tvst);
	itb_map.push_back(gd_oktagon);

	Shape comlabs = Shape();
	comlabs.set_shape_color(Color(255, 255, 255));
	comlabs.set_line_color(Color(255, 255, 255));
	comlabs.add_line(Line(Point(0.00, 0.02), Point(0.00, 0.20)));
	comlabs.add_line(Line(Point(0.00, 0.20), Point(0.02, 0.22)));
	comlabs.add_line(Line(Point(0.02, 0.22), Point(0.06, 0.22)));
	comlabs.add_line(Line(Point(0.06, 0.22), Point(0.08, 0.20)));
	comlabs.add_line(Line(Point(0.08, 0.20), Point(0.08, 0.02)));
	comlabs.add_line(Line(Point(0.08, 0.02), Point(0.06, 0.00)));
	comlabs.add_line(Line(Point(0.06, 0.00), Point(0.02, 0.00)));
	comlabs.add_line(Line(Point(0.02, 0.00), Point(0.00, 0.02)));

	Renderable gd_pln = Renderable(&comlabs, Point(0.375, 0.55));
	Renderable labfis = Renderable(&comlabs, Point(0.285, 0.55));

	itb_map.push_back(gd_pln);
	itb_map.push_back(labfis);

	return itb_map;
}