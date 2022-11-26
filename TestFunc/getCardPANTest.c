#include "../card/card.h"

int main()
{
    EN_cardError_t ret;
    ST_cardData_t cardData;

    printf("\nTester Name: Islam sayed\n");
    printf("Function Name: getCardPAN\n");
    //test case 1
    printf("Test Case 1: Correct PAN\n"); 
    printf("Input Data: ");
    ret=getCardPAN(&cardData);

    printf("\nExpected Result: CARD_OK\n");
    if(ret==0)
        printf("Actual Result: CARD_OK\n");
    else
        printf("Actual Result: WRONG_PAN\n");
    //test case 2
    printf("\n\nTest Case 2: PAN with length less than 16 char\n"); 
    printf("Input Data: ");
    ret=getCardPAN(&cardData);
    printf("\nExpected Result: WRONG_PAN\n");
    if(ret==3)
        printf("Actual Result: WRONG_PAN\n");
    else
        printf("Actual Result: CARD_OK\n");
    //test case 3
    printf("\n\nTest Case 3: PAN with length more than 19 char\n"); 
    printf("Input Data: ");
    ret=getCardPAN(&cardData);
    printf("\nExpected Result: WRONG_PAN\n");
    if(ret==3)
        printf("Actual Result: WRONG_PAN\n");
    else
        printf("Actual Result: CARD_OK\n");
    //test case 4
    printf("\n\nTest Case 3: PAN with alphabitic char premitted length name\n"); 
    printf("Input Data: ");
    ret=getCardPAN(&cardData);
    printf("\nExpected Result: WRONG_PAN\n");
    if(ret==3)
        printf("Actual Result: WRONG_PAN\n");
    else
        printf("Actual Result: CARD_OK\n");

    return 0;
}