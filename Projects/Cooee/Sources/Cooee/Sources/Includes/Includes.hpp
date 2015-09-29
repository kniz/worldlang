#pragma once

//	인클루드:	//////////////////////////////////////////////////////////////////////////
#include <iostream>
using namespace std;
#include <Editor/Sources/EntryPoints/Headers.hpp>
#include "../../../LazyGenius/Sources/EntryPoints/Headers.hpp"
//#include <CoreTester/Sources/EntryPoints/Headers.hpp>
using namespace NE;
using LG::Window;
using LG::Gliph;
using LG::ListGliph;
using LG::TextGliph;
using LG::WHITE;
using LG::RED;
using LG::BLACK;
using LG::LIGHTRED;
using LG::CYAN;
using LG::LIGHTCYAN;
using LG::DARKGRAY;
using LG::GREEN;
using LG::LIGHTGREEN;
using LG::LIGHTGRAY;
using LG::MAGENTA;
using LG::LIGHTMAGENTA;
using LG::YELLOW;
using LG::BLUE;
using LG::LIGHTBLUE;
using LG::BROWN;
using LG::BACKSPACE;
using LG::UP;
using LG::DOWN;
using LG::REMOVE;
using LG::ADD;
using LG::CONFIRM;
using LG::CANCEL;
using LG::RIGHT;
using LG::LEFT;
using LG::CLOSE;
using LG::ENTER;
using LG::ADD;
using LG::REMOVE;
using LG::COPY;
using LG::PASTE;
using LG::HELP;
using LG::COMMAND;
using LG::MAP;
using LG::CUT;

//	디파인:		//////////////////////////////////////////////////////////////////////////
#define _NAME			"Cooee"
#define _DEVELOPER		"kniz"
#define _REVISION		1
#define _VERSION			"0.0.1a.316.Lazy Genius"
#define _DATE			"2014-06-07"
#define _WEBSITE			"http://www.kniz.net"
#define _EMAIL			"kniz@kniz.net"
#define _MAX_BUFFER		256
#define _VERSION_STRING	_NAME##" v"##_VERSION##" Update"