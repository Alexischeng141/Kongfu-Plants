#pragma once
#ifndef _ROLE_H_
#define _ROLE_H_

#include "Animation.h"
#include "SilenceBuffer.h"
#include "SpeedBoost.h"
#include "RecoveryBuffer.h"
#include "Invisible.h"
#include "BufferHUD.h"
#include "Bullet.h"
#include "Camera.h"
#include "Particle.h"
#include "Platform.h"
#include "RoleId.h"
#include "Timer.h"
#include "Vector2.h"

#include <graphics.h>

extern bool is_debug;

extern std::vector<Bullet*> Bullet_list;
extern std::vector<BufferHUD*> BufferHUD_list;
extern std::vector<Platform> Platform_list;

extern Atlas atlas_run_effect_right;
extern Atlas atlas_jump_effect_right;
extern Atlas atlas_land_effect;

extern IMAGE img_1P_cursor;
extern IMAGE img_2P_cursor;

class Role
{
public:

	Role(bool facing_right = true) : is_facing_right(facing_right) {

		current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;

		animation_jump_effect.set_atlas(&atlas_jump_effect_right);
		animation_jump_effect.set_inter_time(25);
		animation_jump_effect.set_loop(false);
		animation_jump_effect.set_callback([&]()
			{
				is_jump_effect_visible = false;
			});
		
		animation_land_effect.set_atlas(&atlas_land_effect);
		animation_land_effect.set_inter_time(50);
		animation_land_effect.set_loop(false);
		animation_land_effect.set_callback([&]()
			{
				is_land_effect_visible = false;
			});

		timer_cursor_visibility.restart();
		timer_cursor_visibility.set_wait_time(2500);
		timer_cursor_visibility.set_one_shot(true);
		timer_cursor_visibility.set_callback([&]()
			{
				is_cursor_visible = false;
			});
		
		timer_attack.set_wait_time(attack_cd);
		timer_attack.set_one_shot(true);
		timer_attack.set_callback([&]() { can_attack = true; });

		timer_invulnerable.set_wait_time(750);
		timer_invulnerable.set_one_shot(true);
		timer_invulnerable.set_callback([&]() { is_invulnerable = false; });

		timer_invulnerable_blink.set_wait_time(75);
		timer_invulnerable_blink.set_callback([&]() { 
			is_showing_invulnerable_frame = !is_showing_invulnerable_frame; 
		});

		/*
			emplace_back 是 C++ 标准库中 std::vector 类的一个成员函数，用于在容器的末尾直接构造一个元素。
			与 push_back 相似，但 emplace_back 更高效，因为它避免了不必要的拷贝或移动操作。
			emplace_back 直接调用 MyClass 的构造函数，在容器 vec 的末尾创建一个对象，而不需要通过临时对象来进行拷贝或移动。
		*/
		timer_run_effect_generator.set_wait_time(75);
		timer_run_effect_generator.set_callback([&]()
			{
				Vector2 particle_position;
				IMAGE* frame = atlas_run_effect_right.get_image(0);
				particle_position.x = position.x + (role_collision_box.x - frame->getwidth()) / 2;
				particle_position.y = position.y + (role_collision_box.y - frame->getheight());
				Particle_list.emplace_back(particle_position, &atlas_run_effect_right, 45);		//在容器中添加一个新的粒子对象
			});

		timer_die_effect_generator.set_wait_time(35);
		timer_die_effect_generator.set_callback([&]()
			{
				Vector2 particle_position;
				IMAGE* frame = atlas_run_effect_right.get_image(0);
				particle_position.x = position.x + (role_collision_box.x - frame->getwidth()) / 2;
				particle_position.y = position.y + (role_collision_box.y - frame->getheight());
				Particle_list.emplace_back(particle_position, &atlas_run_effect_right, 150);
			});

		

	}

	~Role() = default;

	virtual void on_attack() {}

	virtual void on_attack_ex() {}

