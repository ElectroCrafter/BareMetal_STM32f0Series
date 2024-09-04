#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#define BUFFER_SIZE 10

typedef struct {
    uint8_t buffer[BUFFER_SIZE];
    volatile uint8_t head; // Index for the next write operation
    volatile uint8_t tail; // Index for the next read operation
    volatile bool full;    // Flag indicating if the buffer is full
} CircularBuffer;

CircularBuffer uart_buffer;

uint8_t UART_Receive(void) {

}

int main() {
    char input[6];

	/*
	check size of uart_buffer -> BUFFER_SIZE+1=1+1
	it can be reduced with another method on the struct 
	*/

	// printf("size of CircularBuffer :%d\n",sizeof(uart_buffer));


    // printf("Enter data from keyboard. To exit, type 'exit'.\n");
    
    //initialize random int values
    srand(time(NULL)); 
    uint32_t id=10;
    int arr[id];
    int i;
    for (i=0;i<id;i++){
        arr[i]=rand()%100+1; //from 1 until 100
        printf("%d ",arr[i]);
    }

    // while (1) {

		// read on string
        // fgets(input, sizeof(input), stdin);
        // Remove trailing newline character
        // input[strcspn(input, "\n")] = 0;

        // Check if user wants to exit
        // if (strcmp(input, "exit") == 0) {
        //     printf("Exiting...\n");
        //     break;
        // }
		
		//read single char
		// printf("Enter a single character: ");
    	// scanf(" %c", &input); // Notice the space before %c

        // printf("You entered: %c\n", input);
    // }

    return 0;
}
