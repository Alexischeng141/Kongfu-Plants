#ifndef _SILENCEBUFFER_H_
#define _SILENCEBUFFER_H_

#include "Buffer.h"

class SilenceBuffer : public Buffer
{
public:
	SilenceBuffer();
	~SilenceBuffer() = default;
	
	bool getIsSilence() const { return _is_silence; }
	void on_update(int delta) override {
		Buffer::on_update(delta);
	}
private:
	const bool _is_silence = true;
};

SilenceBuffer::SilenceBuffer()
{
	type = Buffer::Silence; 
}

#endif // !_SILENCEBUFFER_H_

