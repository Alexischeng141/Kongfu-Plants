#pragma comment(lib, "Winmm.lib")
#include "Utils.h"
#include "Atlas.h"
#include "Role.h"
#include "Bullet.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "platform.h"
#include "SelectorScene.h"
#include "SceneManager.h"

#include <graphics.h>

#pragma warning(disable: 28159)

#define WIN_WIDHT 1280
#define WIN_HEIGHT 720
#define STANDAR_FRAME_INTERVAL_TIME 1000 / 90

bool is_debug = false;

IMAGE img_vs;
IMAGE img_pea;
IMAGE img_winner_bar;
IMAGE img_platform_small;
IMAGE img_platform_large;

IMAGE img_menu_background;

IMAGE img_selector_tip;
IMAGE img_selector_background;
IMAGE img_nut_selector_background_left;
IMAGE img_nut_selector_background_right;
IMAGE img_sunflower_selector_background_left;
IMAGE img_sunflower_selector_background_right;
IMAGE img_peashooter_selector_background_left;
IMAGE img_peashooter_selector_background_right;
IMAGE img_gloomshroom_selector_background_left;
IMAGE img_gloomshroom_selector_background_right;

IMAGE img_sky;
IMAGE img_hills;
IMAGE img_gravestone_left;
IMAGE img_gravestone_right;

IMAGE img_buff_icon_silence;
IMAGE img_buff_icon_recover;
IMAGE img_buff_icon_invisible;
IMAGE img_buff_icon_hurry;

IMAGE img_avatar_sunflower;
IMAGE img_avatar_peashooter;
IMAGE img_avatar_nut;
IMAGE img_avatar_gloomshroom;

IMAGE img_1P;
IMAGE img_1P_desc;
IMAGE img_1P_winner;
IMAGE img_1P_cursor;
IMAGE img_1P_selector_btn_idle_left;
IMAGE img_1P_selector_btn_idle_right;
IMAGE img_1P_selector_btn_down_left;
IMAGE img_1P_selector_btn_down_right;

IMAGE img_2P;
IMAGE img_2P_desc;
IMAGE img_2P_winner;
IMAGE img_2P_cursor;
IMAGE img_2P_selector_btn_idle_left;
IMAGE img_2P_selector_btn_idle_right;
IMAGE img_2P_selector_btn_down_left;
IMAGE img_2P_selector_btn_down_right;

Atlas atlas_bubbles;
Atlas atlas_bubbles_ex;

Atlas atlas_buff_box_blue;
Atlas atlas_buff_box_pink;
Atlas atlas_buff_box_yellow;

Atlas atlas_gloomshroom_die;
Atlas atlas_gloomshroom_attack_ex_right;
Atlas atlas_gloomshroom_attack_ex_left;
Atlas atlas_gloomshroom_idle_right;
Atlas atlas_gloomshroom_idle_left;
Atlas atlas_gloomshroom_run_right;
Atlas atlas_gloomshroom_run_left;

Atlas atlas_run_effect_right;
Atlas atlas_run_effect_left;
Atlas atlas_jump_effect_right;
Atlas atlas_jump_effect_left;
Atlas atlas_land_effect;

Atlas atlas_nut_die;
Atlas atlas_nut_idle_left;
Atlas atlas_nut_idle_right;
Atlas atlas_nut_run_left;
Atlas atlas_nut_run_right;
Atlas atlas_nut_explode;
Atlas atlas_nut_attack_ex;

Atlas atlas_peashooter_die;						// 死亡动画
Atlas atlas_peashooter_idle_left;
Atlas atlas_peashooter_idle_right;
Atlas atlas_peashooter_run_left;
Atlas atlas_peashooter_run_right;
Atlas atlas_peashooter_attack_ex_right;
Atlas atlas_peashooter_attack_ex_left;

Atlas atlas_pea_break;

Atlas atlas_sun;
Atlas atlas_sun_ex;
Atlas atlas_sun_ex_explode;
Atlas atlas_sun_explode;
Atlas atlas_sun_text;

Atlas atlas_sunflower_die;
Atlas atlas_sunflower_idle_left;
Atlas atlas_sunflower_idle_right;
Atlas atlas_sunflower_run_left;
Atlas atlas_sunflower_run_right;
Atlas atlas_sunflower_attack_ex_right;
Atlas atlas_sunflower_attack_ex_left;

