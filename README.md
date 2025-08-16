# Find Factors Of Any Positive Number

This program finds the factors of a positive number.

## How It Works
```
It reads input from the user, let's call it N.
Creates a dynamically allocated array of some size K (this size is hardcoded into the code).
Then runs a loop COUNTER from 1 while COUNTER*COUNTER is less than N:
  If N is divisible by COUNTER:
    Then COUNTER and N / COUNTER are added to the FACTORS array.
    If array is full:
        size of array is doubled K * 2 (i.e., array size grows exponentially)
LOOP END
If COUNTER*COUNTER is equal to N:
  Then only COUNTER is added to the FACTORS array.

This is just a basic explaination of the logic.
```
##### Note: There are a lot of optimizations done in the program which I have not explained here.

## How to Run

1. Clone the repository:
   ```
   git clone https://github.com/ANON4620/factors-of-a-number.git
   ```

2. Navigate to the project folder:
   ```
   cd factors-of-a-number
   ```

3. Compile and run (for C program example):
   ```
   gcc factors.c -lm -o factors
   ./factors
   ```

## Example
```
Enter the number: 100
1 2 4 5 10 20 25 50 100
```

## Notes
```
- Written in C.
- Requires GCC or any C compiler.
```
