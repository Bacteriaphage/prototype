#pragma once
#include <glm/glm.hpp>
#include <SDL/SDL.h>
class SceneControl{
public:
	//camera locking switch
	bool _scenelocker;
	//all objects rotating switch
	bool _rotate;
	//sun rise
	bool _sunrise;
	//reset scene
	bool _reset;
	//test toggle
	int _test;
	//translate direction
	char _dir;
	//relative mouse move
	Sint32 _difx;
	Sint32 _dify;
	SceneControl();
	void changeStatus(const SDL_Keycode&);
	void cameraMove(const Sint16&, const Sint16&);
	void cameraMove(const Sint32&, const Sint32&);
};