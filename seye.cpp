#include "lodepng.h"
#include <stdint.h>
#include <iostream>

class Pixel {
	public:
		Pixel() {}
		Pixel(uint16_t r, uint16_t g, uint16_t b, uint16_t a) 
			: r_(r), g_(g), b_(b), a_(a) {}
		std::vector<uint16_t> getRGBA() {
			return { r_, g_, b_, a_ };
		}
		Pixel& operator=(const uint16_t* rgba) {
			r_ = rgba[0];
			g_ = rgba[1];
			b_ = rgba[2];
			a_ = rgba[3];
		}
		bool operator==(const Pixel*& rgba) {
			return 
				r_ == rgba->r_ && 
				g_ == rgba->g_ && 
				b_ == rgba->b_ &&
				a_ == rgba->a_;
		}
		void printt() {
			std::cout << r_ << " " << g_ << " " << b_ << " " << a_ << std::endl;
		}
	private:
		uint16_t r_, g_, b_, a_;
};

class Image {
	public:
		Image(const char* filename) {
			std::vector<uint8_t> rawData;
			unsigned error = lodepng::decode( rawData, width_, height_, filename);
			if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

			for(uint16_t i = 0; i < rawData.size(); i+=4) {
				data_.push_back(new Pixel(
						rawData[i],
						rawData[i+1], 
						rawData[i+2], 
						rawData[i+3]));
			}
		}
		Pixel* operator()(int x, int y) {
			return data_[y * width_ + x];
		}
		uint16_t getWidth() { return width_; }
		uint16_t getHeight() { return height_; }
	private:
		unsigned int width_;
		unsigned int height_;
		std::vector<Pixel*> data_;
};

int main(int argc, char* argv[]) {
	const char* filename = argc > 1 ? argv[1] : "maze.png";

	Image maze(filename);

	//pixelify();	
}
