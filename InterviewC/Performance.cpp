#include <ctime>
#include <memory>
#include <iostream>

// Plain C pointers are about 8% faster than unique_ptr.
void unique_ptr_performance() {
    clock_t begin = clock();

    auto uptr = std::unique_ptr<volatile int>(new int());
    auto cptr = new volatile int();

    const unsigned long long iterations = 1000 * 1000 * 1000;
    const unsigned long long iteration_factor = 10;
    
    for (auto i = 0; i < iterations; ++i) 
        for (auto i = 0; i < iteration_factor; ++i)
          //*cptr = 0xFF;
          *uptr = 0xFF;

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    std::cout << elapsed_secs << std::endl;
}