	virtual void on_update(int interval_time) {

		int move_direction = is_right_key_down - is_left_key_down;		// move_direction 的值大于1 表示角色朝向右边

		if (move_direction != 0) {
			// 玩家移动时播放移动动画
			if (is_attacking_ex && !(type==playerType::gloomshroom))
				return;
			is_facing_right = move_direction > 0;
			current_animation = is_facing_right ? &animation_run_right : &animation_run_left;
			float distance = move_direction * role_run_velocity * interval_time;
			on_run(distance);
		}
		else {
			// 玩家无位移时播放角色待机动画
			current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;
			timer_run_effect_generator.pause();		// 玩家无位移时暂停粒子发射器,此时粒子不在生成
		}

		// 玩家处于特殊攻击状态时改变 current_animation 指针
		if (is_attacking_ex)
		{
			current_animation = is_facing_right ? &animation_attack_ex_right : &animation_attack_ex_left;
		}

		// 如果玩家死亡，开始更新死亡粒子特效
		if (hp <= 0) {
			timer_die_effect_generator.on_update(interval_time);
			current_animation = last_hurt_direction.x < 0 ? &animation_die_left : &animation_die_right;
		}
		
		current_animation->on_update(interval_time);					// 更新动画帧
		animation_jump_effect.on_update(interval_time);					// 更新跳跃特效定时器
		animation_land_effect.on_update(interval_time);					// 更新落地特效定时器
		timer_cursor_visibility.on_update(interval_time);				// 更新玩家指示器定时器
		timer_attack.on_update(interval_time);							// 更新攻击cd
		timer_invulnerable.on_update(interval_time);					// 更新无敌时间定时器
		timer_invulnerable_blink.on_update(interval_time);				// 更新无敌帧闪烁定时器
		timer_run_effect_generator.on_update(interval_time);			// 更新奔跑粒子发射器

		// 删除粒子
		Particle_list.erase(std::remove_if(
			Particle_list.begin(), Particle_list.end(),
			[](const Particle& particle)
			{
				return !particle.check_valid();
			}),
			Particle_list.end());

		// 更新粒子
		for (Particle& particle : Particle_list) {
			particle.on_update(interval_time);
		}

		Buffer_list_triggered.erase(std::remove_if(
			Buffer_list_triggered.begin(), Buffer_list_triggered.end(),
			[](const Buffer* buffer)
			{
				bool delectable = buffer->checkIsExpired();
				if (delectable) {
					buffer->on_callback();
					delete buffer;
				}
				return delectable;
			}
		), Buffer_list_triggered.end());

		// 更新buffer
		for (Buffer* buffer : Buffer_list_triggered) {
			buffer->on_update(interval_time);
		}

		// 碰撞检测
		move_and_collide(interval_time);

		// 渲染无敌帧动画
		if (is_showing_invulnerable_frame && hp > 0) 
			sketch_image(current_animation->get_current_frame(), &img_sketch);
		

	}

