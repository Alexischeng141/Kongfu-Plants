#ifndef _SCENE_H_
#define _SCENE_H_

#include <graphics.h>
#include <stdio.h>
#include "Camera.h"

class scene {
public:
	scene() = default;
	~scene() = default;

	virtual void OnEnter() { } // 进入游戏场景
	virtual void OnInput(const ExMessage& msg) { } // 获取用户操作消息
	virtual void OnUpdate(int interval_time) { } // 更新数据
	virtual void OnDraw(const Camera& camera) { }	// 渲染场景
	virtual void OnExit() { }	// 退出场景

};

#endif // !_SCENE_H_


