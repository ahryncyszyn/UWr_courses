#include <stdio.h>
#include <stdbool.h>

// O((n-1) + (n-2) + ... + 1) = n*(n-1)/2 = O(n^2)
void bubble_sort(int arr[], int n) 
{
    for (int i = 0; i < n - 1; i++) 
    {
        bool swapped = false; 
        for (int j = 0; j < n - i - 1; j++) 
        {
            if (arr[j] > arr[j + 1]) 
            {
                // zamiana elementów jezeli napotkalo sie wiekszy
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
            printf("%d\n", arr[j]);
        }
        // jeśli w tej iteracji nie było zamian, tablica jest posortowana
        if (!swapped) break;
    }
}

// a1 ≤, . . . , ≤ an:
// porownania: n-1, podstawienia: 0

//  a1 ≥ . . . ≥ an
// porownania: n(n-1)/2, podstawienia: n(n-1)/2

void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    bubble_sort(arr, n);
    printf("Posortowana tablica: ");
    print_array(arr, n);
    return 0;
}
