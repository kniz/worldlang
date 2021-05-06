#pragma once

#include "ncontainer.hpp"
#include "../../../ast/node.hpp"

namespace wrd {

    class nchain : public ncontainer {
        WRD_CLASS(nchain, ncontainer)

        friend class nchainIteration;
        class nchainIteration : public iteration {
            WRD_CLASS(nchainIteration, iteration)
            friend class nchain;

        public:
            nchainIteration(const nchain& own, const nchain& iteratingChain, const iterator& conIter)
                : _own(const_cast<nchain&>(own)), _ownIter(iteratingChain), _iter(conIter) {
                    if(!_iter) next(1);
                }

            wbool isEnd() const override {
                return !_iter;
            }

            wcnt next(wcnt step) override {
                if(step <= 0) return 0;
                wcnt stepped = _iter.next(step),
                     remain = step - stepped;
                if(remain == 0) return stepped;

                // arr iteration has reached to tail of the arr:
                _ownIter = _ownIter->_next;
                if(!_ownIter) return stepped;
                _iter = _ownIter->_arr->begin();
                remain--;
                return stepped + next(remain);
            }

            node& get() override {
                return *_iter;
            }

            ncontainer& getContainer() override { return _own; }
            iterator& getContainerIter() { return _iter; }

        protected:
            wbool _onSame(const typeProvidable& rhs) const override {
                if(!super::_onSame(rhs)) return false;

                const me& cast = (const me&) rhs;
                if(nul(cast)) return false;

                return _iter == cast._iter;
            }

        private:
            nchain& _own;
            tstr<nchain> _ownIter;
            iterator _iter;
        };

    public:
        nchain();
        explicit nchain(const ncontainer& con): _arr(con) {}

        wcnt len() const override;

        using super::set;
        wbool set(const iterator& at, const node& new1) override;

        iterator begin() const override;
        iterator end() const override;
        iterator last() const override;
        iterator iter(wcnt step) const override;

        using super::add;
        wbool add(const iterator& at, const node& new1) override;
        wbool add(const node& new1) override;

        using super::del;
        wbool del() override;
        wbool del(const node& it) override;
        wbool del(const iterator& at) override;
        wcnt del(const iterator& from, const iterator& end) override;

        tstr<nchain> link(const ncontainer& new1);
        wbool link(const nchain& new1);
        wbool unlink();

        void empty() override;

        ncontainer& getContainer() { return *_arr; }
        const ncontainer& getContainer() const { return *_arr; }
        nchain& getNext() { return *_next; }
        const nchain& getNext() const { return *_next; }

        using super::each;
        template <typename T>
        void each(const iterator& from, const iterator& end, std::function<wbool(nchain&, T&)> l) {
            const nchain* endChn = nullptr;
            if(!nul(end)) {
                endChn = &end.getContainer().cast<nchain>();
                if(nul(endChn)) return;
            }

            for(nchain* e = (nchain*) &from.getContainer().cast<nchain>();
                !nul(e) && e != endChn;
                e = &(*e->_next)) {
                auto& arr = e->_arr->cast<T>();
                if(nul(arr)) continue;

                if(!l(*e, arr)) break;
            }
        }
        /// @param  end Nullable. meaning of the end of nchain list.
        template <typename T>
        void each(const iterator& from, const iterator& end, std::function<wbool(const nchain&, const T&)> l) const {
            const nchain* endChn = nullptr;
            if(!nul(end)) {
                endChn = &end.getContainer().cast<nchain>();
                if(nul(endChn)) return;
            }

            for(const nchain* e = &from.getContainer().cast<nchain>();
                !nul(e) && e != endChn;
                e = &(*e->_next)) {
                auto& arr = e->_arr->cast<T>();
                if(nul(arr)) continue;

                if(!l(*e, arr)) break;
            }
        }
        template <typename T>
        void each(std::function<wbool(nchain&, T&)> l) {
            each(begin(), nulOf<iterator>(), l);
        }
        template <typename T>
        void each(std::function<wbool(const nchain&, const T&)> l) const {
            each(begin(), nulOf<iterator>(), l);
        }

        /// returned deep cloned of this object.
        /// @remark even if the chain has already linked to the another chain instance,
        ///         only this object will be deep cloned. cloned instance has the same linkage like
        ///         which the original chain object has.
        tstr<instance> deepClone() const override {
            nchain* ret = new nchain(getContainer().deepClone()->cast<ncontainer>());
            ret->link(getNext());
            return tstr<instance>(ret);
        }

    private:
        iterator& _getContainerIterFromChainIter(const iterator& wrap) {
            if(nul(wrap)) return nulOf<iterator>();
            if(!wrap._step->getType().isSub<nchainIteration>()) return nulOf<iterator>();
            nchainIteration& cast = (nchainIteration&) *wrap._step;
            if(nul(cast)) return nulOf<iterator>();

            return cast.getContainerIter();
        }
        nchain& _getLastChain();
        const nchain& _getLastChain() const WRD_UNCONST_FUNC(_getLastChain())

        tstr<ncontainer> _arr;
        tstr<nchain> _next;
    };
}
