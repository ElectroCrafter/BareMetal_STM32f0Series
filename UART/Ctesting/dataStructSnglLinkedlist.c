#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
/*
--Objective--
Create a single nexted list
1. Create an head node for initial nexted list
--Impact--
*/


/*
--the structure of a node--
it cointains :
    -data (value of that node)
    -next (the address connects to an another node)
    -own nodes address (will pass to next node)
*/
struct node
{
    int data;           //value
    struct node *next ; //the next address node
};

struct node* createNode(int data)
{    
    // Allocate memory for a node structure using malloc
    struct node* newNode = (struct node *)malloc(sizeof(struct node));
    
    //check if memory allocation was succesfull
    if (newNode==NULL){
        printf("Memory allocation failed.\\n");
        exit(1); 
    }
    
    //--Create a new node--//
    // fill the data with value
    newNode-> data = data;
    // create a next for new last node with NULL address
    newNode-> next = NULL;
    return newNode;
};

void insHead(struct node **headPtr,int data){
    //1. aloocate memodry for the new node
    struct node* newNode = (struct node *)malloc(sizeof(struct node));
    
    //check if memory allocation was succesfull
    if (newNode==NULL){
        printf("Memory allocation failed.\\n");
        exit(1); 
    }
    // else{
    //     puts("memory allocation sucessed");
    // }

    //2. Set data and next pointer
    //store a new data into new node
    newNode->data = data;
    //set the next pointer into new node address for current node
    newNode->next = *headPtr;

    //3. Update the head pointer to the point to the new node
    *headPtr = newNode;
}

void freeList(struct node* head) {
    struct node* temp;
    //address NULL is an empty node
    while (head != NULL) {
        //update temp node into head
        temp = head;
        //change head node into next node
        head = head->next;
        //clear memory on the temp (it means prev head)
        free(temp);
    }
}
void printList(struct node *ptrNode) {
    puts("Linkedlist");
    //address NULL is an empty node
    while (ptrNode != NULL) {
        printf("%d > ", ptrNode->data);
        ptrNode = ptrNode->next;
    }
    printf("\n");
}

//insert a node after tail
void insAfterTail(struct node **headPtr,int data){
    //1. aloocate memory for the new node
    struct node* newNode = (struct node *)malloc(sizeof(struct node));
    //insert the value of data into new Node
    newNode->data = data;
    //insert the NULL address into next point for the last node
    newNode->next = NULL;
    
    //2. Check if memory allocation was succesfull
    if (newNode==NULL){
        printf("Memory allocation failed.\\n");
        exit(1); 
    }

    //3. Check if the List is Empty
    if (*headPtr==NULL){
        // the initial head pointer
        *headPtr = newNode;
        return;
    }

    //4. Transverse the List to Find the Last Node
    //create a new node to scan each node from head until the tail
    //this code only works with nodes with greater than 2 
    struct node *current = *headPtr;
    while(current->next!=NULL){
        current = current->next;
        // puts("inside function");
        // printf("data:%d\tAddress:%d\tNextAddress:%d\n",current->data,current,current->next);
    }

    //5. Insert the New Node at the End of the list
    current->next = newNode;

    /*--To sum up--
    -1 nodes                : STEP 1,2,3
    -2 nodes                : STEP 1,2,3,5
    -greate than 2 nodes    : ALL STEP
    */
    // printf("data:%d\tAddress:%d\tNextAddress:%d\n",current->data,current,current->next);
    // puts("inside function");
    // printf("data:%d\tAddress:%d\tNextAddress:%d\n",(*headPtr)->data,*headPtr,(void*)(*headPtr)->next);

}

int main (){
    // Declare an empty pointer to a Point structure with NULL value
    struct node *head = NULL;
    /*
    node-> data = NULL  //At this point, head doesn't hold any data value because it's a pointer variable
    node-> next = NULL  //there is no node following it
    node = NULL         //the node only stores NULL, it means hoesn't point to any valid memory
    */
    
    //share the head memory address to manipulate it
    // insHead(&head,100);
    // insHead(&head,-4);
    // insHead(&head,21);
    // insHead(&head,-32);
    // insHead(&head,45);
    // insHead(&head,0);
    insAfterTail(&head,33);
    insAfterTail(&head,-45);
    insAfterTail(&head,12312);
    insAfterTail(&head,-32);
    insAfterTail(&head,0);
    
    // puts("Outside function");
    // if (head!=NULL){
    //     printf("data:%d\tAddress:%d\tNextAddress:%d\n",head->data,head,(void*)head->next);
    // }

    printList(head);

    // Free the memory allocated for the linked list
    freeList(head);
    
    return 0 ;
}