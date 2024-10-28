#ifndef _GLOOMSHROOMBULLET_H_
#define _GLOOMSHROOMBULLET_H_

#include "Bullet.h"
#include "Role.h"

extern Atlas atlas_bubbles;
extern bool is_debug;
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
	bool checkCollisionBox(const Vector2& position, const Vector2& collisionBox) override;

protected:

private:
	
	Animation animation_bubble;
	Circle gloomshroomCollisionBox = { 0,0,0 };

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
			role_2->set_attack(true) : role_1->set_attack(true); 
		});

	collisionBox.x = (float)animation_bubble.get_current_frame()->getheight();
	collisionBox.y = (float)animation_bubble.get_current_frame()->getwidth();

	bulletSize.x = (float)animation_bubble.get_current_frame()->getwidth();
	bulletSize.y = (float)animation_bubble.get_current_frame()->getheight();

	gloomshroomCollisionBox.setRadius(bulletSize.x / 3.5f);
	
	
}

GloomshroomBullet::~GloomshroomBullet() {}

void GloomshroomBullet::on_collide() {
	Bullet::on_collide(); 
	
}


void GloomshroomBullet::on_update(int delta) {

	if (targetId == RoleId::P1) {
		position.x = role_2->get_position().x - (bulletSize.x / 2 - role_2->get_role_collision_box().x / 2);
		position.y = role_2->get_position().y - (bulletSize.y / 2 - role_2->get_role_collision_box().y / 2);
		gloomshroomCollisionBox.center.x = position.x + bulletSize.x / 2.0f;
		gloomshroomCollisionBox.center.y = position.y + bulletSize.y / 2.0f;
		
	}

	if (targetId == RoleId::P2) {
		position.x = role_1->get_position().x - (bulletSize.x / 2 - role_1->get_role_collision_box().x / 2);
		position.y = role_1->get_position().y - (bulletSize.y / 2 - role_1->get_role_collision_box().y / 2);
		gloomshroomCollisionBox.center.x = position.x + bulletSize.x / 2.0f;
		gloomshroomCollisionBox.center.y = position.y + bulletSize.y / 2.0f;
	}

	// 增加子弹的碰撞半径
	if (gloomshroomCollisionBox.getRadius() <= MAXLONG) {
		gloomshroomCollisionBox.radius += 0.5f;
	}

	animation_bubble.on_update(delta);

	if (checkIsExceedScreen()) {
		can_remove = true;
	}
}


void GloomshroomBullet::on_draw(const Camera& camera) const {

	//Bullet::on_draw(camera);

	if (is_debug) {
		gloomshroomCollisionBox.draw();
	}
	
	if (can_cause_damage) {
		animation_bubble.on_draw(camera, (int)position.x, (int)position.y);
	}

}

const Animation* GloomshroomBullet::get_animation() const {
	return &animation_bubble;
}

// 传入玩家的位置和碰撞箱与子弹的碰撞箱进行碰撞检测
inline bool GloomshroomBullet::checkCollisionBox(const Vector2& position, const Vector2& collisionBox) {	
	return gloomshroomCollisionBox.checkCollisionBox(position, collisionBox.x, collisionBox.y);	
}

#endif // !_GLOOMSHROOMBULLET_H_
