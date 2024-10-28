#ifndef _BUFFERHUD_H_
#define _BUFFERHUD_H_

#include "Role.h"
#include "Animation.h"
#include "Vector2.h"
#include "Camera.h"
#include "Timer.h"
#include "Buffer.h"
#include "Platform.h"
#include "Utils.h"

extern Atlas atlas_buff_box_blue;
extern Atlas atlas_buff_box_pink;
extern Atlas atlas_buff_box_yellow;

extern bool is_debug;

extern std::vector<Platform> Platform_list;

class BufferHUD
{
public:
	BufferHUD();
	~BufferHUD();

	void on_draw(const Camera& camera) const;
	void on_update(int delta);
	void setCanRemove(bool can_remove);
	bool checkCanRemove() const;
	bool checkCollisionBox(const Vector2& position, const Vector2& collisionBox) const;
private:

	Animation animation_blue_HUD;
	Animation animation_pink_HUD;
	Animation animation_yellow_HUD;
	Animation* current_animation_HUD = nullptr;

	Vector2 position = { 0,0 };						// bufferHUD 在场景中的位置
	Vector2 collisionBox = { 0,0 };					// bufferHUD 碰撞盒子的大小
	
	Timer timer_remain_show;						// bufferHUD 在场景中显示的时间

	Platform*  target_platform = nullptr;			// 目标生成 bufferHUD 的平台

	bool can_remove = false;						// bufferHUD 是否可以被删除

	int duration = 12000;							// bufferHUD 持续时间

};

BufferHUD::BufferHUD()
{
	// 动画类初始化
	animation_blue_HUD.set_atlas(&atlas_buff_box_blue);
	animation_blue_HUD.set_inter_time(100);
	
	animation_pink_HUD.set_atlas(&atlas_buff_box_pink);
	animation_pink_HUD.set_inter_time(100);
	
	animation_yellow_HUD.set_atlas(&atlas_buff_box_yellow);
	animation_yellow_HUD.set_inter_time(100);
	
	timer_remain_show.set_wait_time(duration);
	timer_remain_show.set_one_shot(true);
	timer_remain_show.set_callback([&]()
		{
			can_remove = true;
		});

	duration = 1000;

	// 随机生成 bufferHUD 的图标
	switch (generateRandomInt(0,2))
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

	// 随机生成 bufferHUD 的位置
	switch (generateRandomInt(0,3))
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

	
}

BufferHUD::~BufferHUD() { }

inline void BufferHUD::on_draw(const Camera& camera) const
{
	if (is_debug) {
		setcolor(WHITE);
		setlinecolor(WHITE);
		rectangle((int)position.x, (int)position.y, (int)(position.x + collisionBox.x), (int)(position.y + collisionBox.y));
		solidcircle((int)(position.x + collisionBox.x / 2), (int)(position.y + collisionBox.y / 2), 5);
	}

	current_animation_HUD->on_draw(camera, (int)position.x, (int)position.y);

}

inline void BufferHUD::on_update(int delta)
{
	current_animation_HUD->on_update(delta);
	timer_remain_show.on_update(delta);
}

inline void BufferHUD::setCanRemove(bool can_remove)
{
	can_remove = can_remove;
}

inline bool BufferHUD::checkCanRemove() const
{
	return can_remove;
}

// 检测 bufferHUD 的中心点是否玩家的碰撞外形内部
inline bool BufferHUD::checkCollisionBox(const Vector2& position, const Vector2& collisionBox) const
{
	Vector2 center;
	center.x = (this->position.x + this->collisionBox.x / 2);
	center.y = (this->position.y + this->collisionBox.y / 2);
	
	bool is_center_x_in = (center.x >= position.x) && (center.x <= position.x + collisionBox.x);
	bool is_center_y_in = (center.y >= position.y) && (center.y <= position.y + collisionBox.y);

	return is_center_x_in && is_center_y_in;
}

#endif // !_BUFFERHUD_H_

