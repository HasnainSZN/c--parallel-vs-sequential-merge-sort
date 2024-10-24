# Parallel vs Sequential Merge Sort

## Description
This project compares the performance of **Parallel Merge Sort** and **Sequential Merge Sort**. The implementation measures the execution time of both algorithms across various input sizes and analyzes the efficiency and speedup achieved by parallel processing. The goal is to demonstrate how parallelism can enhance the performance of computationally intensive sorting algorithms.

## Features
- **Parallel Merge Sort**: Utilizes Python's `multiprocessing` to sort arrays in parallel.
- **Sequential Merge Sort**: A traditional recursive implementation of merge sort.
- Performance comparison across multiple input sizes.

## Files
- **`Comparison.cpp`**: Contains the code for both parallel and sequential versions of merge sort, along with time measurement.

## Results
- Execution time analysis for different input sizes (ranging from 10,000 to 1,000,000 elements).
- Visualization of performance through table comparing sequential and parallel execution.

## Technologies
- **C++**
- **Multiprocessing module** for parallelism
