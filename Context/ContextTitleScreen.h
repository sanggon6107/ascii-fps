#pragma once
#include "IContext.h"

class ProcTitleScreen : public IContext
{
public :
	ProcTitleScreen();
	ContextState Run() override;
private:

};