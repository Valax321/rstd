#include <rstd/rtti.hpp>

#include <cstdio>

using namespace rstd;

struct MyBaseClass {
    DECLARE_CLASSINFO_NOBASE(MyBaseClass);

    int test() {
        return 0;
    }

private:
    float m_FloatValue;
    bool m_BoolValue;
};

struct MyDerivedClass : public MyBaseClass {
    DECLARE_CLASSINFO(MyDerivedClass, MyBaseClass);

    int test2() const {
        return m_IntValue;
    }

private:
    s32 m_IntValue;
};

int main() {
    MyBaseClass* b = new MyDerivedClass();
    if (auto* d = rtti::dynamicCast<MyDerivedClass>(b)) {
        std::printf("dynamicCast correct passed test\n");
        return 0;
    }

    return 1;
}
