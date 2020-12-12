#pragma once

#include "../common.hpp"

namespace wrd { namespace meta {
	///	@remark	Type returning TType<Type> as result of getType()
	///			because this func always returns metaclass no matter of what This type is,
	///			users need to care about getting meta of metaclass on calling getType().
	///			for example,
	///				Thing& thing1 = ...; // let's assume that got from outside.
	///				Object obj;
	///
	///				wbool compare = obj.isSub(thing1.getType()); // user intend to get class of Thing.
	///				// however, value 'compare' will definitely be false if
	///				// thing was actually a retrived one by calling Thing.getType() before.
	///
	///				// because Type::getType() will return TType<TType<T> >,
	///				// that stmt will be translated that checks object vs TType<T>.
    class Type {
        WRD_DECL_THIS(Type)

    public:
        virtual wbool operator==(const This& rhs) const;
        wbool operator!=(const This& rhs) const;

        virtual wbool isTemplate() const = 0;
        virtual wbool isAbstract() const = 0;
        virtual const std::string& getName() const = 0;
        virtual void* make() const = 0;
		virtual wcnt getSize() const = 0;
		virtual wbool init();
        virtual wbool rel();
        virtual const Type& getSuper() const = 0;
        virtual const wbool& isInit() const = 0;
		const Types& getLeafs() const;
        const Types& getSubs() const {
            return (const_cast<This*>(this))->_getSubs();
        }
        const Types& getSupers() const {
            return (const_cast<This*>(this))->_getSupers();
        }

        wbool isSuper(const Type& it) const;
		template <typename T> wbool isSuper() const { return isSuper(T::get()); }
		wbool isSub(const Type& it) const { return it.isSuper(*this); }
		template <typename T> wbool isSub() const { return T::get().isSuper(*this); }

    protected:
		//	Type:
		virtual Types& _getSupers() = 0;
		virtual Types& _getSubs() = 0;
        void _setInit(wbool newState) {
            const wbool& res = isInit();
            wbool& isInit = const_cast<wbool&>(res);

            isInit = newState;
        }

    private:
        wbool _logInitOk(wbool res);
    };
}}
