#ifndef _RECOVERYBUFFER_H_
#define _RECOVERYBUFFER_H_

#include "Buffer.h"


class RecoveryBuffer : public Buffer
{
public:
	RecoveryBuffer();
	~RecoveryBuffer() = default;

	float getRecoveryPercentage() const { return _recoveryPercentage;  }

	void on_update(int delta) override {
		Buffer::on_update(delta);
	}

private:

	float _recoveryPercentage = 0.8f;	// »Ø¸´Á¿

};

RecoveryBuffer::RecoveryBuffer()
{
	type = Buffer::HpRecovery;
	_recoveryPercentage = 0.8f;
}

#endif // !_RECOVERYBUFFER_H_
