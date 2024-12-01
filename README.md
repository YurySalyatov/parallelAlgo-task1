# Parallel QuickSort Benchmark

start with command: cmake -B build && cmake --build build && ./build/firstTask

## Results

### Correctness Test

**Correctness test PASSED**

### Speed Test

#### Sequential QuickSort Times

| Run | Time (seconds) |
|-----|----------------|
| 1   | 22.1781        |
| 2   | 22.5359        |
| 3   | 22.1398        |
| 4   | 23.304         |
| 5   | 22.1647        |

**Mean Time: 22.4645 seconds**

#### Parallel QuickSort Times

| Run | Time (seconds) |
|-----|----------------|
| 1   | 6.76058        |
| 2   | 6.7067         |
| 3   | 6.87893        |
| 4   | 6.99102        |
| 5   | 6.58859        |

**Mean Time: 6.78516 seconds**

### Performance Ratio

**Ratio: 3.31083**

### Conclusion

**Speed test PASSED**