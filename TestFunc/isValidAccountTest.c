#include "../server/server.h"

int main()
{
    EN_serverError_t ret;
    ST_cardData_t cardData;
    ST_accountsDB_t* accountRefrence=0;

    printf("\nTester Name: Islam sayed\n");
    printf("Function Name: getTransactionDate\n");
    //test case 1
    printf("\n\nTest Case 1:the PAN doesn't exist\n"); 
    printf("Input Data: ");
    ret=isValidAccount(&cardData,&accountRefrence);
    printf("\nExpected Result: ACCOUNT_NOT_FOUND\n");
    if(ret==3)
        printf("Actual Result: ACCOUNT_NOT_FOUND\n");
    else
        printf("Actual Result: SERVER_OK\n");
    //test case 2
    printf("\n\nTest Case 2: every things ok\n"); 
    printf("Input Data: ");
    ret=isValidAccount(&cardData,&accountRefrence);
    printf("\nExpected Result: SERVER_OK\n");
    if(ret==0)
        printf("Actual Result: SERVER_OK\n");
    else
        printf("Actual Result: ACCOUNT_NOT_FOUND\n");

    return 0;
}