#pragma once

#ifndef SILENCE_TEXT

#include <iostream>
#include <chrono>

#define LOG(a) std::cout << "[Log] " << a << "\n"
#define LOG_VARIABLE(a) std::cout << "[Log_Var] " << #a << " = " << a << "\n"

#define ERR(message) \
    std::cerr << "[Error] " << message \
    << "\n  File: " << __FILE__ \
    <<  "\n  Function: " << __FUNCTION__ \
    << "\n  Line: " << __LINE__ << "\n"

#define WARN(message) \
    std::cerr << "[Warning] " << message \
    << "\n  File: " << __FILE__ \
    << "\n  Function: " << __FUNCTION__ \
    << "\n  Line: " << __LINE__ << "\n"

#define INFO(message) \
    std::cout << "[Info] " << message \
    << "\n  File: " << __FILE__ \
    << "\n  Line: " << __LINE__ << "\n"

#define ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            ERR("[Assertion failed] " << message); \
            std::terminate(); \
        } \
    } while (0)

#define TRACK_PERFORMANCE(message, code) \
    do { \
        auto start = std::chrono::high_resolution_clock::now(); \
        code; \
        auto end = std::chrono::high_resolution_clock::now(); \
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(); \
        std::cout << message << " - Duration: " << duration << " microseconds\n"; \
    } while (0)

#else

#define LOG(a)
#define LOG_VARIABLE(a)
#define ERR(message)
#define WARN(message)
#define INFO(message)
#define ASSERT(condition, message)
#define TRACK_PERFORMANCE(message, code)

#endif