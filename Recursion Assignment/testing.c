#include <stdio.h>
#include <stdbool.h>

#define NUM_HOUSES 3
#define MAX_CATS 9 // Maximum number of cats

void printCombinations(int cats[], int n) {
    printf("{ ");
    for (int i = 0; i < n; ++i) {
        printf("%d ", cats[i]);
    }
    printf("}\n");
}

void distributeCats(int n, int index, int cats[]) {
    static int count = 0;
    if (index == n) {
        bool has_one = false, has_two = false, has_three = false; //used to keep track if there is atleast one cat in each house
        for (int i = 0; i < n; ++i) {
            if (cats[i] == 1) has_one = true;
            if (cats[i] == 2) has_two = true;
            if (cats[i] == 3) has_three = true;
        }
        if (has_one && has_two && has_three) { //if there is at least one cat in each house, then combination works
            count++;
            printf("%d. ", count);
            printCombinations(cats, n);
            
        }
        return;
    }

    for (int i = 0; i < NUM_HOUSES; ++i) {
        cats[index] = i + 1; //moves cat at index to new house i+1
        distributeCats(n, index + 1, cats); //recursive call function, increasing index by one
    }
}

int main() {
    int n;
    printf("Enter the number of cats: ");
    scanf("%d", &n);


    int cats[n];

    distributeCats(n, 0, cats);

    return 0;
}
