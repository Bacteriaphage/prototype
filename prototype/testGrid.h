#pragma once
#include <GL/glew.h>
#include "Vertex.h"
#include "GLTexture.h"
#include <vector>
#include <string>

class TestGrid {
public:
	double granular;
	GLuint _vboID;
	GLTexture _texture;
	TestGrid(double);
	~TestGrid();
	void initGrid();
	void drawGrid();
	void initPlane(std::string);
	void drawPlane();
};