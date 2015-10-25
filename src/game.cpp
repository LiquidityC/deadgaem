#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <flat/flat.h>
#include <iostream>

#include "Soldier.h"
#include "ParticleEngine.h"
#include "ResourceContainer.h"
#include "GameSettings.h"
#include "MapParser.h"
#include "LayerService.h"
#include "ResourceLoader.h"
#include "CustomGameData.h"
#include "FrameCounter.h"

int main( int argc, char* args[] )
{
	flat2d::FlatBuilder *flat = new flat2d::FlatBuilder;
	if (!flat->initSDL("Just Don't Die", GameSettings::SCREEN_WIDTH, GameSettings::SCREEN_HEIGHT)) {
		return -1;
	}
	if (!flat->initContainers()) {
		return -1;
	}

	GameStateController *gameStateController = new GameStateController();
	gameStateController->resetGame(flat->getGameData());

	flat2d::GameEngine *engine = flat->getGameEngine();
	engine->init(GameSettings::SCREEN_WIDTH, GameSettings::SCREEN_HEIGHT, GameSettings::SCREEN_FPS);

	// Start the game loop
	engine->run(gameStateController);

	delete static_cast<CustomGameData*>(flat->getGameData()->getCustomGameData());
	delete flat;

	return 0;
}