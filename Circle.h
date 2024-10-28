#pragma once
#ifndef _CIRCLE_H_
#define	_CIRCLE_H_

#include "Vector2.h"
#include "graphics.h"


class Circle {
public:
    Circle(float x, float y, float radius)
        : center(x, y), radius(radius) {}

    // 计算圆的面积
    float area() const {
        return 3.14159f * radius * radius;
    }

    // 计算圆的周长
    float circumference() const {
        return 2 * 3.14159f * radius;
    }

    // 判断点是否在圆内
    bool contains(float x, float y) const {
        float dx = x - center.x;
        float dy = y - center.y;
        return (dx * dx + dy * dy) <= (radius * radius);
    }

    // 设置圆心
    void setCenter(float x, float y) {
        center.x = x;
        center.y = y;
    }

    // 获取圆心
    Vector2 getCenter() const {
        return center;
    }

    // 设置半径
    void setRadius(float r) {
        radius = r;
    }

    // 获取半径
    float getRadius() const {
        return radius;
    }

    // 根据玩家位置，更新圆的位置
    void on_update() {
       
    }

    bool checkCollisionBox(const Vector2& rectangleTopLeft, float width, float height) const {
        // 找到矩形的最近点
        float closestX = fmax(rectangleTopLeft.x, fmin(center.x, rectangleTopLeft.x + width));
        float closestY = fmax(rectangleTopLeft.y, fmin(center.y, rectangleTopLeft.y + height));

        // 计算圆心与矩形最近点之间的距离
        float dx = center.x - closestX;
        float dy = center.y - closestY;

        // 检查圆的半径与最近点之间的距离
        return (dx * dx + dy * dy) <= (radius * radius);
    }

    void draw() const {
        // 绘制圆形，center.x 和 center.y 是圆心的坐标
        setcolor(WHITE);
        circle((int)center.x, (int)center.y, (int)radius); // 绘制圆的轮廓
    }
public:
    Vector2 center; // 圆心
    float radius;   // 半径

};

#endif // _CIRCLE_H_

