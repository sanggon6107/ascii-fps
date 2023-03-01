#pragma once

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 80

#define MAP_WIDTH 17
#define MAP_HEIGHT 17


#define MAKE_SINGLETON(classname)			     \
private :										 \
	classname();								 \
	classname(const classname& c) = delete;		 \
	void operator=(const classname&) = delete;   \
public :										 \
	static classname& GetInstance()				 \
	{											 \
		static classname instance;				 \
		return instance;						 \
	}											 

#define DECLARE_CONTEXT_FACTORY(class_name)								       \
public:																  	       \
	static shared_ptr<IContext> Create() { return make_shared<class_name>(); } \
	static FactoryRegister rs;

#define IMPLEMENT_CONTEXT_FACTORY(context_state, class_name)			       \
FactoryRegister class_name::rs(context_state, &class_name::Create);


enum class ContextState : int { kContextGamePlay, kContextTitleScreen, kContextExit, kContextStateMaxSize };