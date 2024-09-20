#pragma once
#ifndef _UTILS_H_
#define _UTILS_H_
#pragma comment(lib, "Msimg32.lib")
#include <graphics.h>
#include "Camera.h"
#include "Atlas.h"

// Í¼Æ¬·­×ª
inline void filp_image(IMAGE* src, IMAGE* dst) {
	int width = src->getwidth();
	int height = src->getheight();
	Resize(dst, width, height);
	DWORD* src_image = GetImageBuffer(src);
	DWORD* dst_image = GetImageBuffer(dst);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int src_index = y * width + x;
			int dst_index = y * width + (width - x - 1);
			dst_image[dst_index] = src_image[src_index];
		}
	}
}

inline void filp_atlas(Atlas& src_atlas, Atlas& dst_atlas) {
	dst_atlas.clear();
	for (int i = 0; i < src_atlas.get_frame_size(); i++) {
		IMAGE dst_img;
		filp_image(src_atlas.get_image(i), &dst_img);
		dst_atlas.add_image(dst_img);
	}
}

// äÖÈ¾´øÍ¸Ã÷¶ÈµÄÍ¼Æ¬
inline void putimage_alpha(int dst_x, int dst_y, IMAGE* img) {
	int width = img->getwidth();
	int height = img->getheight();
	AlphaBlend(GetImageHDC(GetWorkingImage()), dst_x, dst_y, width, height,
		GetImageHDC(img), 0, 0, width, height, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}

inline void putimage_alpha(const Camera camera, int dst_x, int dst_y, IMAGE* img) {
	int width = img->getwidth();
	int height = img->getheight();
	const Vector2& pos_camera = camera.get_camera();
	AlphaBlend(GetImageHDC(GetWorkingImage()), (int)(dst_x - pos_camera.x), (int)(dst_y - pos_camera.y),
		width, height, GetImageHDC(img), 0, 0, width, height, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}

inline void putimage_alpha(int dst_x, int dst_y, int width, int height, IMAGE* img, int src_x, int src_y) {
	int w = width > 0 ? width : img->getwidth();
	int h = height > 0 ? height : img->getheight();
	AlphaBlend(GetImageHDC(GetWorkingImage()), dst_x, dst_y, w, h,
		GetImageHDC(img), src_x, src_y, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

inline void on_draw_line(const Camera& camera, int x_left, int y_left, int x_right, int y_right) {
	const Vector2& pos_camera = camera.get_camera();
	line((int)(x_left - pos_camera.x), (int)(y_left - pos_camera.y), (int)(x_right - pos_camera.x), (int)(y_right - pos_camera.y));
}

#endif // !_UTILS_H_

