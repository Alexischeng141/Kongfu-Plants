#pragma once
#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include <cmath>

// 二维平面向量类
class Vector2
{
public:
	float x;
	float y;

public:
	Vector2() = default;
	~Vector2() = default;

	Vector2(float x, float y) : x(x), y(y) {}; // 成员变量初始化函数

	Vector2 operator+(const Vector2& vec) const {
		return Vector2(x + vec.x, y + vec.y);
	}

	void operator+=(const Vector2& vec) {
		x += vec.x;
		y += vec.y;
	}

	Vector2 operator-(const Vector2& vec) const {
		return Vector2(x - vec.x, y - vec.y);
	}

	void operator-=(const Vector2& vec) {
		x -= vec.x;
		y -= vec.y;
	}

	float operator*(const Vector2& vec) const {
		return x * vec.x + y * vec.y;
	}

	Vector2 operator*(float val) const {
		return Vector2(x * val, y * val);
	}

	void operator*=(float val) {
		x *= val, y *= val;
	}

	// 获取向量的长度
	float length() const {
		return sqrt(x * x + y * y);
	}

	// 重置向量坐标
	void reset() {
		x = 0;
		y = 0;
	}

	// 向量标准化
	Vector2 normalize() const {
		float len = length();
		if (len == 0)
			return Vector2(0, 0);
		return Vector2(x / len, y / len);
	}

};
#endif // !_VECTOR2_H_
