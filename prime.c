// Check whether a given number is prime or not

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int isPrime(char *isPrimeValue) 
{
    int divisor = 0;
    int number = atoi(isPrimeValue);

    if (!isdigit(isPrimeValue[0]) || number <= 1) 
    {
        return 1;
    }
    else
    {
        for (divisor = 2; divisor * divisor <= number; divisor++) 
        {
            if (number % divisor == 0) 
            {
                return 1;
            }
        }
        return 0;
    }
    return 2;
}
