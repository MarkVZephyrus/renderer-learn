#include <cmath>
#include <iostream>
#include "tgaimage.h"

const TGAColor white = TGAColor(255,255,255,255);
const TGAColor red = TGAColor(255, 0, 0, 255);

void line(int, int, int, int, TGAImage&, TGAColor);

int main(int argc, char** argv){
	TGAImage image(100, 100, TGAImage::RGB);
	line(20, 13, 40, 80, image, white);
	image.flip_vertically();
	image.write_tga_file("output.tga");
	return 0;
}

void line_dep(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color){	//slow
	
	bool steep = false;
	if(std::abs(x0-x1)<std::abs(y0-y1)){	//if the line is steep transpose line such that slope is <1 
						//and the rendered line is unbroken.
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}

	if(x0>x1){				//reverse line so that logic does not break.
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	float m = (y1 - y0)/(float)(x1 - x0); 	//slope
	std::cout << m;

	for(int x = x0; x <= x1; x++){
		int y = y0 + m*(x-x0);
		if(steep){
			image.set(y, x, color);	//restore transposed line.
		} else {
			image.set(x, y, color);
		}
	}	
}
/*
 *  Cooler way. 
 *  The derror2 variable is an approximiation of the slope.
 *  As of currently I do not fully understand this, when I do I'll change this.
 * */
void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) { 
    bool steep = false; 
    if (std::abs(x0-x1)<std::abs(y0-y1)) { 
        std::swap(x0, y0); 
        std::swap(x1, y1); 
        steep = true; 
    } 
    if (x0>x1) { 
        std::swap(x0, x1); 
        std::swap(y0, y1); 
    } 
    int dx = x1-x0; 
    int dy = y1-y0; 
    int derror2 = std::abs(dy)*2; 
    int error2 = 0; 
    int y = y0; 
    for (int x=x0; x<=x1; x++) { 
        if (steep) { 
            image.set(y, x, color); 
        } else { 
            image.set(x, y, color); 
        } 
        error2 += derror2; 
        if (error2 > dx) { 
            y += (y1>y0?1:-1); 
            error2 -= dx*2; 
        } 
    } 
} 
