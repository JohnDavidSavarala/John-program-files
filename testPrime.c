// testPrime.c

// Test the prime.c program

#include <stdio.h>
#include <stdlib.h>
#include "prime.c"

int main() 
{
    int counter, passCounter = 0;
    char testCases[5][10] = {"5", "2", "3", "11", "John"};
    int testCasesSize = 5; // Corrected size

    for (counter = 0; counter < testCasesSize; counter++) 
    {
        if (isPrime(testCases[counter]) != 0) // Check if return value is 0
        {
            printf("Failed(%s)\n", testCases[counter]);
        }
        else
        {
            passCounter++;
        }
    }
    if (counter == passCounter)
    {
        printf("All tests passed.\n");
    }
    return 0;
}
