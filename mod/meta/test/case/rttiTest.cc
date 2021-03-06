#include "../common/dep.hpp"

struct noSuper {
    virtual void abstract() = 0;
    static void staticMethod() {}
};
struct hasSuper : public noSuper {
    typedef noSuper super;
    void abstract() {}
};

using namespace wrd;

TEST(rttiTest, basicBehavior) {
    ASSERT_FALSE(tifHasSuperTypedef<noSuper>::is);
    ASSERT_TRUE(tifHasSuperTypedef<hasSuper>::is);

    ASSERT_EQ(ttype<tadaptiveSuper<noSuper>::super>(), ttype<adam>());
    ASSERT_EQ(ttype<tadaptiveSuper<hasSuper>::super>(), ttype<noSuper>::get());

    ASSERT_FALSE((tifSub<noSuper, hasSuper>::is));
    ASSERT_TRUE((tifSub<hasSuper, noSuper>::is));

    void* instance = tinstanceMaker<noSuper>::make();
    WRD_I("instance=%x", instance);
    ASSERT_FALSE(instance);
    instance = tinstanceMaker<hasSuper>::make();
    WRD_I("instance=%x", instance);
    ASSERT_TRUE(instance);

    ASSERT_FALSE(tifHasSuperTypedef<noSuper>::is);
    ASSERT_TRUE(tifHasSuperTypedef<hasSuper>::is);

    ASSERT_EQ(typeid(tadaptiveSuper<noSuper>::super), typeid(adam));
    ASSERT_EQ(typeid(tadaptiveSuper<hasSuper>::super), typeid(noSuper));
}

TEST(rttiTest, superTypeDefTest) {
    struct A {};
    struct customA {
        typedef struct myType : type {
            int foo() {
                return 22;
            }
        } superType;
    };

    ASSERT_EQ(typeid(tsuperTypeDef<A>::is), typeid(type));
    ASSERT_EQ(typeid(tsuperTypeDef<customA>::is), typeid(customA::myType));
}
