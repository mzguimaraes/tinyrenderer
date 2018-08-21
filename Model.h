#ifndef __MODEL_H__
#define __MODEL_H__

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include <stdio.h>
#include <stdlib.h>

struct Vertex {
	float x;
	float y;
	float z;
	Vertex(float x, float y, float z) : x(x), y(y), z(z) {}
};

struct Face {
	//indices of verts in face
	int v0;
	int v1;
	int v2;
	Face(int v0, int v1, int v2) : v0(v0), v1(v1), v2(v2) {}
};

struct Model {
	std::vector<Vertex*> verts;
	std::vector<Face*> faces;
	Model(const char* filename);
	int nfaces() const;
	int nverts() const;
	Face* face(int i) const;
	Vertex* vert(int i) const;
};

// struct Vertex {
// 	float x;
// 	float y;
// 	float z;
// 	Vertex(float X, float Y, float Z) : x(X), y(Y), z(Z) {}
// 	Vertex(std::string& X, std::string& Y, std::string& Z) :
// 		x(std::stof(X)), y(std::stof(Y)), z(std::stof(Z)) {}
// 	Vertex(Vertex& other) : x(other.x), y(other.y), z(other.z) {}
// };

// struct Face {
// 	Vertex* v0;
// 	Vertex* v1;
// 	Vertex* v2;
// 	Face(Vertex* V0, Vertex* V1, Vertex* V2) : v0(V0), v1(V1), v2(V2) {}
// 	Face(Face& other) : v0(new Vertex(*other.v0)),
// 						v1(new Vertex(*other.v1)),
// 						v2(new Vertex(*other.v2)) {}
// 	//TODO: assignment operator, destructor
// };

// class Model {
// public:
// 	std::vector<Vertex*> verts;
// 	std::vector<Face*> faces;

// 	Model(const char* filename);
// 	int nfaces() const;
// 	int nverts() const;

// 	//copy control
// 	//copy constructor
// 	Model(const Model& model);
// 	//destructor
// 	~Model();
// 	//assignment operator
// 	Model& operator = (const Model& rhs);
// };

//helper functions

void split(const std::string& str, std::vector<std::string>& v, const char* delim = " /");



























#endif