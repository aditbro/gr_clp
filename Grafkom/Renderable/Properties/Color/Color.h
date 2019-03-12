#ifndef COLOR_H
#define COLOR_H

class Color {
private:
	int r;
	int g;
	int b;

public:
	Color();
	Color(int r, int g, int b);

	void setRed(int r);
	void setGreen(int g);
	void setBlue(int b);

	int getRed();
	int getGreen();
	int getBlue();

	char* toPixelArray();
};

#endif // !COLOR_H
