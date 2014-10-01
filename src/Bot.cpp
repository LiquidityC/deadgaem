#include <iostream>
#include <algorithm>
#include "Bot.h"
#include "CompContainer.h"
#include "BloodParticle.h"
#include "Layers.h"

void Bot::init(const flat2d::RenderData *data)
{
	setTexture(flat2d::MediaUtil::loadTexture("resources/textures/bot.png", data->getRenderer()));
	setClip(clips[currentClip]);
}

void Bot::handle(const SDL_Event& e)
{
	if (e.type != SDL_KEYDOWN) {
		return;
	}

	if (e.key.keysym.sym == SDLK_SPACE) {
		if( yvel > -300 && yvel < 300) {
			yvel = -1000;
			grounded = false;
		}
	} else if (e.key.keysym.sym == SDLK_h) {
		CompContainer::getInstance().getParticleEngine().createBloodSprayAt(xpos-10, ypos-10);
	}
}

void Bot::postHandle()
{
	xvel = 0;

	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_A]) {
		xvel = -300;
	}
	if (currentKeyStates[SDL_SCANCODE_D]) {
		xvel = 300;
	}

}

void Bot::preRender(const flat2d::RenderData *data)
{
	flat2d::CollisionDetector& colDetector = CompContainer::getInstance().getCollisionDetector();
	float deltaTime = data->getCamera()->getDeltaTime();

	// Gravity
	if (yvel < 800) {
		yvel += std::min(3600 * deltaTime, 800 - yvel);
	}

	xpos += (xvel * deltaTime);
	GameObject *object;
	if ((object = colDetector.checkForCollisions(this)) != NULL) {
		xpos -= (xvel * deltaTime);

		// Completly reach the obstruction
		while (!colDetector.hasCollided(this, object)) {
			xpos += xvel > 0 ? 1 : -1;
		}
		xpos += xvel > 0 ? -1 : 1;
		xvel = 0;
		object = NULL;
	}

	ypos += (yvel * deltaTime);
	if ((object = colDetector.checkForCollisions(this)) != NULL) {
		ypos -= (yvel * deltaTime);

		// Completly ground the bot
		while (!colDetector.hasCollided(this, object)) {
			ypos += yvel > 0 ? 1 : -1;
		}
		ypos += yvel > 0 ? -1 : 1;
		if (yvel > 0) {
			grounded = true;
		}
		yvel = 0;
		object = NULL;
	}

	calculateCurrentClip();

	data->getCamera()->centerOn(xpos + (width/2), ypos + (height/2));
}

void Bot::calculateCurrentClip()
{
	if (xvel != 0) {
		if (xvel > 0
				&& currentClip != ClipIndex::RIGHT
				&& currentClip != ClipIndex::WALK_RIGHT_1
				&& currentClip != ClipIndex::WALK_RIGHT_2)
		{
			currentClip = ClipIndex::WALK_RIGHT_1;
		} else if (xvel < 0
				&& currentClip != ClipIndex::LEFT
				&& currentClip != ClipIndex::WALK_LEFT_1
				&& currentClip != ClipIndex::WALK_LEFT_2)
		{
			currentClip = ClipIndex::WALK_LEFT_1;
		}

		if (xvel > 0) {
			static int rightClipCount = 0;
			static int rightClipIndex = 0;

			ClipIndex walkRightClips[4] = { 
				ClipIndex::WALK_RIGHT_1,
				ClipIndex::RIGHT,
				ClipIndex::WALK_RIGHT_2,
				ClipIndex::RIGHT
			};

			if (rightClipCount > 4) {
				rightClipCount = 0;

				currentClip = walkRightClips[rightClipIndex];

				++rightClipIndex;
				if (rightClipIndex > 3) {
					rightClipIndex = 0;
				}
			}
			++rightClipCount;

		} else if (xvel < 0) {
			static int leftClipCount = 0;
			static int leftClipIndex = 0;

			ClipIndex walkLeftClips[4] = { 
				ClipIndex::WALK_LEFT_1,
				ClipIndex::LEFT,
				ClipIndex::WALK_LEFT_2,
				ClipIndex::LEFT
			};

			if (leftClipCount > 4) {
				leftClipCount = 0;

				currentClip = walkLeftClips[leftClipIndex];

				++leftClipIndex;
				if (leftClipIndex > 3) {
					leftClipIndex = 0;
				}
			}
			++leftClipCount;
		}
	}

	if (!grounded) {
		if (currentClip == ClipIndex::GHOST_RIGHT) {
			currentClip = ClipIndex::RIGHT;
		} else if (currentClip == ClipIndex::GHOST_LEFT) {
			currentClip = ClipIndex::LEFT;
		}
	}

	if (xvel == 0 && yvel == 0 && grounded) {
		if (currentClip == ClipIndex::WALK_RIGHT_1
				|| currentClip == ClipIndex::WALK_RIGHT_2
				|| currentClip == ClipIndex::RIGHT)
		{
			currentClip = ClipIndex::GHOST_RIGHT;
		} else if (currentClip == ClipIndex::WALK_LEFT_1
				|| currentClip == ClipIndex::WALK_LEFT_2
				|| currentClip == ClipIndex::LEFT)
		{
			currentClip = ClipIndex::GHOST_LEFT;
		}
	}

	setClip(clips[currentClip]);
}

