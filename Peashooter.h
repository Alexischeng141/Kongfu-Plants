#pragma once 
#ifndef  _PEASHOOTER_H_
#define _PEASHOOTER_H_

#include "Role.h"
#include "Timer.h"
#include "PeashooterBullet.h"

extern Atlas atlas_peashooter_die;
extern Atlas atlas_peashooter_idle_left;
extern Atlas atlas_peashooter_idle_right;
extern Atlas atlas_peashooter_run_left;
extern Atlas atlas_peashooter_run_right;
extern Atlas atlas_peashooter_attack_ex_right;
extern Atlas atlas_peashooter_attack_ex_left;

// extern Camera main_camera;


class Peashooter : public Role 
{
public:
	Peashooter() {
		// 设置动画图集
		animation_idle_left.set_atlas(&atlas_peashooter_idle_left);
		animation_idle_right.set_atlas(&atlas_peashooter_idle_right);
		animation_run_left.set_atlas(&atlas_peashooter_run_left);
		animation_run_right.set_atlas(&atlas_peashooter_run_right);
		animation_attack_ex_left.set_atlas(&atlas_peashooter_attack_ex_left);
		animation_attack_ex_right.set_atlas(&atlas_peashooter_attack_ex_right);

		// 设置动画帧间隔
		animation_idle_left.set_inter_time(75);
		animation_idle_right.set_inter_time(75);
		animation_run_left.set_inter_time(75);
		animation_run_right.set_inter_time(75);
		animation_attack_ex_left.set_inter_time(75);
		animation_attack_ex_right.set_inter_time(75);

		role_collision_box.x = 96;
		role_collision_box.y = 96;
		
		timer_attack_ex.set_wait_time(attack_ex_duration);
		timer_attack_ex.set_one_shot(true);
		timer_attack_ex.set_callback([&]() { is_attacking_ex = false; });

		timer_spwan_pea_ex.set_wait_time(100);
		timer_spwan_pea_ex.set_callback([&]() { spawn_pea_bullet(speed_pea_ex); });

		attack_cd = 100;

	}
	~Peashooter() = default;

	void on_update(int interval_time) {

		Role::on_update(interval_time);

		if (is_attacking_ex) {
			main_camera.shake(5, 100);
			timer_attack_ex.on_updata(interval_time);
			timer_spwan_pea_ex.on_updata(interval_time);
		}
	}

	void on_input(const ExMessage& msg) {
		Role::on_input(msg);
	}

	void on_draw(const Camera& camera) {
		Role::on_draw(camera);

		
	}

	void on_attack() {

		spawn_pea_bullet(speed_pea);

		switch (rand() % 2)
		{
		case 0:
			mciSendString(_T("play pea_shoot_1 from 0"), NULL, 0, NULL);
			break;
		case 1:
			mciSendString(_T("play pea_shoot_2 from 0"), NULL, 0, NULL);
			break;
		default:
			break;
		}
	}

	void on_attack_ex() {
		is_attacking_ex = true;
		timer_attack_ex.restart();

		is_facing_right ? animation_attack_ex_right.reset() : animation_attack_ex_left.reset();
		mciSendString(_T("play pea_shoot_ex from 0"), NULL, 0, NULL);
	}

private:

	// 子弹生成逻辑
	void spawn_pea_bullet(float speed) {
		Bullet* bullet = new PeashooterBullet();

		Vector2 bullet_position;
		Vector2 bullet_velocity = { 0,0 };

		const Vector2& bullet_collisionBox = bullet->getCollisionBox();

		bullet_position.x = is_facing_right
			? position.x + role_collision_box.x - bullet_collisionBox.x / 2
			: position.x - bullet_collisionBox.x / 2;
		bullet_position.y = position.y;

		bullet_velocity.x = is_facing_right ? speed : -speed;
		bullet_velocity.y = 0;

		bullet->setPosition(bullet_position.x, bullet_position.y);
		bullet->setVelocity(bullet_velocity.x, bullet_velocity.y);

		bullet->setCollideTarget(role_id == RoleId::P1 ? RoleId::P2 : RoleId::P1);
		bullet->setCallback([&]() { mp += 25; });

		Bullet_list.push_back(bullet);
	}

private:

	const float speed_pea = 0.75f;
	const float speed_pea_ex = 1.5f;
	const int attack_ex_duration = 2500;		// 特殊攻击持续时间
private:
	
	Timer timer_attack_ex;						// 特殊攻击定时器
	Timer timer_spwan_pea_ex;					// 豌豆子弹发射定时器

};

#endif // ! _PEASHOOTER_H_
