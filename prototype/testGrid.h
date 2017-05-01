#pragma once
#include <GL/glew.h>
#include "Vertex.h"
#include <vector>

class TestGrid {
public:
	double granular;
	GLuint _vboID;

	TestGrid(double);
	~TestGrid();
	void init();
	void draw();
};