#ifndef _GLOOMSHROOMBULLET_H_
#define _GLOOMSHROOMBULLET_H_

#include "Animation.h"
#include "role.h"
#include "Bullet.h"
#include "Vector2.h"

extern Atlas atlas_bubbles;

class GloomshroomBullet : public Bullet
{
public:
	GloomshroomBullet();
	~GloomshroomBullet();

	void on_draw(const Camera& camera) const {}
	
	void on_update(int delta) {}
	
	void on_input(const ExMessage& msg) {}
	
	// 利用不同于透明的具有色彩的区域进行碰撞检测
	void on_collide() {}
	
	void getCollisionBox() {}


private:
	Animation animation_bubble;
	Animation* current_animation = nullptr;
	Vector2 bubble_randre_position = { 0,0 };

	// 每一帧中跑跑子弹的位置
	std::vector<Vector2> each_gloomshroombullet_within_frame_list;
	


};
GloomshroomBullet::GloomshroomBullet()
{
	damage = 10;

	animation_bubble.set_atlas(&atlas_bubbles);
	animation_bubble.set_inter_time(75);
	animation_bubble.set_loop(false);
	
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

}

void GloomshroomBullet::on_draw(const Camera& camera) const {
	animation_bubble.on_draw(camera, (int)bubble_randre_position.x, (int)bubble_randre_position.y);
}

void GloomshroomBullet::on_input(const ExMessage& msg) {

}


void GloomshroomBullet::getCollisionBox() {
	
	// 由于gloomshroom的子弹类型比特殊，故重写方法

	// 用容器
	
	
	
}


#endif // !_GLOOMSHROOMBULLET_H_
