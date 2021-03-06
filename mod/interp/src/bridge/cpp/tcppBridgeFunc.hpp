#pragma once

#include "../../ast/func.hpp"
#include "marshaling.hpp"

namespace wrd {

    template <typename Ret, typename T, typename... Args>
    class tcppBridgeFuncBase : public func {
        WRD_INTERFACE(tcppBridgeFuncBase, func)
    protected:
        typedef Ret (T::*fptrType)(Args...);

    public:
        tcppBridgeFuncBase(const std::string& name, fptrType fptr): super(name), _fptr(fptr) {}

        static_assert(allTrues<(sizeof(tmarshaling<Args>::canMarshal() ) == sizeof(metaIf::yes))...>::value,
            "can't marshal one of this func's parameter types.");

    protected:
        wbool _onInFrame(frame& sf, const ncontainer& args) override { return true; }
        wbool _onOutFrame(frame& sf, const ncontainer& args) override { return true; }

        const wtype& getReturnType() const override {
            return ttype<typename tmarshaling<Ret>::mgdType>::get();
        }

        const wtypes& getTypes() const override;

    protected:
        fptrType _fptr;
    };

    template <typename Ret, typename T, typename... Args>
    class tcppBridgeFunc : public tcppBridgeFuncBase<Ret, T, Args...> {
        typedef tcppBridgeFuncBase<Ret, T, Args...> __super;
        WRD_CLASS(tcppBridgeFunc, __super)

    public:
        tcppBridgeFunc(const std::string& name, typename __super::fptrType fptr): super(name, fptr) {}

    protected:
        str _onCast(narr& args) override {
            return _marshal(args, std::index_sequence_for<Args...>());
        }

        template <size_t... index>
        str _marshal(narr& args, std::index_sequence<index...>);
    };

    template <typename T, typename... Args>
    class tcppBridgeFunc<void, T, Args...> : public tcppBridgeFuncBase<void, T, Args...> {
        typedef tcppBridgeFuncBase<void, T, Args...> __super;
        WRD_CLASS(tcppBridgeFunc, __super)

    public:
        tcppBridgeFunc(const std::string& name, typename __super::fptrType fptr): super(name, fptr) {}

    protected:
        str _onCast(narr& args) override {
            return _marshal(args, std::index_sequence_for<Args...>());
        }

        template <size_t... index>
        str _marshal(narr& args, std::index_sequence<index...>);
    };
}
