
#include "main.h"


int main() {
	Game g = Game();

	// one day maybe support CLI args and send them over to game
	GameStartArgs args = GameStartArgs(); 
	args.width = 1280;
	args.height = 720;

	int exit = g.Start(args);

	return exit;
}
