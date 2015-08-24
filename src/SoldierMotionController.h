#ifndef SOLDIERMOTIONCONTROLLER_H_
#define SOLDIERMOTIONCONTROLLER_H_

#include <SDL2/SDL.h>
#include <flat/flat.h>
#include <map>

class Soldier;

class SoldierMotionController
{
	private:
		enum MovementMapping {
			MOVE_LEFT,
			MOVE_RIGHT,
			FLOAT,
			LAST
		};

		typedef std::map<MovementMapping, bool> MovementMap;

		Soldier *soldier = nullptr;
		MovementMap movementMap;

		void keyDown(const SDL_KeyboardEvent&);
		void keyUp(const SDL_KeyboardEvent&);
		void controllerAxisMotion(const SDL_ControllerAxisEvent&);
		void controllerButtonDown(const SDL_ControllerButtonEvent&);
		void controllerButtonUp(const SDL_ControllerButtonEvent&);

		void stop();
		void moveLeft();
		void moveRight();
		void jump();
		void ghostMode();

	public:
		explicit SoldierMotionController(Soldier* soldier);

		void handle(const SDL_Event&);
		void preMove(const flat2d::GameData*);
		void freeze();
};

#endif // SOLDIERMOTIONCONTROLLER_H_
