
#include "main.h"


int main() {
	Game g = Game();

	// one day maybe support CLI args and send them over to game
	GameOptions opts; 
	opts.width = 1280;
	opts.height = 720;
	opts.vsync = true;

	int exit = g.Start(opts);

	return exit;
}
