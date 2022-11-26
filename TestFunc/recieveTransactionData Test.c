#include "../server/server.h"

int main()
{
    EN_transState_t ret;
    ST_transaction_t transData;

    printf("\nTester Name: Islam sayed\n");
    printf("Function Name: getTransactionDate\n");
    //test case 1
    printf("\n\nTest Case 1:the account does not exist  \n"); 
    printf("Input Data: ");
    ret=recieveTransactionData(&transData);
    printf("\nExpected Result: FRAUD_CARD\n");
    if(ret==3)
        printf("Actual Result: FRAUD_CARD\n");
    else
        printf("Actual Result: APPROVED\n");
    //test case 2
    printf("\n\nTest Case 2: the amount is not available \n"); 
    printf("Input Data: ");
    ret=recieveTransactionData(&transData);
    printf("\nExpected Result: DECLINED_INSUFFECIENT_FUND\n");
    if(ret==1)
        printf("Actual Result: DECLINED_INSUFFECIENT_FUND\n");
    else
        printf("Actual Result: APPROVED\n");
    //test case 3
    printf("\n\nTest Case 2: the account is blocked  \n"); 
    printf("Input Data: ");
    ret=recieveTransactionData(&transData);
    printf("\nExpected Result: DECLINED_STOLEN_CARD\n");
    if(ret==2)
        printf("Actual Result: DECLINED_STOLEN_CARD\n");
    else
        printf("Actual Result: APPROVED\n");
    //test case 4
    printf("\n\nTest Case 2: the transaction can't be saved  \n"); 
    printf("Input Data: ");
    ret=recieveTransactionData(&transData);
    printf("\nExpected Result: INTERNAL_SERVER_ERROR\n");
    if(ret==4)
        printf("Actual Result: INTERNAL_SERVER_ERROR\n");
    else
        printf("Actual Result: APPROVED\n");
    //test case 5
    printf("\n\nTest Case 2: every things ok\n"); 
    printf("Input Data: ");
    ret=recieveTransactionData(&transData);
    printf("\nExpected Result: APPROVED\n");
    if(ret==0)
        printf("Actual Result: APPROVED\n");
    else
        printf("Actual Result: INTERNAL_SERVER_ERROR\n");

    return 0;
}