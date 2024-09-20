#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Vector2.h"
#include "Timer.h"
#include <iostream>

class Camera
{
public:
	Camera() {
		timer_shake.set_one_shot(true);
		timer_shake.set_callback(
			[&]() {
				is_shaking = false;
				reset();
			});
	}
	~Camera() = default;

	// 返回摄像机位置
	const Vector2& get_camera() const {
		return position;
	}

	void reset() {
		position.x = 0;
		position.y = 0;
	}

	void shake(float strength, int duration) {
		is_shaking = true;
		shaking_strength = strength;

		timer_shake.set_wait_time(duration);
		timer_shake.restart();
	}

	void on_updata(int interval_time) {
		timer_shake.on_updata(interval_time);

		// 在以抖动强度为半径的圆内进行随机设置摄像机的世界坐标
		if (is_shaking) {
			position.x = (-50 + rand() % 100) / 50.0f * shaking_strength;
			position.y = (-50 + rand() % 100) / 50.0f * shaking_strength;
		}
	}

private:
	Vector2 position;	// 摄像机位置
	Timer timer_shake;			// 摄像机抖动计时器
	bool is_shaking = false;	// 摄像机是否震动
	float shaking_strength = 0;	// 摄像机震动强度
};
#endif // _CAMERA_H_




