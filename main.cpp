#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <cassert>
#include <cstring>

#include "quicksort.h"

std::random_device device;
std::mt19937 mt(device());

const int testSize = 5;

double oneTest(std::vector<std::vector<int>> &arr, void(*func)(std::vector<int> &, int, int), std::string nm) {
    std::cout << nm << " quicksort times: " << std::endl;
    double sum = 0;
    for (int i = 0; i < testSize; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        func(arr[i], 0, SIZE_TEST_ARRAY);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = (end - start);
        std::cout << i + 1 << " " << elapsed.count() << " seconds" << std::endl;
        sum += elapsed.count();
    }
    double meanTime = sum / testSize;
    std::cout << nm << " quicksort mean times: " << meanTime << std::endl;
    return meanTime;
}


void correctnessTest() {
    int corSize = 1e6;
    std::vector<int> arr(corSize);
    std::vector<int> arrCopy(corSize);
    std::vector<int> arrCopyCopy(corSize);
    for (int i = 0; i < corSize; ++i) {
        arr[i] = mt();
        arrCopy[i] = arr[i];
        arrCopyCopy[i] = arr[i];
    }
    std::sort(arr.begin(), arr.end());
    sequentiallQuickSort(arrCopy, 0, corSize);
    parallelQuickSort(arrCopyCopy, 0, corSize);
    for (int i = 0; i < corSize; ++i) {
        assert(arr[i] = arrCopy[i]);
        assert(arr[i] = arrCopyCopy[i]);
    }
    std::cout << "Correctness test PASSED" << std::endl;
}

void speedTest() {
    std::vector<std::vector<int>> arr(testSize);
    std::vector<std::vector<int>> arrCopy(testSize);
    for (int i = 0; i < testSize; i++) {
        arr[i] = std::vector<int>(SIZE_TEST_ARRAY);
        arrCopy[i] = std::vector<int>(SIZE_TEST_ARRAY);
    }
    for (int i = 0; i < testSize; ++i) {
        for (int j = 0; j < SIZE_TEST_ARRAY; ++j) {
            arr[i][j] = mt();
            arrCopy[i][j] = arr[i][j];
        }
    }
    std::cout << "End generate for speed test" << std::endl;
    double seq = oneTest(arrCopy, sequentiallQuickSort, "sequential");
    tbb::global_control control(tbb::global_control::max_allowed_parallelism, 4);
    double par = oneTest(arr, parallelQuickSort, "parallel");
    double ratio = seq / par;
    std::cout << "ratio: " << ratio << std::endl;
    assert(ratio > 3);
    std::cout << "Speed test PASSED" << std::endl;

}

int main() {
    correctnessTest();
    speedTest();
    return 0;
}