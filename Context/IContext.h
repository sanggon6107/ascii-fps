#pragma once
#include <windows.h>
#include <wchar.h>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <memory>

#include "../CommonLib/CommonUtil.h"
#include "../CommonLib/MapCreator.h"
#include "../CommonLib/ScreenMgr.h"


using namespace std;
typedef shared_ptr<IContext>(*CREATOR)();

class ContextFactory
{
	MAKE_SINGLETON(ContextFactory)
public:
	shared_ptr<IContext> CreateContext(ContextState context_state)
	{
		shared_ptr<IContext> ptr = nullptr;
		auto ret = create_map_.find(context_state);

		if (ret == create_map_.end()) return nullptr;

		ptr = create_map_[context_state]();

		return ptr;
	}

	void Register(ContextState context_state, CREATOR f)
	{
		create_map_[context_state] = f;
	}
private:

	map<ContextState, CREATOR> create_map_;
};

class FactoryRegister
{
public:
	FactoryRegister(ContextState context_state, CREATOR creator)
	{
		auto& factory = ContextFactory::GetInstance();
		factory.Register(context_state, creator);
	}
};


class IContext
{
public:
	virtual ContextState Run() = 0;
	virtual ~IContext() {}
protected:
	IContext();
	int screen_width_;
	int screen_height_;
	shared_ptr<wchar_t[]> screen_;
};
