#include <stdio.h>
#include <stdlib.h>

void printArray(int A[], int n) {
    for(int i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");
}

int findFactors(int n, int **factors, int *returnSize) {
    // Small numbers or multiplicand
    int *small = (int *) malloc(sizeof(int));
    if(small == NULL) {
        return 0;
    }
    // Big numbers or multiplier
    int *big = (int *) malloc(sizeof(int));
    if(big == NULL) {
        return 0;
    }

    int idx = 0, len = 1;

    int step;
    if(n % 2 == 0) {
        step = 1;           // since factors of an even number can be either even or odd
    }
    else {
        step = 2;           // since all factors of an odd number are odd
    }

    int i;
    for(i = 1; i * i < n; i += step) {
        if(n % i == 0) {
            small[idx] = i;
            big[idx] = n / i;
            idx++;
            if(idx == len) {
                len *= 2;

                int *newSmall = (int *) realloc(small, len * sizeof(int));
                if(newSmall == NULL) {
                    free(small);
                    free(big);
                    return 0;
                }
                small = newSmall;

                int *newBig = (int *) realloc(big, len * sizeof(int));
                if(newBig == NULL) {
                    free(small);
                    free(big);
                    return 0;
                }
                big = newBig;
            }
        }
    }

    *returnSize = idx * 2;

    // this inserts a single factor M into the array such that M * M = n
    int perfectSquare = 0;
    if(i * i == n) {
        small[idx] = i;
        idx++;
        (*returnSize)++;
        perfectSquare = 1;
    }

    // Resize small to returnSize
    int *newSmall = (int *) realloc(small, *returnSize * sizeof(int));
    if(newSmall == NULL) {
        free(small);
        free(big);
        return 0;
    }
    small = newSmall;

    // Copy big array values to remaining space in small array
    for(int i = idx - perfectSquare - 1; i >= 0; i--) {
        small[idx++] = big[i];
    }

    *factors = small;

    free(big);
    return 1;
}

int main() {
    int n;
    int *factors;
    int size;
    printf("Enter the number: ");
    scanf("%d", &n);
    int status = findFactors(n, &factors, &size);
    if(status == 1) {
        printArray(factors, size);
        free(factors);
    }
    else {
        printf("factors() function failed!");
    }
    return 0;
}