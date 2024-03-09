#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HOUSES 3

//BRAINSTORM:
//combinations equate to (n+k-1)!/n!(k-1)! (n is num of cats and k is houses) (make sure that each house has atleast 1 cat)
//recursively call all comb, making the base case if index == num of cats
//have variable that = the max num of coziness for each possible comb rec call
//have global variable that = the greatest number from each rec call
//print global variable

int maxCozy = 0; //max possible combined cozy value from all combinations of cats and houses

void maxCoziness(int** initialCozy, int** changeInCozy, int catCombo[], int numCats){
    int curMaxCozy = 0; //number used to assign max sum of coziness value of current combo
    int cozyCounter[numCats];

    for(int i = 0; i < numCats; i++){
        cozyCounter[i] = initialCozy[i][catCombo[i]-1]; //assigns base values to cozy counter for each cat depending on their house
    }

    for(int i = 0; i < numCats; i++){
        for(int j = 0; j < numCats; j++){
            if(i != j){ //makes sure it doesn't compare the same index of the array as it will always be true (e.x : if i = 0 and j = 0)
                if(catCombo[i] == catCombo[j]){ //if the cat at i has the same house as cat at j, then they affect each other
                    cozyCounter[i] += changeInCozy[i][j]; //add the change in coziness value to the cozy counter for cat i using the value that cat j affects on cat i
                }
            }
        }
    }

    for(int i = 0; i < numCats; i++){
        curMaxCozy += cozyCounter[i]; //adds all the cozy values together to get the sum of cozy values for the current combination
    }

    if(maxCozy < curMaxCozy){
        maxCozy = curMaxCozy; //finds and sets the total max coziness value possible from all combinations
    }
}

int maxLeastCozy = -10001; //maximum cozy value of the least cozy cat from all possible combinations

void minCoziness(int** initialCozy, int** changeInCozy, int catCombo[], int numCats){
    int minCozy = 10001; //number used to assign max coziness value of current combo
    int cozyCounter[numCats]; //array used to keep track of the cozy value of each cat for current combination

    for(int i = 0; i < numCats; i++){
        cozyCounter[i] = initialCozy[i][catCombo[i]-1]; //assigns base values to cozy counter for each cat depending on their house
        
    }

    for(int i = 0; i < numCats; i++){
        for(int j = 0; j < numCats; j++){
            if(i != j){ //makes sure it doesn't compare the same index of the array to give false positives
                if(catCombo[i] == catCombo[j]){ //if the cat at i has the same house as cat at j, then they affect each other
                    cozyCounter[i] += changeInCozy[i][j]; //add the change in coziness value to the cozy counter for cat i using the value that cat j affects on cat i
                }
            }
        }
    }

    for(int i = 0; i < numCats; i++){
        if(minCozy > cozyCounter[i]){
            minCozy = cozyCounter[i]; //finds the least cozy cat value of the current combination
        }
    }

    if(maxLeastCozy < minCozy ){
        maxLeastCozy = minCozy; //finds and sets the max value of the least cozy cat with all combinations
    }
}

void allCatCombos(int numCats, int index, int cats[], int** initialCozy, int** changeInCozy) {
    if (index == numCats) {
        int has_one = 0, has_two = 0, has_three = 0; //used to keep track if there is atleast one cat in each house

        for (int i = 0; i < numCats; ++i) { //checks to see if there is at least one cat in each house
            if (cats[i] == 1) has_one = 1;
            if (cats[i] == 2) has_two = 1;
            if (cats[i] == 3) has_three = 1;
        }

        if (has_one && has_two && has_three) { //if there is at least one cat in each house, then combination works
            maxCoziness(initialCozy, changeInCozy, cats, numCats); //find the max combined coziness of given combo
            minCoziness(initialCozy, changeInCozy, cats, numCats); //find the max cozy value possible of the least cozy cat
        }

        return;
    }

    for (int i = 0; i < HOUSES; ++i) {
        cats[index] = i + 1; //moves cat at index to new house i+1
        allCatCombos(numCats, index + 1, cats, initialCozy, changeInCozy); //recursive call function, increasing index by one
    }
}

int main(){
    int numOfCats = 0;
    
    scanf("%d", &numOfCats); //get input for amount of cats

    //initialize arrays for Initial Cozy values and change in cozy values (dynamic as you cant pass an array with a variable as its parameters for a 2d array)
    int ** initialCozy =  (int**)malloc(sizeof(int*) * numOfCats);
    for(int i = 0 ; i < numOfCats ; ++i){
        initialCozy[i] = malloc(sizeof(int) * HOUSES);
    }

    int ** changeInCozy = (int**) malloc(sizeof(int*) * numOfCats);
    for(int i = 0 ; i < numOfCats ; ++i){
        changeInCozy[i] = malloc(sizeof(int) * numOfCats);
    }

    for(int i = 0; i < numOfCats; i++){
        for(int j = 0; j < HOUSES; j++){
            scanf("%d ", &initialCozy[i][j]); //gets input for initial coziness for each cat at each house
        }
    }

    for(int i = 0; i < numOfCats; i++){
        for(int j = 0; j < numOfCats; j++){
            scanf("%d ", &changeInCozy[i][j]); //gets input for changeInCoziness for each cat
        }
    }
    
    int catCombo[numOfCats]; //array used to store a combination that meets condition in current recursive call

    allCatCombos(numOfCats,0, catCombo, initialCozy, changeInCozy); //call function to find all possible combonitations of cats in houses
    
    printf("%d %d", maxCozy, maxLeastCozy); //prints the values found 

    //free arrays
    for(int i = 0; i < numOfCats; i++){ //free each array at index i
        free(initialCozy[i]);
        free(changeInCozy[i]);
    }
    //free the array as a whole
    free(initialCozy); 
    free(changeInCozy);
}