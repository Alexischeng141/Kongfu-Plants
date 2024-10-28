#ifndef _SILENCEBUFFER_H_
#define _SILENCEBUFFER_H_

#include "Buffer.h"

class SilenceBuffer : public Buffer
{
public:
	SilenceBuffer() = default;
	~SilenceBuffer() = default;
	SilenceBuffer(int duration);
	bool getBooleanValue() override { return _canReleaseEx; }
	void on_update(int delta) override {
		Buffer::on_update(delta);
	}
private:
	const bool _canReleaseEx = false;
};

SilenceBuffer::SilenceBuffer(int duration) : Buffer(duration)
{
	this->type = Buffer::Silence; 
}

#endif // !_SILENCEBUFFER_H_

