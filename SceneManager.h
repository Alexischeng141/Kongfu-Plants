#pragma once
#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_
//³¡¾°¹ÜÀíÆ÷
#include "scene.h"

extern scene* game_scene;
extern scene* menu_scene;
extern scene* selector_scene;

class SceneManager {
public:
	enum class scenes
	{
		GAME_SCENE,
		MENU_SCENE,
		SELECTOR_SCENE
	};

	SceneManager() = default;
	~SceneManager() = default;

	void set_current_scene(scene* current_scene) {
		this->current_scene = current_scene;
		current_scene->OnEnter();
	}

	void swtich_scene_to(scenes type) {
		current_scene->OnExit();
		switch (type) {
		case scenes::GAME_SCENE: {
			current_scene = game_scene;
			break;
		}
		case scenes::MENU_SCENE: {
			current_scene = menu_scene;
			break;
		}
		case scenes::SELECTOR_SCENE: {
			current_scene = selector_scene;
			break;
		}
		default:
			break;
		}
		current_scene->OnEnter();
	}

	void OnUpdate(int interval_time) {
		current_scene->OnUpdate(interval_time);
	}

	void OnDraw(const Camera& camera) {
		current_scene->OnDraw(camera);
	}

	void OnInput(const ExMessage& msg) {
		current_scene->OnInput(msg);
	}


private:
	scene* current_scene;
};

#endif // !_SCENEMANAGER_H_


