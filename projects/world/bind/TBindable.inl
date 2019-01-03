#pragma once

#include "../base/TGettable.inl"

namespace wrd
{
    class Res;
	class Instance;

	template <typename S=void>
    class TBindable : public TGettable<Instance, S>
    {	WRD_CLASS_DECL_2(TBindable<S>, TGettable<Instance WRD_COMMA() S>)
    public:
        operator wbool() const;
		This& operator=(const Instance& newone);
		This& operator=(const Instance* newone);
		template <typename V> wbool operator==(const TBindable<V>& rhs) const { return &this->get() == &rhs.get(); }
		template <typename V> wbool operator!=(const TBindable<V>& rhs) const { return ! operator==(rhs); }
		wbool operator!=(const This& rhs) const;

    public:
        virtual Res& bind(const Instance& new1) = 0;
		template <typename V> Res& bind(const TBindable<V>& rhs) { return bind(rhs.get()); }
        /// mostly, unbind is replacable to release() comletely.
        /// but some class(e.g. Refer) treat differently between unbind() and release().
        Res& bind(const Instance* new1);
        virtual Res& unbind() = 0;
        virtual wbool isBind() const = 0;
    };
}
