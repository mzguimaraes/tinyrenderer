#include <iostream>
#include <cstdlib>
#include <cmath>
#include "tgaimage.h"
#include "Model.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

const int width = 500;
const int height = 500;

void line(int x0, int y0, int x1, int y1, TGAImage& image, const TGAColor& color);
void draw_face(const Face* face, const Model* model, TGAImage& image, const TGAColor& color);
void line_between(Vertex* v0, Vertex* v1, TGAImage& image, const TGAColor& color);

int main(int argc, char** argv) {


	TGAImage image(width, height, TGAImage::RGB);
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image

	// draw mesh
	Model* mesh = new Model("head.obj");
	for (int i = 0; i < mesh->nfaces(); i ++) {
		const Face* face = mesh->face(i);
		
		draw_face(face, mesh, image, white);
	}

	// line(0,50,100,75, image, white);
	// line (20, 0, 30, 100, image, white);

	// if (argc >= 5) {
	// 	std::cout << "printing input line" << std::endl;
	// 	line(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), image, red);
	// }

	image.write_tga_file("output.tga");
	return 0;
}

void line(int x0, int y0, int x1, int y1, TGAImage &image, const TGAColor &color) {
	bool transposed = false;

	if (std::abs(x1-x0) < std::abs(y1-y0)) {
		//transpose so that the pixel density is determined by the dimension of greatest change
		std::swap(x0, y0);
		std::swap(x1, y1);
		transposed = true;
	}

	if (x0 > x1) {
		//swap coordinates so we draw left to right
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	int dx = x1 - x0;
	int dy = y1 - y0;

	//tracking deviation from ideal straight line path
	int derror2 = std::abs(dy) * 2; //change per pixel drawn
	int error2 = 0;
	int y = y0;

	for (int x = x0; x <= x1; x++) {
		if (transposed)
			image.set(y, x, color);
		else
			image.set(x, y, color);

		error2 += derror2;
		if (error2 > dx) {
			y += (y1 > y0 ? 1 : -1);
			error2 -= dx * 2;
		}
	}
}

void draw_face(const Face* face, const Model* model, TGAImage& image, const TGAColor& color) {
	//draw v0-v1
	line_between(model->vert(face->v0), 
				 model->vert(face->v1), 
				 image, color);

	//draw v1-v2
	line_between(model->vert(face->v1), 
				 model->vert(face->v2),
				 image, color);

	//draw v2-v0
	line_between(model->vert(face->v2),
				 model->vert(face->v0),
				 image, color);
}

void line_between(Vertex* v0, Vertex* v1, TGAImage& image, const TGAColor& color) {
	int x0 = (v0->x + 1.) * width/2;
	int y0 = (v0->y + 1.) * height/2;
	int x1 = (v1->x + 1.) * width/2;
	int y1 = (v1->y + 1.) * height/2;
	line(x0, y0, x1, y1, image, color);
}














