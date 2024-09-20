#pragma once
#ifndef _TIMER_H_
#define _TIMER_H	
#include <functional>

// 计时器基类
class Timer
{
public:
	Timer() = default;
	~Timer() = default;

	void restart() {
		passed_time = 0;
		is_shotted = false;
	}

	void set_wait_time(int wait_time) {
		this->wait_time = wait_time;
	}

	void set_one_shot(bool flag) {
		is_one_shot = flag;
	}

	void pause() {
		is_paused = true;
	}

	void on_updata(int val) {
		if (is_paused)
			return;
		passed_time += val;
		if (passed_time >= wait_time) {
			if (((!is_one_shot) || (is_one_shot && !is_shotted)) && callback) {	// 不是单次触发且回调函数存在或者是单次触发（计时器未触发）且回调函数存在
				callback();
				is_shotted = true;
				passed_time = 0;
			}
		}
	}

	// 解除暂停
	void resume() {
		is_paused = false;
	}

	// 设置回调函数
	void set_callback(const std::function<void()> callback) {
		this->callback = callback;
	}

private:
	int passed_time = 0;			// 已过去的时间
	int wait_time = 0;				// 等待时间
	bool is_paused = false;			// 是否暂停
	bool is_shotted = false;		// 是否触发
	bool is_one_shot = false;		// 是否单次触发
	std::function<void()> callback = nullptr;	// 设置计时器回调函数
};

#endif // !_TIMER_H_
