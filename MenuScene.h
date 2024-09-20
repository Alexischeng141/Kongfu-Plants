#ifndef _MENUSCENE_H_
#define _MENUSCENE_H_

#include "scene.h"
#include "Timer.h"
#include "Camera.h"
#include "Atlas.h"
#include "Animation.h"
#include "SceneManager.h"
#include <iostream>

extern IMAGE img_menu_background;

extern Atlas atlas_peashooter_run_right;
extern Atlas atlas_peashooter_run_left;

extern SceneManager _SM;

class MenuScene : public scene {

public:
	MenuScene() {};
	~MenuScene() = default;


	void OnEnter() {
		// 初始化动画资源
		mciSendString(_T("play bgm_menu repeat from 0"), NULL, 0, NULL);
	}

	void OnInput(const ExMessage& msg) {
		if (msg.message == WM_KEYDOWN) {
			mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
			_SM.swtich_scene_to(SceneManager::scenes::SELECTOR_SCENE);
		}
	}

	void OnUpdate(int interval_time) {

	}

	void OnDraw(const Camera& camera) {
		putimage(0, 0, &img_menu_background);
	}

	void OnExit() {

	}

private:
	Timer timer;
	Animation animation_peashooter_run_right;

};

#endif // !_MENUSCENE_H_

