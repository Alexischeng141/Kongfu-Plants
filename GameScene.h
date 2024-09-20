#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "scene.h"
#include "Camera.h"
#include "platform.h"
#include "SceneManager.h"

extern SceneManager _SM;

extern IMAGE img_sky;
extern IMAGE img_hills;
extern IMAGE img_platform_large;
extern IMAGE img_platform_small;

extern std::vector<Platform> Platform_list;

extern Camera camera;

extern bool is_debug;

class GameScene : public scene {
public:
	GameScene() = default;
	~GameScene() = default;

	// 游戏场景的基类
	// 不同的游戏场景可以继承这个基类

	void OnEnter() {
		pos_img_sky.x = (getwidth() - img_sky.getwidth()) / 2;
		pos_img_sky.y = (getheight() - img_sky.getheight()) / 2;

		pos_img_hills.x = (getwidth() - img_hills.getwidth()) / 2;
		pos_img_hills.y = (getheight() - img_hills.getheight()) / 2;

		Platform_list.resize(4);

		Platform& large_platform = Platform_list[0];
		large_platform.img = &img_platform_large;
		large_platform.position.x = 122;
		large_platform.position.y = 455;
		large_platform.collision_box.x_left = (float)large_platform.position.x + 30;
		large_platform.collision_box.x_right = (float)large_platform.position.x + img_platform_large.getwidth() - 30;
		large_platform.collision_box.y = (float)large_platform.position.y + 60;

		Platform& small_platform_1 = Platform_list[1];
		small_platform_1.img = &img_platform_small;
		small_platform_1.position.x = 175;
		small_platform_1.position.y = 360;
		small_platform_1.collision_box.x_left = (float)small_platform_1.position.x + 40;
		small_platform_1.collision_box.x_right = (float)small_platform_1.position.x + img_platform_small.getwidth() - 40;
		small_platform_1.collision_box.y = (float)small_platform_1.position.y + img_platform_small.getheight() / 2;

		Platform& small_platform_2 = Platform_list[2];
		small_platform_2.img = &img_platform_small;
		small_platform_2.position.x = 855;
		small_platform_2.position.y = 360;
		small_platform_2.collision_box.x_left = (float)small_platform_2.position.x + 40;
		small_platform_2.collision_box.x_right = (float)small_platform_2.position.x + img_platform_small.getwidth() - 40;
		small_platform_2.collision_box.y = (float)small_platform_2.position.y + img_platform_small.getheight() / 2;

		Platform& small_platform_3 = Platform_list[3];
		small_platform_3.img = &img_platform_small;
		small_platform_3.position.x = 515;
		small_platform_3.position.y = 225;
		small_platform_3.collision_box.x_left = (float)small_platform_3.position.x + 40;
		small_platform_3.collision_box.x_right = (float)small_platform_3.position.x + img_platform_small.getwidth() - 40;
		small_platform_3.collision_box.y = (float)small_platform_3.position.y + img_platform_small.getheight() / 2;

	}

	void OnInput(const ExMessage& msg) {
		switch (msg.message)
		{
		case WM_KEYUP:
			if (msg.vkcode == 0x51) {
				is_debug = true;
			}
			break;
		default:
			break;
		}
	}

	void OnUpdate(int interval_time) {

	}


	void OnDraw(const Camera& camera) {
		putimage_alpha(camera, pos_img_sky.x, pos_img_sky.y, &img_sky);
		putimage_alpha(camera, pos_img_hills.x, pos_img_hills.y, &img_hills);

		for (const Platform& platform : Platform_list) {
			platform.on_draw(camera);
		}

		if (is_debug) {
			settextcolor(RGB(255, 0, 0));
			outtextxy(15, 15, _T("Press 'Q' again to stop debuging"));
		}


	}

	void OnExit() {

	}

private:

	POINT pos_img_sky = { 0 };
	POINT pos_img_hills = { 0 };

};


#endif // !_GAMESCENE_H_

