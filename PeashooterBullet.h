#ifndef _PEASHOOTERBULLET_H_
#define _PEASHOOTERBULLET_H_

#include "Bullet.h"
#include "Animation.h"


extern IMAGE img_pea;
extern Atlas atlas_pea_break;

class PeashooterBullet : public Bullet
{
public:
	PeashooterBullet() {
		collisionBox.x = 64;
		collisionBox.y = 64;

		damage = 10;

		animation_pea_break.set_atlas(&atlas_pea_break);
		animation_pea_break.set_inter_time(100);
		animation_pea_break.set_loop(false);
		animation_pea_break.set_callback([&]() { can_remove = true; });


	}
	~PeashooterBullet() = default;

	void on_collide() override {

		Bullet::on_collide();
		
		switch (rand() % 3)
		{
		case 0:
			mciSendString(_T("play pea_break_1 from 0"), NULL, 0, NULL);
			break;
		case 1:
			mciSendString(_T("play pea_break_2 from 0"), NULL, 0, NULL);
			break;
		case 2:
			mciSendString(_T("play pea_break_3 from 0"), NULL, 0, NULL);
			break;
		default:
			break;
		}
	}

	// 更新子弹的坐标信息
	void on_update(int delta) {
		position += velocity * (float)delta;

		if (!can_cause_damage) {
			animation_pea_break.on_update(delta);
		}

		if (checkIsExceedScreen()) {
			can_remove = true;
		}
	}

	void on_draw(const Camera& camera) const override {
		if (can_cause_damage) {
			putimage_alpha(camera, (int)position.x, (int)position.y, &img_pea);
		}
		else
		{	
			animation_pea_break.on_draw(camera, (int)position.x, (int)position.y);
		}
		Bullet::on_draw(camera);
	}


private:

	Animation animation_pea_break;

};


#endif // !_PEASHOOTERBULLET_H_
