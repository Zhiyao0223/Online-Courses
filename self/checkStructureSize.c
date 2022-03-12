#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef int8_t SMALLINT;
typedef int16_t MEDIUMINT;
typedef int32_t LARGEINT;
typedef uint8_t SMALLUNINT;
typedef uint16_t MEDIUMUINT;
typedef uint32_t LARGEUNINT;


typedef union {

    float f;
    struct
    {

        // Order is important.
        // Here the members of the union data structure
        // use the same memory (32 bits).
        // The ordering is taken
        // from the LSB to the MSB.
        unsigned int mantissa : 23;
        unsigned int exponent : 8;
        unsigned int sign : 1;

    } raw;
} myfloat;

struct Data{
    int number;
    float decimal;
    double moreDecimal;
    SMALLINT        smallInt;
    MEDIUMINT       mediumInt;
    LARGEINT        largeInt;
    SMALLUNINT      smallUnInt;
    MEDIUMUINT      mediumUnInt;
    LARGEUNINT      largeUnInt;
};



void printBits(struct Data data, int size, char type[50]);
int bit_return(int a, int loc);
void printBinary(int n, int i);
void printIEEE(myfloat var);
void printIEEE1(myfloat var);


int main() {
    // Declare variables
    char input[2][100];
    struct Data data;
    char numberInput[100];
    char option = 0;
    int size = 0;

    // Taking input
    printf("Acceptable datatype: int8_t, int16_t, int32_t, uint8_t, uint16_t, uint32_t, float, double");
    while(1) {
        int i = 0;
        char option;

        printf("\nNumber %d: ", i+1);
        fgets(numberInput, 100, stdin);
        strtok(numberInput, "\n");
        if (strcmp(numberInput, "\n") == 0) {
            printf("No number entered.\n");
            return -1;
        }
        data.number = atoi(numberInput);

        printf("Datatype %d: ", i+1);
        fgets(input[i], 100, stdin);
        strtok(input[i], "\n");

        // Check if empty string
        if (strcmp(input[i], "\n") == 0) {
            printf("No string entered.\n");
            return -1;
        }

        // Check for variable match
        if (strcmp(input[i], "int8_t") == 0) {
            data.smallInt = data.number;
            size = sizeof(int8_t);
        }
        else if (strcmp(input[i], "int16_t") == 0) {
            data.mediumInt = data.number;
            size = sizeof(int16_t);
        }
        else if (strcmp(input[i], "int32_t") == 0) {
            data.largeInt = data.number;
            size = sizeof(int32_t);
        }
        else if (strcmp(input[i], "uint8_t") == 0) {
            data.smallUnInt = data.number;
            size = sizeof(uint8_t);
        }
        else if (strcmp(input[i], "uint16_t") == 0) {
            data.mediumUnInt = data.number;
            size = sizeof(uint16_t);
        }
        else if (strcmp(input[i], "uint32_t") == 0) {
            data.largeUnInt = data.number;
            size = sizeof(uint32_t);
        }
        else if (strcmp(input[i], "float") == 0) {
            data.decimal = data.number;
            size = sizeof(float);
        }
        else if (strcmp(input[i], "double") == 0) {
            data.moreDecimal = data.number;
            size = sizeof(double);
        }
        else {
            printf("Invalid datatype. Exit with status -1\n");
            return -1;
        }
        printf("Size of int8_t: %d bytes\n", size);

        // Do requirements
        printBits(data, size, input[i]);

        printf("\nDo you still want to continue?(Y/N): ");
        option = getc(stdin);
        getchar();
        if (option == 'N' || option == 'n') {
            printf("\n----------   Thanks for using the application ----------\n");
            break;
        }
        else {
            printf("Proceed to next input...\n");
        }

        i++;
    }

    return 0;
}


// Print all the bits
void printBits(struct Data data, int size, char type[50]) {
    // Declare variable
    int i = 0;
    unsigned int maxPow = 1<<(size*8-1);
    float maxPow1 = 1<<(size*8-1);


    // Loop taking bits, print last bit and shift left.
    for (;i<size*8; i++){
        // Ineffective way in checking struct values, will modify if could think of better.
        if (strcmp(type, "int8_t") == 0) {
            printf("%u",data.smallInt&maxPow ? 1 : 0);
            data.smallInt = data.smallInt<<1;
        }
        else if (strcmp(type, "int16_t") == 0) {
            printf("%u",data.mediumInt&maxPow ? 1 : 0);
            data.mediumInt = data.mediumInt<<1;
        }
        else if (strcmp(type, "int32_t") == 0) {
            printf("%u",data.largeInt&maxPow ? 1 : 0);
            data.largeInt = data.largeInt<<1;
        }
        else if (strcmp(type, "uint8_t") == 0) {
            printf("%u",data.smallUnInt&maxPow ? 1 : 0);
            data.smallUnInt = data.smallUnInt<<1;
        }
        else if (strcmp(type, "uint16_t") == 0) {
            printf("%u",data.mediumUnInt&maxPow ? 1 : 0);
            data.mediumUnInt = data.mediumUnInt<<1;
        }
        else if (strcmp(type, "uint32_t") == 0) {
            printf("%u",data.largeUnInt&maxPow ? 1 : 0);
            data.largeUnInt = data.largeUnInt<<1;
        }
        else if (strcmp(type, "float") == 0) {
            myfloat var;
            var.f = data.decimal;
            printIEEE(var);
            break;
        }
        else if (strcmp(type, "double") == 0) {
            myfloat var;
            var.f = data.moreDecimal;
            printIEEE1(var);
            break;
        }
        else {
            printf("ERROR: New bug has been discovered. RIP larr");
        }
    }
    printf("\n");
    return;
}


void printBinary(int n, int i)
{

    // Prints the binary representation
    // of a number n up to i-bits.
    int k;
    for (k = i - 1; k >= 0; k--) {

        if ((n >> k) & 1)
            printf("1");
        else
            printf("0");
    }
}


// Function to convert real value
// to IEEE floating point representation
void printIEEE(myfloat var)
{

    // Prints the IEEE 754 representation
    // of a float value (32 bits)

    printf("%d | ", var.raw.sign);
    printBinary(var.raw.exponent, 8);
    printf(" | ");
    printBinary(var.raw.mantissa, 23);
    printf("\n");
}

void printIEEE1(myfloat var)
{

    // Prints the IEEE 754 representation
    // of a float value (32 bits)

    printf("%d | ", var.raw.sign);
    printBinary(var.raw.exponent, 11);
    printf(" | ");
    printBinary(var.raw.mantissa, 52);
    printf("\n");
}