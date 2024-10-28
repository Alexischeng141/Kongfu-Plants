#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "scene.h"
#include "Role.h"
#include "Camera.h"
#include "Buffer.h"
#include "BufferHUD.h"
#include "platform.h"
#include "SceneManager.h"
#include "StatusBar.h"

extern SceneManager _SM;

extern IMAGE img_sky;
extern IMAGE img_hills;
extern IMAGE img_platform_large;
extern IMAGE img_platform_small;

extern std::vector<Platform> Platform_list;
extern std::vector<BufferHUD*> BufferHUD_list;

extern Camera main_camera;

extern Role* role_1;
extern Role* role_2;

extern IMAGE* img_1p_avatar;
extern IMAGE* img_2p_avatar;
extern IMAGE img_winner_bar;
extern IMAGE img_1P_winner;
extern IMAGE img_2P_winner;

extern bool is_debug;

class GameScene : public scene {
public:
	GameScene() = default;
	~GameScene() = default;

	// 游戏场景的基类
	// 不同的游戏场景可以继承这个基类

	void OnEnter() {

		is_game_over = false;
		is_slide_out_started = false;

		pos_img_winner_bar.x = -img_winner_bar.getwidth();
		pos_img_winner_bar.y = (getheight() - img_winner_bar.getheight()) / 2;
		pos_img_winner_bar_dst = (getwidth() - img_winner_bar.getwidth()) / 2;
		
		pos_img_winner_text.x = pos_img_winner_bar.x;
		pos_img_winner_text.y = (getheight() - img_1P_winner.getheight()) / 2;
		pos_img_winner_text_dst = (getwidth() - img_1P_winner.getwidth()) / 2;

		timer_winner_slide_in.restart();
		timer_winner_slide_in.set_wait_time(2500);
		timer_winner_slide_in.set_one_shot(true);
		timer_winner_slide_in.set_callback([&]()
			{
				is_slide_out_started = true;
			}); 
		
		timer_winner_slide_out.restart();
		timer_winner_slide_out.set_wait_time(1000);
		timer_winner_slide_out.set_one_shot(true);
		timer_winner_slide_out.set_callback([&]()
			{
				_SM.switch_scene_to(SceneManager::scenes::MENU_SCENE);
			});

		timer_generate_buffer.restart();
		timer_generate_buffer.set_wait_time(3000);
		timer_generate_buffer.set_one_shot(false);
		timer_generate_buffer.set_callback([&]()
			{
				if (BufferHUD_list.size() <= 4) {
					BufferHUD* bufferHUF = new BufferHUD();
					BufferHUD_list.push_back(bufferHUF);
				}

			});

		role_1->set_position(200, 50);
		role_2->set_position(975, 50);

		

		pos_img_sky.x = (getwidth() - img_sky.getwidth()) / 2;
		pos_img_sky.y = (getheight() - img_sky.getheight()) / 2;

		pos_img_hills.x = (getwidth() - img_hills.getwidth()) / 2;
		pos_img_hills.y = (getheight() - img_hills.getheight()) / 2;

		Platform_list.resize(4);

		status_bar_1P.set_hp(role_1->get_hp());
		status_bar_1P.set_mp(role_1->get_mp());
		status_bar_2P.set_hp(role_2->get_hp());
		status_bar_2P.set_mp(role_2->get_mp());

		status_bar_1P.set_position(235, 625);
		status_bar_2P.set_position(675, 625);

		status_bar_1P.set_avatar(img_1p_avatar);
		status_bar_2P.set_avatar(img_2p_avatar);
		

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

		mciSendString(_T("play bgm_game repeat from 0"), NULL, 0, NULL);

	}

	void OnInput(const ExMessage& msg) {

		role_1->on_input(msg);
		role_2->on_input(msg);

		switch (msg.message)
		{
		case WM_KEYDOWN:

			break;
		case WM_KEYUP:
			if (msg.vkcode == 0x51 && is_debug == false) {
				is_debug = true;
			}
			else if (msg.vkcode == 0x51 && is_debug == true) {
				is_debug = false;
			}
			break;
		default:
			break;
		}
	}

