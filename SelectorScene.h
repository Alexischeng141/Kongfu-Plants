#pragma once
#ifndef _SELECTORSCENE_H_
#define _SELECTORSCENE_H_

#include <iostream>
#include "scene.h"
#include "RoleId.h"
#include "SceneManager.h"
#include "Animation.h"

#include "Nut.h"
#include "Peashooter.h"
#include "Sunflower.h"
#include "Gloomshroom.h"

extern IMAGE img_vs;
extern IMAGE img_1P;
extern IMAGE img_2P;
extern IMAGE img_1P_desc;
extern IMAGE img_2P_desc;
extern IMAGE img_gravestone_left;
extern IMAGE img_gravestone_right;
extern IMAGE img_selector_tip;
extern IMAGE img_selector_background;

extern IMAGE img_1P_selector_btn_idle_left;
extern IMAGE img_1P_selector_btn_idle_right;
extern IMAGE img_1P_selector_btn_down_left;
extern IMAGE img_1P_selector_btn_down_right;
extern IMAGE img_2P_selector_btn_idle_left;
extern IMAGE img_2P_selector_btn_idle_right;
extern IMAGE img_2P_selector_btn_down_left;
extern IMAGE img_2P_selector_btn_down_right;

//角色背景
extern IMAGE img_peashooter_selector_background_left;
extern IMAGE img_peashooter_selector_background_right;
extern IMAGE img_sunflower_selector_background_left;
extern IMAGE img_sunflower_selector_background_right;
extern IMAGE img_gloomshroom_selector_background_left;
extern IMAGE img_gloomshroom_selector_background_right;
extern IMAGE img_nut_selector_background_left;
extern IMAGE img_nut_selector_background_right;

extern Atlas atlas_peashooter_idle_right;
extern Atlas atlas_sunflower_idle_right;
extern Atlas atlas_gloomshroom_idle_right;
extern Atlas atlas_nut_idle_right;


extern IMAGE img_avatar_peashooter;
extern IMAGE img_avatar_sunflower;
extern IMAGE img_avatar_gloomshroom;
extern IMAGE img_avatar_nut;

extern Role* role_1;
extern Role* role_2;

extern IMAGE* img_1p_avatar;
extern IMAGE* img_2p_avatar;

extern SceneManager _SM;

class SelectorScene : public scene {
public:
	SelectorScene() = default;
	~SelectorScene() = default;

