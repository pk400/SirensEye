#include "lodepng.h"
#include <iostream>

struct Pixel {
	Pixel() {};
	Pixel(unsigned char tr, unsigned char tg, unsigned char tb, unsigned char ta)
		: r(tr), g(tg), b(tb), a(ta) {	
	}
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
	void print() {
		printf("%u %u %u %u\n", r, g, b, a);
	}
	/* 
	 * Allows for easy RGBA value assignment to the pixel at coordinates x and y
	 * Example usage: maze(x, y) = (unsigned char*)rgba
	 */
	Pixel& operator=(const unsigned char* rgba) {
		r = rgba[0];
		b = rgba[1];
		g = rgba[2];
		a = rgba[3];
	}
	bool operator==(const Pixel& rgba) {
		return r == rgba.r
			&& g == rgba.g
			&& b == rgba.b
			&& a == rgba.a;
	}
} BLACK(255, 255, 255, 255), WHITE(0, 0, 0, 255);

struct image {
	unsigned height;
	unsigned width;
	std::vector<unsigned char> data;
	Pixel** pixel;
	/*
	 * Allows for easy access to the pixel at coordinates x and y
	 * Example usage: maze(x, y).print()
	 */
	Pixel& operator()(int x, int y) {
		return pixel[x][y];
	}
} maze;

/*
 * pixelify() initializes a grid populated with pixels
 */
void pixelify() {
	int idx = 0; // Keeps track of the current position in the maze.data vector

	maze.pixel = new Pixel*[maze.width];
	for(int x = 0; x < maze.width; x++) {
		maze.pixel[x] = new Pixel[maze.height];
		for(int y = 0; y < maze.height; y++) {
			unsigned char rgba[4] = {
				maze.data[idx++], maze.data[idx++],
				maze.data[idx++], maze.data[idx++]
			};

			// Allocates RGBA values for pixels at coordinates x and y
			maze(x,y) = rgba;
			if(maze(x, y) == WHITE) {
				std::cout << "#";
			}
			else {
				std::cout << " ";
			}
			//maze(x, y).print();
		}
		std::cout << std::endl;
	}
}

void decodePNG(const char* filename) {
	unsigned error = lodepng::decode(maze.data, maze.width, maze.height, filename);

	if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
}

int main(int argc, char* argv[]) {
	const char* filename = argc > 1 ? argv[1] : "maze.png";

	decodePNG(filename);
	pixelify();	
}
