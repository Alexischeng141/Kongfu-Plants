#pragma once
#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "RoleId.h"
#include "Timer.h"
#include "Animation.h"
#include "Vector2.h"
#include "Camera.h"
#include "Platform.h"
#include "Utils.h"

extern Atlas atlas_buff_box_blue;
extern Atlas atlas_buff_box_pink;
extern Atlas atlas_buff_box_yellow;

extern std::vector<Platform> Platform_list;


// 颜色只是增加了画面的丰富度，每个 buffer 盒子里面的效果都随机的

class Buffer
{
public:

	enum Type
	{
		None = 0,
		SpeedBoost,
		HpRecovery,
		Silence,
		Invisible
	};

	Buffer();
	~Buffer() = default;
	void resetTimer();
	void pauseTimer();
	bool isBufferExists(Buffer::Type type);
	bool checkCanRemove() const;
	bool checkCollisionBox(const Vector2& position, const Vector2& collisionBox) const;
	void setCanRemove();
	void setIsTriggered();
	virtual void on_draw(const Camera& camera) const;
	void set_callback(std::function<void()> callback) { this->callback = callback; }

	// 获取 buffer 类型
	Type get_type() const { return type; }

	// 设置 buffer 类型
	void set_type(Type type) { this->type = type; }

	// 检查 buffer 是否过期
	bool checkIsExpired() const { return is_expired; }

	 // 数据更新
	virtual void on_update(int delta) {
		current_animation_HUD->on_update(delta);
		if(is_triggered)
			timer_remaining.on_update(delta); 
		timer_remain_show.on_update(delta);
	}

	void on_callback() const {
		if (callback) {
			callback();
		}
	}

	const Timer& get_timer() const;

	const RoleId& getRoleId() const;

	void set_RoleId(RoleId triggered_by);
public:
	Type type;								// buffer 的类型

protected:
	Animation animation_blue_HUD;
	Animation animation_pink_HUD;
	Animation animation_yellow_HUD;
	Animation* current_animation_HUD = nullptr;


	Vector2 position = { 0,0 };				// buffer 在场景中的位置
	Vector2 collisionBox = { 0,0 };			// buffer的碰撞外形
	
	Timer timer_remain_show;				// buffer 在场景中的定时器
	Timer timer_remaining;					// buffer 在角色身上的定时器
	
	Platform* target_platform = nullptr;	// 平台指针

	int duration_in_scene = 12000;			// buffer 在场景中的出现时间
	int duration_on_role = 1000;			// buffer 在角色身上持续时间

	bool can_remove = false;				// buffer 是否能在场景中被移除
	bool is_triggered = false;				// buffer 是否被触发
	bool is_expired = false;				// buffer 是否被过期
	std::function<void()> callback;

};

inline Buffer::Buffer()
{
	// 动画加载
	animation_blue_HUD.set_atlas(&atlas_buff_box_blue);
	animation_blue_HUD.set_inter_time(100);

	animation_pink_HUD.set_atlas(&atlas_buff_box_pink);
	animation_pink_HUD.set_inter_time(100);
	
	animation_yellow_HUD.set_atlas(&atlas_buff_box_yellow);
	animation_yellow_HUD.set_inter_time(100);
	
	// 定时器初始化
	timer_remaining.set_wait_time(duration_on_role);
	timer_remaining.set_one_shot(true);
	timer_remaining.set_callback([&]()
		{
			is_expired = true;
		});

	timer_remain_show.set_wait_time(duration_in_scene);
	timer_remain_show.set_one_shot(true);
	timer_remain_show.set_callback([&]()
		{
			can_remove = true;
		});

	// 随机生成 buffer 的图标
	switch (generateRandomInt(0, 2))
	{
	case 0:
		current_animation_HUD = &animation_blue_HUD;
		break;
	case 1:
		current_animation_HUD = &animation_pink_HUD;
		break;
	case 2:
		current_animation_HUD = &animation_yellow_HUD;
		break;
	default:
		break;
	}

	// 随机生成 buffer 的位置
	switch (generateRandomInt(0, 3))
	{
	case 0:
		target_platform = &Platform_list[0];
		break;
	case 1:
		target_platform = &Platform_list[1];
		break;
	case 2:
		target_platform = &Platform_list[2];
		break;
	case 3:
		target_platform = &Platform_list[3];
		break;
	default:
		break;
	}

	

	if (target_platform != NULL) {
		position.x = generateRandomFloat(target_platform->collision_box.x_left, target_platform->collision_box.x_right - this->collisionBox.y);
		position.y = target_platform->collision_box.y - (float)animation_blue_HUD.get_current_frame()->getheight();
	}

	// 设置 bufferHUD 的碰撞盒子
	collisionBox.x = (float)animation_blue_HUD.get_current_frame()->getwidth();
	collisionBox.y = (float)animation_blue_HUD.get_current_frame()->getheight();

	type = None;
	
}

inline void Buffer::resetTimer()
{
	timer_remaining.restart();
}

inline void Buffer::pauseTimer()
{
	timer_remaining.pause();
}

inline bool Buffer::isBufferExists(Buffer::Type type)
{
	return this->type == type;
}

inline bool Buffer::checkCanRemove() const
{
	return can_remove;
}

inline bool Buffer::checkCollisionBox(const Vector2& position, const Vector2& collisionBox) const
{
	Vector2 center;
	center.x = (this->position.x + this->collisionBox.x / 2);
	center.y = (this->position.y + this->collisionBox.y / 2);
	
	bool is_center_x_in = (center.x >= position.x) && (center.x <= position.x + collisionBox.x);
	bool is_center_y_in = (center.y >= position.y) && (center.y <= position.y + collisionBox.y);

	return is_center_x_in && is_center_y_in;
}

inline void Buffer::setCanRemove()
{
	can_remove = true;
}

inline void Buffer::setIsTriggered()
{
	is_triggered = true;
}

inline void Buffer::on_draw(const Camera& camera) const
{
	if (is_debug) {
		setcolor(WHITE);
		setlinecolor(WHITE);
		rectangle((int)position.x, (int)position.y, (int)(position.x + collisionBox.x), (int)(position.y + collisionBox.y));
		solidcircle((int)(position.x + collisionBox.x / 2), (int)(position.y + collisionBox.y / 2), 5);
		
		settextcolor(LIGHTCYAN);

		switch (this->type)
		{
		case Buffer::SpeedBoost:
			outtextxy((int)(position.x + 10), (int)(position.y - 10), _T("SpeedBoost"));
			break;
		case Buffer::Silence:
			outtextxy((int)(position.x + 10), (int)(position.y - 10), _T("Silence"));
			break;
		case Buffer::HpRecovery:
			outtextxy((int)(position.x + 10), (int)(position.y - 10), _T("HP"));
			break;
		case Buffer::Invisible:
			outtextxy((int)(position.x + 10), (int)(position.y - 10), _T("Invisible"));
		default:
			break;
		}
	}

	if (!is_triggered) {
		current_animation_HUD->on_draw(camera, (int)position.x, (int)position.y);
	}
}

inline const Timer& Buffer::get_timer() const  {
	return timer_remaining;
}

inline const RoleId& Buffer::getRoleId() const
{
	
	// TODO: 在此处插入 return 语句
}

inline void Buffer::set_RoleId(RoleId triggered_by)
{
	
}



#endif // !_BUFFER_H_
