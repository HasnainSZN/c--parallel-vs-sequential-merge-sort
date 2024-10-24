#include <iostream>
#include <omp.h>
#include <ctime>  // For clock()
#include <cstdlib> // For rand(), malloc, free

// Helper function to merge two arrays
void merge(int* arr1, int size1, int* arr2, int size2, int* result) {
    int i = 0, j = 0, k = 0;
    
    while (i < size1 && j < size2) {
        if (arr1[i] < arr2[j]) {
            result[k++] = arr1[i++];
        } else {
            result[k++] = arr2[j++];
        }
    }

    while (i < size1) {
        result[k++] = arr1[i++];
    }

    while (j < size2) {
        result[k++] = arr2[j++];
    }
}

// Sequential merge sort
void merge_sort(int* arr, int size) {
    if (size <= 1) return;

    int mid = size / 2;
    int* left = (int*)malloc(mid * sizeof(int));
    int* right = (int*)malloc((size - mid) * sizeof(int));

    for (int i = 0; i < mid; ++i) left[i] = arr[i];
    for (int i = mid; i < size; ++i) right[i - mid] = arr[i];

    merge_sort(left, mid);
    merge_sort(right, size - mid);

    merge(left, mid, right, size - mid, arr);

    free(left);
    free(right);
}

// Parallel merge sort
void parallel_merge_sort(int* arr, int size) {
    if (size <= 1) return;

    // Threshold for parallelism, fall back to sequential for smaller sizes
    if (size < 50000) {
        merge_sort(arr, size);
        return;
    }

    int mid = size / 2;
    int* left = (int*)malloc(mid * sizeof(int));
    int* right = (int*)malloc((size - mid) * sizeof(int));

    for (int i = 0; i < mid; ++i) left[i] = arr[i];
    for (int i = mid; i < size; ++i) right[i - mid] = arr[i];

    // Parallel sections for sorting the two halves
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            merge_sort(left, mid);
        }
        #pragma omp section
        {
            merge_sort(right, size - mid);
        }
    }

    merge(left, mid, right, size - mid, arr);

    free(left);
    free(right);
}

// Measure execution time of a sorting function
double measure_time(void (*sort_function)(int*, int), int* arr, int size) {
    clock_t start = clock();
    sort_function(arr, size);
    clock_t end = clock();
    return double(end - start) / CLOCKS_PER_SEC;
}

int main() {
    int sizes[] = {10000, 50000, 100000, 500000, 1000000};
    double seq_times[5];
    double par_times[5];

    for (int i = 0; i < 5; i++) {
        int size = sizes[i];
        int* arr = (int*)malloc(size * sizeof(int));

        // Generate random array
        for (int j = 0; j < size; j++) {
            arr[j] = rand() % 1000000;
        }

        // Measure sequential merge sort time
        int* arr_copy = (int*)malloc(size * sizeof(int));
        for (int j = 0; j < size; j++) arr_copy[j] = arr[j];
        seq_times[i] = measure_time(merge_sort, arr_copy, size);
        free(arr_copy);

        // Measure parallel merge sort time
        arr_copy = (int*)malloc(size * sizeof(int));
        for (int j = 0; j < size; j++) arr_copy[j] = arr[j];
        par_times[i] = measure_time(parallel_merge_sort, arr_copy, size);
        free(arr_copy);

        free(arr);
    }

    // Output the results
    std::cout << "Input Size\tSequential Time (s)\tParallel Time (s)\n";
    for (int i = 0; i < 5; i++) {
        std::cout << sizes[i] << "\t\t" << seq_times[i] << "\t\t" << par_times[i] << "\n";
    }

    return 0;
}