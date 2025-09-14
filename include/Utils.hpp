#ifndef UTILS_HPP
#define UTILS_HPP


#define TIME_BLOCK(name, code) \
    do { \
        auto start = std::chrono::steady_clock::now(); \
        code \
        auto end = std::chrono::steady_clock::now(); \
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); \
        std::cout << "[TIMER] " << name << " took " << duration << " ms\n"; \
    } while(0)


#endif