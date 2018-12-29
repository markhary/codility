#ifndef MACROS_H
#define MACROS_H

#include <iostream>

#define PRINT_VECTOR(X) { \
    std::cout << #X << ": ["; \
    for (const auto &x: X) { std::cout << x << ", "; } \
    std::cout << "]" << std::endl; \
}

#define PRINT_VAR(X) { std::cout << #X << ": " << X << std::endl; }

#define SIZEOF(X) { std::cout << "sizeof(" << #X << "): " << sizeof(X) << " bytes" << std::endl; }

#endif
