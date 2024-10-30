#ifndef _BULLET_H_
#define _BULLET_H_

#include "Vector2.h"
#include "Animation.h"
#include "functional"
#include "RoleId.h"
#include "Camera.h"
#include "graphics.h"
#include "Circle.h"

extern bool is_debug;

class Bullet
{
public:
	Bullet() = default;
	~Bullet() = default;

	

	void setDamage(int damage) {
		this->damage = damage;
	}

	int getDamage() {
		return damage;
	}

	int getBulletType() const {
		return type;
	}

	void setPosition(float x, float y) {
		position.x = x;
		position.y = y;
	}

	const Vector2& getPosition() {
		return position;
	}

	const Vector2& getCollisionBox() const {
		return collisionBox;
	}

	const Vector2& getBulletSize() const {
		return bulletSize;
	}

	void setVelocity(float x, float y) {
		velocity.x = x;
		velocity.y = y;
	}

	void setCollideTarget(RoleId target) {
		targetId = target;
	}

	RoleId getCollideTargetId() const {
		return targetId;
	}

	void setCallback(std::function<void()> callback) {
		this->callback = callback;
	}

	void setCanCauseDamage(bool val) {
		can_cause_damage = val;
	}

	void setBulletType(int type) {
		this->type = (bulletType)type;
	}

	bool getCanCauseDamage() const {
		return can_cause_damage;
	}

	bool checkCanReMove() const {
		return can_remove;
	}

	virtual void on_collide() {
		if (callback) {
			callback();
		}
	}

	// 传入玩家的位置和碰撞箱
	// 以子弹的圆心为判定条件
	virtual bool checkCollisionBox(const Vector2& position, const Vector2& collisionBox) {
		return this->position.x + this->collisionBox.x / 2 >= position.x
			&& this->position.x + this->collisionBox.x / 2 <= position.x + collisionBox.x
			&& this->position.y + this->collisionBox.y / 2 >= position.y
			&& this->position.y + this->collisionBox.y / 2 <= position.y + collisionBox.y;
	}

	virtual void on_update(int interval_time) { }

	virtual const Animation* get_animation() const { return nullptr; };

	virtual void on_draw(const Camera& camera) const {

		if (is_debug) {
			setfillcolor(RGB(255, 255, 255));
			setlinecolor(RGB(255, 255, 255));
			rectangle((int)position.x, (int)position.y, (int)(position.x + collisionBox.x), (int)(position.y + collisionBox.y));
			solidcircle((int)(position.x + collisionBox.x / 2), (int)(position.y + collisionBox.y / 2), 5);
		}

	}


	enum bulletType
	{
		none = 0,
		peas,
		sunflower,
		gloomshroom,
		nut
	};

protected:
	
	Vector2 collisionBox = { 0,0 };			// 子弹的碰撞箱即碰撞范围
	Vector2 bulletSize = { 0,0 };			// 子弹的单帧宽高
	Vector2 position = { 0,0 };				// 子弹的位置
	Vector2 velocity = { 0,0 };				// 子弹的速度

	int damage = 0;							// 子弹的伤害
	bool can_cause_damage = true;			// 子弹是否能造成伤害
	bool can_remove = false;				// 子弹是否能被移除
	
	std::function<void()> callback;			// 子弹发生碰撞时的回调函数
	
	RoleId targetId = RoleId::P1;			// 子弹的攻击目标

	bulletType type = bulletType::none;		// 子弹的类型

protected:
	
	bool checkIsExceedScreen() {
		return (position.x + collisionBox.x <= 0 || position.x >= getwidth()
			|| position.y + collisionBox.y <= 0 || position.y >= getheight());
	}
	
};


#endif // !_BULLET_H_