	virtual void on_input(const ExMessage& msg) {
		if (!is_alive)
			return;
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
						if (this->type == playerType::gloomshroom) {
							on_attack();
							can_attack = false;
							break;
						}
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
						if (this->type == playerType::gloomshroom) {
							on_attack();
							can_attack = false;
							break;
						}
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

		if (is_cursor_visible) {
			switch (role_id)
			{
			case RoleId::P1:
				putimage_alpha(camera, (int)(position.x + (role_collision_box.x - img_1P_cursor.getwidth()) / 2),
					(int)(position.y - img_1P_cursor.getheight()), &img_1P_cursor);
				break;
			case RoleId::P2:
				putimage_alpha(camera, (int)(position.x + (role_collision_box.x - img_2P_cursor.getwidth()) / 2),
					(int)(position.y - img_2P_cursor.getheight()), &img_2P_cursor);
				break;
			default:
				break;
			}
		}

		if (is_land_effect_visible) {
			animation_land_effect.on_draw(camera, (int)position_land_effect.x, (int)position_land_effect.y);
		}
		if (is_jump_effect_visible) {
			animation_jump_effect.on_draw(camera, (int)position_jump_effect.x, (int)position_jump_effect.y);
		}

		for (const Particle& particle : Particle_list)
			particle.on_draw(camera);

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

	// 控制玩家行走
	virtual void on_run(float distance) {
		position.x += distance * _speedBoostRate;
		timer_run_effect_generator.resume();		// 恢复粒子发射器，生成粒子
	}

	// 控制玩家掉落
	virtual void on_land() {
		is_land_effect_visible = true;
		animation_land_effect.reset();
		IMAGE* effect_frame = animation_land_effect.get_current_frame();
		position_land_effect.x = position.x + (role_collision_box.x - effect_frame->getwidth()) / 2;
		position_land_effect.y = position.y + role_collision_box.y - effect_frame->getheight();
	}

	// 控制玩家跳跃
	virtual void on_jump() {

		if (velocity.y != 0 || is_attacking_ex)
			return;
		velocity.y += role_jump_velocity;
		is_jump_effect_visible = true;
		animation_jump_effect.reset();
		IMAGE* effect_frame = animation_jump_effect.get_current_frame();
		position_jump_effect.x = position.x + (role_collision_box.x - effect_frame->getwidth()) / 2;
		position_jump_effect.y = position.y + role_collision_box.y - effect_frame->getheight();
	}

	void set_id(RoleId role_id) {
		this->role_id = role_id;
	}

	void set_hp(int hp) {
		this->hp = hp;
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

	int get_player_type() {
		return type;
	}

	void set_attack(bool val) {
		this->can_attack = val;
	}

	void set_player_type(int type) {
		this->type = (playerType)type;
	}

	int get_hp() {
		return this->hp;
	}

	int get_mp() {
		return this->mp; 
	}

	// 设置玩家为无敌状态
	void make_invulnerable() {
		is_invulnerable = true;
		timer_invulnerable.restart();
	}


	// 使玩家处于减速状态
	void make_slow_speed() {
		_speedBoostRate = 0.5f;
	}

	// 使玩家处于正常速度
	void make_normal_speed() {
		_speedBoostRate = 1.0f;
	}

	// 使玩家处于减速移动
	void move_slow_down(int strength, int delta) {
		switch (strength)
		{
		case slowDownLevel::low:
            position += velocity * (float)(delta / 0.8f);
			break;
		case slowDownLevel::medium:
			position += velocity * (float)(delta / 0.6f);
			break;
		case slowDownLevel::high:
			position += velocity * (float)(delta / 0.4f);
			break;
		default:
			break;
		}
	}

	// 在玩家的 buffer 容器中添加一个 buffer
	Buffer* generateBuffer() {
		Buffer* buffer = nullptr;
		switch (generateRandomInt(0,3))
		{
		case 0:
			buffer = new SpeedBoost(1000, 1.5f);
			buffer->set_callback([&]
				{
					_speedBoostRate = 1.0f;
				});
			break;
		case 1:
			buffer = new SilenceBuffer(1000);
			buffer->set_callback([&]()
				{
					_is_silence = false;
				});
			break;
		case 2:
			buffer = new RecoveryBuffer(1000, 0.8f);
			buffer->set_callback([&]()
				{
					_recovery = 0.0f;
				});
			break;
		case 3:
			buffer = new InvisibleBuffer(1000);
			buffer->set_callback([&]()
				{
					_is_invisible = false;
				});
			break;
		default:
			break;
		}

		return buffer;
	}

	// 应用 buffer
	void applyBuffer(Buffer* buffer) {

		switch (buffer->get_type())
		{
		case Buffer::SpeedBoost:
			_speedBoostRate = buffer->getFloatValue();
			break;
		case Buffer::HpRecovery:
			_recovery = buffer->getFloatValue();
			break;
		case Buffer::Silence:
			_is_silence = buffer->getBooleanValue();
			break;
		case Buffer::Invisible:
			_is_invisible = buffer->getBooleanValue();
			break;
		default:
			break;
		}

	}

protected:
	void move_and_collide(int delta) {

		float last_velocity = velocity.y;		// 速度存储器记录了y方向上的速度分量
		velocity.y += gravity * delta;			// 更新y方向上的速度
		position.y += velocity.y * (float)delta;

		if (hp <= 0) {
			return;
		}

		// 角色与平台的碰撞检测
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
						if (last_velocity != 0)
							on_land();
						break;
					}
				}
			}
		}

		// 角色与 buffer 碰撞检测
		for (BufferHUD* bufferHUD : BufferHUD_list) {
			if (bufferHUD->checkCollisionBox(position, role_collision_box)) {
				bufferHUD->setCanRemove(false);
				Buffer* newBuffer = generateBuffer();
				applyBuffer(newBuffer);
				Buffer_list_triggered.push_back(newBuffer);
			}
		}

		// 不处于无敌状态时
		if (!is_invulnerable) {
			for (Bullet* bullet : Bullet_list) {

				// 在Bullet_list容器找出所有作用与自身的子弹
				if (!bullet->getCanCauseDamage() || bullet->getCollideTargetId() != role_id)
					continue;
				
				// 判定子弹与自身是否发生碰撞
				if (bullet->checkCollisionBox(position, role_collision_box)) {
					
					make_invulnerable();												// 更新角色为无敌状态
					bullet->on_collide();												// 子弹的碰撞方法
					if(!(bullet->getBulletType() == Bullet::bulletType::gloomshroom))
						bullet->setCanCauseDamage(false);								// 更新子弹可造成伤害状态为 false 
					if ((hp -= bullet->getDamage()) == 0) {								// 更新玩家血量以及存活状态
						is_alive = false;
					}
					last_hurt_direction.x = bullet->getPosition().x - position.x;
					if (hp <= 0) {
							velocity.x = last_hurt_direction.x < 0 ? 0.35f : -0.35f;
						velocity.y = -1.0f;
					}
				}
			}
		}
	}

	// 碰撞判定成功的条件：上一帧平台的y坐标小于角色碰撞箱底部y坐标，下一帧平台的y坐标大于角色碰撞箱底部y坐标
