#include"Engine.h"

int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

	Engine game("Tank++" , 1920 , 1080 , true , 60);

	game.run();

	return 0;
}
