#ifndef _RECOVERYBUFFER_H_
#define _RECOVERYBUFFER_H_

#include "Buffer.h"


class RecoveryBuffer : public Buffer
{
public:
	RecoveryBuffer() = default;
	~RecoveryBuffer() = default;
	RecoveryBuffer(int duration, float _recoveryPercentage);

	float getFloatValue() override { return _recoveryPercentage;  }

	void on_update(int delta) override {
		Buffer::on_update(delta);
	}

private:

	float _recoveryPercentage = 0.0f;	// »Ø¸´Á¿

};

RecoveryBuffer::RecoveryBuffer(int duration, float _recoveryPercentage) : Buffer(duration)
{
	this->type = Buffer::HpRecovery;
	this->_recoveryPercentage = _recoveryPercentage;
}

#endif // !_RECOVERYBUFFER_H_
