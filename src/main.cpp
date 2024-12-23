
#include "main.h"


int main() {
	Game g = Game();

	// one day maybe support CLI args and send them over to game
	GameOptions opts; 

	int exit = g.Start(opts);

	return exit;
}
