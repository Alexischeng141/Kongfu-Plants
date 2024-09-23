#pragma once
#ifndef _ROLE_H_
#define _ROLE_H_

#include "Camera.h"
#include "Vector2.h"
#include "RoleId.h"
#include "Animation.h"
#include "Platform.h"

#include <graphics.h>

extern std::vector<Platform> Platform_list;

class Role
{
public:

	Role() {
		current_animation = &animation_idle_right;
	}

	~Role() = default;

	virtual void on_update(int interval_time) {

		int move_direction = is_right_key_down - is_left_key_down;		// move_diection的值大于1 表示角色朝向右边

		if (move_direction != 0) {
			// 玩家移动时播放移动动画
			is_facing_right = move_direction > 0;
			current_animation = is_facing_right ? &animation_run_right : &animation_run_left;
			float distance = move_direction * role_run_velocity * interval_time;
			on_run(distance);
		}
		else {
			// 玩家无移动是播放角色待机动画
			current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;
		}

		current_animation->on_update(interval_time);

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
		current_animation->on_draw(camera, (int)position.x, (int)position.y);
	}

	virtual void on_run(float distance) {
		position.x += distance;
	}

	virtual void on_jump() {

		if (velocity.y != 0)
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
	}

	// 碰撞判定成功的条件：
	// 上一帧平台的y坐标小于角色碰撞箱底部y坐标
	// 下一帧平台的y坐标大于角色碰撞箱底部y坐标

protected:
	Vector2 position = { 0,0 };					// 角色位置
	Vector2 velocity = { 0,0 };					// 记录角色速度

	Vector2 role_collision_box = { 96, 96 };	// 角色碰撞箱

	Animation animation_idle_left;				// 朝向左的默认动画
	Animation animation_idle_right;
	Animation animation_run_left;				// 朝向左的奔跑动画
	Animation animation_run_right;

	RoleId role_id = RoleId::P1;

	bool is_left_key_down = false;
	bool is_right_key_down = false;

	bool is_facing_right = true;

protected:
	const float	gravity = 1.6e-3f;				// 重力加速度
	const float role_run_velocity = 0.55f;		// 玩家奔跑速度
	const float role_jump_velocity = -0.85f;	// 跳跃速度
	
private:
	Animation* current_animation = nullptr;

};
#endif // !_ROLE_H_
