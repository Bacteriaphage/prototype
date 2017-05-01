#pragma once
#include <GL/glew.h>
#include "GLTexture.h"
#include <glm\/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>

//A 2D quad that can be rendered to the screen
class Sprite
{
public:
    Sprite();
    ~Sprite();

    void init(float x, float y, float z, float len, float wid, float hei, std::string texturePath);

    void draw();
    
//private:
    float _x;
    float _y;
	float _z;
    float _width;
    float _height;
	float _length;
    GLuint _vboID;
    GLTexture _texture;

};

class Bullet : public Sprite{
public:
	int _ttl;
	Bullet(int t) {
		_ttl = t;
	}
	void init(float, float, float);
	void bulletmove(glm::vec3);
};

