#ifndef _NUT_H_
#define _NUT_H_

#include "Role.h"
#include "NutBullet.h"

extern Atlas atlas_nut_die;
extern Atlas atlas_nut_idle_left;
extern Atlas atlas_nut_idle_right;
extern Atlas atlas_nut_run_left;
extern Atlas atlas_nut_run_right;


extern std::vector<Bullet*> Bullet_list;

// Nut拥有超高血量，和一次使用必杀技的的机会
// 必杀技使用之后如果没有击杀敌人，则自己死亡
class Nut : public Role
{
public:
	Nut() {
		// 设置动画图集
		animation_idle_left.set_atlas(&atlas_nut_idle_left);
		animation_idle_right.set_atlas(&atlas_nut_idle_right);
		animation_run_left.set_atlas(&atlas_nut_run_left);
		animation_run_right.set_atlas(&atlas_nut_run_right);
		// 设置帧间隔
		animation_idle_left.set_inter_time(75);
		animation_idle_right.set_inter_time(75);
		animation_run_left.set_inter_time(75);
		animation_run_right.set_inter_time(75);
	}

	~Nut() = default;

	void on_update(int interval_time) {
		Role::on_update(interval_time);
	}

	void on_input(const ExMessage& msg) {
		Role::on_input(msg);
	}

	void on_draw(const Camera& camera) {
		Role::on_draw(camera);
	}

	void on_attack() {
		// 该角色没有攻击模式
	}

	void on_attack_ex() {
		Bullet* bullet = new NutBullet();

		Vector2 postiion = { 0,0 };
		

		/*
		
		子弹初始化代码块

		*/



		Bullet_list.push_back(bullet);
		mciSendString(_T("play nut_explode from 0"), NULL, 0, NULL);
	}

private:
	int exattack_remain_time = 1;		// 表示必杀的释放次数只有一次

};

#endif // ! _NUT_H_
