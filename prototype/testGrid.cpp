#include "testGrid.h"
#include <cstddef>

TestGrid::TestGrid(double gran = 1.0f) {
	_vboID = 0;
	granular = gran;
	
}
TestGrid::~TestGrid(){
		if (_vboID != 0) {
			glDeleteBuffers(1, &_vboID); //is 2 ok?
		}
}

void TestGrid::init() {
	if (_vboID == 0) {
		glGenBuffers(1, &_vboID);
	}
	Vertex vertexData[204];
	vertexData[200].setPosition(25 * granular, 0.0, 0.0);
	vertexData[201].setPosition(-25 * granular, 0.0, 0.0);
	vertexData[202].setPosition(0.0, 0.0, 25 * granular);
	vertexData[203].setPosition(0.0, 0.0, -25 * granular);
	vertexData[200].setColor(255, 255, 255, 100);
	vertexData[201].setColor(255, 255, 255, 100);
	vertexData[202].setColor(255, 255, 255, 100);
	vertexData[203].setColor(255, 255, 255, 100);
	vertexData[200].setNormal(0, 1, 0);
	vertexData[201].setNormal(0, 1, 0);
	vertexData[202].setNormal(0, 1, 0);
	vertexData[203].setNormal(0, 1, 0);
	for (int i = 0; i < 25; i++) {
		vertexData[0 + i * 8].setNormal(0, 1, 0);
		vertexData[1 + i * 8].setNormal(0, 1, 0);
		vertexData[2 + i * 8].setNormal(0, 1, 0);
		vertexData[3 + i * 8].setNormal(0, 1, 0);
		vertexData[0 + i * 8].setPosition(25 * granular, 0.0, i * granular);
		vertexData[1 + i * 8].setPosition(-25 * granular, 0.0, i * granular);
		vertexData[2 + i * 8].setPosition(i * granular, 0.0, 25 * granular);
		vertexData[3 + i * 8].setPosition(i * granular, 0.0, -25 * granular);
		vertexData[0 + i * 8].setColor(255, 255, 255, 100);
		vertexData[1 + i * 8].setColor(255, 255, 255, 100);
		vertexData[2 + i * 8].setColor(255, 255, 255, 100);
		vertexData[3 + i * 8].setColor(255, 255, 255, 100);

		vertexData[4 + i * 8].setNormal(0, 1, 0);
		vertexData[5 + i * 8].setNormal(0, 1, 0);
		vertexData[6 + i * 8].setNormal(0, 1, 0);
		vertexData[7 + i * 8].setNormal(0, 1, 0);
		vertexData[4 + i * 8].setPosition(25 * granular, 0.0, -i * granular);
		vertexData[5 + i * 8].setPosition(-25 * granular, 0.0, -i * granular);
		vertexData[6 + i * 8].setPosition(-i * granular, 0.0, 25 * granular);
		vertexData[7 + i * 8].setPosition(-i * granular, 0.0, -25 * granular);
		vertexData[4 + i * 8].setColor(255, 255, 255, 100);
		vertexData[5 + i * 8].setColor(255, 255, 255, 100);
		vertexData[6 + i * 8].setColor(255, 255, 255, 100);
		vertexData[7 + i * 8].setColor(255, 255, 255, 100);
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void TestGrid::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glDrawArrays(GL_LINES, 0, 204);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
