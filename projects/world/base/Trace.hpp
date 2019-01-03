#pragma once

#include "Instance.hpp"
#include "../bind/TBindable.inl"

namespace wrd
{
	class Block;

    class Trace : public TBindable<Instance>
    {	WRD_CLASS_DECL(Trace, TBindable<Instance>)
    public:
        Trace();
        Trace(Id id, wcnt serial);

	public:
		wbool operator==(const This& rhs);
		wbool operator!=(const This& rhs);

    public: //  Trace:
        wcnt getSerial() const;
		//  Thing:
        virtual Res& release();

	protected://Trace:
        Res& _setSerial(wcnt new1);

    private:
        wcnt _serial;
    };
}