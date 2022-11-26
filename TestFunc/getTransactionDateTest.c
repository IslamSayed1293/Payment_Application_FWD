#include "../terminal/terminal.h"

int main()
{
    EN_terminalError_t ret;
    ST_terminalData_t termData;

    printf("\nTester Name: Islam sayed\n");
    printf("Function Name: getTransactionDate\n");
    //test case 1
    printf("\n\nTest Case 1: Correct date \n"); 
    printf("Input Data: ");
    ret=getTransactionDate(&termData);
    printf("\nExpected Result: TERMINAL_OK\n");
    if(ret==0)
        printf("Actual Result: TERMINAL_OK\n");
    else
        printf("Actual Result: WRONG_DATE\n");
    //test case 2
    printf("\n\nTest Case 2: Wrong Formate\n"); 
    printf("Input Data: ");
    ret=getTransactionDate(&termData);
    printf("\nExpected Result: WRONG_DATE\n");
    if(ret==1)
        printf("Actual Result: WRONG_DATE\n");
    else
        printf("Actual Result: TERMINAL_OK\n");
    //test case 3
    printf("\n\nTest Case 3: Wrong month number\n"); 
    printf("Input Data: ");
    ret=getTransactionDate(&termData);
    printf("\nExpected Result: WRONG_DATE\n");
    if(ret==1)
        printf("Actual Result: WRONG_DATE\n");
    else
        printf("Actual Result: TERMINAL_OK\n");

    

    return 0;
}