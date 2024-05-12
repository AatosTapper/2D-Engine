#pragma once

// implements the static instance and a getter for it: S::instance()
#define IMPL_SINGLETON_DISPATCHER(S)    \
    static S &instance()                \
    {                                   \
        static S instance;              \
        return instance;                \
    }                                   

// Same as above but also implements function get_base_instance() that returns the instance
// casted to the base class.
#define IMPL_VIRTUAL_SINGLETON_DISPATCHER(DERIVED, BASE)    \
    IMPL_SINGLETON_DISPATCHER(DERIVED)                      \
    static BASE &get_base_instance()                        \
    {                                                       \
        return dynamic_cast<BASE&>(instance());             \
    }                                                       