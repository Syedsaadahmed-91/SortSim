#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // for usleep

#define N 15
#define DELAY 150000 // microseconds between frames

// ANSI colors
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"

void print_array(int arr[], int n, int a, int b, const char* note) {
    printf("%-8s ", note);
    for (int i = 0; i < n; i++) {
        if (i == a || i == b)
            printf(RED "%2d " RESET, arr[i]);
        else
            printf("%2d ", arr[i]);
    }
    printf("\n");
    usleep(DELAY);
}

// ---------------- Bubble Sort ----------------
void bubble_sort(int arr[], int n) {
    printf(CYAN "\nBubble Sort:\n" RESET);
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            print_array(arr, n, j, j+1, "compare");
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                print_array(arr, n, j, j+1, "swap");
            }
        }
    }
}

// ---------------- Merge Sort ----------------
void merge(int arr[], int l, int m, int r, int n) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        print_array(arr, n, l+i, m+1+j, "compare");
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
        print_array(arr, n, k-1, -1, "write");
    }
    while (i < n1) {
        arr[k++] = L[i++];
        print_array(arr, n, k-1, -1, "write");
    }
    while (j < n2) {
        arr[k++] = R[j++];
        print_array(arr, n, k-1, -1, "write");
    }
}

void merge_sort(int arr[], int l, int r, int n) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort(arr, l, m, n);
        merge_sort(arr, m + 1, r, n);
        merge(arr, l, m, r, n);
    }
}

// ---------------- Quick Sort ----------------
int partition(int arr[], int low, int high, int n) {
    int pivot = arr[high];
    print_array(arr, n, high, -1, "pivot");
    int i = low - 1;
    for (int j = low; j < high; j++) {
        print_array(arr, n, j, high, "compare");
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
            print_array(arr, n, i, j, "swap");
        }
    }
    int temp = arr[i+1]; arr[i+1] = arr[high]; arr[high] = temp;
    print_array(arr, n, i+1, high, "swap");
    return i + 1;
}

void quick_sort(int arr[], int low, int high, int n) {
    if (low < high) {
        int pi = partition(arr, low, high, n);
        quick_sort(arr, low, pi - 1, n);
        quick_sort(arr, pi + 1, high, n);
    }
}

// ---------------- Main ----------------
void copy_array(int src[], int dest[], int n) {
    for (int i = 0; i < n; i++) dest[i] = src[i];
}

int main() {
    int original[N];
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        original[i] = rand() % 90 + 10; // 10-99
    }

    int arr1[N], arr2[N], arr3[N];
    copy_array(original, arr1, N);
    copy_array(original, arr2, N);
    copy_array(original, arr3, N);

    printf("Original array:\n");
    print_array(original, N, -1, -1, "start");

    bubble_sort(arr1, N);

    printf(CYAN "\nMerge Sort:\n" RESET);
    merge_sort(arr2, 0, N-1, N);

    printf(CYAN "\nQuick Sort:\n" RESET);
    quick_sort(arr3, 0, N-1, N);

    printf(CYAN "\nAll sorts completed.\n" RESET);
    return 0;
}