#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define NUM_SIZES 6

const int sizes[NUM_SIZES] = {
    1000, 2000, 4000, 8000, 16000, 20000
};
void generate_data(int arr[], int n)
{
    for (int i = 0; i < n; i++) {
        arr[i] = rand();
    }
}
int is_sorted(const int arr[], int n)
{
    for (int i = 1; i < n; i++) {
        if (arr[i - 1] > arr[i]) {
            return 0;
        }
    }

    return 1;
}
long long insertion_sort(int arr[], int n)
{
    long long comparisons = 0;

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0) {
            comparisons++;

            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            } else {
                break;
            }
        }

        arr[j + 1] = key;
    }

    return comparisons;
}
long long shell_sort_original(int arr[], int n)
{
    long long comparisons = 0;

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int key = arr[i];
            int j = i;

            while (j >= gap) {
                comparisons++;

                if (arr[j - gap] > key) {
                    arr[j] = arr[j - gap];
                    j -= gap;
                } else {
                    break;
                }
            }

            arr[j] = key;
        }
    }

    return comparisons;
}
long long shell_sort_knuth(int arr[], int n)
{
    long long comparisons = 0;
    int gap = 1;

    while (gap < n / 3) {
        gap = 3 * gap + 1;
    }

    while (gap >= 1) {
        for (int i = gap; i < n; i++) {
            int key = arr[i];
            int j = i;

            while (j >= gap) {
                comparisons++;

                if (arr[j - gap] > key) {
                    arr[j] = arr[j - gap];
                    j -= gap;
                } else {
                    break;
                }
            }

            arr[j] = key;
        }

        gap = (gap - 1) / 3;
    }

    return comparisons;
}
int main(void)
{
    srand((unsigned int)time(NULL));

    for (int s = 0; s < NUM_SIZES; s++) {
        int n = sizes[s];

        int *original = malloc((size_t)n * sizeof(int));
        int *arr_insertion = malloc((size_t)n * sizeof(int));
        int *arr_original = malloc((size_t)n * sizeof(int));
        int *arr_knuth = malloc((size_t)n * sizeof(int));

        if (original == NULL ||
            arr_insertion == NULL ||
            arr_original == NULL ||
            arr_knuth == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");

            free(original);
            free(arr_insertion);
            free(arr_original);
            free(arr_knuth);

            return 1;
        }

        generate_data(original, n);

        memcpy(arr_insertion, original, (size_t)n * sizeof(int));
        memcpy(arr_original, original, (size_t)n * sizeof(int));
        memcpy(arr_knuth, original, (size_t)n * sizeof(int));

        long long c1 = insertion_sort(arr_insertion, n);
        long long c2 = shell_sort_original(arr_original, n);
        long long c3 = shell_sort_knuth(arr_knuth, n);

        if (!is_sorted(arr_insertion, n) ||
            !is_sorted(arr_original, n) ||
            !is_sorted(arr_knuth, n)) {
            printf("Sorting verification failed!\n");

            free(original);
            free(arr_insertion);
            free(arr_original);
            free(arr_knuth);

            return 1;
        }

        printf("Data Size : %d\n", n);
        printf("Insertion Sort       : %lld comparisons\n", c1);
        printf("Shell Sort (Original): %lld comparisons\n", c2);
        printf("Shell Sort (Knuth)   : %lld comparisons\n\n", c3);

        free(original);
        free(arr_insertion);
        free(arr_original);
        free(arr_knuth);
    }

    return 0;
}