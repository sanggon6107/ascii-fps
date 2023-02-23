#include "Game.h"

void Game::Launch()
{
	auto& factory = ContextFactory::GetInstance();
	for (int state = 0; state < static_cast<int>(ContextState::kContextStateMaxSize); state++)
	{
		context_.push_back(factory.CreateContext(static_cast<ContextState>(state)));
	}

	ContextState state = ContextState::kContextTitleScreen;
	do
	{
		state = context_[static_cast<int>(state)]->Run();
	} while (state != ContextState::kContextExit);
}


int main()
{
	Game game;
	game.Launch();

	return 0;
}