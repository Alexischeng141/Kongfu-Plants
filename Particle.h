#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "Camera.h"
#include "Atlas.h"
#include "Vector2.h"

// 粒子对象类

class Particle
{
public:
	Particle() = default;
	// position:粒子生成位置 atlas:粒子图集资源 lifespan:粒子生命周期
	Particle(const Vector2& position, Atlas* atlas, int lifespan) : position(position), atlas(atlas),lifespan(lifespan) {}
	~Particle() = default;
	void set_timer(int deltaTime);
	void set_life_span(int lifespan);
	void set_frame_index(int index);
	void set_position(const Vector2& position);
	void set_atlas(Atlas* atlsa);
	bool check_valid() const;
	void on_update(int deltaTime);
	void on_draw(const Camera& camera) const;

private:
	int timer = 0;				// 定时器
	int lifespan = 0;			// 粒子生命周期
	int frameIndex = 0;			// 当前帧索引
	Vector2 position;			// 粒子生成位置
	bool valid = true;			// 粒子是否可用
	Atlas* atlas = nullptr;		// 粒子图集
};

inline void Particle::set_timer(int deltaTime) {
	this->timer = deltaTime;
}

inline void Particle::set_life_span(int lifespan)
{
	this->lifespan = lifespan;
}

inline void Particle::set_frame_index(int index)
{
	this->frameIndex = index;
}

inline void Particle::set_position(const Vector2& position)
{
	this->position = position;
}

inline void Particle::set_atlas(Atlas* atlas)
{
	this->atlas = atlas;
}

inline bool Particle::check_valid() const
{
	return valid;
}

inline void Particle::on_update(int deltaTime)
{
	timer += deltaTime;
	if (timer >= lifespan) {
		timer -= lifespan;
		frameIndex++;
		if (frameIndex >= atlas->get_frame_size()) {
			valid = false;
			frameIndex = atlas->get_frame_size() - 1;
		}
	}
}

inline void Particle::on_draw(const Camera& camera) const
{
	putimage_alpha(camera, (int)position.x, (int)position.y, atlas->get_image(frameIndex));
}


#endif // !_PARTICLE_H_
