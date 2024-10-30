#ifndef _TIMER_H_
#define _TIMER_H_
#include <functional>

// 定时器基类
class Timer
{
public:
	Timer() = default;
	~Timer() = default;

	// 重置定时器<is_shouted;passed_time>
	void restart() {
		passed_time = 0;
		is_shotted = false;
	}

	// 设置定时器
	void set_wait_time(int wait_time) {
		this->wait_time = wait_time;
	}

	// 设置单次触发
	void set_one_shot(bool flag) {
		is_one_shot = flag;
	}

	// 设置暂停
	void pause() {
		is_paused = true;
	}

	// 定时器更新
	void on_update(int delta) {
		if (is_paused)
			return;
		passed_time += delta;
		if (passed_time >= wait_time) {
			// 这里主要是要考虑定时器有没有被触发
			// 如果定时器是可以多次触发则不需要考虑有没有被触发过
			// 如果定时器是单次触发的则需要考虑是否已经被触发过
			if (((!is_one_shot) || (is_one_shot && !is_shotted)) && callback) {	
				callback();
				is_shotted = true;
				passed_time = 0;
			}
		}
	}

	/*void on_update(int val, int delta) {
		if (is_paused)
			return;
		passed_time += val;
		if (passed_time >= wait_time) {
			if (((!is_one_shot) || (is_one_shot && !is_shotted)) && callback) {
				callback();
				is_shotted = true;
				passed_time = 0;
			}
		}
	}*/

	// 恢复暂停
	void resume() {
		is_paused = false;
	}

	// 设置回调函数
	void set_callback(const std::function<void()> callback) {
		this->callback = callback;
	}
	
	int get_remain_time() const {
		return wait_time - passed_time;
	}
	
private:
	int passed_time = 0;			// 已过去的时间
	int wait_time = 0;				// 等待时间
	bool is_paused = false;			// 是否暂停
	bool is_shotted = false;		// 是否触发
	bool is_one_shot = false;		// 是否单次触发
	std::function<void()> callback = nullptr;	// 设置计时器回调函数
	std::function<void(int delta)> callback_buff = nullptr;
};

#endif // !_TIMER_H_