	void OnUpdate(int interval_time) {

		// 角色
		role_1->on_update(interval_time);
		role_2->on_update(interval_time);

		// 人物状态组件
		status_bar_1P.set_hp(role_1->get_hp());
		status_bar_1P.set_mp(role_1->get_mp());
		status_bar_2P.set_hp(role_2->get_hp());
		status_bar_2P.set_mp(role_2->get_mp());

		main_camera.on_updata(interval_time);
		timer_generate_buffer.on_update(interval_time);

		// 对已经失效的子弹进行清理
		Bullet_list.erase(std::remove_if(Bullet_list.begin(), Bullet_list.end(), [](const Bullet* bullet) {
			bool delectable = bullet->checkCanReMove();
			if (delectable) {
				delete bullet;
			}
			return delectable;
			}), Bullet_list.end());

		// 对已经失效的BufferHUD进行清理
		BufferHUD_list.erase(std::remove_if(BufferHUD_list.begin(), BufferHUD_list.end(), [](const BufferHUD* bufferHUD) {
			bool delectable = bufferHUD->checkCanRemove();
			if (delectable) {
				delete bufferHUD;
			}
			return delectable;
			}), BufferHUD_list.end());
		
		// 更新bufferHUD
		for (BufferHUD* bufferHUD : BufferHUD_list) 
			bufferHUD->on_update(interval_time);

		// 子弹更新
		for (Bullet* bullet : Bullet_list) 
			bullet->on_update(interval_time);
		
		// 检测玩家是否掉入屏幕之外
		const Vector2& position_1p = role_1->get_position();
		const Vector2& position_2p = role_2->get_position();
		if (position_1p.y >= getheight())
			role_1->set_hp(0);
		if (position_2p.y >= getheight())
			role_2->set_hp(0);
		
		// 控制结束游戏
		if (role_1->get_hp() <= 0 || role_2->get_hp() <= 0) {
			// 防止音乐循环播放
			if (!is_game_over) {
				mciSendString(_T("stop bgm_game"), NULL, 0, NULL);
				mciSendString(_T("play ui_win from 0"), NULL, 0, NULL);
			}
			is_game_over = true;
		}
		
		// 游戏结束后的动画
		if (is_game_over) {
			pos_img_winner_bar.x += (int)(speed_winner_bar * interval_time);
			pos_img_winner_text.x += (int)(speed_winner_text * interval_time);
			if (!is_slide_out_started) {
				timer_winner_slide_in.on_update(interval_time);
				if (pos_img_winner_bar.x > pos_img_winner_bar_dst)
					pos_img_winner_bar.x = pos_img_winner_bar_dst;
				if (pos_img_winner_text.x > pos_img_winner_text_dst)
					pos_img_winner_text.x = pos_img_winner_text_dst;
			}
			else
				timer_winner_slide_out.on_update(interval_time);
		}

	}

	void OnDraw(const Camera& camera) {
		// 地形加载
		putimage_alpha(camera, pos_img_sky.x, pos_img_sky.y, &img_sky);
		putimage_alpha(camera, pos_img_hills.x, pos_img_hills.y, &img_hills);

		// 平台加载
		for (const Platform& platform : Platform_list) {
			platform.on_draw(camera);
		}

		// debug提示字样加载
		if (is_debug) {
			settextcolor(RGB(255, 0, 0));
			outtextxy(15, 15, _T("Press 'Q' again to stop debugging"));
		}

		// buffer渲染
		for (const BufferHUD* buffer : BufferHUD_list)
			buffer->on_draw(camera);

		// 角色渲染
		role_1->on_draw(camera);
		role_2->on_draw(camera);

		// 子弹渲染
		for (const Bullet* bullet : Bullet_list)
			bullet->on_draw(camera);


		if (is_game_over) {
			putimage_alpha(pos_img_winner_bar.x, pos_img_winner_bar.y, &img_winner_bar);
			putimage_alpha(pos_img_winner_text.x, pos_img_winner_text.y, role_1->get_hp() > 0 ? &img_1P_winner : &img_2P_winner);
		}
		else
		{
			status_bar_1P.on_draw();
			status_bar_2P.on_draw(); 
		}


	}

	void OnExit() {
		delete role_1; role_1 = nullptr;
		delete role_2; role_2 = nullptr;
		
		is_debug = false;
		Bullet_list.clear();
		BufferHUD_list.clear();
		Platform_list.clear();
		main_camera.reset(); 
	}

private:

	const float speed_winner_bar = 3.0f;	// 结算动效背景移动速度
	const float speed_winner_text = 1.5f;	// 结算动效文本移动速度

	POINT pos_img_sky = { 0 };
	POINT pos_img_hills = { 0 };

	StatusBar status_bar_1P;				// 角色状态栏
	StatusBar status_bar_2P;				// 角色状态栏

	bool is_game_over = false;				// 游戏是否结束
	
	POINT pos_img_winner_bar = { 0 };		// 结算动效动画的背景位置
	POINT pos_img_winner_text = { 0 };		// 结算动效文字的背景位置

	int pos_img_winner_bar_dst = 0;			// 结算动效背景移动的目标位置
	int pos_img_winner_text_dst = 0;		// 结算动效文本移动的目标位置

	Timer timer_winner_slide_in;			// 结算动效背景滑入定时器
	Timer timer_winner_slide_out;			// 结算动效文本滑出计时器
	Timer timer_generate_buffer;			// buffer 测试定时器	

	bool is_slide_out_started = false;		// 开始滑出

	
};


#endif // !_GAMESCENE_H_

