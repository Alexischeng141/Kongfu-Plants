#ifndef _NUTBULLET_H_
#define _NUTBULLET_H_

#include "Animation.h"
#include "Bullet.h"
#include "atlas.h"
#include "Vector2.h"

extern Atlas atlas_nut_explode;
extern Atlas atlas_nut_attack_ex;

class NutBullet : public Bullet {
public:

	NutBullet();
	~NutBullet();

	void on_update(int delta);
	void on_draw(const Camera& camera);
	void on_input(const ExMessage& msg);
	void on_collide();


private:
	Animation animation_explode;
	Animation animation_attack_ex;

	Vector2 collisionBox = { 0,0 };			// ×Óµ¯µÄÅö×²Ïä

};

NutBullet::NutBullet() {

	damage = 200;

	animation_explode.set_atlas(&atlas_nut_explode);
	animation_attack_ex.set_atlas(&atlas_nut_attack_ex);

	animation_explode.set_inter_time(75);
	animation_attack_ex.set_inter_time(75);
	
	animation_explode.set_loop(false);
	animation_attack_ex.set_loop(false);

	animation_explode.set_callback([&]() { can_remove = true; });
	animation_attack_ex.set_callback([&]() { can_remove = true; });

	/*
	
	Åö×²Ïä³õÊ¼»¯´úÂë¿é
	
	*/

}
NutBullet::~NutBullet() {}

void NutBullet::on_update(int delta) {


}

void NutBullet::on_draw(const Camera& camera) {

}

void NutBullet::on_input(const ExMessage& msg) {

}

void NutBullet::on_collide() {

}


#endif // !_NUTBULLET_H_
