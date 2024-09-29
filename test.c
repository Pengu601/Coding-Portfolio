// Arup Guha
// 10/10/2017
// Program to check your GCD Calculations.
// Updated on 10/9/2018 to show backsub for EEA, mod inverse and all solutions.

#include <stdio.h>

void copy(int a[], int b[], int len);

int main() {

    int a, b;
    printf("Enter a, b, a > b > 0, for your gcd calculation.\n");
    scanf("%d%d", &a, &b);

    // Big enough for any gcd run with valid ints.
    int vals[100][4];
    int numEq = 0;

    // We end when there's no remainder.
    while (b != 0) {

        // Here is what gets printed out when we do the algorithm by hand.
        printf("%d = %d x %d + %d\n", a, a/b, b, a%b);

        // Store all values so we can do the equations backwards.
        vals[numEq][0] = a;
        vals[numEq][1] = a/b;
        vals[numEq][2] = b;
        vals[numEq][3] = a%b;
        numEq++;

        // Shuffle variables appropriately.
        int savea = a;
        a = b;
        b = savea%b;
    }

    // Now we solve for x and y in ax + by = gcd(a,b).

    // This equation has the gcd on the RHS.
    numEq -= 2;
    int gcd = vals[numEq][3];

    // Hard code initial equatoin.
    int backSub[4];
    backSub[0] = 1;
    backSub[1] = vals[numEq][0];
    backSub[2] = -vals[numEq][1];
    backSub[3] = vals[numEq][2];

    int i = 0;

    while (numEq>=0) {

        // Next equation to sub into.
        printf("%d x %d + %d x %d = %d\n", backSub[0], backSub[1], backSub[2], backSub[3], gcd);

        // Avoid array out of bounds.
        if (numEq == 0) break;

        // Print substitution.
        printf("%d x %d + %d x (%d + %d x %d) = %d\n", backSub[0], backSub[1], backSub[2], vals[numEq-1][0], -vals[numEq-1][1], vals[numEq-1][2], gcd);

        // Recalculate new four values, then copy back into backsub.
        int tmp[4];
        tmp[0] = backSub[2];
        tmp[1] = vals[numEq-1][0];
        tmp[2] = backSub[0] - backSub[2]*vals[numEq-1][1];
        tmp[3] = backSub[1];
        copy(backSub, tmp, 4);

        // Go up 1 equation.
        numEq--;
    }

    // Print one solution.
    printf("A solution (x,y) to %dx + %dy = %d is (%d, %d).\n", backSub[1], backSub[3], gcd, backSub[0], backSub[2]);

    // Mod inverse.
    if (gcd == 1) {
        int modinv = backSub[2];
        if (modinv < 0) modinv += backSub[1];
        printf("%d inverse mod %d is %d.\n", backSub[3], backSub[1], modinv);
    }

    // All solutions.
    printf("All solutions are of the form x = %d + %dn, y = %d - %dn, where n is an int.\n", backSub[0], backSub[3]/gcd, backSub[2], backSub[1]/gcd);

    return 0;
}

void copy(int a[], int b[], int len) {
    int i;
    for (i=0; i<len; i++)
        a[i] = b[i];
}