#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct Node Node;
typedef struct Stack Stack;
typedef struct Elephant Elephant;

struct Node{
    int row, col;
    Node* next;
};

struct Stack{
    Node* head;
    int size;
};

struct Elephant{
    Stack memory;
};

Node* createNode(int row, int col){ //creates the node containing the elephants location
    Node* res = (Node*)malloc(sizeof(Node));

    res->row = row; res->col = col;
    res->next = NULL;
    return res;
}

void push(Stack* stk, int row, int col, int i){
    int oldRow = row;
    int oldCol = col;
    
    switch(i){ //move elephant to new lpcation depending on where bait is located
        case 0:
            break; //ends as nothing happens to stack if elephant stays on same square
        case 1:
            stk->head->row = row-1;
            stk->head->col = col;
            break;
        case 2:
            stk->head->row = row;
            stk->head->col = col+1;
            break;
        case 3:
            stk->head->row = row+1;
            stk->head->col = col;
            break;
        case 4:
            stk->head->row = row;
            stk->head->col = col-1;
            break;
    }
    //create the stack to keep track of locations of elephants
    row = stk->head->row;
    col = stk->head->col;
    Node* newNode = createNode(oldRow, oldCol);
    newNode->next = stk->head->next;
    stk->head->next = newNode;
    
    stk->size++;    
}
    
void pop(Stack* stk){

    if(stk->head){ //remove top of stack
        Node* oldHead = stk->head;
        stk->head = stk->head->next;
        free(oldHead);
        stk->size--;
    }
}

void top(Stack* stk){
    printf("%d %d\n", stk->head->row+1, stk->head->col+1); //print the current location of elephant
}

void addBait(int ** grid, int row, int col, int amt){
    grid[row][col] += amt; //add bait to grid
}

int isFood[5] = {0}; //list to store if there is food in each direction of elephant (values will be 0 (false) or 1 (true))
int bestMove = 0; //used to find the square with the highest bait amount, if there is one

void move(Elephant* pEle, int ** grid){
    int row = pEle->memory.head->row;
    int col = pEle->memory.head->col;
    int ifOnSquare = 0; //used to check if melons on elephants square
    // printf("%d %d \n", row, col);
    
    for(int i = 0; i <= 4; i++){ //emulates the 4 directions adjacent to each elephant, as well as the square the elephant is on
        switch(i){
            case 0://if food is where the elphant is already located
                if(grid[row][col] > 0){
                    isFood[0] = grid[row][col];
                    ifOnSquare = 1;
                }
                break;
            case 1://if food is north of elephant
                if(pEle->memory.head->row -1 >= 0 && grid[row-1][col] > 0){ 
                    isFood[1] = grid[row-1][col];
                }
                break;
            case 2://if food is east of elephant
                if(pEle->memory.head->col +1 >= 0 && grid[row][col+1] > 0){ 
                    isFood[2] = grid[row][col+1];
                }
                break;
            case 3://if food is south of elephant
                if(pEle->memory.head->row +1 >= 0 && grid[row+1][col] > 0){ 
                    isFood[3] = grid[row+1][col];
                }
                break;
            case 4://if food is west of elephant 
                if(pEle->memory.head->col -1 >= 0 && grid[row][col-1] > 0){ 
                    isFood[4] = grid[row][col-1];
                }
                break;
        }
        if(ifOnSquare){ //stop loop if elephant is sitting on bait
            break;
        }
    }

    for(int i = 0; i <=4; i++){
        if(isFood[i] > bestMove){
            bestMove = isFood[i]; //find the best move from the list of baits located near elephant
        }
    }

    for(int i = 0; i <= 4; i++){ //moves the elephant in the direction with the most bait, if not sitting on any
        if(isFood[i] == bestMove && bestMove!= 0){ 
            push(&(pEle->memory), row, col, i);
        }
    }
}

int eat(Elephant* pEle, int** grid, int numEle){
    int melonsAte = 0;
    int row = pEle->memory.head->row;
    int col = pEle->memory.head->col;
    if(grid[row][col] > 0){
        melonsAte+= grid[row][col]; //find how much watermelon the elephant ate
        return melonsAte;
    }
    else{
        if(pEle->memory.head->next != NULL){ ///if elephant did not eat any bait but has moved previously, move back one step
            pop(&(pEle->memory));
        }
    }
    return 0;
}

int progressHour(Elephant* eleArr, int numEle, int** grid){
    int totalMelonsAte = 0;
    int row = 0;
    int col = 0;
    for(int i = 0; i < numEle; i++){
        if (eleArr[i].memory.head != NULL) { // Ensure head is not NULL
            move(&(eleArr[i]), grid); //attempt to move elephants
            for(int i = 0; i <= 4; i++){ //reset list used to find the direction with highest bait
                isFood[i] = 0; 
            }
            bestMove = 0; //reset best move
        }
    }
    
    for(int i = 0; i < numEle; i++){
        if (eleArr[i].memory.head != NULL) { // Ensure head is not NULL
            row = eleArr[i].memory.head->row;
            col = eleArr[i].memory.head->col;
            totalMelonsAte += eat(&(eleArr[i]), grid, numEle); //add bait eaten by each individual elephant together
            if(grid[row][col] > 0){
                grid[row][col] = 0; //reset bait on grid to 0 if eaten by elephant
            }
        }
    }
    
    return totalMelonsAte;
}


int main(){
    //get user input
    int numElephants;
    int eleRow, eleCol;
    int mSize = 0; //highest number of both the row and col inputted by user (used to create the initial grid size)
    scanf("%d", &numElephants);

    Elephant* eleArr = (Elephant*) malloc(numElephants * sizeof(Elephant));

    //add each elephant to respective row and column in the grid as inputted from user
    for(int i = 0; i < numElephants; i++){
        scanf("%d %d", &eleRow, &eleCol);
        

        eleArr[i].memory.head = createNode(eleRow-1, eleCol-1);
        eleArr[i].memory.size = 0;
    }
    
    mSize=501; //avoids seg fault for out of bounds
    //create grid
    int** grid = (int**) malloc(mSize * sizeof(int*)); //initialize rows

   
    for(int i = 0; i < mSize; i++){
        grid[i] = (int *)malloc(mSize * sizeof(int)); //initialize columns
        for (int j = 0; j < mSize; j++) {
            grid[i][j] = 0; // Initialize grid with 0
        }
    }

    //Loop to take actions until user quits program
    char choice[15];
    int amnt, row, col;
    while(1){
        scanf("%s %d %d %d", choice, &row, &col, &amnt);

        if(strcmp(choice, "BAIT") == 0){
            addBait(grid, row-1, col-1, amnt); //adds bait to grid
        }
        else if(strcmp(choice, "HOUR") == 0){
           printf("%d \n", progressHour(eleArr, numElephants, grid)); //progresses and hour and returns bait eaten
        }
        else if(strcmp(choice, "QUIT") == 0){
            for(int i = 0; i < numElephants; i++){ //prints final location of elephants and quits program
                top(&(eleArr[i].memory));
            }
            break;
        }
    }   

    //free grid
    for (int i = 0; i < mSize; i++) {
        free(grid[i]);
    }
    free(grid);

    return 0;
}