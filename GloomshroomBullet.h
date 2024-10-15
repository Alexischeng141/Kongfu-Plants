#ifndef _GLOOMSHROOMBULLET_H_
#define _GLOOMSHROOMBULLET_H_

#include "Animation.h"
#include "role.h"
#include "Bullet.h"
#include "Vector2.h"

extern Atlas atlas_bubbles;

extern Role* role_1;
extern Role* role_2;

class GloomshroomBullet : public Bullet
{
public:
	GloomshroomBullet();
	~GloomshroomBullet();

	void on_draw(const Camera& camera) const;
	
	void on_update(int delta);
	
	void on_input(const ExMessage& msg);
	
	void on_collide();
	
	void getCollisionBox();


private:
	Animation animation_bubble;
	Vector2 size = { 0,0 };

	// 每一帧中跑跑子弹的位置
	std::vector<Vector2> each_gloomshroombullet_within_frame_list;
	
};


GloomshroomBullet::GloomshroomBullet()
{
	damage = 10;

	animation_bubble.set_atlas(&atlas_bubbles);
	animation_bubble.set_inter_time(75);
	animation_bubble.set_loop(false);
	animation_bubble.set_callback([&]() { can_remove = true; });
	
	size.x = (float)animation_bubble.get_current_frame()->getheight();
	size.y = (float)animation_bubble.get_current_frame()->getwidth();
	
}

GloomshroomBullet::~GloomshroomBullet() {}

void GloomshroomBullet::on_collide() {
	
	switch (rand() % 2)
	{
	case 1:

		break;
	case 2:

		break;
	default:
		break;
	}
}


void GloomshroomBullet::on_update(int delta) {


	// 根据当前的帧动画计算子弹的碰撞范围
	// 由/*于子弹渲染位置是根据角色的位置改变而改变的
	 
	animation_bubble.on_update(delta);

	if (targetId == RoleId::P1) {
		position.x = role_2->get_position().x - (size.x / 2 - role_2->get_role_collision_box().x / 2);
		position.y = role_2->get_position().y - (size.y / 2 - role_2->get_role_collision_box().y / 2);
	}

	if (targetId == RoleId::P2) {
		position.x = role_1->get_position().x - (size.x / 2 - role_1->get_role_collision_box().x / 2);
		position.y = role_1->get_position().y - (size.y / 2 - role_1->get_role_collision_box().y / 2);
	}

}


void GloomshroomBullet::on_draw(const Camera& camera) const {
	
	if (can_cause_damage) {
		animation_bubble.on_draw(camera, (int)position.x, (int)position.y);
	}
}

void GloomshroomBullet::on_input(const ExMessage& msg) {

}


void GloomshroomBullet::getCollisionBox() {
	
}


#endif // !_GLOOMSHROOMBULLET_H_
