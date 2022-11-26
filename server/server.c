/*
 # File:   server.c
 # Date:   25/10/2022
 # Author: islam sayed
 */

#include "server.h"

#define Size_Of_Accounts_DB 255
#define SIZE_OF_TRANSACTION_DB 255

uint8_t gIndexOfValidAccount;
uint16_t gLastIndexSavedTrans = 0;
static uint32_t gLastSequenceNumber =1;

ST_accountsDB_t ST_Accounts_DB_t[Size_Of_Accounts_DB] = {
    1500000.00,RUNNING,
    "121993000000000001",
    1000000.00,RUNNING,
    "121993000000000002",
    1200000.00,RUNNING,
    "121993000000000003",
    500.0,BLOCKED,
    "121993000000000004",
    6500000.00,BLOCKED,
    "121993000000000005",
    5000.00,BLOCKED,
    "121993000000000006",
};
ST_transaction_t ST_Transactions_DB_t[Size_Of_Accounts_DB] = {0};

static EN_serverError_t isAvailabeAccount(char *PAN, uint8_t*gIndexOfValidAccount)
{
    uint8_t i;
    EN_serverError_t Result = SERVER_OK;
     for (i = 0; i < Size_Of_Accounts_DB; i++)
     {
        if(srlen(ST_Accounts_DB_t[i].primaryAccountNumber)> 0)
        {
            if (strcmp(PAN, ST_Accounts_DB_t[i].primaryAccountNumber) == 0)
            {
                *gIndexOfValidAccount= i;
                if(ST_Accounts_DB_t[i].state == RUNNING)
                {
                   Result = SERVER_OK;
                   break;
                }
                else if((ST_Accounts_DB_t[i].state == BLOCKED))
                {
                    Result = BLOCKED_ACCOUNT;
                    break;
                }
            }
            else 
            {
                continue;
            }
        }
        else
        {
            Result= ACCOUNT_NOT_FOUND;
            break;
        }
     }
     return Result;

}

EN_serverError_t isValidAccount(ST_cardData_t *cardData,  ST_accountsDB_t* accountRefrence)
{
    EN_serverError_t Result = ACCOUNT_NOT_FOUND;
    Result = isAvailabeAccount(cardData->primaryAccountNumber, &gIndexOfValidAccount);
    accountRefrence=&ST_Accounts_DB_t[gIndexOfValidAccount];
    return Result;
}

EN_serverError_t isAmountAvailable(ST_transaction_t *transData)
{
    EN_serverError_t Result = SERVER_OK;
    EN_serverError_t isAvailable = SERVER_OK;
    if (transData == NULL)
    {
        Result = ACCOUNT_NOT_FOUND;
    }
    else
    {
        isAvailable = isAvailabeAccount(transData->cardHolderData.primaryAccountNumber, &gIndexOfValidAccount);
        
        if (isAvailable == SERVER_OK)
        {          
            if ((transData->terminalData.transAmount) < (ST_Accounts_DB_t[gIndexOfValidAccount].balance))
            {    
                Result = SERVER_OK;
            }
            else
            {
                Result = LOW_BALANCE;
            }
        }
        else if(isAvailable == BLOCKED_ACCOUNT)
        {
             Result = BLOCKED_ACCOUNT;
        }
        else
        {
            Result = ACCOUNT_NOT_FOUND;
        }
    }
    return Result; 
}

EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
    EN_transState_t Result = APPROVED;
    if(transData == NULL)
    {
        Result = INTERNAL_SERVER_ERROR;
    }
    else
    {
        EN_serverError_t checkAcountValidity = ACCOUNT_NOT_FOUND;
        EN_serverError_t checkAmountAvilabilty = ACCOUNT_NOT_FOUND;
        checkAcountValidity = isValidAccount(&transData->cardHolderData,&ST_Accounts_DB_t[gIndexOfValidAccount]);
        checkAmountAvilabilty = isAmountAvailable(transData);
        if (checkAcountValidity == ACCOUNT_NOT_FOUND)
        {
            Result = FRAUD_CARD;
        }
        else if(checkAcountValidity == BLOCKED_ACCOUNT)
        {
            Result = DECLINED_STOLEN_CARD;
        }
        else if (checkAmountAvilabilty == LOW_BALANCE)
        {
            Result = DECLINED_INSUFFECIENT_FUND;
        }
        else
        {
            EN_serverError_t checkSavedTrans = SAVING_FAILED;
            checkSavedTrans = saveTransaction(transData);
            if (checkSavedTrans != SERVER_OK)
            {
                Result = INTERNAL_SERVER_ERROR;
            }
            else
            {
                float newBalance = 0.f;
                
                newBalance = ST_Accounts_DB_t[gIndexOfValidAccount].balance - transData->terminalData.transAmount;
                ST_Accounts_DB_t[gIndexOfValidAccount].balance = newBalance;
                transData->transState=APPROVED;
            }

        }
    }
    return Result;
}

EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
    EN_serverError_t Result = SERVER_OK;

    if (transData == NULL)
    {
        transData->transState = INTERNAL_SERVER_ERROR;
        Result = SAVING_FAILED;
    }
    else
    {
        if (gLastIndexSavedTrans < 255)
        {
            transData->transactionSequenceNumber = gLastSequenceNumber;
            ST_Transactions_DB_t[gLastIndexSavedTrans].transactionSequenceNumber = transData->transactionSequenceNumber;

            strcpy(ST_Transactions_DB_t[gLastIndexSavedTrans].cardHolderData.cardHolderName, transData->cardHolderData.cardHolderName);
            strcpy(ST_Transactions_DB_t[gLastIndexSavedTrans].cardHolderData.primaryAccountNumber, transData->cardHolderData.primaryAccountNumber);
            strcpy(ST_Transactions_DB_t[gLastIndexSavedTrans].cardHolderData.cardExpirationDate, transData->cardHolderData.cardExpirationDate);

            ST_Transactions_DB_t[gLastIndexSavedTrans].terminalData.transAmount = transData->terminalData.transAmount;
            ST_Transactions_DB_t[gLastIndexSavedTrans].terminalData.maxTransAmount = transData->terminalData.maxTransAmount;
            strcpy(ST_Transactions_DB_t[gLastIndexSavedTrans].terminalData.transactionDate, transData->terminalData.transactionDate);

            ST_Transactions_DB_t[gLastIndexSavedTrans].transState = APPROVED;
            transData->transState = APPROVED;

            gLastSequenceNumber++;
            gLastIndexSavedTrans++;
            Result = SERVER_OK;
        }
        else
        {
            transData->transState = INTERNAL_SERVER_ERROR;
            Result = SAVING_FAILED;
        }
    }

    return Result;
}

