#pragma once
#ifndef _ANIMATION_H_
#define _ANIMATION_H_
#include "Atlas.h"
#include "Utils.h"
#include "vector"
#include "stdio.h"
#include "functional"
#include "Camera.h"

/*
Animation 是对Atlas类的进一步封装，提供了对图集中图像资源的操作函数
*/



class Animation {
public:

	Animation() = default;
	~Animation() = default;


	void reset() {
		this->timer = 0;
		this->current_index_of_frame = 0;
	}

	void set_atlas(Atlas* const atlas_for_animation) {
		reset();
		this->atlas_for_animation = atlas_for_animation;
	}

	void set_inter_time(int stander_interval_time) {
		this->stander_interval_time = stander_interval_time;
	}

	// 默认循环播放
	void set_loop(bool flag) {
		is_loop = flag;
	}

	void set_callback(std::function<void()> callback) {
		this->callback = callback;
	}

	int get_current_index() {
		return current_index_of_frame;
	}

	IMAGE* get_current_frame() const {
		return atlas_for_animation->get_image(current_index_of_frame);
	}

	bool check_finished() {
		if (is_loop) return false;
		return (current_index_of_frame == atlas_for_animation->get_frame_size());
	}

	void on_draw(const Camera& camera, int dst_x, int dst_y) const {
		putimage_alpha(camera, dst_x, dst_y, atlas_for_animation->get_image(current_index_of_frame));
	}

	void on_update(int interval_time) {
		timer += interval_time;
		if (timer >= stander_interval_time) {
			timer -= stander_interval_time;
			current_index_of_frame++;
			if (current_index_of_frame >= atlas_for_animation->get_frame_size()) {
				current_index_of_frame = is_loop ? 0 : atlas_for_animation->get_frame_size() - 1;
				if (!is_loop && callback) {		// 如果动画帧索引到达图集尾部，并且没有设置循环播放，以及回调函数存在则执行回调函数
					callback();
					this->timer = 0;
				}
			}
		}
	}

	int on_update(int interval_time, bool is_return) {
		if (is_return) {
			std::cout << "Timer: " << timer << ", Interval: " << stander_interval_time << std::endl;
			timer += interval_time;
			if (timer >= stander_interval_time) {
				timer = 0;
				current_index_of_frame++;
				if (current_index_of_frame >= atlas_for_animation->get_frame_size()) {
					current_index_of_frame = is_loop ? 0 : atlas_for_animation->get_frame_size() - 1;
					if (!is_loop && callback) {		// 如果动画帧索引到达图集尾部，并且没有设置循环播放，以及回调函数存在则执行回调函数
						callback();
						this->reset();
						current_index_of_frame = 0;
					}
				}
			}
		}
		return current_index_of_frame;
	}


private:
	Atlas* atlas_for_animation = nullptr;
	std::function<void()> callback;
	int stander_interval_time = 0;			// 每一帧动画播放时间
	int timer = 0;							// 当前帧已经播放的时间
	int current_index_of_frame = 0;			// 当前帧索引
	bool is_loop = true;					// 是否循环播放（默认循环播放）

};

#endif // !_ANIMATION_H_
