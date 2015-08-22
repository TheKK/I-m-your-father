#include <stdexcept>
#include <cstdio>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <SDL.h>

#include "systemFactory.h"
#include "system.h"
#include "timer.h"
#include "game.h"

void
mainLoop()
{
	/* TODO Figure out what the heck is happened?
	 *
	 * If I instanced Game in main function then pass it into mainLoop for
	 * emscripten, it will break everything. But this trick won't, pretty
	 * weird...
	 *
	 */
	static Game game;

	game.update();
	game.render();
}

int
main(int argc, char* argv[])
{
	try {
		std::unique_ptr<System> system(SystemFactory::build("jfjf"));

#ifdef __EMSCRIPTEN__
		emscripten_set_main_loop((em_callback_func) mainLoop, 0, 1);
#else
		Game game;
		Timer timer;
		while (game.isRunning()) {
			timer.start();

			game.update();
			game.render();

			if (timer.getTicks() < (1000.0 / 60.0))
				SDL_Delay((1000.0 / 60.0) - timer.getTicks());
		}
#endif

	} catch (const std::runtime_error& e) {
		printf("Exception: %s\n", e.what());
		return 1;
	}

	return 0;
}
