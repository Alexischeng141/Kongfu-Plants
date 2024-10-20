#ifndef _GLOOMSHROOM_H_
#define _GLOOMSHROOM_H_

#include "Role.h"
#include "GloomshroomBullet.h"
#include "GloomshroomBulletEx.h"

extern Atlas atlas_gloomshroom_die;
extern Atlas atlas_gloomshroom_idle_left;
extern Atlas atlas_gloomshroom_idle_right;
extern Atlas atlas_gloomshroom_run_left;
extern Atlas atlas_gloomshroom_run_right;
extern Atlas atlas_gloomshroom_attack_ex_left;
extern Atlas atlas_gloomshroom_attack_ex_right;

extern std::vector<Bullet*> Bullet_list;

extern Role* role_1;
extern Role* role_2;

class Gloomshroom : public Role
{
public:
	Gloomshroom() {
		// 设置动画图集
		animation_idle_left.set_atlas(&atlas_gloomshroom_idle_left);
		animation_idle_right.set_atlas(&atlas_gloomshroom_idle_right);
		animation_run_left.set_atlas(&atlas_gloomshroom_run_left);
		animation_run_right.set_atlas(&atlas_gloomshroom_run_right);
		animation_attack_ex_left.set_atlas(&atlas_gloomshroom_attack_ex_left);
		animation_attack_ex_right.set_atlas(&atlas_gloomshroom_attack_ex_right);

		// 设置帧间隔
		animation_idle_left.set_inter_time(75);
		animation_idle_right.set_inter_time(75);
		animation_run_left.set_inter_time(75);
		animation_run_right.set_inter_time(75);
		animation_attack_ex_left.set_inter_time(100);
		animation_attack_ex_right.set_inter_time(100);

		
		timer_attack_ex_remain.set_wait_time(attack_ex_duration);
		timer_attack_ex_remain.set_one_shot(true);
		timer_attack_ex_remain.set_callback([&]() { is_attacking_ex = false; });

		timer_generate_bubbles.set_wait_time(100);
		timer_generate_bubbles.set_one_shot(false);
		timer_generate_bubbles.set_callback([&]() { generate_gloomshroombullet_ex(); });
		
		Role::set_player_type(4);

		// attack_cd = 100;

	}

	~Gloomshroom() = default;

	void on_update(int interval_time) {
		Role::on_update(interval_time);

		if (is_attacking_ex) {
			timer_attack_ex_remain.on_update(interval_time);
		}

	}

	void on_input(const ExMessage& msg) {
		Role::on_input(msg);
	}

	void on_draw(const Camera& camera) {
		Role::on_draw(camera);
	}

	void on_attack() override {

		generate_gloomshroombullet();
		mp += 100;
		mciSendString(_T("play bubbles_shot from 0"), NULL, 0, NULL);

	}

	void on_attack_ex() {
		// 生成必杀技子弹类型
		generate_gloomshroombullet_ex();
		mciSendString(_T("play bubbles_shot_ex from 0"), NULL, 0, NULL);

	}

private:

	// 生成子弹
	void generate_gloomshroombullet() {
		Bullet* bullet = new GloomshroomBullet();

		Vector2 size;
		Vector2 bulletPosition;

		Role* current_role_ptr = role_id == RoleId::P1 ? role_1 : role_2;

		size.x = 192;
		size.y = 192;

		bulletPosition.x = current_role_ptr->get_position().x - (size.x / 2 - current_role_ptr->get_role_collision_box().x / 2);
		bulletPosition.y = current_role_ptr->get_position().y - (size.y / 2 - current_role_ptr->get_role_collision_box().y / 2);

		bullet->setPosition(bulletPosition.x, bulletPosition.y);			// 设置初始位置

		bullet->setCollideTarget(role_id == RoleId::P1 ? RoleId::P2 : RoleId::P1);

		bullet->setCallback([&]() {
			mp += 20;
		});
		
		Bullet_list.push_back(bullet);
	}

	void generate_gloomshroombullet_ex() {
		is_attacking_ex = true;
		timer_attack_ex_remain.restart();
		


		Bullet* bullet_ex = new GloomshroomBulletEx();

		Vector2 size;
		Vector2 bulletPosititon;

		Role* current_role_ptr = role_id == RoleId::P1 ? role_1 : role_2;

		size.x = 300;
		size.y = 300;
		
		bulletPosititon.x = current_role_ptr->get_position().x - (size.x / 2 - current_role_ptr->get_role_collision_box().x / 2);
		bulletPosititon.y = current_role_ptr->get_position().y - (size.y / 2 - current_role_ptr->get_role_collision_box().y / 2);

		bullet_ex->setPosition(bulletPosititon.x, bulletPosititon.y);
		bullet_ex->setCollideTarget(role_id == RoleId::P1 ? RoleId::P2 : RoleId::P1);
		
		bullet_ex->setCallback([&]() {
			mp = 0;
		});
		
		Bullet_list.push_back(bullet_ex);
	}


private:
	
	Timer timer_attack_ex_remain;			// 必杀技持续时间
	Timer timer_generate_bubbles;			// 特殊攻击子弹生成间隔时间

	int attack_ex_duration = 2500;			// 特殊攻击持续时间
};

#endif // !_GLOOMSHROOM_H_
