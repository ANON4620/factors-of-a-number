#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void printArray(const int A[], int n) {
    printf("Factors: ");
    for(int i = 0; i < n; i++) {
        printf("%d", A[i]);
        if(i < n - 1) printf(", ");
    }
    printf("\n");
}

// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

/**
 * Finds all factors of a given number
 * @param n: The number to find factors for
 * @param factors: Pointer to store the allocated factors array
 * @param returnSize: Pointer to store the number of factors found
 * @return: 1 on success, 0 on failure
 */
int findFactors(unsigned int n, int **factors, int *returnSize) {
    if(n == 0) {
        *returnSize = 0;
        *factors = NULL;
        return 1;  // 0 has no factors, but this isn't an error
    }
    
    if(n == 1) {
        *factors = (int*)malloc(sizeof(int));
        if(*factors == NULL) return 0;
        (*factors)[0] = 1;
        *returnSize = 1;
        return 1;
    }
    
    // Estimate initial capacity more accurately
    int capacity = (int)(2 * sqrt(n)) + 10;  // Better initial estimate
    int *result = (int*)malloc(capacity * sizeof(int));
    if(result == NULL) {
        return 0;
    }
    
    int count = 0;
    unsigned int sqrtN = (unsigned int)sqrt(n);
    
    // Find all factors up to sqrt(n)
    for(unsigned int i = 1; i <= sqrtN; i++) {
        if(n % i == 0) {
            // Resize if needed
            if(count >= capacity - 2) {  // -2 because we might add 2 factors
                capacity *= 2;
                int *newResult = (int*)realloc(result, capacity * sizeof(int));
                if(newResult == NULL) {
                    free(result);
                    return 0;
                }
                result = newResult;
            }
            
            result[count++] = i;
            
            // Add the corresponding factor if it's different
            unsigned int complement = n / i;
            if(complement != i) {
                result[count++] = complement;
            }
        }
    }
    
    // Sort the factors
    qsort(result, count, sizeof(int), compare);
    
    // Resize to exact size needed
    if(count > 0) {
        int *finalResult = (int*)realloc(result, count * sizeof(int));
        if(finalResult == NULL) {
            // If realloc fails, we can still use the original array
            *factors = result;
        } else {
            *factors = finalResult;
        }
    } else {
        free(result);
        *factors = NULL;
    }
    
    *returnSize = count;
    return 1;
}

void printFactorStatistics(unsigned int n, const int factors[], int count) {
    printf("Number: %u\n", n);
    printf("Total factors: %d\n", count);
    
    if(count > 0) {
        // Check if it's a perfect square
        int sqrtN = (int)sqrt(n);
        if(sqrtN * sqrtN == n) {
            printf("Perfect square: Yes (√%u = %d)\n", n, sqrtN);
        }
        
        // Check if it's prime
        if(count == 2) {
            printf("Prime number: Yes\n");
        }
        
        // Sum of factors
        long long sum = 0;
        for(int i = 0; i < count; i++) {
            sum += factors[i];
        }
        printf("Sum of factors: %lld\n", sum);
        
        // Check if it's perfect, abundant, or deficient
        long long properSum = sum - n;  // Sum of proper divisors (excluding n itself)
        if(properSum == n) {
            printf("Perfect number: Yes\n");
        } else if(properSum > n) {
            printf("Abundant number: Yes (proper divisors sum = %lld)\n", properSum);
        } else {
            printf("Deficient number: Yes (proper divisors sum = %lld)\n", properSum);
        }
    }
    printf("\n");
}

int main() {
    unsigned int n;
    int *factors = NULL;
    int size;
    
    printf("=== Factor Finder Program ===\n");
    printf("Enter a positive integer (0 to exit): ");
    
    while(scanf("%u", &n) == 1) {
        if(n == 0) {
            printf("Goodbye!\n");
            break;
        }
        
        printf("\nProcessing number: %u\n", n);
        
        int status = findFactors(n, &factors, &size);
        if(status == 1) {
            printArray(factors, size);
            printFactorStatistics(n, factors, size);
            
            if(factors != NULL) {
                free(factors);
                factors = NULL;
            }
        } else {
            printf("Error: Failed to find factors (memory allocation failed)\n");
        }
        
        printf("Enter another positive integer (0 to exit): ");
    }
    
    // Clean up any remaining memory
    if(factors != NULL) {
        free(factors);
    }
    
    return 0;
}
