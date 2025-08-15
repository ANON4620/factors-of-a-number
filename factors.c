#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void printArray(int A[], int n) {
    for(int i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");
}

void findFactors(int n, int **factors, int *returnSize) {
    int temp[n];
    int idx = 0, last_idx = n - 1;
    *returnSize = 0;

    int root = (int) sqrt((double) n);
    for(int i = 1; i <= root; i++) {
        if(n % i == 0) {
            if(i == (n / i)) {
                temp[idx] = i;
                idx++;
                *returnSize += 1;
            }
            else {
                temp[idx] = i;
                idx++;
                temp[last_idx] = n / i;
                last_idx--;
                *returnSize += 2;
            }
        }
    }

    *factors = (int *) malloc((*returnSize) * sizeof(int));
    for(int i = 0; i < idx; i++) {
        (*factors)[i] = temp[i];
    }
    for(int i = idx; i < (*returnSize); i++) {
        (*factors)[i] = temp[++last_idx];
    }
}

int main() {
    int n;
    int *factors;
    int size;
    printf("Enter the number: ");
    scanf("%d", &n);
    findFactors(n, &factors, &size);
    printArray(factors, size);
    return 0;
}