#include "Class.hpp"

namespace wrd
{
#define THIS Class

    wbool THIS::operator==(const This& rhs) const { return &getName() == &rhs.getName(); }
    wbool THIS::operator!=(const This& rhs) const { return &getName() != &rhs.getName(); }

    const Classes& THIS::getLeafs() const
    {
        WRD_IS_THIS(const Classes)
        static Classes inner;
        //    TODO:
    }

    const Class& THIS::getClass() const
    {
        WRD_IS_THIS(const Class)
        return *this;
    }

    Result& THIS::init()
    {
        //    pre:
        //        exception:
        WRD_IS_SUPER(init)

        //    main:
        //        Object class should not initialize explicitly:
        //            or This makes recursive call.
        //            Because if we make a instance of TClass<Object>, it triggers Class::initialize inside of it.
        if(&getName() == &TClass<Thing>::getStaticName())
            return good;

        //  main:
        //        get Supers info from Super:
        //                at this point TClass<Super> is instantiated, and "Super" also is all of this sequences.
        Class& super = const_cast<Class&>(getSuper());
        super.init();
        //        constructing SuperClass:
        ClassSet& my_supers = _getSupers();
        my_supers = super._getSupers();
        my_supers.push(&super);
        //        notify to super:
        if(super._getSubs().push(*this) != wrongidx)
            return cancel;

        return good;
    }
    wbool THIS::isSuper(const Class& it) const
    {
        //  checking class hierarchy algorithm:
        //        Use the "Tier" of the class hierarchy info to check it.
        //        "Tier" means that how this class are inherited far from the Root class, that is, Object.
        //        So, if the "this" is a super of given object "it", its "tier"th super class
        //        would must be the class of "this".
        if(it.isNull()) return false;
        const Classes& its = it.getSupers();
        wcnt    my_tier = getClass().getSupers().size(),
                its_tier = its_supers.size();
        if(my_tier > its_tier) return false;


        //  main:
        const ClassBase& target = its_tier == my_tier ? it :
            static_cast<const Class&>(its[my_tier]);

        return getClass() == target;//  Remember. We're using Class as "Monostate".
    }
    Classes& THIS::_getSupers()
    {
        WRD_IS_THIS(Classes)
        return const_cast<Classes&>(getSupers());
    }
    Classes& THIS::_getSubs()
    {
        WRD_IS_THIS(Classes)
        return const_cast<Classes&>(getSubs());
    }
    Result& THIS::_initNodes()
    {
        _getNodes() = getSupers()[0].getNodes(); // getSupers()[0]은 바로 위의 부모클래스.
        return good;
    }
    wbool THIS::isSuper(const Class& it) const
    {
        //  checking class hierarchy algorithm:
        //        Use the "Tier" of the class hierarchy info to check it.
        //        "Tier" means that how this class are inherited far from the Root class, that is, Object.
        //        So, if the "this" is a super of given object "it", its "tier"th super class
        //        would must be the class of "this".
        if(it.isNull()) return false;
        const Classes& its = it.getSupers();
        wcnt    my_tier = getClass().getSupers().size(),
                its_tier = its_supers.size();
        if(my_tier > its_tier) return false;


        //  main:
        const ClassBase& target = its_tier == my_tier ? it :
            static_cast<const Class&>(its[my_tier]);

        return getClass() == target;//  Remember. We're using Class as "Monostate".
    }
    Classes& THIS::_getSupers()
    {
        WRD_IS_THIS(Classes)
        return const_cast<Classes&>(getSupers());
    }
    Classes& THIS::_getSubs()
    {
        WRD_IS_THIS(Classes)
        return const_cast<Classes&>(getSubs());
    }
    Result& THIS::_initNodes()
    {
        _getNodes() = getSupers()[0].getNodes(); // getSupers()[0]은 바로 위의 부모클래스.
        return good;
    }
    const Array& THIS::getVariables() const
    {
        WRD_IS_THIS(const Array)
        static Array inner; // means that this class isn't have any variables.
        return inner;
    }
}