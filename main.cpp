#include "Game.h"

int main()
{
    Game game;
    try {
        game.run();
    }
    catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
    return 0;
}