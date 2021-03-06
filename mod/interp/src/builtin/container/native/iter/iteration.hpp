#pragma once

#include "titerable.hpp"
#include "../../../../ast/clonable.hpp"

namespace wrd {

    class node;
    class iteration : public instance, public titerable<instance>, public clonable {
        WRD_INTERFACE(iteration, instance)
        template <typename T>
        friend class titer;

    public:
        wbool isFrom(const ncontainer& rhs) const override;

    };
}
