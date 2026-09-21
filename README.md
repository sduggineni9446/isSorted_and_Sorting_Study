# isSorted and Sorting Study

## Overview

This C++17 program implements and benchmarks four sorting algorithms:

- Bubble sort
- Selection sort
- Insertion sort
- Quicksort

The program also implements `isSorted`, which verifies that each algorithm correctly sorts its input into nondecreasing order. The required sorting algorithms are implemented from scratch without using `std::sort`.

## Testing Method

Each algorithm was tested on three input arrangements:

1. Random input
2. Already-sorted input
3. Reverse-sorted input

The tests used three input sizes:

- 1,000 elements
- 3,000 elements
- 5,000 elements

A fixed random-number seed was used so that the random tests are reproducible. Each algorithm received a separate copy of the same original vector. After every timed run, `isSorted` verified the result.

## Timing Results

Times are measured in milliseconds and may vary between computers.

| Input | Size | Bubble | Selection | Insertion | Quick |
|---|---:|---:|---:|---:|---:|
| Random | 1000 | 6.973 | 2.709 | 1.867 | 0.146 |
| Sorted | 1000 | 0.003 | 1.818 | 0.009 | 3.889 |
| Reverse | 1000 | 4.297 | 1.831 | 2.195 | 2.101 |
| Random | 3000 | 28.425 | 12.122 | 6.968 | 0.231 |
| Sorted | 3000 | 0.007 | 10.747 | 0.012 | 18.029 |
| Reverse | 3000 | 22.616 | 11.224 | 12.913 | 11.490 |
| Random | 5000 | 64.571 | 30.233 | 18.600 | 0.439 |
| Sorted | 5000 | 0.014 | 30.031 | 0.031 | 50.377 |
| Reverse | 5000 | 63.147 | 31.266 | 37.479 | 35.746 |

All four algorithms passed `isSorted` verification.

## Complexity Analysis

| Algorithm | Best Case | Average Case | Worst Case | Auxiliary Space |
|---|---|---|---|---|
| Bubble sort | O(n) | O(n²) | O(n²) | O(1) |
| Selection sort | O(n²) | O(n²) | O(n²) | O(1) |
| Insertion sort | O(n) | O(n²) | O(n²) | O(1) |
| Quicksort | O(n log n) | O(n log n) | O(n²) | O(log n) average |

Bubble sort and insertion sort performed especially well on sorted input. Bubble sort stopped after one pass because no swaps occurred, while insertion sort required very little shifting. Selection sort remained quadratic because it searched the unsorted portion during every pass.

Quicksort was fastest on random input. However, this implementation uses the final element as its pivot, so sorted and reverse-sorted input caused unbalanced partitions and produced its O(n²) worst-case behavior.

## Building and Running

This project uses CMake and C++17.

```bash
cmake -S . -B build
cmake --build build
./build/isSorted_and_Sorting_Study
```