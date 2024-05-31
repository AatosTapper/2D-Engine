#pragma once

// IF USED IN A CLASS, ACCESS IT'S VARIABLES LIKE THIS:

// Classname::instance().my_member_function();
// or
// Classname::instance().my_member_variable = 4.2f;


// implements the static instance and a getter for it: S::instance()
#define IMPL_SINGLETON_DISPATCHER(CLASS)    \
    static CLASS &instance()                \
    {                                       \
        static CLASS instance;              \
        return instance;                    \
    }                                   

// Same as above but also implements function get_base_instance() that returns the instance
// casted to the base class.
#define IMPL_VIRTUAL_SINGLETON_DISPATCHER(DERIVED, BASE)    \
    IMPL_SINGLETON_DISPATCHER(DERIVED)                      \
    static BASE &get_base_instance()                        \
    {                                                       \
        return dynamic_cast<BASE&>(instance());             \
    }

// delete copying and assigning
// IMPORTANT: class needs a constructor for this to work
#define IMPL_NO_COPY(CLASS)                 \
    CLASS(CLASS const&) = delete;           \
    void operator=(CLASS const&) = delete;