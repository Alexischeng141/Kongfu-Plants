#pragma once
#ifndef _ROLE_H_
#define _ROLE_H_

#include "Camera.h"
#include "Bullet.h"
#include "Timer.h"
#include "Vector2.h"
#include "RoleId.h"
#include "Animation.h"
#include "Platform.h"

#include <graphics.h>

extern bool is_debug;

extern std::vector<Platform> Platform_list;
extern std::vector<Bullet*> Bullet_list;

class Role
{
public:

	Role() {

		current_animation = &animation_idle_right;

		timer_attack.set_wait_time(attack_cd);
		timer_attack.set_one_shot(true);
		timer_attack.set_callback([&]() { can_attack = true; });

		timer_invulnerable.set_wait_time(750);
		timer_invulnerable.set_one_shot(true);
		timer_invulnerable.set_callback([&]() { is_invulnerable = false; });

		timer_invulnerable_blink.set_wait_time(750);
		timer_invulnerable_blink.set_one_shot(true);
		timer_invulnerable_blink.set_callback([&]() { 
			is_showing_invulnerable_frame = !is_showing_invulnerable_frame; 
		});


	}

	~Role() = default;

	virtual void on_attack() {}

	virtual void on_attack_ex() {}

	virtual void on_update(int interval_time) {

		int move_direction = is_right_key_down - is_left_key_down;		// move_diection的值大于1 表示角色朝向右边

		if (move_direction != 0) {
			// 玩家移动时播放移动动画
			if (!is_attacking_ex)
				is_facing_right = move_direction > 0;
			current_animation = is_facing_right ? &animation_run_right : &animation_run_left;
			float distance = move_direction * role_run_velocity * interval_time;
			on_run(distance);
		}
		else {
			// 玩家无位移时播放角色待机动画
			current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;
		}

		// 玩家处于特殊攻击状态时改变current_animation指针
		if (is_attacking_ex)
		{
			current_animation = is_facing_right ? &animation_attack_ex_right : &animation_attack_ex_left;
		}
		
		current_animation->on_update(interval_time);			// 更新动画帧

		timer_attack.on_updata(interval_time);
		timer_invulnerable.on_updata(interval_time);
		timer_invulnerable_blink.on_updata(interval_time);

		if (is_showing_invulnerable_frame) {
			sketch_image(current_animation->get_current_frame(), &img_sketch);
		}

		move_and_collide(interval_time);
	}

