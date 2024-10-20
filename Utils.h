#pragma once
#ifndef _UTILS_H_
#define _UTILS_H_
#pragma comment(lib, "Msimg32.lib")
#include <graphics.h>
#include "Camera.h"
#include "Atlas.h"

// 图片翻转
inline void flip_image(IMAGE* src, IMAGE* dst) {
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

inline void flip_atlas(Atlas& src_atlas, Atlas& dst_atlas) {
	dst_atlas.clear();
	for (int i = 0; i < src_atlas.get_frame_size(); i++) {
		IMAGE dst_img;
		flip_image(src_atlas.get_image(i), &dst_img);
		dst_atlas.add_image(dst_img);
	}
}

// 渲染带透明度的图片
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

// 将帧动画处理成素描效果
inline void sketch_image(IMAGE* src, IMAGE* dst) {
	int w = src->getwidth();
	int h = src->getheight();
	Resize(dst, w, h);
	DWORD* src_buffer = GetImageBuffer(src);
	DWORD* dst_buffer = GetImageBuffer(dst);
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {

			/*
			
			公式 idx = y * w + x 是二维数组（或图像）中计算线性索引的常用方法。
			对于图像来说，图像数据通常以一维数组形式存储，但图像本身是二维的。
			因此，需要一个公式将二维坐标转换为一维索引。

			y 表示行（即高度方向上的位置），而 x 表示列（即宽度方向上的位置）。
			每一行有 w 个像素。
			对于某一行 y，它前面有 y 行，每一行有 w 个像素，因此前 y 行共有 y * w 个像素。
			
			y * w 是前面所有行的像素数量总和。
			在行 y 中，再加上列位置 x，就可以精确找到图像中该点的线性索引：idx = y * w + x。
			示例
			
			*/

			int idx = y * w + x;
			dst_buffer[idx] = BGR(RGB(255, 255, 255)) | (src_buffer[idx] & 0xff000000);
		}
	}
}

#endif // !_UTILS_H_

