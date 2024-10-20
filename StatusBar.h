#ifndef _STATUSBAR_H_
#define	_STATUSBAR_H_

#include "Utils.h"

// 类定义中的函数是隐式内联的
// 如果在类定义之外定义函数则需要添加"inline"关键字显示内联

class StatusBar
{
public:
	StatusBar();  
	~StatusBar();
	inline void set_avatar(IMAGE* img_avatar);
	void set_position(int x, int y);
	void set_hp(int hp);
	void set_mp(int mp);
	void on_draw();
private:
	int hp = 0;
	int mp = 0;
	POINT position = { 0,0 };
	IMAGE* img_avatar = nullptr;
	
private:
	const int width = 275;
};

inline StatusBar::StatusBar()
{
}

inline StatusBar::~StatusBar()
{
}

inline void StatusBar::set_avatar(IMAGE* img_avatar) {
	this->img_avatar = img_avatar;
}

inline void StatusBar::set_position(int x, int y) {
	position.x = x, position.y = y;
}

inline void StatusBar::set_hp(int hp) {
	this->hp = hp;
}

inline void StatusBar::set_mp(int mp) {
	this->mp = mp;
 }

inline void StatusBar::on_draw() {
	putimage_alpha(position.x, position.y, img_avatar);
	
	setfillcolor(RGB(5, 5, 5));
	solidroundrect(position.x + 100, position.y + 10, position.x + 100 + width + 3 * 2, position.y + 36, 8, 8);
	solidroundrect(position.x + 100, position.y + 45, position.x + 100 + width + 3 * 2, position.y + 71, 8, 8);
	setfillcolor(RGB(67, 47, 47));
	solidroundrect(position.x + 100, position.y + 10, position.x + 100 + width + 3, position.y + 33, 8, 8);
	solidroundrect(position.x + 100, position.y + 45, position.x + 100 + width + 3, position.y + 68, 8, 8);

	float hp_bar_width = width * max(0, hp) / 100.0f;
	float mp_bar_width = width * min(100, mp) / 100.0f;

	setfillcolor(RGB(197, 61, 67));
	solidroundrect(position.x + 100, position.y + 10, position.x + 100 + (int)hp_bar_width + 3, position.y + 33, 8, 8);
	setfillcolor(RGB(83, 131, 195));
	solidroundrect(position.x + 100, position.y + 45, position.x + 100 + (int)mp_bar_width + 3, position.y + 68, 8, 8);
}

#endif // !_STATUSBAR_H_