	virtual void on_input(const ExMessage& msg) {
		switch (msg.message) {
			{
		case WM_KEYDOWN:
			switch (role_id)
			{
			case RoleId::P1:
				switch (msg.vkcode)
				{
				case 0x41:
					is_left_key_down = true;
					break;
				case 0x44:
					is_right_key_down = true;
					break;
				case 0x57:
					on_jump();
					break;
				case 0x46:
					if (can_attack) {
						on_attack();
						can_attack = false;
						timer_attack.restart();
					}
					break;
				case 0x47:
					if (mp >= 100) {
						on_attack_ex();
						mp = 0;
					}
				default:
					break; 
				}
				break;
			case RoleId::P2:
				switch (msg.vkcode)
				{
				case VK_LEFT:
					is_left_key_down = true;
					break;
				case VK_RIGHT:
					is_right_key_down = true;
					break;
				case VK_UP:
					on_jump();
					break;
				case VK_OEM_PERIOD:
					if (can_attack) {
						on_attack();
						can_attack = false;
						timer_attack.restart();
					}
					break;
				case VK_OEM_2:
					if (mp >= 100) {
						on_attack_ex();
						mp = 0;
					}
				default:
					break;
				}
				break;
			default:
				break;
			}
			break;
		case WM_KEYUP:
			switch (role_id)
			{
			case RoleId::P1:
				switch (msg.vkcode)
				{
				case 0x41:
					is_left_key_down = false;
					break;
				case 0x44:
					is_right_key_down = false;
					break;
				default:
					break;
				}
				break;
			case RoleId::P2:
				switch (msg.vkcode)
				{
				case VK_LEFT:
					is_left_key_down = false;
					break;
				case VK_RIGHT:
					is_right_key_down = false;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
			break;
		default:
			break;
			}
		}
	}

	virtual void on_draw(const Camera & camera) {

		if (hp > 0 && is_invulnerable && is_showing_invulnerable_frame) {
			putimage_alpha(camera, (int)position.x, (int)position.y, &img_sketch);
		}
		else {
			current_animation->on_draw(camera, (int)position.x, (int)position.y);
		}

		if (is_debug) {
			setlinecolor(RGB(0, 125, 255));
			rectangle((int)position.x, (int)position.y, (int)(position.x + role_collision_box.x), (int)(position.y + role_collision_box.y));
		}
	}

	virtual void on_run(float distance) {

		if (is_attacking_ex)
			return;

		position.x += distance;
	}

	virtual void on_jump() {

		if (velocity.y != 0 || is_attacking_ex)
			return;
		
		velocity.y += role_jump_velocity;
	}

	void set_id(RoleId role_id) {
		this->role_id = role_id;
	}

	void set_position(float x, float y) {
		this->position.x = x;
		this->position.y = y;
	}

	const Vector2& get_position() const {
		return position;
	}

	const Vector2& get_role_collision_box() const {
		return role_collision_box;
	}

	RoleId getRoleId() {
		return this->role_id;
	}

protected:
	void move_and_collide(int delta) {
		velocity.y += gravity * delta;			// 速度存储器记录了y方向上的速度分量
		position += velocity * (float)delta;

		if (velocity.y > 0) {
			for (const Platform& platform : Platform_list) {
				const Platform::CollisionBox& platform_collision_box = platform.collision_box;
				bool is_collide_x = (max(position.x + role_collision_box.x, platform_collision_box.x_right) - min(position.x, platform_collision_box.x_left)
					<= role_collision_box.x + (platform_collision_box.x_right - platform_collision_box.x_left));
				bool is_collide_y = (platform_collision_box.y >= position.y && platform_collision_box.y <= position.y + role_collision_box.y);
				
				
				if (is_collide_x && is_collide_y) {
					float delta_position_y = velocity.y * delta;
					float pre_position_y = position.y + role_collision_box.y - delta_position_y;	// 回退到上一帧的碰撞箱底部的y坐标
					if (pre_position_y <= platform_collision_box.y) {
						position.y = platform_collision_box.y - role_collision_box.y;
						velocity.y = 0;
						break;
					}
				}
			}
		}

		// 不处于无敌状态时
		if (!is_invulnerable) {
			for (Bullet* bullet : Bullet_list) {

				// 在Bullet_list容器找出所有作用与自身的子弹
				if (!bullet->getCanCauseDamage() || bullet->getCollideTargetId() != role_id)
					continue;
				
				// 判定是否发生碰撞
				if (bullet->checkCollisionBox(position, role_collision_box)) {
					make_invulnerable();
					bullet->on_collide();	
					bullet->setCanCauseDamage(false);			// 设置可造成伤害状态为false 
					hp -= bullet->getDamage();			 
				}
			}
		}

	}

	// 碰撞判定成功的条件：
	// 上一帧平台的y坐标小于角色碰撞箱底部y坐标
	// 下一帧平台的y坐标大于角色碰撞箱底部y坐标

	// 设置玩家为无敌状态
	void make_invulnerable() {
		is_invulnerable = true;
		timer_invulnerable.restart();
	}

protected:
	enum playerType
	{
		defaulttype = 0,
		peashooter,
		sunFlower,
		nut,
		gloomshroom
	};


protected:
	Vector2 position = { 0,0 };					// 角色位置
	Vector2 velocity = { 0,0 };					// 记录角色速度

	Vector2 role_collision_box = { 96, 96 };	// 角色碰撞箱

	Animation animation_idle_left;				// 朝向左的默认动画
	Animation animation_idle_right;
	Animation animation_run_left;				// 朝向左的奔跑动画
	Animation animation_run_right;
	Animation animation_attack_ex_left;			// 特殊攻击角色动画
	Animation animation_attack_ex_right;

	RoleId role_id = RoleId::P1;

	bool is_left_key_down = false;
	bool is_right_key_down = false;

	bool is_facing_right = true;
	bool is_attacking_ex = false;				// 是否正在释放特殊攻击

	int attack_cd = 500;						// 普通攻击冷却时间
protected:
	const float	gravity = 1.6e-3f;				// 重力加速度
	const float role_run_velocity = 0.55f;		// 玩家奔跑速度
	const float role_jump_velocity = -0.85f;	// 跳跃速度

protected:
	int mp = 0;									// 技能值
	int hp = 100;								// 生命值

private:

	IMAGE img_sketch;
	Animation* current_animation = nullptr;

	bool is_alive = true;
	bool can_attack = true;						// 是否可以释放普通攻击
	bool is_invulnerable = false;				// 角色是否处于无敌状态
	bool is_showing_invulnerable_frame = false;	// 当前帧是否应该显示剪影

	Timer timer_attack;							// 普通攻击冷却定时器
	Timer timer_attack_ex;						// 必杀技持续时间定时器
	Timer timer_invulnerable;					// 无敌状态定时器
	Timer timer_invulnerable_blink;				// 无敌状态闪烁定时器

};
#endif // !_ROLE_H_
