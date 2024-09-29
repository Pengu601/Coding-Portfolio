// Arup Guha
// 9/24/2024
// Some Number Theory Code to Support COT 3100 lecture.

#include <stdio.h>
#include <stdlib.h>

int numDiv(int n, int p);
int gcd(int a, int b);
int lcm(int a, int b);
int isPrime(int n);
int* primelist(int n, int* ptrNumPrimes);

int main(void) {

    // Test number of times 3, and 5 divide evenly into 1000!
    printf("%d\n", numDiv(1000,3));
    printf("%d\n", numDiv(1000,5));

    // Test gcd and lcm.
    printf("%d\n", gcd(117, 45));
    printf("%d\n", lcm(117, 45));

    // Test prime test.
    for (int x=1; x<=100; x++)
        if (isPrime(x))
            printf("%d ", x);
    printf("\n");

    // Run Prime Sieive.
    int numPrimes;
    int* plist =  primelist(97, &numPrimes);
    for (int i=0; i<numPrimes; i++)
        printf("%d ", plist[i]);
    printf("\n");

    return 0;
}

// Returns the gcd of a and b. (Assumes a, b non-negative and that one value is non-zero.)
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a%b);
}

// Returns the LCM of a and b, assumes neither number is 0.
int lcm(int a, int b) {
    return a/gcd(a,b)*b;
}


// Pre-condition: n is non-negative and p is a positive prime number.
// Post-condiition: Returns the number of times p divides evenly into n factorial.
int numDiv(int n, int p) {

    int res = 0;

    // Repeatedly divide by p, adding up each quotient.
    while (n > 0) {
        res += n/p;
        n = n/p;
    }

    return res;
}

// Returns 1 if and only if n is prime.
int isPrime(int n) {

    // First prime is 2.
    if (n<2) return 0;

    // Just do trial division to the square root, see how we avoid doubles?
    for (int i=2; i*i<=n; i++)
        if (n%i == 0)
            return 0;

    // If we get here, n is prime.
    return 1;
}

// Runs prime sieve upto and including n, returns an array storing all the primes <=n
// and stores the size of the returned list into the variable pointed to by ptrNumPrimes.
int* primelist(int n, int* ptrNumPrimes) {

    // Set all to prime.
    int* isprime = calloc(n+1, sizeof(int));
    for (int i=2; i<=n; i++) isprime[i] = 1;

    // Mark off every multiple of i starting at 2i as composite.
    for (int i=2; i*i<=n; i++)
        for (int j=2*i; j<=n; j+=i)
            isprime[j] = 0;

    // Count the primes.
    *ptrNumPrimes = 0;
    for (int i=2; i<=n; i++)
        if (isprime[i])
        (*ptrNumPrimes)++;

    // idx is index into my new list I will return.
    int idx = 0;

    // Allocate the correct amount of space.
    int* myprimes = calloc(*ptrNumPrimes, sizeof(int));

    // Copy in the appropriate values.
    for (int i=2; i<=n; i++)
        if (isprime[i])
            myprimes[idx++] = i;

    // Ta da!
    return myprimes;
}