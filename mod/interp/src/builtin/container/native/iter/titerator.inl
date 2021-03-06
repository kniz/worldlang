#pragma once

#include "titer.hpp"
#include "../../../../ast/node.hpp"

namespace wrd {

#define TEMPL template <typename T>
#define ME titer<T>

    TEMPL
    T& ME::get() {
        if(!_step) return nulOf<T>();

        while(!isEnd()) {
            T& ret = _step->get().cast<T>();
            if(!nul(ret)) return ret;

            next(1);
        }

        return nulOf<T>();
    }


#undef ME
#undef TEMPL
}

