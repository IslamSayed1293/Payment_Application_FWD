#include "../terminal/terminal.h"

int main()
{
    EN_terminalError_t ret;
    ST_terminalData_t termData;

    printf("\nTester Name: Islam sayed\n");
    printf("Function Name: getTransactionDate\n");
    //test case 1
    printf("\n\nTest Case 1:the max amount greater than to 0  \n"); 
    printf("Input Data: ");
    ret=getTransactionDate(&termData);
    printf("\nExpected Result: TERMINAL_OK\n");
    if(ret==0)
        printf("Actual Result: TERMINAL_OK\n");
    else
        printf("Actual Result: INVALID_MAX_AMOUNT\n");
    //test case 2
    printf("\n\nTest Case 2:the max amount less than or equal to 0 \n"); 
    printf("Input Data: ");
    ret=getTransactionDate(&termData);
    printf("\nExpected Result: INVALID_MAX_AMOUNT\n");
    if(ret==6)
        printf("Actual Result: INVALID_MAX_AMOUNT\n");
    else
        printf("Actual Result: TERMINAL_OK\n");

    return 0;
}