protected:
	enum playerType
	{
		defaulttype = 0,
		peashooter,
		sunFlower,
		nut,
		gloomshroom
	};

	enum slowDownLevel
	{
		low = 0,
		medium,
		high
	};

protected:
	Vector2 position = { 0,0 };						// 玩家角色位置
	Vector2 velocity = { 0,0 };						// 玩家的速度
	Vector2 role_collision_box = { 96, 96 };		// 玩家角色碰撞箱
	Vector2 position_jump_effect = { 0,0 };			// 玩家跳跃特效渲染位置 
	Vector2 position_land_effect = { 0,0 };			// 玩家落地特效渲染位置
	Vector2 last_hurt_direction = { 0,0 };			// 玩家最后一次受击方向

	Animation animation_die_left;					// 朝向左的死亡动画
	Animation animation_die_right;					// 朝向右的死亡动画
	Animation animation_idle_left;					// 朝向左的默认动画
	Animation animation_idle_right;					// 朝向有的默认动画
	Animation animation_run_left;					// 朝向左的奔跑动画
	Animation animation_run_right;					// 朝向右的奔跑动画
	Animation animation_attack_ex_left;				// 特殊攻击角色动画
	Animation animation_attack_ex_right;			// 特殊攻击角色动画
	Animation animation_jump_effect;				// 角色跳跃特效
	Animation animation_land_effect;				// 角色落地特效

	RoleId role_id = RoleId::P1;					// 玩家id

	playerType type = defaulttype;					// 玩家角色类型

	bool is_normal_speed = true;					// 是否处于正常速度
	bool is_slow_down = false;						// 是否处于减速状态
	bool is_jump_effect_visible = false;			// 跳跃特效是否可见
	bool is_land_effect_visible = false;			// 落地特效是否可见
	bool is_left_key_down = false;					// 左键是否按下
	bool is_right_key_down = false;					// 右键是否按下
	bool is_facing_right = true;					// 角色是否朝向右边
	bool is_attacking_ex = false;					// 是否处于特殊攻击状态

protected:
	const float	gravity = 1.6e-3f;					// 玩家的重力加速度
	const float role_run_velocity = 0.55f;			// 玩家的奔跑速度
	const float role_jump_velocity = -0.85f;		// 玩家的跳跃速度

protected:
	int mp = 0;										// 玩家技能值
	int hp = 100;									// 玩家生命值
	int attack_cd = 500;							// 玩家普通攻击冷却时间
	int base_damage = 1;							// 玩家基础攻击力
	int current_damage = base_damage;				// 玩家当前的攻击力
	float _speedBoostRate = 1.0f;					// 玩家速度控制器
	float _recovery = 0.0f;							// 玩家的恢复强度
	bool _is_silence = false;						// 玩家是否被沉默
	bool _is_invisible = false;						// 玩家是否不可选中

private:

	IMAGE img_sketch;								// 角色当前需要进行翻转的动画帧
	Animation* current_animation = nullptr;			// 玩家当前正在进行播放的动画
	
	bool can_attack = true;							// 玩家是否可以释放普通攻击 
	bool is_invulnerable = false;					// 玩家是否处于无敌状态
	bool is_showing_invulnerable_frame = false;		// 玩家当前帧是否应该显示剪影，控制无敌帧剪影图片的播放
	bool is_cursor_visible = true;					// 玩家光标是否可见
	bool is_alive = true;							// 玩家是否存活

	Timer timer_attack;								// 玩家普通攻击冷却定时器
	Timer timer_attack_ex;							// 玩家必杀技持续时间定时器
	Timer timer_invulnerable;						// 玩家无敌状态定时器
	Timer timer_invulnerable_blink;					// 玩家无敌帧闪烁定时器
	Timer timer_run_effect_generator;				// 玩家奔跑时的粒子发射器,控制粒子生成
	Timer timer_die_effect_generator;				// 玩家死亡时的粒子发射器,控制粒子生成
	Timer timer_cursor_visibility;					// 玩家光标指示器可见定时器
	
	std::vector<Particle> Particle_list;			// 玩家粒子管理器
	std::vector<Buffer*> Buffer_list_triggered;		// 玩家触发的 buffer

};
#endif // !_ROLE_H_
