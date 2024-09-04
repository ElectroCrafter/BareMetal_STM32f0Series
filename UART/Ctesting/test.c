#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <stdint.h>
#define _OPEN_SYS_ITOA_EXT

typedef enum {
    INT,
    FLOAT,
    UINT32,
    UINT16,
    UINT8,
    STRING,
    CHR,
} DataType;
void UIntToChar(uint16_t num, char *buffer) {
    sprintf(buffer, "%u", num);  // Convert unsigned int to string
}
void serialPrint(void* data, DataType type) {
    char buffer[100];  // Adjust size as needed

    switch (type) {
        /*syntax converts integer*/
        /*
        IntToChar(*(int*)data, buffer,10);

        1. data: A pointer to the data passed to the SerialPrint function.
        2. (int*)data: Casts the void* pointer data to an int* (pointer to an integer).
        3. *(int*)data: Dereferences the int* pointer, accessing the integer value stored at that memory location.
        4. IntToChar(): A function that converts an integer to a string and stores the result in buffer.
        5. buffer: A character array where the converted string is stored.
        6. 10 -> decimal ; 2 -> binary ; 16 -> hexa
        */
        case INT:
            printf(itoa(*(int*)data,buffer,10)); 
            break;
        case UINT32:
            printf(itoa(*(uint32_t*)data,buffer,10)); 
            break;
        case UINT16:
            printf(itoa(*(uint16_t*)data,buffer,2)); 
            break;
        case UINT8:
            printf(itoa(*(uint8_t*)data,buffer,10)); 
            break;
        // case FLOAT:
        //     sprintf(buffer, "%f", *(float*)data);  // Convert float to string
        //     break;
        // case STRING:
        //     strcpy(buffer, (char*)data);  // Copy string
            break;
        default:
            return;  // Unsupported data type
    }
}

void stringLen(char *str,uint8_t *len){

    while(*str!='\0'){
        *len = *len+1;
        str++;
    }

}
//standard ID
void canTransmit(uint16_t *standardId,uint16_t *dlc,uint8_t *data, uint32_t *dataLow, uint32_t *dataHigh){
    
    //Set Unused Bytes to Zero (Padding)
    /*
    uint32_t dataLow = ((uint32_t)data[0]) | ((uint32_t)data[1] << 8) |
                   ((uint32_t)data[2] << 16) | ((uint32_t)data[3] << 24);

    uint32_t dataHigh = ((uint32_t)data[4]) | ((uint32_t)data[5] << 8) |
                    ((uint32_t)data[6] << 16) | ((uint32_t)data[7] << 24);

    */
    *dataLow = 0;
    *dataHigh = 0;

    for (int i = 0; i < *dlc && i < 4; i++) {
        *dataLow |= ((uint32_t)data[i] << (i * 8));
    }

    for (int i = 4; i < *dlc && i < 8; i++) {
        *dataHigh |= ((uint32_t)data[i] << ((i - 4) * 8));
    }

    printf("dlc Value:%d\t dlcPointerAddress:%d\n",*dlc,dlc);
}

void canReceive(uint16_t *standardId,uint16_t *dlc,uint8_t *rtr,uint8_t *data){
    uint32_t canReceiveFL = 0x11223344;
    uint32_t canReceiveHL = 0x55667788;
        //data low register
        for (int i = 0; i < *dlc && i < 4; i++) {
            data[i] = canReceiveFL&(0xFF<<i);
        }

        //data high register
        for (int i = 4; i < *dlc && i < 8; i++) {
            data[i] = canReceiveHL&(0xFF<<(i-4));
        }
}
int main(void){
    uint8_t txCanData[8]={0};
    uint32_t TDHR,TDLR;
    uint16_t stdID = 0x5;
    uint8_t remoteTxReq;
    uint16_t DLC=5;


    //dlc less than 8
    txCanData[0] = 0x11;  // Example data
    txCanData[1] = 0x22;
    txCanData[2] = 0x33;
    txCanData[3] = 0x44;
    txCanData[4] = 0x55;

    //transmit
    puts("Transmission");
    canTransmit(&stdID,&DLC,txCanData,&TDLR,&TDHR);
    printf("ID:0X%X\t DLC:%d",stdID,DLC);
    printf("low register: 0X%X\t high register: 0X%X\n",TDLR,TDHR);

    //receive
    puts("Receiver");
    canReceive(&stdID,&DLC,&remoteTxReq,txCanData);
    printf("0x");
    for (int i = 0; i < DLC; i++)
    {
        printf("%X",txCanData[i]);
    }
    
   
}