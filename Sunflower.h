#ifndef _SUNFLOWER_H_
#define _SUNFLOWER_H_

#include "Role.h"
#include "Vector2.h"
#include "SunflowerBullet.h"
#include "SunflowerBulletEx.h"

extern Atlas atlas_sunflower_die;
extern Atlas atlas_sunflower_idle_left;
extern Atlas atlas_sunflower_idle_right;
extern Atlas atlas_sunflower_run_left;
extern Atlas atlas_sunflower_run_right;
extern Atlas atlas_sunflower_attack_ex_left;
extern Atlas atlas_sunflower_attack_ex_right;
extern Atlas atlas_sun_text;

extern Role* role_1;
extern Role* role_2;


class Sunflower : public Role
{
public:
	Sunflower() {
		// 设置动画图集
		animation_idle_left.set_atlas(&atlas_sunflower_idle_left);
		animation_idle_right.set_atlas(&atlas_sunflower_idle_right);
		animation_run_left.set_atlas(&atlas_sunflower_run_left);
		animation_run_right.set_atlas(&atlas_sunflower_run_right);
		animation_attack_ex_left.set_atlas(&atlas_sunflower_attack_ex_left);
		animation_attack_ex_right.set_atlas(&atlas_sunflower_attack_ex_right);
		animation_sun_text.set_atlas(&atlas_sun_text);

		// 设置动画帧间隔
		animation_idle_left.set_inter_time(75);
		animation_idle_right.set_inter_time(75);
		animation_run_left.set_inter_time(75);
		animation_run_right.set_inter_time(75);
		animation_attack_ex_left.set_inter_time(100);
		animation_attack_ex_right.set_inter_time(100);
		animation_sun_text.set_inter_time(100);

		animation_attack_ex_left.set_loop(false);
		animation_attack_ex_right.set_loop(false);
		animation_sun_text.set_loop(false);

		role_collision_box.x = 96;
		role_collision_box.y = 96;
		
		animation_attack_ex_left.set_callback([&]() {
			is_attacking_ex = false;
			is_sun_text_visible = false;
			});
		
		animation_attack_ex_right.set_callback([&]() {
			is_attacking_ex = false;
			is_sun_text_visible = false;
			});

		attack_cd = 250;
		
	}

	~Sunflower() = default;

	void on_update(int interval_time) {

		Role::on_update(interval_time);

		if (is_sun_text_visible) {
			animation_sun_text.on_update(interval_time);
		}

		if (is_attacking_ex) {
			
		}
	}

	void on_input(const ExMessage& msg) {
		Role::on_input(msg);
	}

	void on_draw(const Camera& camera) {

		Role::on_draw(camera);

		if (is_sun_text_visible) {
			Vector2 text_position;
			IMAGE* frame = animation_sun_text.get_current_frame();
			text_position.x = position.x - (role_collision_box.x - frame->getwidth()) / 2;
			text_position.y = position.y - frame->getheight();
			animation_sun_text.on_draw(camera, (int)text_position.x, (int)text_position.y);
		}
	}

	void on_attack() {
		Bullet* bullet = new SunflowerBullet();
		Vector2 bullet_position;
		const Vector2& bullet_collision = bullet->getCollisionBox();
		bullet_position.x = position.x + (role_collision_box.x - bullet_collision.x) / 2;
		bullet_position.y = position.y;

		bullet->setPosition(bullet_position.x, bullet_position.y);
		bullet->setVelocity(is_facing_right ? velocity_sun.x : -velocity_sun.x, velocity_sun.y);

		bullet->setCollideTarget(role_id == RoleId::P1 ? RoleId::P2 : RoleId::P1);

		bullet->setCallback([&]() { mp += 35; });
		Bullet_list.push_back(bullet);

		mciSendString(_T("play sun_explod_ex from 0"), NULL, 0, NULL);
	}

	void on_attack_ex() {

		is_attacking_ex = true;
		is_sun_text_visible = true;
		animation_sun_text.reset();
		is_facing_right ? animation_attack_ex_right.reset() : animation_attack_ex_left.reset();
		
		Bullet* bullet = new SunflowerBulletEx();
		Role* target_role = (role_id == RoleId::P1 ? role_2 : role_1);

		Vector2 bullet_position;
		Vector2 bullet_velocity;
		const Vector2& bullet_collision_box = bullet->getCollisionBox();						// 子弹的碰撞箱
		const Vector2& target_collision_box = target_role->get_role_collision_box();			// 目标角色碰撞箱
		const Vector2& target_position = target_role->get_position();							// 目标角色的位置

		bullet_position.x = target_position.x + (target_collision_box.x - bullet_collision_box.x) / 2;
		bullet_position.y = -role_collision_box.y;
		bullet_velocity.x = 0;
		bullet_velocity.y = speed_sun_ex;

		bullet->setPosition(bullet_position.x, bullet_position.y);
		bullet->setVelocity(bullet_velocity.x, bullet_velocity.y);

		bullet->setCollideTarget(role_id == RoleId::P1 ? RoleId::P2 : RoleId::P1);

		bullet->setCallback([&]() { mp += 50; });

		Bullet_list.push_back(bullet);

		mciSendString(_T("play sun_text from 0"), NULL, 0, NULL);
	}

private:
	const float speed_sun_ex = 0.15f;
	const Vector2 velocity_sun = { 0.25f, -0.5f };

private:

	Animation animation_sun_text;
	bool is_sun_text_visible = false;

};

#endif // !_SUNFLOWER_H_
