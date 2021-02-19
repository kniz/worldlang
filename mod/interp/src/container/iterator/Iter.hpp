#pragma once

#include "Iteration.hpp"

namespace wrd {

    class Iter : public Iterable, public Clonable, public TypeProvidable {
        WRD_CLASS(Iter)
        friend class Iteration;
        friend class NArr;

    public:
        Iter() {}
        Iter(Iteration* newStep): _step(newStep) {}
        Iter(const Iter& rhs) {
            _assign(rhs);
        }

        /// @return true if there are more data to proceed
        wbool operator==(const This& rhs) const { return _step == rhs._step; }
        wbool operator!=(const This& rhs) const { return !operator==(rhs); }
        wbool operator++() { return next(); }
        wbool operator--() { return prev(); }
        virtual Node& operator*() { return get(); }
        virtual Node* operator->() { return &get(); }
        virtual const Node& operator*() const WRD_UNCONST_FUNC(operator*())
        virtual const Node* operator->() const WRD_UNCONST_FUNC(operator->())
        operator wbool() { return !isEnd(); }

        wbool isFrom(const Containable& it) const override {
            if(!_step) return false;
            return _step->isFrom(it);
        }

        wbool isEnd() const override {
            if(!_step) return true;
            return _step->isEnd();
        }

        wbool next() override {
            if(!_step) return false;
            return _step->next();
        }

        wbool prev() override {
            if(!_step) return false;
            return _step->prev();
        }

        Node& get() override {
            if(!_step) return nulOf<Node>();
            return _step->get();
        }

    private:
        This& _assign(const This& rhs) {
            _step.bind((Iteration*) _step->clone());
            return *this;
        }

    protected:
        TStr<Iteration> _step;
    };

}
