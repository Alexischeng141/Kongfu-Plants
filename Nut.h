#ifndef _NUT_H_
#define _NUT_H_

#include "Role.h"
#include "NutBullet.h"

extern Atlas atlas_nut_die_right;
extern Atlas atlas_nut_die_left;
extern Atlas atlas_nut_idle_left;
extern Atlas atlas_nut_idle_right;
extern Atlas atlas_nut_run_left;
extern Atlas atlas_nut_run_right;
extern Atlas atlas_nut_attack_ex_right;
extern Atlas atlas_nut_attack_ex_left;

extern Role* role_1;
extern Role* role_2;

extern std::vector<Bullet*> Bullet_list;

// Nut拥有超高血量，和一次使用必杀技的的机会
// 必杀技使用之后如果没有击杀敌人，则自己死亡
// Nut在能量值满后可以进行变身，手动控制超大范围的爆炸

class Nut : public Role
{
public:
	Nut(bool facing_right = true) : Role(facing_right) {
		// 设置动画图集
		animation_die_left.set_atlas(&atlas_nut_die_left);
		animation_die_right.set_atlas(&atlas_nut_die_right);
		animation_idle_left.set_atlas(&atlas_nut_idle_left);
		animation_idle_right.set_atlas(&atlas_nut_idle_right);
		animation_run_left.set_atlas(&atlas_nut_run_left);
		animation_run_right.set_atlas(&atlas_nut_run_right);
		animation_attack_ex_right.set_atlas(&atlas_nut_attack_ex_right);
		animation_attack_ex_left.set_atlas(&atlas_nut_attack_ex_left);
		// 设置帧间隔
		animation_die_left.set_inter_time(75);
		animation_die_right.set_inter_time(75);
		animation_idle_left.set_inter_time(75);
		animation_idle_right.set_inter_time(75);
		animation_run_left.set_inter_time(75);
		animation_run_right.set_inter_time(75);
		animation_attack_ex_right.set_inter_time(200);
		animation_attack_ex_left.set_inter_time(200);

		// 设置动画是否循环播放
		animation_die_left.set_loop(false);
		animation_die_right.set_loop(false);
		animation_attack_ex_left.set_loop(false);
		animation_attack_ex_right.set_loop(false);

		animation_attack_ex_right.set_callback([&]()
			{
				hp -= 30;
				is_attacking_ex = false;
				make_invulnerable();
				generate_bullet();
				main_camera.shake(30, 200);
				animation_attack_ex_right.reset();
			});
		animation_attack_ex_left.set_callback([&]()
			{
				hp -= 30;
				is_attacking_ex = false;
				make_invulnerable();
				generate_bullet();
				main_camera.shake(30, 200);
				animation_attack_ex_left.reset();
			});
		
		
		timer_recharge.set_wait_time(200);
		timer_recharge.set_one_shot(false);
		timer_recharge.set_callback([&]()
			{
				mp += 50;				// 用于测试的值
			});
		
		role_size.x = 96;
		role_size.y = 96;
		

		Role::set_player_type(3);	// 设置角色的类型
	}

	~Nut() = default;

	void on_update(int interval_time) {

		Role::on_update(interval_time);
		timer_recharge.on_update(interval_time);
		if (is_attacking_ex) {
			
		}
		
		
	}

	void on_input(const ExMessage& msg) {
		Role::on_input(msg);
	}

	void on_draw(const Camera& camera) {
		Role::on_draw(camera);
	}

	void on_attack() {
		if (!is_attacking_ex)
			return;
		
		// nut的攻击模组为防御可以产生一抵挡数次攻击的护盾
		
		
	}

	void on_attack_ex() {
		is_attacking_ex = true;	//设置特殊攻击状态为 true 此时角色会更改Animation指针
	}

	// 生成子弹
	void generate_bullet() {

		/* nut 的子弹没有速度位置是根据角色释放的位置而决定的 */
		Bullet* bullet = new NutBullet();
		Role* current_role = this->role_id == RoleId::P1 ? role_1 : role_2;

		Vector2 bulletPosition;

		bulletPosition.x = (float)current_role->get_position().x - (bullet->getBulletSize().x / 2 - current_role->get_role_collision_box().x / 2);
		bulletPosition.y = (float)current_role->get_position().y - (bullet->getBulletSize().y / 2 - current_role->get_role_collision_box().x / 2);

		bullet->setPosition(bulletPosition.x, bulletPosition.y);
		bullet->setCollideTarget(role_id == RoleId::P1 ? RoleId::P2 : RoleId::P1);

		bullet->setCallback([&]()
			{
				mp += 40;
			});
		
		Bullet_list.push_back(bullet);
		mciSendString(_T("play nut_explode from 0"), NULL, 0, NULL);
		
	}

private:
	
	Timer timer_recharge;			// nut 自动充能定时器
	Vector2 role_size = { 0,0 };	// 角色帧宽高
	bool start_explode = false;		// 控制子弹是否播放爆炸动画

};

#endif // ! _NUT_H_
