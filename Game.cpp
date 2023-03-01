#include "Game.h"

Game::Game()
{
	auto& factory = ContextFactory::GetInstance();
	for (int state = 0; state < static_cast<int>(ContextState::kContextStateMaxSize); state++)
	{
		context_.push_back(factory.CreateContext(static_cast<ContextState>(state)));
	}
	current_context_state_ = context_[static_cast<int>(ContextState::kContextTitleScreen)];
}


void Game::Launch()
{
	ContextState next_state;
	do
	{
		next_state = current_context_state_->Run();
		current_context_state_ = context_[static_cast<int>(next_state)];
	} while (next_state != ContextState::kContextExit);
}


int main()
{
	Game game;
	game.Launch();

	return 0;
}