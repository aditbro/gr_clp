#ifndef COLOR_H
#define COLOR_H

class Color {
private:
	char r;
	char g;
	char b;

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
	bool equals(Color c);
};

#endif // !COLOR_H
