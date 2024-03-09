#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
typedef struct Stack Stack;

struct Node{
    long long int wealth;
    Node* next;
};

struct Stack{
    Node* head; //each head is a node that contains a value "wealth" and another node "next" 
    int size; //tells how many heads (or nodes) the stack contains
};

Node* createNode(long long int wealth){ //creates a node with wealth value
    Node* res = (Node*)malloc(sizeof(Node));

    res->wealth = wealth;
    res->next = NULL;

    return res;
}

Node* insertHead(Node* head, long long int wealth){ //inserts a new value into the stack (makes this the new top of the stack)
    Node* newHead = createNode(wealth);
    newHead->next = head;

    return newHead;
}

Node* removeHead(Node* head){ //removes the top of the stack
    if(head){
        //printf("%lld\n", head->wealth);
        Node* oldHead = head;
        head = head->next;
        free(oldHead);
    }

    return head;
}

void push(Stack* stk, long long int wealth){ //pushes value onto the stack
    stk->head = insertHead(stk->head, wealth);
    stk->size++;

}

void pop(Stack* stk){ //removes value from the stack
    stk->head = removeHead(stk->head);
    stk->size--;
}


void mergeSort(long long int* arr, int len){
    if(len <= 1)return; //base case (already sorted)

    int halfLen = len/2;

    //sort first half
    mergeSort(arr, halfLen);
    
    //sort last half
    mergeSort(&arr[halfLen], len - halfLen);

    //merge
    long long int* tmp = (long long int*)malloc(sizeof(long long int) * len); //used to store the new morged array that is sorted for recursive call
    int fptr = 0; //used to track what index the first half of array is at
    int bptr = halfLen; //used to track what index the second half of array is at

    for(int i = 0; i < len; i++){
        if(fptr == halfLen){ //if traversed through all of first half array, store remaining elements in second half of array to tmp array
            tmp[i] = arr[bptr];
            bptr++;
        } else if (bptr == len){ //if traversed through all of second half array, store remaining elements in first half of array to tmp array
            tmp[i] = arr[fptr];
            fptr++;
        } else if(arr[fptr] <= arr[bptr]){ //if value at fptr index in first half array is less then value at bptr index in second array half, then store the value at fptr index in first half array to tmp array
            tmp[i] = arr[fptr];
            fptr++;
        } else{ //if value at fptr index in first half array is greater then value at bptr index in second array half, then store the value at bptr index in second half array to tmp array
            tmp[i] = arr[bptr];
            bptr++;
        }
    }

    for(int i = 0; i < len; i++){
        arr[i] = tmp[i]; //stores the new merged sorted array into the array that was passed through to the function as that is what is used in main
    }

    free(tmp); //free the tmp array as it is no longer being used
}

int count = 0; //used to keep track of what index the shop BTS shop couldn't buy is (so when in next loop can check again to see if BTS shop can buy it then)
long long int biggestComp = 0; //used to store the value of the biggest competitor shop's wealth (what BTS Shop is trying to beat)

int buyShops(Stack* stk, long long int* arr, long long int btsWealth, int numShops){
     
    static int shopsBought = 0; //keeps track of how many shops are bought during loop

    while(1){
        if(btsWealth > biggestComp){ //if BTS shop wealth is greater than the biggest competitor's wealth, return how many shops have been bought to get to that value
            return shopsBought; //return amount of shops bought
        }

        for(int i = count; i < numShops; i++){ //pushs all shops that can be bought into stack, with the most expensive shop on top
            if(btsWealth > arr[i]){
                push(stk, arr[i]); //push bought competitor's shop to stack
                count++; //increase index if shop is pushed onto stack
            }
            else{
                break; //if bts shop's wealth is less than current competitor's wealth, stop pushing to stack
            }
        }

        if(stk->head == NULL){ //if stack is empty, means that no more shops can be bought and BTS shop wealth is maximized, so BTS shop has less wealth then biggest competitor
            return -1; //BTS shop can't be the wealthiest shop
        }

        if(stk->head != NULL){ //if stack isn't empty, add wealth from top of stack to bts shop wealth
            btsWealth += stk->head->wealth; 
            pop(stk); //delete the top of stack 
            shopsBought++; //increase counter for how many shops have been bought
        }
    }
}


int main(){
    int numShops; //used to get num of competing shops
    long long int startingWealth; //used to get the starting wealth of BTS

    scanf("%d %lld", &numShops, &startingWealth); //gets input for num shops competing and inital wealth of BTS

    long long int* wealthOfShops = (long long int*)malloc(sizeof(long long int) * numShops); //creates an empty array of how much wealth each shop n has

    for(int i = 0; i < numShops; i++){
        scanf("%lld", &wealthOfShops[i]); //gets the wealth of each shop and puts in array
    }

    mergeSort(wealthOfShops, numShops); //sorts all the wealths of the shop in order of least to greatest, then puts it in a stack so that the greatest is on top
    
    biggestComp = wealthOfShops[numShops-1]; //gets the wealth of the biggest competitor

    Stack shops; //create stack

    //initialize stack
    shops.size = 0;
    shops.head = NULL;
    
    printf("%d", buyShops(&shops, wealthOfShops, startingWealth, numShops)); //print the amount of shops needing to be bought to be the wealthiest shop on the block
    free(wealthOfShops); //frees the dynamic array

    while(shops.head){ //frees all the remaining nodes in the stack
        pop(&shops);
    }
}