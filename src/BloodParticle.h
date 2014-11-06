#ifndef _BLOOD_PARTICLE_H
#define _BLOOD_PARTICLE_H

#include <flat/flat.h>
#include "Particle.h"

class BloodParticle : public Particle
{
	private:
		flat2d::Timer timer;

	public:
		BloodParticle(int x, int y, int size, int xvel, int yvel) 
			: Particle(x, y, size, size, xvel, yvel) { };

	private:
		void setRenderDrawColor(SDL_Renderer* renderer) const;
};

#endif
