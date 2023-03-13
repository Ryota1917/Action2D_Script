#include"SDL.h"
#include"Game.h"


int main(int argc, char** argv) {

	try {
		Game game = Game();
		bool success = game.Initialize();
		if (success) {
			game.RunLoop();
		}
		game.Shutdown();

		return 0;
	}
	catch (std::exception e) {
		SDL_Log(e.what());
		return 1;
	}
}