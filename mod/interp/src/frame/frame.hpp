#pragma once

#include "../ast/node.hpp"
#include <gtest/gtest_prod.h>

struct frameTest;

namespace wrd {

    class frame : public node { // TODO: may be obj, not node.
        WRD_CLASS(frame, node)
        friend struct ::frameTest;

    public:
        ~frame() {
            _rel();
        }

        wbool add(ncontainer& con) {
            return add(*nchain::wrap(con));
        }

        wbool add(nchain& new1) {
            WRD_DI("Stack(%x).push(Chain(%x))", this, &new1);

            if(_links)
                new1.link(*_links);
            return _links.bind(new1);
        }

        tstr<nchain> del() {
            tstr<nchain> ret;
            if(_links) {
                ret.bind(*_links);
                _links.bind(_links->getNext());
            }
            WRD_DI("Stack(%x).pop(%x), .next=%x", &ret.get(), &*_links);
            return ret;
        }

        // node:
        using node::subs;
        ncontainer& subs() override { return *_links; }
        wbool canRun(const wtypes& types) const override { return false; }
        str run(const ncontainer& args) override { return str(); }
        void rel() override {
            _rel();
            super::rel();
        }

    private:
        void _rel() {
            _links.unbind();
        }

        tstr<nchain> _links;
    };

}
