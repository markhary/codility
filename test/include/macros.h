#ifndef CODILITY_MACROS_H
#define CODILITY_MACROS_H

#include <iostream>
#include <chrono>

#define PRINT_VECTOR(X) { \
    std::cout << #X << " = ["; \
    for (int i=0; i<(int)X.size(); i++ ) { \
        std::cout << X[i] << ( (i != ((int)X.size()-1)) ? ", " : ""); \
    } \
    std::cout << "];" << std::endl; \
}

#define PRINT_VAR(X) { std::cout << #X << " = " << X << ";" << std::endl; }

#define SIZEOF(X) { std::cout << "sizeof(" << #X << "): " << sizeof(X) << " bytes" << std::endl; }

#endif
