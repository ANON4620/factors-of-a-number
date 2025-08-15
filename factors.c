#include <stdio.h>
#include <stdlib.h>

void printArray(int A[], int n) {
    for(int i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");
}

int findFactors(int n, int **factors, int *returnSize) {

    int *small = (int *) malloc(sizeof(int));
    if(small == NULL) {
        return 0;
    }
    int *big = (int *) malloc(sizeof(int));
    if(big == NULL) {
        return 0;
    }

    int sidx = 0, bidx = 0, slen = 1, blen = 1;

    int step;
    if(n % 2 == 0) {
        step = 1;           // since factors of an even number can be either even or odd
    }
    else {
        step = 2;           // since all factors of an odd number are odd
    }

    *returnSize = 0;
    int i;
    for(i = 1; i * i < n; i += step) {
        if(n % i == 0) {
            small[sidx] = i;
            sidx++;
            if(sidx == slen) {
                slen *= 2;
                int *newSmall = (int *) realloc(small, slen * sizeof(int));
                if(newSmall == NULL) {
                    free(small);
                    return 0;
                }
                small = newSmall;
            }
            big[bidx] = n / i;
            bidx++;
            if(bidx == blen) {
                blen *= 2;
                int *newBig = (int *) realloc(big, blen * sizeof(int));
                if(newBig == NULL) {
                    free(big);
                    return 0;
                }
                big = newBig;
            }
            *returnSize += 2;
        }
    }

    if(n % i == 0) {
        // this inserts a single factor M into the array such that M * M = n
        if(i == (n / i)) {
            small[sidx] = i;
            sidx++;
            *returnSize += 1;
        }
    }

    *factors = (int *) malloc((*returnSize) * sizeof(int));
    for(int i = 0; i < sidx; i++) {
        (*factors)[i] = small[i];
    }
    for(int i = sidx; i < (*returnSize); i++) {
        (*factors)[i] = big[--bidx];
    }

    free(small);
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