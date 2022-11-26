#include "../server/server.h"

int main()
{
    EN_serverError_t ret;
    ST_transaction_t transData;

    printf("\nTester Name: Islam sayed\n");
    printf("Function Name: getTransactionDate\n");
    //test case 1
    printf("\n\nTest Case 1:the transaction amount is greater than the balance\n"); 
    printf("Input Data: ");
    ret=isAmountAvailable(&transData);
    printf("\nExpected Result: LOW_BALANCE\n");
    if(ret==4)
        printf("Actual Result: LOW_BALANCE\n");
    else
        printf("Actual Result: SERVER_OK\n");
    //test case 2
    printf("\n\nTest Case 2: the transaction amount is lower than the balance\n"); 
    printf("Input Data: ");
    ret=isAmountAvailable(&transData);
    printf("\nExpected Result: SERVER_OK\n");
    if(ret==0)
        printf("Actual Result: SERVER_OK\n");
    else
        printf("Actual Result: LOW_BALANCE\n");

    return 0;
}