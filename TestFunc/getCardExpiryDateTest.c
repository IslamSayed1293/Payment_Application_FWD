#include "../card/card.h"

int main()
{
    EN_cardError_t ret;
    ST_cardData_t cardData;

    printf("\nTester Name: Islam sayed\n");
    printf("Function Name: getCardExpiryDate\n");
    //test case 1
    printf("\n\nTest Case 1: Correct date\n"); 
    printf("Input Data: ");
    ret=getCardExpiryDate(&cardData);
    printf("\nExpected Result: CARD_OK\n");
    if(ret==0)
        printf("Actual Result: CARD_OK\n");
    else
        printf("Actual Result: WRONG_EXP_DATE\n");
    //test case 2
    printf("\n\nTest Case 2: Wrong Formate\n"); 
    printf("Input Data: ");
    ret=getCardExpiryDate(&cardData);
    printf("\nExpected Result: WRONG_EXP_DATE\n");
    if(ret==2)
        printf("Actual Result: WRONG_EXP_DATE\n");
    else
        printf("Actual Result: CARD_OK\n");
    //test case 3
    printf("\n\nTest Case 3: Wrong month number\n"); 
    printf("Input Data: ");
    ret=getCardExpiryDate(&cardData);
    printf("\nExpected Result: WRONG_EXP_DATE\n");
    if(ret==2)
        printf("Actual Result: WRONG_EXP_DATE\n");
    else
        printf("Actual Result: CARD_OK\n");

    

    return 0;
}