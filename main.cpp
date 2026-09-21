#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

// Checks whether the vector is in nondecreasing order.
bool isSorted(const std::vector<int>& values) {
    for (std::size_t i = 1; i < values.size(); ++i) {
        if (values[i] < values[i - 1]) {
            return false;
        }
    }

    return true;
}

// Bubble sort with an early-exit optimization.
void bubbleSort(std::vector<int>& values) {
    if (values.size() < 2) {
        return;
    }

    for (std::size_t pass = 0; pass < values.size() - 1; ++pass) {
        bool swapped = false;

        for (std::size_t i = 0;
             i < values.size() - 1 - pass;
             ++i) {
            if (values[i] > values[i + 1]) {
                std::swap(values[i], values[i + 1]);
                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }
    }
}

// Selection sort.
void selectionSort(std::vector<int>& values) {
    for (std::size_t i = 0; i < values.size(); ++i) {
        std::size_t smallestIndex = i;

        for (std::size_t j = i + 1; j < values.size(); ++j) {
            if (values[j] < values[smallestIndex]) {
                smallestIndex = j;
            }
        }

        if (smallestIndex != i) {
            std::swap(values[i], values[smallestIndex]);
        }
    }
}

// Insertion sort.
void insertionSort(std::vector<int>& values) {
    for (std::size_t i = 1; i < values.size(); ++i) {
        int currentValue = values[i];
        std::size_t position = i;

        while (position > 0 &&
               values[position - 1] > currentValue) {
            values[position] = values[position - 1];
            --position;
        }

        values[position] = currentValue;
    }
}

// Partitions a section of the vector for quicksort.
int partition(std::vector<int>& values, int low, int high) {
    int pivot = values[high];
    int smallerIndex = low - 1;

    for (int current = low; current < high; ++current) {
        if (values[current] <= pivot) {
            ++smallerIndex;
            std::swap(values[smallerIndex], values[current]);
        }
    }

    std::swap(values[smallerIndex + 1], values[high]);
    return smallerIndex + 1;
}

// Recursive quicksort helper.
void quickSortRecursive(
    std::vector<int>& values,
    int low,
    int high
) {
    if (low < high) {
        int pivotIndex = partition(values, low, high);

        quickSortRecursive(values, low, pivotIndex - 1);
        quickSortRecursive(values, pivotIndex + 1, high);
    }
}

// Public quicksort function.
void quickSort(std::vector<int>& values) {
    if (!values.empty()) {
        quickSortRecursive(
            values,
            0,
            static_cast<int>(values.size()) - 1
        );
    }
}

// Generates random input.
std::vector<int> makeRandomInput(
    std::size_t size,
    std::mt19937& generator
) {
    std::uniform_int_distribution<int> distribution(
        0,
        static_cast<int>(size * 10)
    );

    std::vector<int> values(size);

    for (int& value : values) {
        value = distribution(generator);
    }

    return values;
}

// Generates already-sorted input.
std::vector<int> makeSortedInput(std::size_t size) {
    std::vector<int> values(size);

    for (std::size_t i = 0; i < size; ++i) {
        values[i] = static_cast<int>(i);
    }

    return values;
}

// Generates reverse-sorted input.
std::vector<int> makeReverseInput(std::size_t size) {
    std::vector<int> values(size);

    for (std::size_t i = 0; i < size; ++i) {
        values[i] = static_cast<int>(size - i);
    }

    return values;
}

using SortFunction = void (*)(std::vector<int>&);

// Times one sorting algorithm and verifies its result.
double measureTime(
    SortFunction sortingAlgorithm,
    const std::vector<int>& originalValues
) {
    std::vector<int> values = originalValues;

    const auto start = std::chrono::steady_clock::now();
    sortingAlgorithm(values);
    const auto finish = std::chrono::steady_clock::now();

    if (!isSorted(values)) {
        throw std::runtime_error(
            "A sorting algorithm produced an incorrect result."
        );
    }

    return std::chrono::duration<double, std::milli>(
        finish - start
    ).count();
}

void printResults(
    const std::string& inputType,
    std::size_t size,
    const std::vector<int>& values
) {
    std::cout
        << std::left
        << std::setw(16) << inputType
        << std::setw(10) << size
        << std::setw(14) << measureTime(bubbleSort, values)
        << std::setw(14) << measureTime(selectionSort, values)
        << std::setw(14) << measureTime(insertionSort, values)
        << std::setw(14) << measureTime(quickSort, values)
        << '\n';
}

int main() {
    // Fixed seed makes the random tests reproducible.
    std::mt19937 generator(42);

    const std::vector<std::size_t> inputSizes{
        1000,
        3000,
        5000
    };

    std::cout << std::fixed << std::setprecision(3);

    std::cout
        << std::left
        << std::setw(16) << "Input type"
        << std::setw(10) << "Size"
        << std::setw(14) << "Bubble(ms)"
        << std::setw(14) << "Selection(ms)"
        << std::setw(14) << "Insertion(ms)"
        << std::setw(14) << "Quick(ms)"
        << '\n';

    std::cout << std::string(82, '-') << '\n';

    try {
        for (std::size_t size : inputSizes) {
            const std::vector<int> randomValues =
                makeRandomInput(size, generator);

            const std::vector<int> sortedValues =
                makeSortedInput(size);

            const std::vector<int> reverseValues =
                makeReverseInput(size);

            printResults("Random", size, randomValues);
            printResults("Sorted", size, sortedValues);
            printResults("Reverse", size, reverseValues);

            std::cout << '\n';
        }

        std::cout
            << "All four algorithms passed isSorted verification.\n";
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}