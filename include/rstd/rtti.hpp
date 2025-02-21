#pragma once

#include <rstd/types.hpp>
#include <type_traits>

namespace rstd::rtti {

/**
 * Reflection data about the class hierarchy of a type.
 * TODO: support multiple inheritance?
 */
struct ClassInfo {
    constexpr ClassInfo(const char* name, const ClassInfo* parent) 
        : m_Name(name), m_Parent(parent)
    {
    }

    /**
     * The name of this class.
     */
    [[nodiscard]]
    const char* name() const { return m_Name; }

    /**
     * The parent class of this class.
     */
    [[nodiscard]]
    const ClassInfo* parent() const { return m_Parent; }

private:
    const char* m_Name{nullptr};
    const ClassInfo* m_Parent{nullptr};
};

template<typename TDestClass, typename TSourceClass>
TDestClass* dynamicCast(TBaseClass* p) {
    static_assert(std::is_base_of_v<TSourceClass, TDestClass>, "TDestClass must derive from TSourceClass");
    const ClassInfo* t = &TDestClass::staticClassInfo;
    while (t) {
        if (t == &TSourceClass::staticClassInfo) {
            return reinterpret_cast<TClass*>(p);
        }

        t = t->parent();
    }

    return nullptr;
}

template<typename TDestClass, typename TSourceClass>
const TDestClass* dynamicCast(const TSourceClass* p) {
    return dynamicCast(reinterpret_cast<TSourceClass*>(p));
}

}

#define DECLARE_CLASSINFO_NOBASE(clazz)             \
    static constexpr rstd::rtti::ClassInfo staticClassInfo{#clazz, nullptr}

#define DECLARE_CLASSINFO(clazz, parent)            \
    static constexpr rstd::rtti::ClassInfo staticClassInfo{#clazz, &parent::staticClassInfo}
