#include <stdio.h>
#include <stdlib.h>

#define MAX_ARRAY_FIB_SIZE 100

int fib_rec_memo[MAX_ARRAY_FIB_SIZE];
// use loop to find the fib n sequence
int *fib_loop(int n, int arr[]);

// init fib memo
void init_fib_memo();

// use recursion to find the fib n sequence
int fib_rec(int n);


int *fib_loop(int n, int arr[])
{
        for (int i = 0; i < 2; i++) 
               arr[i] = 1;
       
        if (n <= 2)  
                return arr;

        int prev = 0;
        int curr = 1;
        int reach = 1;

        while (n != reach) {
                arr[reach] = prev + curr;
                prev = curr;
                curr = arr[reach];
                reach++;
        }

        return arr;
}

void init_fib_memo()
{
        for (int i = 0; i < MAX_ARRAY_FIB_SIZE; i++) 
                fib_rec_memo[i] = -1;
        // fib rec func doesn't reach 0 instead it stops before assigning array[0] = n not pretty sure on this
        fib_rec_memo[0] = 1;
}

int fib_rec(int n)
{
        if (fib_rec_memo[n] != -1) 
                return fib_rec_memo[n];

        if (n <= 2) {
                fib_rec_memo[n] = n;
        } else {
                fib_rec_memo[n] = fib_rec(n - 1) + fib_rec(n - 2);
        }
        return fib_rec_memo[n];
}

int main() 
{
        int num = 40;
        int arr[num];
        int *fib = fib_loop(num, arr);

        for (int i = 0; i < num; i++) 
                printf(" %d ", fib[i]);
        printf("\n");

        int num_1 = 40;
        init_fib_memo();
        int fib_r = fib_rec(num_1);

        for (int j = 0; j < num_1; j++) 
                printf(" %d ", fib_rec_memo[j]);

        return 0;
}
