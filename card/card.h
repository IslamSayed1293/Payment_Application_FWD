/*
 # File:   card.h
 # Date:   25/10/2022
 # Author: islam sayed
 */

#ifndef CARD_H
#define CARD_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct ST_cardData_t
{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
    CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;
typedef unsigned char uint8_t;
EN_cardError_t getCardHolderName(ST_cardData_t* cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);
EN_cardError_t getCardPAN(ST_cardData_t* cardData);

static uint16_t convertingToInteger(const char* String, uint8_t start, uint8_t end)
{
    uint16_t ResultInteger;
    uint8_t j = 0;
    uint8_t i = 0;

    char  ResultString[4];

    for (i = start; i <= end; ++i)
    {
        ResultString[j++] = String[i];
    }
    ResultString[j] = '\0';

    ResultInteger = atoi(ResultString);

    return ResultInteger;
}

#endif 