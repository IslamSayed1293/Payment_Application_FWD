#include "../card/card.h"

int main()
{
    EN_cardError_t ret;
    ST_cardData_t cardData;

    printf("\nTester Name: Islam sayed\n");
    printf("Function Name: getCardHolderName\n");
     //test case 1
    printf("Test Case 1: Correct Name\n");
    printf("Input Data: ");
    ret=getCardHolderName(&cardData);
    printf("\nExpected Result: CARD_OK\n");
    if(ret==0)
        printf("Actual Result: CARD_OK\n");
    else
        printf("Actual Result: WRONG_NAME\n");
    //test case 2
    printf("\n\nTest Case 2: Name with length less than 20 char\n");
    printf("Input Data: ");
    ret=getCardHolderName(&cardData);
    printf("\nExpected Result: WRONG_NAME\n");
    if(ret==1)
        printf("Actual Result: WRONG_NAME\n");
    else
        printf("Actual Result: CARD_OK\n");

    printf("\n\nTest Case 3: Name with length more than 25 char\n");
    printf("Input Data: ");
    ret=getCardHolderName(&cardData);
    printf("\nExpected Result: WRONG_NAME\n");
    if(ret==1)
        printf("Actual Result: WRONG_NAME\n");
    else
        printf("Actual Result: CARD_OK\n");

    printf("\n\nTest Case 3: Name with special char premitted length name\n");
    printf("Input Data: ");
    ret=getCardHolderName(&cardData);
    printf("\nExpected Result: WRONG_NAME\n");
    if(ret==1)
        printf("Actual Result: WRONG_NAME\n");
    else
        printf("Actual Result: CARD_OK\n");



    return 0;
}
