#pragma once
#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#include "Camera.h"
#include "Utils.h"

extern bool is_debug;

class Platform
{
public:
	Platform() = default;
	~Platform() = default;

	void on_draw(const Camera& camera) const {

		putimage_alpha(camera, position.x, position.y, img);

		if (is_debug) {
			setlinecolor(RGB(255, 0, 0));
			on_draw_line(camera, (int)collision_box.x_left, (int)collision_box.y, (int)collision_box.x_right, (int)collision_box.y);
		}
	}


public:
	struct  CollisionBox
	{
		float y;					// 平台的高度
		float x_left;				// 平台的左侧
		float x_right;				// 平台的右侧
	};

public:
	CollisionBox collision_box = { 0, 0, 0 };
	IMAGE* img = nullptr;
	POINT position = { 0 };

};

#endif // !_PLATFORM_H_
