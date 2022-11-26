#include "../card/card.h"
#include "../terminal/terminal.h"

int main()
{
    EN_terminalError_t ret;
    ST_cardData_t cardData;
    ST_terminalData_t termData;

    printf("\nTester Name: Islam sayed\n");
    printf("Function Name: isCardExpried\n");
    getCardExpiryDate(&cardData);
    getTransactionDate(&termData);
    //test case 1
    printf("\n\nTest Case 1: expiration date is after the transaction date\n"); 
    printf("Input Data: ");
    ret=isCardExpired(&cardData, &termData);
    printf("\nExpected Result: TERMINAL_OK\n");
    if(ret==0)
        printf("Actual Result: TERMINAL_OK\n");
    else
        printf("Actual Result: EXPIRED_CARD\n");
    //test case 2
    printf("\n\nTest Case 2: expiration date is befor the transaction date\n"); 
    printf("Input Data: ");
    ret=isCardExpired(&cardData, &termData);    
    printf("\nExpected Result: EXPIRED_CARD\n");
    if(ret==2)
        printf("Actual Result: EXPIRED_CARD\n");
    else
        printf("Actual Result: TERMINAL_OK\n");
    

    return 0;
}