//Assignment 0: Foster Home
//Nicholas Gonzalez 
//COP 3502C

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
program neeeds to:
    -Create class containing N cages containing N cats
    -Function that has 3 families adopt cats for the week
        If family lands on cage number that is already occupied by another family --> cat isn't there
    -Function that returns cat to cage with new Suffix depending on family
    and moves forward x spaces to adopt new cat for the week
    -Loop the 2 above processes for K weeks
*/

//define Foster shelter class 
typedef struct{
    char catName[19+1+2000]; //max start of 19 chars + 1 null character, with a maximum addition of 2000 chars
    int isAdopted;
}Foster;

//define family class
typedef struct{
    int spot;
    
}Families;

void adoptionSimulator(Foster *cats, Families family[], int cages, int weeks);
void inputDataSet(Foster *cats, int cages);

int main(void){
    int cages;
    int weeks;

    //gets amount of cages and weeks from user
    scanf("%d %d", &cages, &weeks);

    //initalizes database for the amount of cats depending on cages inputted
    Foster *cats = (Foster *)malloc(cages * sizeof(Foster));

    //Initalize and define database for the three families
    Families family[3] = {
        {0}, // First family -->adopts first, starts at cage 1 (0 for index)
        {1}, // First family -->adopts second, starts at cage 2 (1 for index)
        {2}  // First family -->adopts third, starts at cage 3 (2 for index)
    };

    inputDataSet(cats, cages); //call function to create data for cats

    adoptionSimulator(cats, family, cages, weeks); //call function to run adoption simulator that produces output from input

    //free dynamic memory
    free(cats);
    
}


void inputDataSet(Foster *cats,int cages){

    //loop that creates data for each cat corresponding to cage number
    for(int i = 0; i < cages; i++){
        scanf("%19s", cats[i].catName); //gets cat's name from user
    }

}

void adoptionSimulator(Foster *cats,Families family[], int cages, int weeks){

    int counter = 0; //used to stop function when the x amount of weeks pass

    while(counter != weeks){

        //end of first week, since all 3 families will always adopt first 3 cages
        if(counter == 0){
            //first family
            strcat(cats[family[0].spot].catName, "Lee"); //adds lee suffix to cat name
            cats[family[0].spot].isAdopted = 1; //make the cat at the cage where the family is at adopted (1 is true)

            //second family
            strcat(cats[family[1].spot].catName, "Lyn"); //adds lyn suffix to cat name
            cats[family[1].spot].isAdopted = 1; 

            //third family
            strcat(cats[family[2].spot].catName, "Eve"); //adds eve suffix to cat name
            cats[family[2].spot].isAdopted = 1; 

            counter++; //add counter before skipping the rest of loop to prevent infinite looping

            //skips rest of code for the loop iteration
            continue;
        }

        //family 1 code snippet

        cats[family[0].spot].isAdopted = 0;  //make the cat no longer adopted and returned to cage before family moves spots (0 is false)

        //Loop moves family to new cage position, going back to first cage if on the last cage while moving
        for(int i = 0; i < 2; i++){
            if(family[0].spot+1 != cages){
                family[0].spot += 1; //move family over 1 spot
            }
            else{
                family[0].spot = 0; //family returns to first cage of the sequence
            }
        }

        //check if spot is already occupied by another family, and if not then adopt new cat and give suffix
        if(cats[family[0].spot].isAdopted != 1){
            strcat(cats[family[0].spot].catName, "Lee");
            cats[family[0].spot].isAdopted = 1; 
        }
        
        //family 2 code snippet
        
        cats[family[1].spot].isAdopted = 0; 

        for(int i = 0; i < 3; i++){
            if(family[1].spot+1 != cages){
                family[1].spot += 1;
            }
            else{
                family[1].spot = 0;
            }
        }

        if(cats[family[1].spot].isAdopted != 1){
            strcat(cats[family[1].spot].catName, "Lyn");
            cats[family[1].spot].isAdopted = 1; 
        }

        //family 3 code snippet

        cats[family[2].spot].isAdopted = 0; 

        for(int i = 0; i < 5; i++){
            if(family[2].spot+1 != cages){
                family[2].spot += 1;
            }
            else{
                family[2].spot = 0;
            }
        }
        
        if(cats[family[2].spot].isAdopted != 1){
            strcat(cats[family[2].spot].catName, "Eve");
            cats[family[2].spot].isAdopted = 1; 
        }

        counter++;
    }

    //prints output
    for(int i = 0; i < cages; i++){
        if(cats[i].isAdopted == 1){ //if cat at i index is adopted, print "No cat found.", else print the name of the cat
            printf("%s\n", "No cat found.");
        }
        else{
            printf("%s\n", cats[i].catName);
        }
    }

}