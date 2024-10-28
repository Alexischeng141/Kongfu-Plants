#ifndef _INVISIBLE_H_
#define _INVISIBLE_H_

#include "Buffer.h"

class  InvisibleBuffer : public Buffer
{
public:
	InvisibleBuffer() = default;
	 InvisibleBuffer(int duration);
	 ~InvisibleBuffer() = default;
	bool getBooleanValue() override { return _invisible; }
	void on_update(int delta) override { Buffer::on_update(delta); }
private:
	const bool _invisible = true;
};

 InvisibleBuffer:: InvisibleBuffer(int duration) : Buffer(duration)
{
	 this->type = Buffer::Invisible;
}

#endif // !_INVISIBLE_H_

