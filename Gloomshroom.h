#ifndef _GLOOMSHROOM_H_
#define _GLOOMSHROOM_H_

#include "Role.h"

extern Atlas atlas_gloomshroom_die;
extern Atlas atlas_gloomshroom_idle_left;
extern Atlas atlas_gloomshroom_idle_right;
extern Atlas atlas_gloomshroom_run_left;
extern Atlas atlas_gloomshroom_run_right;

class Gloomshroom : public Role
{
public:
	Gloomshroom() {
		// 设置动画图集
		animation_idle_left.set_atlas(&atlas_gloomshroom_idle_left);
		animation_idle_right.set_atlas(&atlas_gloomshroom_idle_right);
		animation_run_left.set_atlas(&atlas_gloomshroom_run_left);
		animation_run_right.set_atlas(&atlas_gloomshroom_run_right);

		// 设置帧间隔
		animation_idle_left.set_inter_time(75);
		animation_idle_right.set_inter_time(75);
		animation_run_left.set_inter_time(75);
		animation_run_right.set_inter_time(75);
		

	}

	~Gloomshroom() = default;

	void on_update(int interval_time) {
		Role::on_update(interval_time);
	}

	void on_input(const ExMessage& msg) {
		Role::on_input(msg);
	}

	void on_draw(const Camera& camera) {
		Role::on_draw(camera);
	}

private:

};

#endif // !_GLOOMSHROOM_H_
