#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "Vector2.h"

class Circle
{
public:
	Circle();
	~Circle();

	const Vector2& getCircleCenter() {}

	void setCircleRadius(float radius) {}

	bool checkCollisionBox(const Vector2& role_collision_box) {}

private:
	Vector2 circle_center = { 0,0 };			// Ô²ÐÄ
	float radius = 0;							// °ë¾¶
private:
	const float TI = 3.14159;					// ³£Á¿					
};

Circle::Circle()
{
}

Circle::~Circle()
{
}

const Vector2& Circle::getCircleCenter() {
	return circle_center;
}

void Circle::setCircleRadius(float radius) {
	this->radius = radius;
}

bool Circle::checkCollisionBox(const Vector2& role_collision_box) {


}

#endif // !_CIRCLE_H_
