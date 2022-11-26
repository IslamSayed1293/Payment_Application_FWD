#include "../terminal/terminal.h"

int main()
{
    EN_terminalError_t ret;
    ST_terminalData_t termData;

    printf("\nTester Name: Islam sayed\n");
    printf("Function Name: getTransactionDate\n");
    //test case 1
    printf("\n\nTest Case 1:the amount is smaller than the terminal max allowed amount \n"); 
    printf("Input Data: ");
    ret=isBelowMaxAmount(&termData);
    printf("\nExpected Result: TERMINAL_OK\n");
    if(ret==0)
        printf("Actual Result: TERMINAL_OK\n");
    else
        printf("Actual Result: EXCEED_MAX_AMOUNT\n");
    //test case 2
    printf("\n\nTest Case 2:the amount is larger than the terminal max allowed amount\n"); 
    printf("Input Data: ");
    ret=isBelowMaxAmount(&termData);
    printf("\nExpected Result: EXCEED_MAX_AMOUNT\n");
    if(ret==5)
        printf("Actual Result: EXCEED_MAX_AMOUNT\n");
    else
        printf("Actual Result: TERMINAL_OK\n");

    return 0;
}