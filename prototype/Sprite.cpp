#include "Sprite.h"
#include "Vertex.h"
#include "ResourceManager.h"

#include <cstddef>

Sprite::Sprite()
{
    _vboID = 0;
}


Sprite::~Sprite()
{
    //Always remember to delete your buffers when
    //you are done!
    if (_vboID != 0) {
        glDeleteBuffers(1, &_vboID);
    }
}

//Initializes the sprite VBO. x, y, width, and height are
//in the normalized device coordinate space. so, [-1, 1]
void Sprite::init(float x, float y, float z, float len, float wid, float hei, std::string texturePath) {
    //Set up our private vars
    _x = x;
    _y = y;
	_z = z;
    _width = wid;
    _height = hei;
	_length = len;
	//if we don`t want to bind any texture to cubes.
	if (texturePath != "") {
		_texture = ResourceManager::get_Texture(texturePath);
	}
    //Generate the buffer if it hasn't already been generated
    if (_vboID == 0) {
        glGenBuffers(1, &_vboID);
    }

    //This array will hold our vertex data.
    //We need 6 vertices, and each vertex has 2
    //floats for X and Y
    Vertex vertexData[36];
/*2D
    //First Triangle
    vertexData[0].setPosition(x + width, y + height, z);
    vertexData[0].setUV(1.0f, 1.0f);

    vertexData[1].setPosition(x, y + height, z);
    vertexData[1].setUV(0.0f, 1.0f);

    vertexData[2].setPosition(x, y, z);
    vertexData[2].setUV(0.0f, 0.0f);

    //Second Triangle
    vertexData[3].setPosition(x, y, z);
    vertexData[3].setUV(0.0f, 0.0f);

    vertexData[4].setPosition(x + width, y, z + depth);
    vertexData[4].setUV(1.0f, 0.0f);

	
    vertexData[5].setPosition(x + width, y + height, z);
    vertexData[5].setUV(1.0f, 1.0f);
*/
	vertexData[0].setPosition(x, y, z);
	vertexData[1].setPosition(x+len, y+hei, z);
	vertexData[2].setPosition(x, y+hei, z);
	vertexData[3].setPosition(x, y, z);
	vertexData[4].setPosition(x+len, y+hei, z);
	vertexData[5].setPosition(x+len, y, z);

	vertexData[6].setPosition(x, y, z-wid);
	vertexData[7].setPosition(x+len, y+hei, z-wid);
	vertexData[8].setPosition(x, y+hei, z-wid);
	vertexData[9].setPosition(x, y, z - wid);
	vertexData[10].setPosition(x+len, y+hei, z - wid);
	vertexData[11].setPosition(x+len, y, z - wid);

	vertexData[12].setPosition(x, y, z - wid);
	vertexData[13].setPosition(x, y+hei, z);
	vertexData[14].setPosition(x, y+hei, z - wid);
	vertexData[15].setPosition(x, y, z - wid);
	vertexData[16].setPosition(x, y+hei, z);
	vertexData[17].setPosition(x, y, z);

	vertexData[18].setPosition(x+len, y, z);
	vertexData[19].setPosition(x + len, y+hei, z-wid);
	vertexData[20].setPosition(x + len, y+hei, z);
	vertexData[21].setPosition(x + len, y, z);
	vertexData[22].setPosition(x + len, y+hei, z-wid);
	vertexData[23].setPosition(x + len, y, z-wid);

	vertexData[24].setPosition(x, y+hei, z);
	vertexData[25].setPosition(x+len, y+hei, z-wid);
	vertexData[26].setPosition(x, y + hei, z-wid);
	vertexData[27].setPosition(x, y + hei, z);
	vertexData[28].setPosition(x+len, y + hei, z-wid);
	vertexData[29].setPosition(x+len, y + hei, z);

	vertexData[30].setPosition(x, y, z-wid);
	vertexData[31].setPosition(x+len, y, z);
	vertexData[32].setPosition(x, y, z);
	vertexData[33].setPosition(x, y, z-wid);
	vertexData[34].setPosition(x+len, y, z);
	vertexData[35].setPosition(x+len, y, z-wid);
	//set normal to display light

	vertexData[0].setNormal(0, 0, 1);
	vertexData[1].setNormal(0, 0, 1);
	vertexData[2].setNormal(0, 0, 1);
	vertexData[3].setNormal(0, 0, 1);
	vertexData[4].setNormal(0, 0, 1);
	vertexData[5].setNormal(0, 0, 1);

	vertexData[6].setNormal(0, 0, -1);
	vertexData[7].setNormal(0, 0, -1);
	vertexData[8].setNormal(0, 0, -1);
	vertexData[9].setNormal(0, 0, -1);
	vertexData[10].setNormal(0, 0, -1);
	vertexData[11].setNormal(0, 0, -1);

	vertexData[12].setNormal(-1, 0, 0);
	vertexData[13].setNormal(-1, 0, 0);
	vertexData[14].setNormal(-1, 0, 0);
	vertexData[15].setNormal(-1, 0, 0);
	vertexData[16].setNormal(-1, 0, 0);
	vertexData[17].setNormal(-1, 0, 0);

	vertexData[18].setNormal(1, 0, 0);
	vertexData[19].setNormal(1, 0, 0);
	vertexData[20].setNormal(1, 0, 0);
	vertexData[21].setNormal(1, 0, 0);
	vertexData[22].setNormal(1, 0, 0);
	vertexData[23].setNormal(1, 0, 0);

	vertexData[24].setNormal(0, 1, 0);
	vertexData[25].setNormal(0, 1, 0);
	vertexData[26].setNormal(0, 1, 0);
	vertexData[27].setNormal(0, 1, 0);
	vertexData[28].setNormal(0, 1, 0);
	vertexData[29].setNormal(0, 1, 0);

	vertexData[30].setNormal(0, -1, 0);
	vertexData[31].setNormal(0, -1, 0);
	vertexData[32].setNormal(0, -1, 0);
	vertexData[33].setNormal(0, -1, 0);
	vertexData[34].setNormal(0, -1, 0);
	vertexData[35].setNormal(0, -1, 0);
	
	vertexData[0].setUV(1.0f, 1.0f);
	vertexData[1].setUV(0.0f, 0.0f);
	vertexData[2].setUV(1.0f, 0.0f);
	vertexData[3].setUV(1.0f, 1.0f);
	vertexData[4].setUV(0.0f, 0.0f);
	vertexData[5].setUV(0.0f, 1.0f);

	vertexData[6].setUV(1.0f, 1.0f);
	vertexData[7].setUV(0.0f, 0.0f);
	vertexData[8].setUV(1.0f, 0.0f);
	vertexData[9].setUV(1.0f, 1.0f);
	vertexData[10].setUV(0.0f, 0.0f);
	vertexData[11].setUV(0.0f, 1.0f);

	vertexData[12].setUV(1.0f, 1.0f);
	vertexData[13].setUV(0.0f, 0.0f);
	vertexData[14].setUV(1.0f, 0.0f);
	vertexData[15].setUV(1.0f, 1.0f);
	vertexData[16].setUV(0.0f, 0.0f);
	vertexData[17].setUV(0.0f, 1.0f);

	vertexData[18].setUV(1.0f, 1.0f);
	vertexData[19].setUV(0.0f, 0.0f);
	vertexData[20].setUV(1.0f, 0.0f);
	vertexData[21].setUV(1.0f, 1.0f);
	vertexData[22].setUV(0.0f, 0.0f);
	vertexData[23].setUV(0.0f, 1.0f);

	vertexData[24].setUV(1.0f, 1.0f);
	vertexData[25].setUV(0.0f, 0.0f);
	vertexData[26].setUV(1.0f, 0.0f);
	vertexData[27].setUV(1.0f, 1.0f);
	vertexData[28].setUV(0.0f, 0.0f);
	vertexData[29].setUV(0.0f, 1.0f);

	vertexData[30].setUV(1.0f, 1.0f);
	vertexData[31].setUV(0.0f, 0.0f);
	vertexData[32].setUV(1.0f, 0.0f);
	vertexData[33].setUV(1.0f, 1.0f);
	vertexData[34].setUV(0.0f, 0.0f);
	vertexData[35].setUV(0.0f, 1.0f);

    //Set all vertex colors to magenta
    for (int i = 0; i < 36; i++) {
        vertexData[i].setColor(255, 255, 255, 100);
    }
	/*for (int i = 6; i < 12; i++) {
		vertexData[i].setColor(0, 0, 255, 100);
	}
	for (int i = 12; i < 18; i++) {
		vertexData[i].setColor(255, 0, 0, 100);
	}
	for (int i = 18; i < 24; i++) {
		vertexData[i].setColor(0, 255, 255, 255);
	}
	for (int i = 24; i < 30; i++) {
		vertexData[i].setColor(0, 255, 0, 255);
	}
	for (int i = 30; i < 36; i++) {
		vertexData[i].setColor(255, 255, 0, 255);
	}*/
    //Tell opengl to bind our vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);
    //Upload the data to the GPU
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    //Unbind the buffer (optional)
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//Draws the sprite to the screen
void Sprite::draw() {

    glBindTexture(GL_TEXTURE_2D, _texture.id);

    //bind the buffer object
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);

    //Tell opengl that we want to use the first
    //attribute array. We only need one array right
    //now since we are only using position.
    glEnableVertexAttribArray(0);

    //This is the position attribute pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    //This is the color attribute pointer
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    //This is the UV attribute pointer
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	//This is the normal pointer
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    //Draw the 6 vertices to the screen
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //Disable the vertex attrib array. This is not optional.
    glDisableVertexAttribArray(0);

    //Unbind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Bullet::init(float x, float y, float z) {
	Sprite::init(x, y, z, 0.01, 0.01, 0.01, "");
}

void Bullet::bulletmove(glm::vec3 dir) {
	init(_x + 0.2*dir.x, _y + 0.2*dir.y - 0.0002 * (40 - _ttl), _z + 0.2*dir.z);
}