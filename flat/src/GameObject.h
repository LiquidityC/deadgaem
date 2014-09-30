#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H

#include <SDL2/SDL.h>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace flat2d 
{
	class Camera;

	class GameObject
	{
		private:
			boost::uuids::uuid id;

		public:

			/* Constructors and destructors */
			GameObject() {

				/* Not providing ran creates valgrind warnings */
				static boost::mt19937 ran;
				id = boost::uuids::random_generator(ran)();
			};
			GameObject(const GameObject& o)	: id(o.id) { };
			virtual ~GameObject() { };

			/* Operators */
			virtual bool operator==(const GameObject& o) const {
				return id == o.id;
			};

			virtual bool operator!=(const GameObject& o) const {
				return id != o.id;
			};

			virtual GameObject& operator=(const GameObject& o) {
				id = o.id;
				return *this;
			};

			virtual std::string getStringId() const {
				return boost::lexical_cast<std::string>(id);
			};

			/* Abstract methods */
			virtual bool isDead() const = 0;

			virtual void init(SDL_Renderer*, Camera*) = 0;
			virtual void preHandle() = 0;
			virtual void handle(const SDL_Event& event) = 0;
			virtual void postHandle() = 0;

			virtual void preRender() = 0;
			virtual void render(SDL_Renderer* renderer) const = 0;
			virtual void postRender() = 0;

			virtual bool isCollider() const = 0;
			virtual SDL_Rect getBoundingBox() const = 0;

			virtual const SDL_Texture* getTexture() const = 0;
			virtual void setTexture(SDL_Texture*) = 0;
	};
}

#endif
