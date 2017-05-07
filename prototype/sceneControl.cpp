#include "sceneControl.h"

SceneControl::SceneControl() {
	_scenelocker = true;
	_rotate = false;
	_reset = false;
	_sunrise = false;
	_test = 0;
	_dir = ' ';
	_difx = 0;
	_dify = 0;
}

void SceneControl::cameraMove(const Sint32& x, const Sint32& y) {
	if (!_scenelocker) {
		_difx = x;
		_dify = y;
	}
}
void SceneControl::cameraMove(const Sint16& x_move, const Sint16& y_move) {
	Sint32 x, y;
	x = x_move / 10000;
	y = y_move / 10000;
	SceneControl::cameraMove(x, y);
}
void SceneControl::changeStatus(const SDL_Keycode& mode) {
	switch (mode){
	//unlock camera
	case SDLK_l: {
		_scenelocker = !_scenelocker;
		break;
	}
	//rotate toggle
	case SDLK_r: {
		_rotate = !_rotate;
		break;
	}
	case SDLK_z: {
		_sunrise = !_sunrise;
		break;
	}
	//reset scene
	case SDLK_b: {
		_reset = true;
		break;
	}
	//toggle testgrid
	case SDLK_t: {
		_test = (_test+1) % 3;
		break;
	}
	//camera position move
	case SDLK_a: {
		_dir = 'a';
		break;
	}
	case SDLK_s: {
		_dir = 's';
		break;
	}
	case SDLK_d: {
		_dir = 'd';
		break;
	}
	case SDLK_w: {
		_dir = 'w';
		break;
	}
	case SDLK_LCTRL: {
		_dir = 'l';
		break;
	}
	case SDLK_SPACE: {
		_dir = 'u';
		break;
	}
	//mouse motion
	default:
		break;
	}
}