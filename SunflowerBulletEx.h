#ifndef _SUNFLOWERBULLETEX_H_
#define _SUNFLOWERBULLETEX_H_

#include "Camera.h"
#include "Bullet.h"
#include "Vector2.h"
#include "Animation.h"

extern Atlas atlas_sun_ex;
extern Atlas atlas_sun_ex_explode;
extern Atlas atlas_sun_text;

extern Camera main_camera;

class SunflowerBulletEx : public Bullet
{
public:
	SunflowerBulletEx();
	~SunflowerBulletEx();

	void on_collide();
	void on_draw(const Camera& camera) const;
	void on_update(int delta);
	bool checkCollisionBox(const Vector2& position, const Vector2& collisionBox);

private:

	Animation animation_ex_explode;
	Animation animation_ex;
	
	Vector2 explode_render_ex = { 0,0 };
	
};

SunflowerBulletEx::SunflowerBulletEx()
{
	collisionBox.x = 288;
	collisionBox.y = 288;

	animation_ex.set_atlas(&atlas_sun_ex);
	animation_ex.set_inter_time(50);
	
	animation_ex_explode.set_atlas(&atlas_sun_ex_explode);
	animation_ex_explode.set_inter_time(50);
	animation_ex_explode.set_loop(false);
	animation_ex_explode.set_callback([&]() {can_remove = true; });

	damage = 20;

	IMAGE* frame_idle = animation_ex.get_current_frame();
	IMAGE* frame_explode = animation_ex_explode.get_current_frame();
	explode_render_ex.x = (frame_idle->getwidth() - frame_explode->getwidth()) / 2.0f;
	explode_render_ex.y = (frame_explode->getheight() - frame_explode->getheight()) / 2.0f;

}

SunflowerBulletEx::~SunflowerBulletEx()
{
}


void SunflowerBulletEx::on_collide() {
	Bullet::on_collide();
	
	main_camera.shake(20, 350);
	
	mciSendString(_T("play sun_explode_ex from 0"), NULL, 0, NULL);
}

void SunflowerBulletEx::on_update(int delta) { 
	
	if (can_cause_damage) {
		position += velocity * (float)delta;
	}

	if (!can_cause_damage) {
		animation_ex_explode.on_update(delta);
	}
	else
	{
		animation_ex.on_update(delta);
	}
	
	// 这里有问题
	if (checkIsExceedScreen()) {
		can_remove = true;
	}
}

void SunflowerBulletEx::on_draw(const Camera& camera) const {

	if (can_cause_damage) {
		animation_ex.on_draw(camera, (int)position.x, (int)position.y);
	}
	else
	{
		animation_ex_explode.on_draw(camera,
			(int)(position.x + explode_render_ex.x),
			(int)(position.y + explode_render_ex.y));
	}
	Bullet::on_draw(camera);
}

bool SunflowerBulletEx::checkCollisionBox(const Vector2& position, const Vector2& collisionBox) {
	bool is_collide_x = (max(this->position.x + this->collisionBox.x, position.x + collisionBox.x)
		- min(this->position.x, position.x) <= this->collisionBox.x + collisionBox.x);
	bool is_collide_y = (max(this->position.y + this->collisionBox.y, position.y + collisionBox.y)
		- min(this->position.y, position.y) <= this->collisionBox.y + collisionBox.y);
	
	return is_collide_x && is_collide_y;
}

#endif // !_SUNFLOWERBULLETEX_H_
