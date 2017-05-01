#pragma once

#include <GL/glew.h>

struct Position {
    float x;
    float y;
	float z;
};

struct Color {
    GLubyte r;
    GLubyte g;
    GLubyte b;
    GLubyte a;
};

struct UV {
    float u;
    float v;
};

struct Normal {
	float x;
	float y;
	float z;
};
//The vertex definition
struct Vertex {
    //This is the position struct. When you store a struct or class
    //inside of another struct or class, it is called composition. This is
    //layed out exactly the same in memory as if we had a float position[2],
    //but doing it this way makes more sense.
    Position position;

    //4 bytes for r g b a color.
    Color color;

    //UV texture coordinates.
    UV uv;

	//normal vector
	Normal normal;

    void setPosition(float x, float y, float z) {
        position.x = x;
        position.y = y;
		position.z = z;
    }

    void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
        color.r = r;
        color.g = g;
        color.b = b;
        color.a = a;
    }

    void setUV(float u, float v) {
        uv.u = u;
        uv.v = v;
    }

	void setNormal(float x, float y, float z) {
		normal.x = x;
		normal.y = y;
		normal.z = z;
	}
};