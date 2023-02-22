#include "Game.h"

Game::Game() : context_factory_(&ContextFactory::GetInstance())
{
	for (int state = 0; state < static_cast<int>(ContextState::kContextStateMaxSize); state++)
	{
		context_.push_back(context_factory_->CreateContext(static_cast<ContextState>(state)));
	}
}

void Game::Launch()
{
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