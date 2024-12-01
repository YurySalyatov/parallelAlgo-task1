#include <vector>
#include<tbb/tbb.h>

const int SIZE_TEST_ARRAY = 1e8;
const int B = SIZE_TEST_ARRAY / 1e5;


void sequentiallQuickSort(std::vector<int>& arr, int left, int right) {
    if (right - left <= 1) return;
    int pivot = arr[right - 1];
    int i = left;
    for (int j = left; j < right - 1; j++) {
        if (arr[j] < pivot) {
            std::swap(arr[i], arr[j]);
            i++;
        }
    }
    std::swap(arr[i], arr[right - 1]);
    sequentiallQuickSort(arr, left, i);
    sequentiallQuickSort(arr, i + 1, right);
}

void parallelQuickSort(std::vector<int>& arr, int left, int right) {
    if(right - left <= B) {
        sequentiallQuickSort(arr, left, right);
        return;
    }
    int pivot = arr[right - 1];
    int i = left;
    for (int j = left; j < right - 1; j++) {
        if (arr[j] < pivot) {
            std::swap(arr[i], arr[j]);
            i++;
        }
    }
    std::swap(arr[i], arr[right - 1]);
    tbb::parallel_invoke(
            [&] { parallelQuickSort(arr, left, i); },
            [&] { parallelQuickSort(arr, i + 1, right); }
    );
}