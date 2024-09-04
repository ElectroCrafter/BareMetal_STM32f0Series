#include <stdio.h>
#include<stdlib.h>
#include <stdint.h>

/*
--Objective--
To create swap value without using temporary variable

--Impact--
it will reduce more variable and make the system more effecient
*/
//Swap Value without using temporary variable
void swapVal(int *d1,int *d2){
    *d1 = (*d1+*d2);     //a = initiala + initialb    
    *d2 = *d1-*d2;       //b = (initiala+initialb) - initialb   ->initiala
    *d1 = *d1-*d2;       //a = initiala + initialb - b(initiala)->initialb
}

int main(void){
    int a=-20,b=100;
    uint8_t id=10;
    float arr[id];
    
    //produce random floating value on an array
    for (int i=0;i<id;i++){
        //float data type
        float scale = rand() / (float) RAND_MAX;

        //int data type
        // arr[i]=rand()%100+1; //from 1 until 100
        // printf("%d ",arr[i]);
    }

    

    //Swap Value without using temporary variable
    swapVal(&a,&b);
    printf("value a:%d\tvalue b:%d\n",a,b);

    return 0;
}