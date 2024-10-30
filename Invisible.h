#ifndef _INVISIBLE_H_
#define _INVISIBLE_H_

#include "Buffer.h"

class  InvisibleBuffer : public Buffer
{
public:
	InvisibleBuffer();
	 ~InvisibleBuffer() = default;
	 bool getIsInvisible() const { return _is_invisible; }
	
	void on_update(int delta) override { Buffer::on_update(delta); }
private:
	bool _is_invisible = true;
};

 InvisibleBuffer::InvisibleBuffer()
{
	 type = Buffer::Invisible;
}

#endif // !_INVISIBLE_H_

