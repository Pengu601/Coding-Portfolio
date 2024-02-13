#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Placement {
    long long int foodLevel;
    long long int pFoodLevel;
    long long int sumFoodLost;
    int id;
} Placement;

typedef struct Location {
    char name[20];
    Placement* placementList;
    int maxPlacements;
    int numPlacements;
    long long int foodTaken;
} Location;

typedef struct LocationList {
    Location* locations;
    int numLocations;
    int maxLocations;
} LocationList;

LocationList* createLocationList() {
    LocationList* locList = (LocationList*)malloc(sizeof(LocationList));
    locList->numLocations = 0;
    locList->maxLocations = 10;
    locList->locations = (Location*)malloc(sizeof(Location) * locList->maxLocations);

    return locList;
}

Location* createLocation(LocationList* locList, char name[20]) {
    if (locList->numLocations == locList->maxLocations - 1) {
        locList->maxLocations *= 2;
        locList->locations = realloc(locList->locations, locList->maxLocations * sizeof(Location));
    }

    Location* loc = &(locList->locations[locList->numLocations]);
    strncpy(loc->name, name, sizeof(loc->name));
    loc->numPlacements = 0;
    loc->maxPlacements = 10;
    loc->foodTaken = 0;
    loc->placementList = (Placement*)malloc(sizeof(Placement) * loc->maxPlacements);

    locList->numLocations++;

    return loc;
}

void appendData(LocationList* locList, int id, long long int foodLevel, int tracker) {

    if (locList->locations[tracker].numPlacements == locList->locations[tracker].maxPlacements) {
        locList->locations[tracker].maxPlacements *= 2;
        locList->locations[tracker].placementList = realloc(locList->locations[tracker].placementList, locList->locations->maxPlacements * sizeof(Placement));
    }

    // Populate the new placement
    Placement newPlacement;
    newPlacement.id = id;
    newPlacement.foodLevel = foodLevel;
    newPlacement.sumFoodLost = 0;
    // Add the new placement to the list
    locList->locations[tracker].placementList[locList->locations[tracker].numPlacements] = newPlacement;
    
    locList->locations[tracker].numPlacements++;
}

void appendPlacementData(LocationList* locList, long long int foodLevel, int id, int tracker){

    if (locList->locations[tracker].numPlacements == locList->locations[tracker].maxPlacements) {
        locList->locations[tracker].maxPlacements *= 2;
        locList->locations[tracker].placementList = realloc(locList->locations[tracker].placementList, locList->locations[tracker].maxPlacements * sizeof(Placement));
    }

    Placement newPlacement;
    newPlacement.foodLevel = foodLevel;
    newPlacement.sumFoodLost = 0;
    newPlacement.id = id;
    locList->locations[tracker].placementList[locList->locations[tracker].numPlacements] = newPlacement;
    locList->locations[tracker].numPlacements++;

}

int alterData(LocationList* locList, int tracker, int id, int foodLevel){
    int newPlacement;
    long long int tFoodLost;
    for(int j = 0; j < locList->locations[tracker].numPlacements; j++){
            
        if(locList->locations[tracker].placementList[j].id == id){
            if(locList->locations[tracker].placementList[j].foodLevel > foodLevel){
                
                locList->locations[tracker].placementList[j].sumFoodLost += (locList->locations[tracker].placementList[j].foodLevel - foodLevel);
                tFoodLost = (locList->locations[tracker].placementList[j].foodLevel - foodLevel);
                //locList->locations[tracker].placementList[j].pFoodLevel = locList->locations[tracker].placementList[j].foodLevel;
                locList->locations[tracker].placementList[j].foodLevel = foodLevel;
                printf("%lld\n", tFoodLost);
            }
            else if(locList->locations[tracker].placementList[j].foodLevel < foodLevel){
                
                // locList->locations[tracker].placementList[j].sumFoodLost -= (foodLevel - locList->locations[tracker].placementList[j].foodLevel);
                
                locList->locations[tracker].placementList[j].foodLevel = foodLevel;
                printf("%d\n", 0);
            }
            else if(locList->locations[tracker].placementList[j].foodLevel == foodLevel){
                printf("%d\n", 0);
            }
            
            newPlacement = 1; // Update newPlacement after altering data
            break;
        }
        newPlacement = 0;
    }
    
    return newPlacement;
}

void totalLoss(LocationList* locList, int amntLoc, int amntPlacement){

    for (int i = 0; i < amntLoc; i++) {
        for(int j = 0; j < amntPlacement; j++){
            locList->locations[i].foodTaken += locList->locations[i].placementList[j].sumFoodLost; //add the sum food lost from each placement in location to total food taken
        }
    }
    
}

int main() {
    LocationList* locList = createLocationList();

    char name[20];
    int id;
    long long int foodLevel;
    int newLocation;
    int newPlacement;
    int tracker = 0; //used to keep track of index
    while(1){
        newLocation = 0;
        newPlacement = 0;

        scanf("%19s %d %lld", name, &id, &foodLevel); //get user input

        //termination case
        if(strcmp(name, "END") == 0 && id == -1 && foodLevel == -1){
            break;
        }

        for(tracker = 0; tracker < locList->numLocations; tracker++){

            if(strcmp(locList->locations[tracker].name, name) == 0){ //if location name already in array, dont append new location
                newLocation = 1; //Location already there
                break;
            }
            
        }

        if(newLocation != 1){ //append new location and the parameter included with it if location isnt there
            createLocation(locList, name);
            appendData(locList, id, foodLevel, tracker);
            printf("New placement.\n");
            continue;
        }

        for(int i = 0; i < locList->numLocations; i++){
            if(strcmp(locList->locations[i].name, name) == 0 ){
                tracker = i;
            }
        }

        newPlacement = alterData(locList, tracker, id, foodLevel);

        if(newPlacement != 1){ //append new placement and the parameter if no placement found
            appendPlacementData(locList, foodLevel, id, tracker);
            printf("New placement.\n");
        }

    }

    int amntLoc = locList->numLocations;
    int amntPlacement = locList->locations->numPlacements;
    // Add sum of food lossed from placements of each location
    totalLoss(locList, amntLoc, amntPlacement);

    for (int i = 0; i < amntLoc; i++) {
        printf("%s %lld\n", locList->locations[i].name, locList->locations[i].foodTaken);
    }

    // Free allocated memory
    for (int i = 0; i < amntPlacement; i++) {
        free(locList->locations[i].placementList);
    }
    free(locList->locations);
    free(locList);

    return 0;
}