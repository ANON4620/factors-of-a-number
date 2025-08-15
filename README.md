# Find Factors Of Any Positive Number

This program finds the factors of a positive number.

## How It Works

It reads input from the user, let's call it N.
Finds the square root of that number, let's call it SQRT.
Then runs a loop COUNTER from 1 to SQRT:
  If N is divisible by COUNTER
    Then COUNTER and N / COUNTER are added to the FACTORS array.

This is a basic explaination of the logic.

## How to Run

1. Clone the repository:
   git clone https://github.com/ANON4620/factors-of-a-number.git

2. Navigate to the project folder:
   cd factors-of-a-number

3. Compile and run (for C program example):
   gcc factors.c -lm -o factors
   ./factors

## Example

Enter the number: 100
1 2 4 5 10 20 25 50 100
