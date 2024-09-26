#ifndef _SUNFLOWERBULLET_H_
#define	_SUNFLOWERBULLET_H_

#include "Bullet.h"
#include "Camera.h"
#include "Animation.h"


extern Atlas atlas_sun;
extern Atlas atlas_sun_explode;

extern Camera main_camera;

class SunflowerBullet : public Bullet
{
public:
	SunflowerBullet();
	~SunflowerBullet();

	void on_collide();

	void on_update(int delta);

	void on_draw(const Camera& camera) const;

private:
	Animation animation_idle;
	Animation animation_explode;
	Vector2 explode_render_offset;		// 爆炸动画位置修正

private:
	const float gravity = 1e-3f;		// 龙日葵炸弹的重力
};

SunflowerBullet::SunflowerBullet()
{
	collisionBox.x = 96;
	collisionBox.y = 96;

	damage = 20;
	
	animation_idle.set_atlas(&atlas_sun);
	animation_idle.set_inter_time(50);

	animation_explode.set_atlas(&atlas_sun_explode);
	animation_explode.set_inter_time(50);
	animation_explode.set_loop(false);
	animation_explode.set_callback([&]() { can_remove = true; });


	IMAGE* frame_idle = animation_idle.get_current_frame();
	IMAGE* frame_explode = animation_explode.get_current_frame();
	explode_render_offset.x = (frame_idle->getwidth() - frame_explode->getwidth()) / 2.0f;
	explode_render_offset.y = (frame_idle->getheight() - frame_explode->getheight()) / 2.0f;

	
}

SunflowerBullet::~SunflowerBullet()
{
}

void SunflowerBullet::on_collide() {

	Bullet::on_collide();
	
	main_camera.shake(5, 250);
	
	mciSendString(_T("play sun_explode from 0"), NULL, 0, NULL);
}


void SunflowerBullet::on_update(int delta) {

	if (can_cause_damage) {
		velocity.y += gravity * delta;
		position += velocity * (float)delta;
	}

	if (can_cause_damage) {
		animation_idle.on_update(delta);
	}
	else {
		animation_explode.on_update(delta);
	}

	if (checkIsExceedScreen()) {
		can_remove = true;
	}

}

void SunflowerBullet::on_draw(const Camera& camera) const {
	if (can_cause_damage) {
		animation_idle.on_draw(camera, (int)position.x, (int)position.y);
	}
	else
	{
		animation_explode.on_draw(camera, 
			(int)(position.x + explode_render_offset.x), 
			(int)(position.y + explode_render_offset.y));
	}
}

#endif // !_SUNFLOWERBULLET_H_