	void OnEnter() {

		animation_peashooter.set_atlas(&atlas_peashooter_idle_right);
		animation_sunflower.set_atlas(&atlas_sunflower_idle_right);
		animation_gloomshroom.set_atlas(&atlas_gloomshroom_idle_right);
		animation_nut.set_atlas(&atlas_nut_idle_right);
		animation_peashooter.set_inter_time(100);
		animation_sunflower.set_inter_time(100);
		animation_gloomshroom.set_inter_time(100);
		animation_nut.set_inter_time(100);

		static const int OFFSET_X = 50;

		pos_img_vs.x = (getwidth() - img_vs.getwidth()) / 2;
		pos_img_vs.y = (getheight() - img_vs.getheight()) / 2;
		pos_img_tip.x = (getwidth() - img_selector_tip.getwidth()) / 2;
		pos_img_tip.y = getheight() - 125;
		pos_img_1P.x = (getwidth() / 2 - img_1P.getwidth()) / 2 - OFFSET_X;
		pos_img_1P.y = 35;
		pos_img_2P.x = getwidth() / 2 + (getwidth() / 2 - img_2P.getwidth()) / 2 + OFFSET_X;
		pos_img_2P.y = pos_img_1P.y;
		pos_img_1P_desc.x = (getwidth() / 2 - img_1P_desc.getwidth()) / 2 - OFFSET_X;
		pos_img_1P_desc.y = getheight() - 150;
		pos_img_2P_desc.x = getwidth() / 2 + (getwidth() / 2 - img_2P_desc.getwidth()) / 2 + OFFSET_X;
		pos_img_2P_desc.y = pos_img_1P_desc.y;
		pos_img_1P_gravestone.x = (getwidth() / 2 - img_gravestone_right.getwidth()) / 2 - OFFSET_X;
		pos_img_1P_gravestone.y = pos_img_1P.y + img_1P.getheight() + 35;
		pos_img_2P_gravestone.x = getwidth() / 2 + (getwidth() / 2 - img_gravestone_left.getwidth()) / 2 + OFFSET_X;
		pos_img_2P_gravestone.y = pos_img_1P_gravestone.y;
		pos_animation_1P.x = (getwidth() / 2 - atlas_peashooter_idle_right.get_image(0)->getwidth()) / 2 - OFFSET_X;
		pos_animation_1P.y = pos_img_1P_gravestone.y + 80;
		pos_animation_2P.x = getwidth() / 2 + (getwidth() / 2 - atlas_peashooter_idle_right.get_image(0)->getwidth()) / 2 + OFFSET_X;
		pos_animation_2P.y = pos_animation_1P.y;
		pos_img_1P_name.y = pos_animation_1P.y + 155;
		pos_img_2P_name.y = pos_img_1P_name.y;
		pos_1P_selector_btn_left.x = pos_img_1P_gravestone.x - img_1P_selector_btn_idle_left.getwidth();
		pos_1P_selector_btn_left.y = pos_img_1P_gravestone.y + (img_gravestone_right.getheight() - img_1P_selector_btn_idle_left.getheight()) / 2;
		pos_1P_selector_btn_right.x = pos_img_1P_gravestone.x + img_gravestone_right.getwidth();
		pos_1P_selector_btn_right.y = pos_1P_selector_btn_left.y;
		pos_2P_selector_btn_left.x = pos_img_2P_gravestone.x - img_2P_selector_btn_idle_left.getwidth();
		pos_2P_selector_btn_left.y = pos_1P_selector_btn_left.y;
		pos_2P_selector_btn_right.x = pos_img_2P_gravestone.x + img_gravestone_left.getwidth();
		pos_2P_selector_btn_right.y = pos_1P_selector_btn_left.y;

		mciSendString(_T("play bgm_menu repeat from 0"), NULL, 0, NULL);
	}

