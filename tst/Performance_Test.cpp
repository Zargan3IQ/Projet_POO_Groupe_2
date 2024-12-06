#include <iostream>
#include <chrono>
#include "../src/grid.h"

static void testPerformance() {
    const int width = 500;
    const int height = 500;
    const int iterations = 50   ;

    grid g(width, height);

    std::vector initialState(height, std::vector<int>(width, 0));

    g.initializeWithState(initialState);

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < iterations; ++i) {
        g.update();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Performance test with multithreading : " << iterations << " iterations on a "
              << width << "x" << height << " grid took "
              << duration.count() << " seconds." << std::endl;

    g.initializeWithState(initialState);

    auto start2 = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < iterations; ++i) {
        g.updateTest();
    }

    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration2 = end2 - start2;

    std::cout << "Performance test without multithreading : " << iterations << " iterations on a "
              << width << "x" << height << " grid took "
              << duration2.count() << " seconds." << std::endl;

}
