#ifndef _GLOOMSHROOMBULLETEX_H_
#define _GLOOMSHROOMBULLETEX_H_

#include "GloomshroomBullet.h"

extern Role* role_1;
extern Role* role_2;

extern Atlas atlas_bubbles_ex;

class GloomshroomBulletEx : public GloomshroomBullet
{
public:
	GloomshroomBulletEx();
	~GloomshroomBulletEx();
	void on_update(int delta) override;
	void on_draw(const Camera& camera) const override;
	void on_collide() override;
	const Animation* get_animation() const override;

private:
	Animation animation_bubble_ex;
	//Vector2 bulletSize = { 0,0 };				// Ö¡µÄ¿í¸ß

};

GloomshroomBulletEx::GloomshroomBulletEx() {
	damage = 20;

	animation_bubble_ex.set_atlas(&atlas_bubbles_ex);
	animation_bubble_ex.set_loop(true);
	animation_bubble_ex.set_inter_time(50);
	animation_bubble_ex.set_callback([&]() {  can_remove = true; });
	
	bulletSize.x = (float)animation_bubble_ex.get_current_frame()->getwidth();
	bulletSize.y = (float)animation_bubble_ex.get_current_frame()->getheight();
	
}

GloomshroomBulletEx::~GloomshroomBulletEx() {
}


void GloomshroomBulletEx::on_update(int delta) {
	GloomshroomBullet::on_update(delta);
}

void GloomshroomBulletEx::on_draw(const Camera& camera) const {
	Bullet::on_draw(camera);
	

}

void GloomshroomBulletEx::on_collide() {
	Bullet::on_collide();
	
}

const Animation* GloomshroomBulletEx::get_animation() const {
	return &animation_bubble_ex;
}

#endif // !_GLOOMSHROOMBULLETEX_H_
