#include <stdio.h>

int b[] = {-1, -1, -1, -1, -1, -1, -1, -1};

int isfree(int x, int y)
// isfree(x,y) = 1 wtw (x,y) nie jest atakowane
// przez hetmany z kolumn 0,1,2,...,x-1
{
    for (int i = 0; i < x; i++)
    {
        if (b[i] - i == y - x || b[i] + i == y + x || b[i] == y) return 0;
    }
return 1;
}

int solveNQueens(int n, int b[])
{ 
    int k = 1; 
    b[0] = 0;  
    int count = 0;
    while (k >= 0) 
    { 
        do{
            b[k]++; 
        } while ( b[k] < n && !isfree (k, b[k])); 

        printf("przed k to %d\n", k);

        if (b[k] < n) k++; 

        else { b[k] = -1; k--; } 
        printf("po k to %d\n", k);

        if (k == n) // dotarlismy do ostatniej kolumny
        {
            printf("----------------\n");
            count++; // zwiekszenie wyniku
        }
    } 
    printf("%d\n", count);
    return k; 
}

int main()
{

    solveNQueens(8, b);
}