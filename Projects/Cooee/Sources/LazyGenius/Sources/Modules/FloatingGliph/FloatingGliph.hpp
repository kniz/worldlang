#pragma once

#include "../Gliph/Gliph.hpp"

namespace LG
{
	class NE_DLL FloatingGliph: public Gliph
	{
	public:
		FloatingGliph(type_ushort new_x = 0, type_ushort new_y = 0, type_ushort new_width = 0, type_ushort new_height = 0,
			type_ushort new_fore = LIGHTGRAY, type_ushort new_back = 0, const NEString& new_text = "");
		FloatingGliph(const FloatingGliph& rhs);

		virtual void onDraw();
		virtual void onKeyPressed(int inputed);

		int term_for_hiding;
	};
}