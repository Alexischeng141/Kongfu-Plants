#ifndef _SPEEDBOOST_H_
#define _SPEEDBOOST_H_

#include "Buffer.h"

class SpeedBoost : public Buffer
{
public:
	SpeedBoost() = default;
	~SpeedBoost() = default;
	SpeedBoost(int duration, float _speedRate);

	float getFloatValue() override { return _speedRate;  }

	float getSpeedRate() {
		return _speedRate;
	}

	void on_update(int delta) override {
		Buffer::on_update(delta);
	}

	float _speedRate = 1.5f;	// 速度增加倍率
private:
};

SpeedBoost::SpeedBoost(int duration, float _speedRate) : Buffer(duration)
{
	this->type = Buffer::SpeedBoost;
	this->_speedRate = _speedRate;
}

#endif // !_SPEEDBOOST_H_

