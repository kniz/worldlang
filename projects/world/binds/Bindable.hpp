#pragma once

#include "../wrd-commons.hpp"

namespace wrd
{
    class Instance;
    class Result;
    class Bindable
    {
    public:
        operator wbool() const;

    public:
        virtual Result& bind(Instance& new1) = 0;
        /// mostly, unbind is replacable to release() comletely.
        /// but some class(e.g. Refer) treat differently between unbind() and release().
        Result& bind(Instance* new1);
        virtual Result& unbind() = 0;
        virtual wbool isBind() const = 0;
		const Instance& get() const;
		Instance& get();

	protected:
		virtual Instance& _get() = 0;
    };
}