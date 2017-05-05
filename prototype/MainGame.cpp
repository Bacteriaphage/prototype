#include "MainGame.h"
#include "Errors.h"
#include <cstdint>

#include <string>

#define WIDTH 800
#define Height 600

//Constructor, just initializes private member variables
MainGame::MainGame() : 
    _screenWidth(WIDTH),
    _screenHeight(Height), 
    _time(0.0f),
    _window(nullptr), 
    _gameState(GameState::PLAY),
    _maxFPS(60.0f)
{
}

//Destructor
MainGame::~MainGame()
{
	for (int i = 0; i < _testGrid.size(); i++) {
		delete _testGrid[i];
	}
}

//This runs the game
void MainGame::run() {
    initSystems();

    //Initialize our sprites. (temporary)
	_testGrid.push_back(new TestGrid(1.0f));
	_testGrid.back()->initPlane("Textures/floor.png");
	//_testGrid.back()->initPlane("");
	_testGrid.push_back(new TestGrid(1.0f));
	_testGrid.back()->initGrid();
    _sprites.push_back(new Sprite);
    _sprites.back()->init(-1.0f, 0.0f, 1.0f, 2.0f, 2.0f, 2.0f, "Textures/brick.png");
	//_sprites.back()->init(-1.0f, 0.0f, 1.0f, 2.0f, 2.0f, 2.0f, "");
	_sprites.push_back(new Sprite);
	_sprites.back()->init(-4.0f, 0.0f, 4.0f, 2.0f, 2.0f, 2.0f, "Textures/stonewall.png");
	//_sprites.back()->init(-4.0f, 0.0f, 4.0f, 2.0f, 2.0f, 2.0f, "");

	_sprites.push_back(new Sprite);
	_sprites.back()->init(4.0f, 2.0f, -4.0f, 2.0f, 2.0f, 2.0f, "Textures/wood.png");
	//_sprites.back()->init(4.0f, 2.0f, -4.0f, 2.0f, 2.0f, 2.0f, "");

//    _sprites.push_back(new Sprite);
//    _sprites.back()->init(0.0f, -1.0f, 1.0f, 1.0f, "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");
  
    //This only returns when the game ends
    gameLoop();
}

//Initialize SDL and Opengl and whatever else we need
void MainGame::initSystems() {
    //Initialize SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    //Open an SDL window
    _window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
    if (_window == nullptr) {
        fatalError("SDL Window could not be created!");
    }

    //Set up our OpenGL context
    SDL_GLContext glContext = SDL_GL_CreateContext(_window);
    if (glContext == nullptr) {
        fatalError("SDL_GL context could not be created!");
    }

    //Set up glew (optional but recommended)
    GLenum error = glewInit();
    if (error != GLEW_OK) {
        fatalError("Could not initialize glew!");
    }

    //Tell SDL that we want a double buffered window so we dont get
    //any flickering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    //Set the background color to blue
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    initShaders();
}

void MainGame::initShaders() {
    _colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
    _colorProgram.addAttribute("vertexColor");
    _colorProgram.addAttribute("vertexUV");
	_colorProgram.addAttribute("vertexNormal");
    _colorProgram.linkShaders();

	_shadowProgram.compileShaders("Shaders/shadowShading.vert", "Shaders/shadowShading.frag");
	_shadowProgram.addAttribute("vertexPosition");
	_shadowProgram.addAttribute("vertexColor");
	_shadowProgram.addAttribute("vertexUV");
	_shadowProgram.addAttribute("vertexNormal");
	_shadowProgram.linkShaders();
}

//This is the main game loop for our program
void MainGame::gameLoop() {

    //Will loop until we set _gameState to EXIT
    while (_gameState != GameState::EXIT) {
        //Used for frame time measuring
        float startTicks = SDL_GetTicks(); 

        processInput();
		//control scene part
		if(_control._rotate)
			_time += 0.01;
		//reset scene
		if (_control._reset) {
			_camera.reset();
			_control._reset = false;
		}
		//if camera is unlocked do camera translateion
		if (!_control._scenelocker) {
			_camera.cameraTranslate(_control._dir);
			_control._dir = ' ';
			_camera.cameraRotate(_control._difx, _control._dify);
			_control._difx = 0;
			_control._dify = 0;
		}
		checkbullet();
        drawGame();
		//GLuint shadowTexture = 0;
		//GLuint FramebufferName = 0;
		//GLuint renderbuffer = 0;
		//drawShadow(&shadowTexture, &FramebufferName, &renderbuffer);
        calculateFPS();

        //print only once every 10 frames
        static int frameCounter = 0;
        frameCounter++;
        if (frameCounter == 10) {
            //std::cout << _fps << std::endl;
            frameCounter = 0;
        }

        float frameTicks = SDL_GetTicks() - startTicks;
        //Limit the FPS to the max FPS
        if (1000.0f / _maxFPS > frameTicks) {
            SDL_Delay((Uint32)(1000.0f / _maxFPS - frameTicks));
        }
    }
}

