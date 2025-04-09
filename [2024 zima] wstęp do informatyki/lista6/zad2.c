#include <stdio.h>

// O((n-1) + (n-2) + ... + 1) = O(n^2)
void selectionSort(int arr[], int n) {
    
    for (int i = 0; i < n - 1; i++) 
    {
        // poczatek iteracji (wczesniejsze juz ułozone)
        int min_idx = i;
        
        // szukanie najmniejszego elementu
        for (int j = i + 1; j < n; j++) 
        {
            if (arr[j] < arr[min_idx]) min_idx = j;
        }
        
        // przeniesc najmniejszy element na pozycje i
        if (min_idx != i)
        {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}

// a1 ≤, . . . , ≤ an:
// porownania: n(n-1)/2, podstawienia: 0

//  a1 ≥ . . . ≥ an
// porownania: n(n-1)/2, podstawienia: n-1

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {64, 25, 12, 22, 11};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Original array: ");
    printArray(arr, n);
    
    selectionSort(arr, n);
    
    printf("Sorted array: ");
    printArray(arr, n);
    
    return 0;
}
