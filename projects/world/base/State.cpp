#include "State.hpp"
#include "../meta.hpp"
#include "../pretypes.hpp"

namespace wrd
{
#define THIS State
	WRD_CLASS_DEF(THIS)

	wbool THIS::isInit() { return _is_init; }

	Res& THIS::init()
	{
		WRD_ASSERT(isInit(), wascancel)
		return _setInit(true);
	}

	Res& THIS::release()
	{
		_setInit(false);
		return Super::release();
	}

	Res& THIS::_setInit(wbool new1)
	{
		_is_init = new1;
		return wasgood;
	}
}