	void OnInput(const ExMessage& msg) {

		switch (msg.message)
		{
		case WM_KEYDOWN:
			switch (msg.vkcode)
			{
			case 0x41:
				// "A"
				is_btn_1P_left_down = true;

				break;
			case 0x44:
				// "D"
				is_btn_1P_right_down = true;

				break;
			case VK_LEFT:
				// "←"
				is_btn_2P_left_down = true;

				break;
			case VK_RIGHT:
				// "→"
				is_btn_2P_right_down = true;

				break;
			default:
				break;
			}
			break;
		case WM_KEYUP:
			switch (msg.vkcode)
			{
			case 0x41:
				// "A"
				is_btn_1P_left_down = false;
				player_type_1 = (playerType)(((int)playerType::Invalid + (int)player_type_1 - 1) % (int)playerType::Invalid);
				mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
				break;
			case 0x44:
				// "D"
				is_btn_1P_right_down = false;
				player_type_1 = (playerType)(((int)player_type_1 + 1) % (int)playerType::Invalid);
				mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
				break;
			case VK_LEFT:
				// "←"
				is_btn_2P_left_down = false;
				player_type_2 = (playerType)(((int)playerType::Invalid + (int)player_type_2 - 1) % (int)playerType::Invalid);
				mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
				break;
			case VK_RIGHT:
				// "→"
				is_btn_2P_right_down = false;
				player_type_2 = (playerType)(((int)player_type_2 + 1) % (int)playerType::Invalid);
				mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
				break;
			case VK_RETURN:
				mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
				_SM.swtich_scene_to(SceneManager::scenes::GAME_SCENE);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}

	void OnUpdate(int interval_time) {
		animation_peashooter.on_update(interval_time);
		animation_sunflower.on_update(interval_time);
		animation_gloomshroom.on_update(interval_time);
		animation_nut.on_update(interval_time);
		

		selector_background_scroll_locate_offset += 5;
		if (selector_background_scroll_locate_offset >= img_peashooter_selector_background_right.getwidth()) {
			selector_background_scroll_locate_offset = 0;
		}
	}

	void OnDraw(const Camera& camera) {

		IMAGE* img_P1_selector_background = &img_peashooter_selector_background_right;
		IMAGE* img_P2_selector_background = &img_sunflower_selector_background_left;

		switch (player_type_1)
		{
		case SelectorScene::playerType::Peashooter:
			img_P1_selector_background = &img_peashooter_selector_background_right;
			break;
		case SelectorScene::playerType::Sunflower:
			img_P1_selector_background = &img_sunflower_selector_background_right;
			break;
		case SelectorScene::playerType::Gloomshroom:
			img_P1_selector_background = &img_gloomshroom_selector_background_right;
			break;
		case SelectorScene::playerType::Nut:
			img_P1_selector_background = &img_nut_selector_background_right;
			break;
		case SelectorScene::playerType::Invalid:
			break;
		default:
			break;
		}

		switch (player_type_2)
		{
		case SelectorScene::playerType::Peashooter:
			img_P2_selector_background = &img_peashooter_selector_background_left;
			break;
		case SelectorScene::playerType::Sunflower:
			img_P2_selector_background = &img_sunflower_selector_background_left;
			break;
		case SelectorScene::playerType::Gloomshroom:
			img_P2_selector_background = &img_gloomshroom_selector_background_left;
			break;
		case SelectorScene::playerType::Nut:
			img_P2_selector_background = &img_nut_selector_background_left;
			break;
		case SelectorScene::playerType::Invalid:
			break;
		default:
			break;
		}

		putimage(0, 0, &img_selector_background);

		putimage_alpha(selector_background_scroll_locate_offset - img_P1_selector_background->getwidth(), 0, img_P1_selector_background);
		putimage_alpha(selector_background_scroll_locate_offset, 0,
			img_P1_selector_background->getwidth() - selector_background_scroll_locate_offset, 0, img_P1_selector_background, 0, 0);
		putimage_alpha(getwidth() - img_P2_selector_background->getwidth(), 0, img_P2_selector_background->getwidth() -
			selector_background_scroll_locate_offset, 0, img_P2_selector_background, selector_background_scroll_locate_offset, 0);
		putimage_alpha(getwidth() - selector_background_scroll_locate_offset, 0, img_P2_selector_background);

		putimage_alpha(camera, pos_img_vs.x, pos_img_vs.y, &img_vs);

		putimage_alpha(camera, pos_img_1P.x, pos_img_1P.y, &img_1P);
		putimage_alpha(camera, pos_img_2P.x, pos_img_2P.y, &img_2P);
		putimage_alpha(camera, pos_img_1P_gravestone.x, pos_img_1P_gravestone.y, &img_gravestone_right);
		putimage_alpha(camera, pos_img_2P_gravestone.x, pos_img_2P_gravestone.y, &img_gravestone_left);


		switch (player_type_1)
		{
		case SelectorScene::playerType::Peashooter:
			animation_peashooter.on_draw(camera, pos_animation_1P.x, pos_animation_1P.y);
			pos_img_1P_name.x = pos_img_1P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_peashooter_name)) / 2;
			outtextxy_shaded(pos_img_1P_name.x, pos_img_1P_name.y, str_peashooter_name);
			break;
		case SelectorScene::playerType::Sunflower:
			animation_sunflower.on_draw(camera, pos_animation_1P.x, pos_animation_1P.y);
			pos_img_1P_name.x = pos_img_1P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_sunflower_name)) / 2;
			outtextxy_shaded(pos_img_1P_name.x, pos_img_1P_name.y, str_sunflower_name);
			break;
		case SelectorScene::playerType::Gloomshroom:
			animation_gloomshroom.on_draw(camera, pos_animation_1P.x, pos_animation_1P.y);
			pos_img_1P_name.x = pos_img_1P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_gloomshroom_name)) / 2;
			outtextxy_shaded(pos_img_1P_name.x, pos_img_1P_name.y, str_gloomshroom_name);
			break;
		case SelectorScene::playerType::Nut:
			animation_nut.on_draw(camera, pos_animation_1P.x, pos_animation_1P.y);
			pos_img_1P_name.x = pos_img_1P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_nut_name)) / 2;
			outtextxy_shaded(pos_img_1P_name.x, pos_img_1P_name.y, str_nut_name);
		case SelectorScene::playerType::Invalid:
			break;
		default:
			break;
		}

		switch (player_type_2)
		{
		case SelectorScene::playerType::Peashooter:
			animation_peashooter.on_draw(camera, pos_animation_2P.x, pos_animation_2P.y);
			pos_img_2P_name.x = pos_img_2P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_peashooter_name)) / 2;
			outtextxy_shaded(pos_img_2P_name.x, pos_img_2P_name.y, str_peashooter_name);
			break;
		case SelectorScene::playerType::Sunflower:
			animation_sunflower.on_draw(camera, pos_animation_2P.x, pos_animation_2P.y);
			pos_img_2P_name.x = pos_img_2P_gravestone.x + (img_gravestone_left.getwidth() - textwidth(str_sunflower_name)) / 2;
			outtextxy_shaded(pos_img_2P_name.x, pos_img_2P_name.y, str_sunflower_name);
			break;
		case SelectorScene::playerType::Gloomshroom:
			animation_gloomshroom.on_draw(camera, pos_animation_2P.x, pos_animation_2P.y);
			pos_img_2P_name.x = pos_img_2P_gravestone.x + (img_gravestone_left.getwidth() - textwidth(str_gloomshroom_name)) / 2;
			outtextxy_shaded(pos_img_2P_name.x, pos_img_2P_name.y, str_gloomshroom_name);
			break;
		case SelectorScene::playerType::Nut:
			animation_nut.on_draw(camera, pos_animation_2P.x, pos_animation_2P.y);
			pos_img_1P_name.x = pos_img_2P_gravestone.x + (img_gravestone_left.getwidth() - textwidth(str_nut_name)) / 2;
			outtextxy_shaded(pos_img_2P_name.x, pos_img_2P_name.y, str_nut_name);
			break;
		case SelectorScene::playerType::Invalid:
			break;
		default:
			break;
		}

		putimage_alpha(pos_1P_selector_btn_left.x, pos_1P_selector_btn_left.y,
			is_btn_1P_left_down ? &img_1P_selector_btn_down_left : &img_1P_selector_btn_idle_left);
		putimage_alpha(pos_1P_selector_btn_right.x, pos_1P_selector_btn_right.y,
			is_btn_1P_right_down ? &img_1P_selector_btn_down_right : &img_1P_selector_btn_idle_right);
		putimage_alpha(pos_2P_selector_btn_left.x, pos_2P_selector_btn_left.y,
			is_btn_2P_left_down ? &img_2P_selector_btn_down_left : &img_2P_selector_btn_idle_left);
		putimage_alpha(pos_2P_selector_btn_right.x, pos_2P_selector_btn_right.y,
			is_btn_2P_right_down ? &img_2P_selector_btn_down_right : &img_2P_selector_btn_idle_right);

		putimage_alpha(camera, pos_img_1P_desc.x, pos_img_1P_desc.y, &img_1P_desc);
		putimage_alpha(camera, pos_img_2P_desc.x, pos_img_2P_desc.y, &img_2P_desc);
		putimage_alpha(camera, pos_img_tip.x, pos_img_tip.y, &img_selector_tip);
		
	}

	void OnExit() {
		
		switch (player_type_1)
		{
		case SelectorScene::playerType::Peashooter:
			role_1 = new Peashooter();
			img_1p_avatar = &img_avatar_peashooter;
			break;
		case SelectorScene::playerType::Sunflower:
			role_1 = new Sunflower();
			img_1p_avatar = &img_avatar_sunflower;
			break;
		case SelectorScene::playerType::Gloomshroom:
			role_1 = new Gloomshroom();
			img_1p_avatar = &img_avatar_gloomshroom;
			break;
		case SelectorScene::playerType::Nut:
			role_1 = new Nut();
			img_1p_avatar = &img_avatar_nut;
			break;
		case SelectorScene::playerType::Invalid:
			break;
		default:
			break;
		}
		role_1->set_id(RoleId::P1);

		switch (player_type_2)
		{
		case SelectorScene::playerType::Peashooter:
			role_2 = new Peashooter(false);
			img_2p_avatar = &img_avatar_peashooter;
			break;
		case SelectorScene::playerType::Sunflower:
			role_2 = new Sunflower(false);
			img_2p_avatar = &img_avatar_sunflower;
			break;
		case SelectorScene::playerType::Gloomshroom:
			role_2 = new Gloomshroom();
			img_2p_avatar = &img_avatar_gloomshroom;
			break;
		case SelectorScene::playerType::Nut:
			role_2 = new Nut();
			img_2p_avatar = &img_avatar_nut;
			break;
		case SelectorScene::playerType::Invalid:
			break;
		default:
			break;
		}
		role_2->set_id(RoleId::P2);

		mciSendString(_T("stop bgm_menu"), NULL, 0, NULL);
	}
	

	// 渲染带阴影的文字
	void outtextxy_shaded(int x, int y, LPCTSTR str) {
		settextcolor(RGB(45, 45, 45));
		outtextxy(x + 3, y + 3, str);
		settextcolor(RGB(255, 255, 255));
		outtextxy(x, y, str);
	}