//Processes input with SDL
void MainGame::processInput() {
    SDL_Event evnt;

    //Will keep looping until there are no more events to process
    while (SDL_PollEvent(&evnt)) {
        switch (evnt.type) {
            case SDL_QUIT:
                _gameState = GameState::EXIT;
                break;
            case SDL_MOUSEMOTION:
				SDL_SetRelativeMouseMode(SDL_TRUE);
				_control.cameraMove(evnt.motion.xrel, evnt.motion.yrel);
                break;
			case SDL_KEYDOWN:
				_control.changeStatus(evnt.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				shootbullet();
				break;
        }
    }
}
void drawtest(GLuint texture) {
	GLuint _VboID = 0;
	float granular = 0.1;
	glGenBuffers(1, &_VboID);
	Vertex vertexData[4];
	vertexData[0].setPosition(0, 0.0, 0);
	vertexData[1].setPosition(-100 * granular, 0.0, 0);
	vertexData[2].setPosition(-100 * granular, 100 * granular, 0);
	vertexData[3].setPosition(0, 100 * granular, 0);
	vertexData[0].setColor(200, 200, 200, 200);
	vertexData[1].setColor(200, 200, 200, 200);
	vertexData[2].setColor(200, 200, 200, 200);
	vertexData[3].setColor(200, 200, 200, 200);
	vertexData[0].setUV(1, 1);
	vertexData[1].setUV(0, 1);
	vertexData[2].setUV(0, 0);
	vertexData[3].setUV(1, 0);
	vertexData[0].setNormal(0, 1, 0);
	vertexData[1].setNormal(0, 1, 0);
	vertexData[2].setNormal(0, 1, 0);
	vertexData[3].setNormal(0, 1, 0);
	glBindBuffer(GL_ARRAY_BUFFER, _VboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindBuffer(GL_ARRAY_BUFFER, _VboID);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glDrawArrays(GL_QUADS, 0, 4);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
//Draws the game using the almighty OpenGL

void MainGame::drawGame() {
	GLuint shadowTexture = 0;
	GLuint depthTexture = 0;
	GLuint FramebufferName = 0;
	drawShadow(&shadowTexture, &FramebufferName, &depthTexture);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
    //Set the base depth to 1.0
    //glClearDepth(1.0);
    //Clear the color and depth buffer
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LEQUAL);
	// Enable blending
	/*glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
    //Enable the shader

    _colorProgram.use();

	GLint shadowMap = _colorProgram.getUniformLocation("shadowMap");
	glUniform1i(shadowMap, 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, shadowTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

	//Get the uniform location
	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	//Tell the shader that the texture is in texture unit 0
	glUniform1i(textureLocation, 0);
	glActiveTexture(GL_TEXTURE0);

	//MVP matrix;
	GLint u_matrixLocation = _colorProgram.getUniformLocation("u_matrix");
	glm::mat4 view = glm::lookAt(_camera.viewPoint, _camera.destination, _camera.upper);
	glm::mat4 model(1.0f);
	model = glm::rotate(model, _time, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 proj = glm::perspective(120.0f, 800.0f / 600.0f, 0.01f, 100.0f);
	glm::mat4 mvp = proj * view * model;
	glUniformMatrix4fv(u_matrixLocation, 1, GL_FALSE, &mvp[0][0]);
	GLint u_modelLocation = _colorProgram.getUniformLocation("u_model");
	glUniformMatrix4fv(u_modelLocation, 1, GL_FALSE, &model[0][0]);
	
	//reverse light direction
	GLint u_reverseLightDirectionLocation = _colorProgram.getUniformLocation("u_reverseLightDirection");
	glm::vec3 reverseLightDirection = glm::vec3(0.0, 9.0, 36.0);
	glUniform3fv(u_reverseLightDirectionLocation, 1, &reverseLightDirection[0]);
	
	//depth_matrix
	glm::mat4 depthProjectionMatrix = glm::perspective(120.0f, 800.0f / 600.0f, 0.01f, 100.0f);
	glm::mat4 depthViewMatrix = glm::lookAt(reverseLightDirection, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 depthModelMatrix = glm::rotate(glm::mat4(1.0f), _time, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;

	/*Send our transformation to the currently bound shader,
	in the "MVP" uniform*/
	GLuint depthMatrixID = _colorProgram.getUniformLocation("u_depthMatrix");
	glUniformMatrix4fv(depthMatrixID, 1, GL_FALSE, &depthMVP[0][0]);
	//Draw our sprite!
	//drawtest(shadowTexture);
    for (int i = 0; i < _sprites.size(); i++) {
        _sprites[i]->draw();
    }

	mvp = proj * view;
	model = glm::mat4(1.0f);
	glUniformMatrix4fv(u_matrixLocation, 1, GL_FALSE, &mvp[0][0]);
	glUniformMatrix4fv(u_modelLocation, 1, GL_FALSE, &model[0][0]);
	for (auto it = _bullets.begin(); it != _bullets.end(); it++) {
		it->_bull.draw();
	}


	//We are using texture unit 0
	if (_control._test) {
		if (_control._test == 1)
			_testGrid[0]->drawPlane();
		else {
			_testGrid[1]->drawGrid();
		}
	}
    //unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &shadowTexture);
	glDeleteFramebuffers(1, &FramebufferName);
	//glDeleteRenderbuffers(1, &renderbuffer);
    //disable the shader
    _colorProgram.unuse();

    //Swap our buffer and draw everything to the screen!
    SDL_GL_SwapWindow(_window);
}    

void MainGame::drawShadow(GLuint * shadowTexture, GLuint * FramebufferName, GLuint * depthTexture) {
	//Set the base depth to 1.0
	//glClearDepth(1.0);
	//Clear the color and depth buffer
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	//Enable the shader
	_shadowProgram.use();

	glm::vec3 reverseLightDirection = glm::vec3(0.0, 9.0, 36.0);
#if 1
	// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
	//GLuint FramebufferName = 0;
	glGenFramebuffers(1, FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, *FramebufferName);

	// Depth texture. Slower than a depth buffer, but you can sample it later in your shader
	glGenTextures(1, shadowTexture);
	glBindTexture(GL_TEXTURE_2D, *shadowTexture);
	//glGenTextures(1, depthTexture);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 800, 600, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 800, 600, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, *shadowTexture, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *shadowTexture, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, *depthTexture, 0);
	//GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	//glDrawBuffer(GL_NONE); // No color buffer is drawn to.
	//glReadBuffer(GL_NONE);
	// Always check that our framebuffer is ok
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "Fail to initialize framebuffer" << " "<< glCheckFramebufferStatus(GL_FRAMEBUFFER) << std::endl;
		return;
	}
#endif
	//Compute the MVP matrix from the light's point of view
	glm::mat4 depthProjectionMatrix = glm::perspective(120.0f, 800.0f / 600.0f, 0.01f, 100.0f);
	//glm::mat4 depthProjectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.01f, 100.0f);
	glm::mat4 depthViewMatrix = glm::lookAt(reverseLightDirection, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 depthModelMatrix = glm::rotate(glm::mat4(1.0f), _time, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;

	/*Send our transformation to the currently bound shader,
	in the "MVP" uniform*/
	GLuint depthMatrixID = _shadowProgram.getUniformLocation("u_depthMatrix");
	glUniformMatrix4fv(depthMatrixID, 1, GL_FALSE, &depthMVP[0][0]);

	//Draw our sprite!
	//We are using texture unit 0
	if (_control._test) {
		if (_control._test == 1)
			_testGrid[0]->drawPlane();
		else {
			_testGrid[1]->drawGrid();
		}
	}

	for (int i = 0; i < _sprites.size(); i++) {
		_sprites[i]->draw();
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//glBindRenderbuffer(GL_RENDERBUFFER, 0);
	//disable the shader
	_shadowProgram.unuse();
	//SDL_GL_SwapWindow(_window);
}

void MainGame::calculateFPS() {
    //The number of frames to average
    static const int NUM_SAMPLES = 10;
    //Stores all the frametimes for each frame that we will average
    static float frameTimes[NUM_SAMPLES];
    //The current frame we are on
    static int currentFrame = 0;
    //the ticks of the previous frame
    static float prevTicks = SDL_GetTicks();
    
    //Ticks for the current frame
    float currentTicks = SDL_GetTicks();

    //Calculate the number of ticks (ms) for this frame
    _frameTime = currentTicks - prevTicks;
    frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

    //current ticks is now previous ticks
    prevTicks = currentTicks;

    //The number of frames to average
    int count;

    currentFrame++;
    if (currentFrame < NUM_SAMPLES) {
        count = currentFrame;
    } else {
        count = NUM_SAMPLES;
    }

    //Average all the frame times
    float frameTimeAverage = 0;
    for (int i = 0; i < count; i++) {
        frameTimeAverage += frameTimes[i];
    }
    frameTimeAverage /= count;

    //Calculate FPS
    if (frameTimeAverage > 0) {
        _fps = 1000.0f / frameTimeAverage;
    } else {
        _fps = 60.0f;
    }
}
void MainGame::shootbullet() {
	_bullets.push_back(BulletTrace(_camera.viewPoint, glm::normalize(_camera.destination - _camera.viewPoint)));
}
void MainGame::checkbullet() {
	for (auto it = _bullets.begin(); it != _bullets.end();) {
		it->_bull.bulletmove(it->_dir);
		--(it->_bull._ttl);
		it++;
	}
	for (auto it = _bullets.begin(); it != _bullets.end();) {
		if (it->_bull._ttl == 0) {
			auto del = it;
			it++;
			_bullets.erase(del);
		}
		else break;
	}
}