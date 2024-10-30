#ifndef _SPEEDBOOST_H_
#define _SPEEDBOOST_H_

#include "Buffer.h"

class SpeedBoost : public Buffer
{
public:
	SpeedBoost();
	~SpeedBoost() = default;
	

	float getSpeedRate() const {
		return _speedRate;
	}

	void on_update(int delta) override {
		Buffer::on_update(delta);
	}

	float _speedRate;	// 速度增加倍率
private:
};

SpeedBoost::SpeedBoost()
{
	_speedRate = 1.5f;
	type = Buffer::SpeedBoost;
}

#endif // !_SPEEDBOOST_H_

