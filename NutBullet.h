#ifndef _NUTBULLET_H_
#define _NUTBULLET_H_

#include "Animation.h"
#include "Bullet.h"
#include "atlas.h"
#include "Vector2.h"

extern Atlas atlas_nut_explode;
extern Atlas atlas_nut_explode_effect;


extern Role* role_1;
extern Role* role_2;

extern Camera main_camera;

class NutBullet : public Bullet {
public:

	NutBullet();
	~NutBullet();

	void on_update(int delta) override;
	void on_draw(const Camera& camera) const override;
	void on_collide() override;
	bool checkCollisionBox(const Vector2& position, const Vector2& collisionBox) override;
	const Animation* get_animation() const override;

private:
	Animation animation_explode;			// 子弹的爆炸特效
	Animation animation_explode_effect;		// 子弹的爆炸特效

};

NutBullet::NutBullet() {

	damage = 50;

	animation_explode_effect.set_atlas(&atlas_nut_explode_effect);
	animation_explode_effect.set_inter_time(75);
	animation_explode_effect.set_loop(false);
	animation_explode_effect.set_callback([&]()
		{
			can_remove = true;
			
		});

	animation_explode.set_atlas(&atlas_nut_explode);
	animation_explode.set_inter_time(75);
	animation_explode.set_loop(false);
	animation_explode.set_callback([&]()
		{
			can_remove = true;
		});

	// 设置子弹的碰撞箱
	collisionBox.x = (float)animation_explode.get_current_frame()->getwidth();
	collisionBox.y = (float)animation_explode.get_current_frame()->getwidth();
	
	// 设置子弹的单帧宽高
	bulletSize.x = (float)(animation_explode.get_current_frame()->getwidth());
	bulletSize.y = (float)(animation_explode.get_current_frame()->getheight());

	

}
NutBullet::~NutBullet() {}

void NutBullet::on_update(int delta) {
	this->Bullet::on_update(delta);
	animation_explode.on_update(delta);
	//animation_explode_effect.on_update(delta);

}

inline void NutBullet::on_draw(const Camera& camera) const {
	this->Bullet::on_draw(camera);
	animation_explode.on_draw(camera, (int)position.x, (int)position.y);
	//animation_explode_effect.on_draw(camera, (int)position.x, (int)position.y);
	
}


void NutBullet::on_collide() {
	// 子弹的碰撞判定方式与其他子弹类不一样
	
	Bullet::on_collide();						//基类中的on_collide方法调用了回调函数

	can_cause_damage = false;

	
}

inline bool NutBullet::checkCollisionBox(const Vector2& position, const Vector2& collisionBox) {
	bool is_collide_x = (max(this->position.x + this->collisionBox.x, position.x + collisionBox.x)
		- min(this->position.x, position.x) <= this->collisionBox.x + collisionBox.x);
	bool is_collide_y = (max(this->position.y + this->collisionBox.y, position.y + collisionBox.y)
		- min(this->position.y, position.y) <= this->collisionBox.y + collisionBox.y);
	return is_collide_x && is_collide_y;
}

inline const Animation* NutBullet::get_animation() const {
	return &animation_explode;
}

#endif // !_NUTBULLET_H_