scene* game_scene = nullptr;
scene* menu_scene = nullptr;
scene* selector_scene = nullptr;

Role* role_1 = nullptr;
Role* role_2 = nullptr;

std::vector<Platform> Platform_list;		// 场景中所中平台的管理容器
std::vector<Bullet*> Bullet_list;			// 子弹容器中管理着场景中所有的子弹

SceneManager _SM;
Camera main_camera;


void load_game_resource() {

	AddFontResourceEx(_T("resource/IPix.ttf"), FR_PRIVATE, NULL);

	loadimage(&img_menu_background, _T("resource/menu_background.png"));
	// 1P
	loadimage(&img_1P, _T("resource/1P.png"));
	loadimage(&img_1P_desc, _T("resource/1P_desc.png"));
	loadimage(&img_1P_cursor, _T("resource/1P_cursor.png"));
	loadimage(&img_1P_selector_btn_down_right, _T("resource/1P_selector_btn_down.png"));
	filp_image(&img_1P_selector_btn_down_right, &img_1P_selector_btn_down_left);
	loadimage(&img_1P_selector_btn_idle_right, _T("resource/1P_selector_btn_idle.png"));
	filp_image(&img_1P_selector_btn_idle_right, &img_1P_selector_btn_idle_left);
	loadimage(&img_1P_winner, _T("resource/1P_winner.png"));
	// 2P
	loadimage(&img_2P, _T("resource/2P.png"));
	loadimage(&img_2P_desc, _T("resource/2P_desc.png"));
	loadimage(&img_2P_cursor, _T("resource/2P_cursor.png"));
	loadimage(&img_2P_selector_btn_down_right, _T("resource/2P_selector_btn_down.png"));
	filp_image(&img_2P_selector_btn_down_right, &img_2P_selector_btn_down_left);
	loadimage(&img_2P_selector_btn_idle_right, _T("resource/2P_selector_btn_idle.png"));
	filp_image(&img_2P_selector_btn_idle_right, &img_2P_selector_btn_idle_left);
	loadimage(&img_2P_winner, _T("resource/2P_winner.png"));

	loadimage(&img_avatar_gloomshroom, _T("resource/avatar_gloomshroom.png"));
	loadimage(&img_avatar_nut, _T("resource/avatar_gloomshroom.png"));
	loadimage(&img_avatar_peashooter, _T("resource/avatar_peashooter.png"));
	loadimage(&img_avatar_sunflower, _T("resource/avatar_sunflower.png"));
	loadimage(&img_sky, _T("resource/sky.png"));
	loadimage(&img_gravestone_right, _T("resource/gravestone.png"));
	filp_image(&img_gravestone_right, &img_gravestone_left);
	loadimage(&img_hills, _T("resource/hills.png"));
	loadimage(&img_selector_background, _T("resource/selector_background.png"));
	loadimage(&img_selector_tip, _T("resource/selector_tip.png"));
	loadimage(&img_vs, _T("resource/VS.png"));
	loadimage(&img_winner_bar, _T("resource/winner_bar.png"));
	loadimage(&img_pea, _T("resource/pea.png"));
	loadimage(&img_platform_small, _T("resource/platform_small.png"));
	loadimage(&img_platform_large, _T("resource/platform_large.png"));

	// 角色选择界面背景
	loadimage(&img_nut_selector_background_right, _T("resource/nut_selector_background.png"));
	filp_image(&img_nut_selector_background_right, &img_nut_selector_background_left);
	loadimage(&img_sunflower_selector_background_right, _T("resource/sunflower_selector_background.png"));
	filp_image(&img_sunflower_selector_background_right, &img_sunflower_selector_background_left);
	loadimage(&img_peashooter_selector_background_right, _T("resource/peashooter_selector_background.png"));
	filp_image(&img_peashooter_selector_background_right, &img_peashooter_selector_background_left);
	loadimage(&img_gloomshroom_selector_background_right, _T("resource/gloomshroom_selector_background.png"));
	filp_image(&img_gloomshroom_selector_background_right, &img_gloomshroom_selector_background_left);

	loadimage(&img_buff_icon_silence, _T("resource/buff_icon_silence.png"));
	loadimage(&img_buff_icon_hurry, _T("resource/buff_icon_hurry.png"));
	loadimage(&img_buff_icon_invisible, _T("resource/buff_icon_invisible.png"));
	loadimage(&img_buff_icon_recover, _T("resource/buff_icon_invisible.png"));

	atlas_bubbles.load_atlas_resource(_T("resource/bubbles_%d.png"), 7);
	atlas_bubbles_ex.load_atlas_resource(_T("resource/bubbles_ex_%d.png"), 7);

	atlas_buff_box_blue.load_atlas_resource(_T("resource/buff_box_blue_%d.png"), 4);
	atlas_buff_box_pink.load_atlas_resource(_T("resource/buff_box_pink_%d.png"), 4);
	atlas_buff_box_yellow.load_atlas_resource(_T("resource/buff_box_yellow_%d.png"), 4);

	atlas_run_effect_right.load_atlas_resource(_T("resource/run_effect_%d.png"), 4);
	filp_atlas(atlas_run_effect_right, atlas_run_effect_left);
	atlas_jump_effect_right.load_atlas_resource(_T("resource/jump_effect_%d.png"), 5);
	filp_atlas(atlas_jump_effect_right, atlas_jump_effect_left);
	atlas_land_effect.load_atlas_resource(_T("resource/land_effect_%d.png"), 2);

	// 泡泡菇
	atlas_gloomshroom_die.load_atlas_resource(_T("resource/gloomshroom_die_%d.png"), 3);
	atlas_gloomshroom_idle_right.load_atlas_resource(_T("resource/gloomshroom_idle_%d.png"), 4);
	filp_atlas(atlas_gloomshroom_idle_right, atlas_gloomshroom_idle_left);
	atlas_gloomshroom_attack_ex_right.load_atlas_resource(_T("resource/gloomshroom_attack_ex_%d.png"), 7);
	filp_atlas(atlas_gloomshroom_attack_ex_right, atlas_gloomshroom_attack_ex_left);
	atlas_gloomshroom_run_right.load_atlas_resource(_T("resource/gloomshroom_run_%d.png"), 3);
	filp_atlas(atlas_gloomshroom_run_right, atlas_gloomshroom_run_left);

	atlas_nut_run_right.load_atlas_resource(_T("resource/nut_run_%d.png"), 3);
	filp_atlas(atlas_nut_run_right, atlas_nut_run_left);
	atlas_nut_die.load_atlas_resource(_T("resource/nut_die_%d.png"), 3);
	atlas_nut_idle_right.load_atlas_resource(_T("resource/nut_idle_%d.png"), 3);
	filp_atlas(atlas_nut_idle_right, atlas_nut_idle_left);
	atlas_nut_explode.load_atlas_resource(_T("resource/nut_explode_%d.png"), 5);
	atlas_nut_attack_ex.load_atlas_resource(_T("resource/nut_attack_ex_%d.png"), 5);

	atlas_peashooter_run_right.load_atlas_resource(_T("resource/peashooter_run_%d.png"), 5);
	filp_atlas(atlas_peashooter_run_right, atlas_peashooter_run_left);
	atlas_peashooter_die.load_atlas_resource(_T("resource/peashooter_die_%d.png"), 4);
	atlas_peashooter_idle_right.load_atlas_resource(_T("resource/peashooter_idle_%d.png"), 9);
	filp_atlas(atlas_peashooter_idle_right, atlas_peashooter_idle_left);
	atlas_peashooter_attack_ex_right.load_atlas_resource(_T("resource/peashooter_attack_ex_%d.png"), 3);
	filp_atlas(atlas_peashooter_attack_ex_right, atlas_peashooter_attack_ex_left);

	atlas_pea_break.load_atlas_resource(_T("resource/pea_break_%d.png"), 3);

	atlas_sun.load_atlas_resource(_T("resource/sun_%d.png"), 5);
	atlas_sun_explode.load_atlas_resource(_T("resource/sun_explode_%d.png"), 5);
	atlas_sun_ex.load_atlas_resource(_T("resource/sun_ex_%d.png"), 5);
	atlas_sun_ex_explode.load_atlas_resource(_T("resource/sun_ex_explode_%d.png"), 5);
	atlas_sun_text.load_atlas_resource(_T("resource/sun_text_%d.png"), 6);

	atlas_sunflower_idle_right.load_atlas_resource(_T("resource/sunflower_idle_%d.png"), 8);
	filp_atlas(atlas_sunflower_idle_right, atlas_sunflower_idle_left);
	atlas_sunflower_run_right.load_atlas_resource(_T("resource/sunflower_run_%d.png"), 5);
	filp_atlas(atlas_sunflower_run_right, atlas_sunflower_run_left);
	atlas_sunflower_die.load_atlas_resource(_T("resource/sunflower_die_%d.png"), 2);
	atlas_sunflower_attack_ex_right.load_atlas_resource(_T("resource/sunflower_attack_ex_%d.png"), 9);
	filp_atlas(atlas_sunflower_attack_ex_right, atlas_sunflower_attack_ex_left);

	mciSendString(_T("open resource/bgm_game.mp3 alias bgm_game"), NULL, 0, NULL);
	mciSendString(_T("open resource/bgm_menu.mp3 alias bgm_menu"), NULL, 0, NULL);
	mciSendString(_T("open resource/bubbles_shot.mp3 alias bubbles_shot"), NULL, 0, NULL);
	mciSendString(_T("open resource/bubbles_shot_ex.mp3 alias bubbles_shot_ex"), NULL, 0, NULL);
	mciSendString(_T("open resource/nut_explode.mp3 alias nut_explode"), NULL, 0, NULL);
	mciSendString(_T("open resource/pea_break_1.mp3 alias pea_break_1"), NULL, 0, NULL);
	mciSendString(_T("open resource/pea_break_2.mp3 alias pea_break_2"), NULL, 0, NULL);
	mciSendString(_T("open resource/pea_break_3.mp3 alias pea_break_3"), NULL, 0, NULL);
	mciSendString(_T("open resource/pea_shoot_1.mp3 alias pea_shoot_1"), NULL, 0, NULL);
	mciSendString(_T("open resource/pea_shoot_2.mp3 alias pea_shoot_2"), NULL, 0, NULL);
	mciSendString(_T("open resource/pea_shoot_ex.mp3 alias pea_shoot_ex"), NULL, 0, NULL);
	mciSendString(_T("open resource/sun_explode.mp3 alias sun_explode"), NULL, 0, NULL);
	mciSendString(_T("open resource/sun_explode_ex.mp3 alias sun_explode_ex"), NULL, 0, NULL);
	mciSendString(_T("open resource/sun_text.mp3 alias sun_text"), NULL, 0, NULL);
	mciSendString(_T("open resource/ui_confirm.wav alias ui_confirm"), NULL, 0, NULL);
	mciSendString(_T("open resource/ui_switch.wav alias ui_switch"), NULL, 0, NULL);
	mciSendString(_T("open resource/ui_win.wav alias ui_win"), NULL, 0, NULL);

}


int main(void) {

	ExMessage msg;
	menu_scene = new MenuScene;
	game_scene = new GameScene;
	selector_scene = new SelectorScene;
	_SM.set_current_scene(menu_scene);

	load_game_resource();
	initgraph(WIN_WIDHT, WIN_HEIGHT, EW_SHOWCONSOLE);

	settextstyle(28, 0, _T("IPix"));
	setbkmode(TRANSPARENT);

	BeginBatchDraw();
	while (true) {
		DWORD startTime = GetTickCount();

		while (peekmessage(&msg)) {
			_SM.OnInput(msg);
		}

		static DWORD last_frame_time = GetTickCount();
		DWORD current_frame_time = GetTickCount();
		DWORD interval_time = current_frame_time - last_frame_time;
		_SM.OnUpdate(interval_time);
		last_frame_time = current_frame_time;

		cleardevice();
		_SM.OnDraw(main_camera);
		FlushBatchDraw();

		DWORD endTime = GetTickCount();
		DWORD intervalTime = endTime - startTime;
		if (intervalTime < STANDAR_FRAME_INTERVAL_TIME) {
			Sleep(STANDAR_FRAME_INTERVAL_TIME - intervalTime);
		}
	}

	EndBatchDraw();

	closegraph();
	return 0;
}