#pragma once

#include "VSExpHack.hpp"

//		make it count for arguments:
#define _ARGCOUNT(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, N, ...)	N
#define WRD_ARGCOUNT(...)	WRD_VS_EXP_HACK(_ARGCOUNT(__VA_ARGS__, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))
#define _ARGCOUNT2(_X1, _Y1, X2, _Y2, _X3, _Y3, _X4, _Y4, _X5, _Y5, _X6, _Y6, _X7, _Y7, _X8, _Y8, _X9, _Y9, _X10, _Y10, _X11, _Y11, _X12, _Y12, _X13, _Y13, _X14, _Y14, _X15, _Y15, _X16, _Y16, N, ...)	N
#define WRD_ARGCOUNT2(...)	WRD_VS_EXP_HACK(_ARGCOUNT2(__VA_ARGS__, 16, 16, 15, 15, 14, 14, 13, 13, 12, 12, 11, 11, 10, 10, 9, 9, 8, 8, 7, 7, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 0, 0))
