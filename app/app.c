/*
 # File:   app.c
 # Date:   25/10/2022
 # Author: islam sayed
 */

#include "app.h"

extern uint8_t gIndexOfValidAccount; 
extern ST_accountsDB_t ST_Accounts_DB_t[];


extern float gMaxTransAmount;

void appStart(void)
{
    ST_cardData_t cardData;
    ST_terminalData_t termData;
    ST_transaction_t transData;

    EN_serverError_t checkResultServ;
    EN_terminalError_t checkResultTerm;

    ST_accountsDB_t* accountRefrence=NULL;

    // Card module: get card data from user.
    getCardHolderName(&cardData);
    fflush(stdin);
    getCardExpiryDate(&cardData);
    fflush(stdin);
    getCardPAN(&cardData);
    fflush(stdin);

    // Teminal module: get terminat data and make some checks.
    setMaxAmount(&termData, gMaxTransAmount);
    getTransactionDate(&termData);
    

    checkResultTerm = isCardExpired(&cardData, &termData);

    if (checkResultTerm != TERMINAL_OK)
    {
        printf("\nDeclined Expired Card\n");
    }
    else
    {
        //to reset the value of checkResult to avoid confusion from last checkResult.
        checkResultTerm =INVALID_MAX_AMOUNT; 

        getTransactionAmount(&termData);
        fflush(stdin);
        checkResultTerm = isBelowMaxAmount(&termData);

        if ( checkResultTerm != TERMINAL_OK)
        {
            printf("\nDeclined Amount Exceeding Limit");
        }
        else
        {
            //to reset the value of checkResult to avoid confusion from last checkResult.
            checkResultServ =ACCOUNT_NOT_FOUND; 
            checkResultServ = isValidAccount(&cardData, accountRefrence);

            if(checkResultServ != TERMINAL_OK)
            {
                printf("\nDecliend invalid account\n");
            }
            else
            {
                //to reset the value of checkResult to avoid confusion from last checkResult.
                checkResultServ =ACCOUNT_NOT_FOUND;

                transData = (ST_transaction_t) {&cardData,&termData,0,0};

                checkResultServ = isAmountAvailable(&transData);

                if( checkResultServ != TERMINAL_OK )
                {
                    printf("\nDecliend insuffecient funds\n");
                }
                else
                {   
                    EN_transState_t checkResultState;
                    checkResultState = INTERNAL_SERVER_ERROR;

                    checkResultState = recieveTransactionData(&transData);

                    if(checkResultState != APPROVED)
                    {
                        printf("\nFaild\n");
                    }
                    else
                    {
                        printf("\nSuccess Transactions Process\n");
                        printf("Your Updated balance is %.2f",ST_Accounts_DB_t[gIndexOfValidAccount].balance);
                    }
                }
            }
        }
    }
}

void main(void)
{
    printf("\t\t\tWelcom to The Payment Application FWD\n");
    printf("\t\t\t The Application will start Now\n\n");

    appStart();
    
}