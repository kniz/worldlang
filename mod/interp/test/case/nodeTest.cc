#include "../common/dep.hpp"

using namespace wrd;
using namespace std;

namespace {
    class myFunc : public func {
        WRD_CLASS(myFunc, func)

    public:
        myFunc(): super("myFunc") {}

        void setUp() {
            _executed = false;
        }

        str run(ncontainer& args) override {
            WRD_I("hello world!");
            _executed = true;
            return str();
        }

        using super::subs;
        ncontainer& subs() override { return _shares; }

        wbool isRun() const {
            return _executed;
        }

        const wtype& getReturnType() const override {
            return ttype<node>::get();
        }

        const wtypes& getTypes() const override {
            static wtypes inner;
            if(inner.size() == 0)
                inner.push_back(&ttype<obj>::get());

            return inner;
        }

    protected:
        str _onRun(ncontainer& args) override {
            return str();
        }

    private:
        wbool _executed;
        narr _shares;
    };
}

TEST(NodeTest, testManuallyMakeNodeStructure) {
    // prepare:
    tstr<nchain> frameEmulator;
    obj obj;
    myFunc func;
    WRD_E("func.tag.chkId=%d", func.getBindTag().getId().chkN);

    obj.subs().add(func);
    myFunc funcOffunc;
    func.subs().add(funcOffunc);

    WRD_E("func.tag.chkId=%d", func.getBindTag().getId().chkN);
    WRD_E("funcOffunc.tag.chkId=%d", funcOffunc.getBindTag().getId().chkN);

    // when:
    frameEmulator.bind(obj.subs());
    //  push another:
    nchain* chnOffunc = new nchain(func.subs());
    chnOffunc->link(*frameEmulator);
    frameEmulator.bind(*chnOffunc);

    WRD_E("func.tag.chkId=%d", func.getBindTag().getId().chkN);
    WRD_E("funcOffunc.tag.chkId=%d", funcOffunc.getBindTag().getId().chkN);

    // then:
    ASSERT_EQ(chnOffunc->getLen(), 2);
    ASSERT_EQ(chnOffunc->getLen(), 2);
    ASSERT_EQ(chnOffunc->getLen(), 2);

    int n=0;
    for(wrd::iterator e=chnOffunc->head(); e ;e++)
        WRD_E("[%d]=%s", n++, e->getType().getName().c_str());

    WRD_E("func.tag.chkId=%d", func.getBindTag().getId().chkN);
    WRD_E("funcOffunc.tag.chkId=%d", funcOffunc.getBindTag().getId().chkN);

    ASSERT_EQ(n, 2);
    WRD_E("func.tag.chkId=%d", func.getBindTag().getId().chkN);
    WRD_E("funcOffunc.tag.chkId=%d", funcOffunc.getBindTag().getId().chkN);
}

TEST(NodeTest, testManualNativefuncCall) {
    // prepare:
    myFunc func;

    obj obj;
    obj.subs().add(func);

    narr args;
    args.add(obj);
    narr subs = obj.sub(func.getName(), args);
    ASSERT_EQ(subs.getLen(), 1);
    ASSERT_TRUE(subs[0].canRun(args));

    // when:
    func.setUp();
    subs[0].run(args);
    ASSERT_TRUE(func.isRun());
}