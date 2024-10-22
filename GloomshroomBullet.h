#ifndef _GLOOMSHROOMBULLET_H_
#define _GLOOMSHROOMBULLET_H_

#include "Bullet.h"
#include "Role.h"

extern Atlas atlas_bubbles;

extern Role* role_1;
extern Role* role_2;

class GloomshroomBullet : public Bullet
{
public:
	GloomshroomBullet();
	~GloomshroomBullet();

	void on_draw(const Camera& camera) const;
	void on_update(int delta) override;
	void on_collide() override;
	const Animation* get_animation() const override;


protected:
	Vector2 bulletSize = { 0,0 };

private:
	Animation animation_bubble;

	// 每一帧中跑跑子弹的位置
	std::vector<Vector2> each_gloomshroombullet_within_frame_list;
	
};


GloomshroomBullet::GloomshroomBullet()
{ 
	damage = 10;
	
	animation_bubble.set_atlas(&atlas_bubbles);
	animation_bubble.set_inter_time(100);
	animation_bubble.set_loop(false);
	animation_bubble.set_callback([&]() 
		{ 
			can_remove = true; 
			this->getCollideTargetId() == RoleId::P1 ? 
			role_2->set_can_attack() : role_1->set_can_attack(); 
		});

	collisionBox.x = (float)animation_bubble.get_current_frame()->getheight();
	collisionBox.y = (float)animation_bubble.get_current_frame()->getwidth();
	
	bulletSize.x = (float)animation_bubble.get_current_frame()->getheight();
	bulletSize.y = (float)animation_bubble.get_current_frame()->getwidth();
	
}

GloomshroomBullet::~GloomshroomBullet() {}

void GloomshroomBullet::on_collide() {
	
	
}


void GloomshroomBullet::on_update(int delta) {

	if (targetId == RoleId::P1) {
		position.x = role_2->get_position().x - (bulletSize.x / 2 - role_2->get_role_collision_box().x / 2);
		position.y = role_2->get_position().y - (bulletSize.y / 2 - role_2->get_role_collision_box().y / 2);
	}

	if (targetId == RoleId::P2) {
		position.x = role_1->get_position().x - (bulletSize.x / 2 - role_1->get_role_collision_box().x / 2);
		position.y = role_1->get_position().y - (bulletSize.y / 2 - role_1->get_role_collision_box().y / 2);
	}

	animation_bubble.on_update(delta);

	if (checkIsExceedScreen()) {
		can_remove = true;
	}
}


void GloomshroomBullet::on_draw(const Camera& camera) const {

	Bullet::on_draw(camera);
	
	if (can_cause_damage) {
		animation_bubble.on_draw(camera, (int)position.x, (int)position.y);
	}

}

const Animation* GloomshroomBullet::get_animation() const {
	return &animation_bubble;
}

#endif // !_GLOOMSHROOMBULLET_H_
