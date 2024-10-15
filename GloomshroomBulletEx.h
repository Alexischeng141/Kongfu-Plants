#ifndef _GLOOMSHROOMBULLETEX_H_
#define _GLOOMSHROOMBULLETEX_H_

#include "Bullet.h"

extern Role* role_1;
extern Role* role_2;

extern Atlas atlas_bubbles_ex;

class GloomshroomBulletEx : public Bullet
{
public:
	GloomshroomBulletEx();
	~GloomshroomBulletEx();
	void on_updata(int delta);
	void on_draw(const Camera& camera);
	void on_collide();


private:
	Animation animation_bubble_ex;
	Vector2 size = { 0,0 };

};

GloomshroomBulletEx::GloomshroomBulletEx() {
	damage = 20;
	animation_bubble_ex.set_atlas(&atlas_bubbles_ex);
	animation_bubble_ex.set_loop(false);
	animation_bubble_ex.set_inter_time(75);
	animation_bubble_ex.set_callback([&]() { can_remove = true; });
	
	size.x = (float)animation_bubble_ex.get_current_frame()->getwidth();
	size.y = (float)animation_bubble_ex.get_current_frame()->getheight();
	
}

GloomshroomBulletEx::~GloomshroomBulletEx() {
}


void GloomshroomBulletEx::on_updata(int delta) {
	animation_bubble_ex.on_update(delta);

	if (targetId == RoleId::P1) {
		position.x = role_2->get_position().x - (size.x / 2 - role_2->get_role_collision_box().x / 2);
		position.y = role_2->get_position().y - (size.y / 2 - role_2->get_role_collision_box().y / 2);
	}

	if (targetId == RoleId::P2) {
		position.x = role_1->get_position().x - (size.x / 2 - role_1->get_role_collision_box().x / 2);
		position.y = role_1->get_position().y - (size.y / 2 - role_1->get_role_collision_box().y / 2);
	}
}

void GloomshroomBulletEx::on_draw(const Camera& camera) {
	
	if (can_cause_damage) {
		animation_bubble_ex.on_draw(camera, (int)position.x, (int)position.y);
	}

}

void GloomshroomBulletEx::on_collide() {

}


#endif // !_GLOOMSHROOMBULLETEX_H_
