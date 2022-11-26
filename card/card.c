/*
 # File:   card.c
 # Date:   25/10/2022
 # Author: islam sayed
 */

#include "card.h"


#define cardMonthStartInd   0
#define cardMonthEndInd     1
#define cardYearStartInd    3
#define cardYearEndInd      4

//function for asking card holder name
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	uint8_t cardHolderName[25];
	uint8_t cardHolderNameLength;
	EN_cardError_t Result = CARD_OK;
	EN_cardError_t IsChar = WRONG_NAME;

	// printf("please enter your card name: ");
	gets(cardHolderName);

	cardHolderNameLength = strlen(cardHolderName);

	if (cardData == NULL)
		Result = WRONG_NAME;
	else if (cardHolderNameLength < 25 && cardHolderNameLength > 19)
	{
		int i;
		for (i = 0; cardHolderName[i] != '\0'; i++)
		{
			if ((cardHolderName[i] >= 'A' && cardHolderName[i] <= 'Z')
				|| (cardHolderName[i] >= 'a' && cardHolderName[i] <= 'z')
				|| cardHolderName[i] == ' ')
				{
					IsChar = CARD_OK;
					continue;
				}
			else
			{
				IsChar = WRONG_NAME;
				Result = WRONG_NAME;
				break;
			}
		}
	}
	else
	{
		Result=WRONG_NAME;
	}
	if (IsChar == CARD_OK)
	{
		strcpy(cardData->cardHolderName, cardHolderName);
	}
	
	return Result;
}
// get card expiration date 
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	uint8_t cardExpirationDate[6];
	uint8_t cardExpirationDateLength;
	EN_cardError_t Result = CARD_OK;

	// printf("please enter your card expiration date: ");
	gets(cardExpirationDate);

	cardExpirationDateLength = strlen(cardExpirationDate);

	//To validate the month and year if the month bigger then 12 or less than 1 and the year bigger than 0
	uint8_t MONTH;
	uint8_t YEAR;

	MONTH = convertingToInteger(cardExpirationDate, cardMonthStartInd, cardMonthEndInd);
	YEAR = convertingToInteger(cardExpirationDate, cardYearStartInd, cardYearEndInd);

	if (cardData == NULL)

		Result = WRONG_EXP_DATE;
	
	else if (cardExpirationDateLength == 5 && cardExpirationDate[2] == '/' && YEAR > 0 && MONTH > 0 && MONTH < 13)

		strcpy(cardData->cardExpirationDate, cardExpirationDate);

	else
	
		Result = WRONG_EXP_DATE;
	

	return Result;
}

// get Primary Account Number
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	uint8_t primaryAccountNumber[20];
	uint8_t primaryAccountNumberLength;
	EN_cardError_t Result = CARD_OK;
	EN_cardError_t IsNumeric = CARD_OK;

	// printf("please enter your card PAN: ");
	gets(primaryAccountNumber);

	primaryAccountNumberLength = strlen(primaryAccountNumber);

	if (cardData == NULL)
		Result = WRONG_NAME;
	else if (primaryAccountNumberLength > 15 && primaryAccountNumberLength < 20)
	{
		int i;

		for (i = 0; i < primaryAccountNumberLength; i++)
		{
			if (primaryAccountNumber[i] >= '0' && primaryAccountNumber[i] <= '9')

				continue;

			else
			{
				Result = WRONG_PAN;
				IsNumeric = WRONG_PAN;
				break;
			}
		}
		if (IsNumeric == CARD_OK)

			strcpy(cardData->primaryAccountNumber, primaryAccountNumber);

	}
	else
		Result = WRONG_PAN;


	return Result;
}







