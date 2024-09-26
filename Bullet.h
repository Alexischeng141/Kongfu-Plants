#ifndef _BULLET_H_
#define _BULLET_H_

#include "Vector2.h"
#include "functional"
#include "RoleId.h"
#include "Camera.h"
#include "graphics.h"

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

	void setPosition(float x, float y) {
		position.x = x;
		position.y = y;
	}

	const Vector2& getPosition() {
		return position;
	}

	const Vector2& getCollisionBox() {
		return collisionBox;
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
	virtual bool checkCollisionBox(const Vector2& position, const Vector2& collisionBox) {
		return this->position.x + this->collisionBox.x / 2 >= position.x
			&& this->position.x + this->collisionBox.x / 2 <= position.x + collisionBox.x
			&& this->position.y + this->collisionBox.y / 2 >= position.y
			&& this->position.y + this->collisionBox.y / 2 <= position.y + collisionBox.y;
	}

	virtual void on_update(int interval_time) {

	}

	virtual void on_draw(const Camera& camera) const {

	}

protected:
	
	Vector2 collisionBox = { 0,0 };			// 子弹的碰撞箱
	Vector2 position = { 0,0 };				// 子弹的位置
	Vector2 velocity = { 0,0 };				// 子弹的速度

	int damage = 10;						// 伤害
	bool can_cause_damage = true;			// 是否能造成伤害
	bool can_remove = false;				// 是否能被移除
	
	std::function<void()> callback;			// 子弹碰撞时回调函数
	
	RoleId targetId = RoleId::P1;			// 攻击目标

protected:
	
	bool checkIsExceedScreen() {
		return (position.x + collisionBox.x <= 0 || position.x >= getwidth()
			|| position.y + collisionBox.y <= 0 || position.y >= getheight());
	}
	
};


#endif // !_BULLET_H_
