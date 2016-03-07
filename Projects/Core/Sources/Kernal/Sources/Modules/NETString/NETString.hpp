#pragma once

namespace NE
{	
	//	Forward declaration only:
	//		We can't use typedef to forward-declareded one. It occurs error.
	//		So, there are so many circumstances to write down next following codes.
	//		This header is for when that happen.
	//		Of course, This header file doesn't care who import itself wants to
	//		have dependencies to those string collections or not.
	//		If you want to so, you have to include concrete headers too.
	//		Like,
	//			#include "../NETstring/NETString.hpp"	- forward-declaration only.
	//
	//			#include "../NEString/NEString.hpp"		- concrete one.
	//			#include "../NEWString/NEWString.hpp"	-		"
	class NEString;
	class NEWString;
#ifdef _UNICODE
	typedef NEWString NETString;
#else
	typedef NEString NETString;
#endif
}