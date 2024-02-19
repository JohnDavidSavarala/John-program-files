// testPrime.c

// Test the prime.c program

#include <stdio.h>
#include <stdlib.h>
#include "prime.c"

int main() 
{
    int counter, passCounter = 0;
    char testCases[5][10] = {"5", "2", "3", "0", "John"};
    int testCasesSize = 5; 

    for (counter = 0; counter < testCasesSize; counter++) 
    {
        if (isPrime(testCases[counter]) == 2) 
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
