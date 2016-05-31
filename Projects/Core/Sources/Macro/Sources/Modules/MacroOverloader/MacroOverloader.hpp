///	@file	MacroOverloader
///	@brief	Make it possible to overide specified macro.
#include <iostream>
using namespace std;

//	macro:
//		constants:
#define NE_MACRO_MAXIMUM_OF_ARGUMENT_COUNT	32

//		helpers:
//			VS HACK for EXPanding macro:
//				Visual Studio's compiler expand macro weirdly. 
//				So in order to get output same as GCCed ones, we should wrap
//				varidic arguments once again.
//				
//				these just happen to STRINGIZER macro as same. That's why we are
//				define STRINGIZER with what looks like useless macro __STRINGIZER.
#define _VS_EXP_HACK(...) __VA_ARGS__
//			concatenate:
#define NE_MACRO_CONCATENATE(x, y) x##y
//			stringizer:
#define __NE_MACRO_STRINGIZER(x)	#x
#define NE_MACRO_STRINGIZER(x)	__NE_MACRO_STRINGIZER(x)
//			make it count for arguments:
//				with this macro, you can know the count of varidic arguments.
//				But beware of ARGCOUNT2 because it's meaning somewhat different.
//				that means for count of arguments when you make two of them pair.
//				ARGCOUNT2 will be used only at specular circumstances.
#define _ARGCOUNT(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, N, ...)	N
#define NE_MACRO_ARGCOUNT(...)	_VS_EXP_HACK(_ARGCOUNT(__VA_ARGS__, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))
#define _ARGCOUNT2(_X1, _Y1, X2, _Y2, _X3, _Y3, _X4, _Y4, _X5, _Y5, _X6, _Y6, _X7, _Y7, _X8, _Y8, _X9, _Y9, _X10, _Y10, _X11, _Y11, _X12, _Y12, _X13, _Y13, _X14, _Y14, _X15, _Y15, _X16, _Y16, N, ...)	N
#define NE_MACRO_ARGCOUNT2(...)	_VS_EXP_HACK(_ARGCOUNT2(__VA_ARGS__, 16, 16, 15, 15, 14, 14, 13, 13, 12, 12, 11, 11, 10, 10, 9, 9, 8, 8, 7, 7, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 0, 0))

//		overloader:
//			Inspired by boost codes.
//			branching macros would be choosed by its argument count.
//			
//			usage:
//				//	define macro:
//				#define MyMacro_1(x) (x)+5
//				#define MyMacro_2(x, y) (x)+(y)
//				#define MyMacro(...)	NE_MACRO_OVERLOADER(MyMacro, __VA_ARGS__)
//
//				//	using:
//				cout << MyMacro(5) << ", " << MyMacro(3, 5) << "\n";
//
//			output:
//				10, 8
#define ___NE_MACRO_OVERLOADER(macro_name, argcount)	macro_name##_##argcount
#define __NE_MACRO_OVERLOADER(macro_name, argcount)	___NE_MACRO_OVERLOADER(macro_name, argcount)
#define NE_MACRO_OVERLOADER(macro_name, ...)	\
	__NE_MACRO_OVERLOADER(macro_name, NE_MACRO_ARGCOUNT(__VA_ARGS__))##(__VA_ARGS__)