private:
	enum class playerType
	{
		Peashooter = 0,
		Sunflower,
		Gloomshroom,
		Nut,
		Invalid
	};

private:
	POINT pos_img_vs = { 0 };
	POINT pos_img_tip = { 0 };
	POINT pos_img_1P = { 0 };
	POINT pos_img_2P = { 0 };
	POINT pos_img_1P_desc = { 0 };
	POINT pos_img_2P_desc = { 0 };
	POINT pos_img_1P_name = { 0 };
	POINT pos_img_2P_name = { 0 };
	POINT pos_animation_1P = { 0 };
	POINT pos_animation_2P = { 0 };
	POINT pos_img_1P_gravestone = { 0 };
	POINT pos_img_2P_gravestone = { 0 };
	POINT pos_1P_selector_btn_left = { 0 };
	POINT pos_1P_selector_btn_right = { 0 };
	POINT pos_2P_selector_btn_left = { 0 };
	POINT pos_2P_selector_btn_right = { 0 };

	Animation animation_peashooter;
	Animation animation_sunflower;
	Animation animation_gloomshroom;
	Animation animation_nut;

	playerType player_type_1 = playerType::Peashooter;
	playerType player_type_2 = playerType::Sunflower;

	LPCTSTR str_peashooter_name = _T("婉豆射手");
	LPCTSTR str_sunflower_name = _T("龙日葵");
	LPCTSTR str_gloomshroom_name = _T("泡泡菇");
	LPCTSTR str_nut_name = _T("坚果");

	int selector_background_scroll_locate_offset = 0;	// 背景板滚动距离基准线

	bool is_btn_1P_left_down = false;
	bool is_btn_1P_right_down = false;
	bool is_btn_2P_left_down = false;
	bool is_btn_2P_right_down = false;
};
#endif // !_SELECTORSCENE_H_


