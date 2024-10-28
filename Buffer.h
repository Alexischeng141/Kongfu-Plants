#pragma once
#ifndef _BUFFER_H_
#define _BUFFER_H_
#include "Timer.h"

extern Atlas atlas_buff_box_blue;
extern Atlas atlas_buff_box_pink;
extern Atlas atlas_buff_box_yellow;

// 颜色只是增加了画面的丰富度，每个 buffer 盒子里面的效果都随机的

class Buffer
{
public:

	enum Type
	{
		SpeedBoost = 0,
		HpRecovery,
		Silence,
		Invisible
	};

	Buffer() = default;
	~Buffer() = default;

	Buffer(int duration);

	virtual float getFloatValue() { return 0.0f; }
	virtual int getIntValue() { return 0; }
	virtual bool getBooleanValue() { return true; }

	void set_callback(std::function<void()> callback) {
		this->callback = callback;
	}

	// 获取 buffer 类型
	Type get_type() { return type; }

	// 设置 buffer 类型
	void set_type(Type type) { this->type = type; }

	// 检查 buffer 是否过期
	bool checkIsExpired() const { return is_expired; }

	 // 数据更新
	virtual void on_update(int delta) { timer_remaining.on_update(delta); }

	void on_callback() const {
		if (callback) {
			callback();
		}
	}

public:
	Type type;							// buffer 的类型

protected:
	Timer timer_remaining;				// buffer 持续时间
	int duration;						// buffer 的持续时间
	bool is_expired = false;			// buffer 是否被过期
	std::function<void()> callback;

};

inline Buffer::Buffer(int duration) : duration(duration), is_expired(false)
{

	timer_remaining.set_wait_time(duration);
	timer_remaining.set_one_shot(true);
	timer_remaining.set_callback([&]()
		{
			is_expired = true;
		});
}



#endif // !_BUFFER_H_
