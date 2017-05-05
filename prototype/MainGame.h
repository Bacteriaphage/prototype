#pragma once


#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <cmath>
#include "GLSLProgram.h"
#include "GLTexture.h"
#include "sceneControl.h"
#include "Sprite.h"
#include "testGrid.h"

#include <list>
#include <vector>

enum class GameState {PLAY, EXIT};

class MainGame
{
private:
	struct Camera {
		glm::vec3 viewPoint;
		glm::vec3 destination;
		glm::vec3 upper;
		//default view
		Camera() :viewPoint(glm::vec3(0.0, 1.0, 10.0)),
			destination(glm::vec3(0.0, 1.0, 9.0)),
			upper(glm::vec3(0.0, 1.0, 0.0)) {}
		void reset() {
			viewPoint.x = 0.0;
			viewPoint.y = 1.0;
			viewPoint.z = 10.0;
			destination.x = 0.0;
			destination.y = 1.0;
			destination.z = 9.0;
			upper.x = upper.z = 0.0;
			upper.y = 1.0;
		}
		void cameraRotate(const Sint32& x, const Sint32& y) {
			if (x == 0 && y == 0) return;
			glm::mat4 model(1.0f);
			glm::vec4 res(destination, 1);
			model = glm::translate(model, -viewPoint);
			res = model * res;
			std::cout << std::endl;
			glm::vec3 forward = glm::normalize(destination - viewPoint);
			glm::vec3 verticleAxle = glm::normalize(glm::cross(forward, upper));
			//indicate how fast camera horizontal rotate
			float horizontalfactor = glm::dot(forward, upper);
			//front and upper smaller than 10 degree, dont do vertical rotate;
			if (horizontalfactor < 0.8 && horizontalfactor >-0.8) {
				model = glm::rotate(glm::mat4(1.0f), (float)0.004 * -y, verticleAxle);
				res = model * res;
			}
			else if (horizontalfactor > 0.8 && y > 0) {
				model = glm::rotate(glm::mat4(1.0f), (float)0.004 * -y, verticleAxle);
				res = model * res;
			}
			else if (horizontalfactor < -0.8 && y < 0) {
				model = glm::rotate(glm::mat4(1.0f), (float)0.004 * -y, verticleAxle);
				res = model * res;
			}
			model = glm::rotate(glm::mat4(1.0f), (float)(0.0001 * fabs(horizontalfactor)+0.01) * -x, upper);
			res = model * res;
			std::cout << std::endl;
			res = glm::translate(glm::mat4(1.0f), viewPoint) * res;
			destination = glm::vec3(res);
		}
		void cameraTranslate(const char& dir) {
			glm::vec3 forword = glm::normalize(destination - viewPoint);
			glm::vec3 left = glm::normalize(glm::cross(upper, forword));

			switch (dir) {
			case 'a':
				viewPoint += left * 0.05f;
				destination += left * 0.05f;
				break;
			case 's':
				viewPoint -= forword * 0.05f;
				destination -= forword * 0.05f;
				break;
			case 'd':
				viewPoint -= left * 0.05f;
				destination -= left * 0.05f;
				break;
			case 'w':
				viewPoint += forword * 0.05f;
				destination += forword * 0.05f;
				break;
			case 'l':
				viewPoint.y -= 0.05f;
				destination.y -= 0.05f;
				break;
			case 'u':
				viewPoint.y += 0.05f;
				destination.y += 0.05f;
				break;
			}
		}
	};
	struct BulletTrace{
		Bullet _bull;
		glm::vec3 _dir;
		BulletTrace(glm::vec3 from, glm::vec3 dir) : _bull(40) {
			_bull.init(from.x, from.y,from.z);
			_dir = dir;
		}
	};
public:
    MainGame();
    ~MainGame();
    void run();

private:
    void initSystems();
    void initShaders();
    void gameLoop();
    void processInput();
	void drawShadow(GLuint *, GLuint *, GLuint *);
    void drawGame();
    void calculateFPS();
	void shootbullet();
	void checkbullet();
    SDL_Window* _window;
    int _screenWidth;
    int _screenHeight;
    GameState _gameState;

    std::vector <Sprite*> _sprites;
	std::list <BulletTrace> _bullets;
	std::vector<TestGrid*> _testGrid;

    GLSLProgram _colorProgram;
	GLSLProgram _shadowProgram;

    float _fps;
    float _maxFPS;
    float _frameTime;
    float _time;
	//control camera
	SceneControl _control;
	Camera _camera;
};

