/*
 # File:   terminal.c
 # Date:   25/10/2022
 # Author: islam sayed
 */

#include "terminal.h"

#define TransDayStartInd    0   // start index of day of transaction date
#define TransDayEndInd       1	// end index of day of transaction date
#define TransMonthStartInd   3	// start index of month of transaction date
#define TransMonthEndInd     4	// end index of month of transaction date
#define TransYearStartInd    6	// start index of year of transaction date
#define TransYearEndInd      9	// end index of year of transaction date

#define cardMonthStartInd   0	// start index of month of card expiry date
#define cardMonthEndInd     1	// end index of month of card expiry date
#define cardYearStartInd    3	// start index of year of card expiry date
#define cardYearEndInd      4	// end index of year of card expiry date
float gMaxTransAmount = 20000.0f;

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	uint8_t transactionDate[11];
	uint8_t transactionDateLength;
	EN_terminalError_t Result = TERMINAL_OK;
	uint8_t DAY;
	uint8_t MONTH;
	uint16_t YEAR;

	printf("please enter the transaction date in form  DD/MM/YYYY:");
	gets(transactionDate);

	transactionDateLength = strlen(transactionDate);

	//To validate the day less than 32 or bigger than 0 , the month less than 13 or bigger than 0 and the year bigger than 0
	DAY = convertingToInteger(transactionDate, TransDayStartInd, TransDayEndInd);
	MONTH = convertingToInteger(transactionDate, TransMonthStartInd, TransMonthEndInd);
	YEAR = convertingToInteger(transactionDate, TransYearStartInd, TransYearEndInd);
	if (termData == NULL)
		Result = WRONG_DATE;
	else if ((transactionDateLength == 10) && (transactionDate[2] == '/') && (transactionDate[5] == '/') &&( YEAR > 0 )&& (MONTH > 0 )&&( MONTH < 13 )&& (DAY > 0 )&&( DAY < 32))
		strcpy(termData->transactionDate, transactionDate);
	else 
		Result = WRONG_DATE;

	return Result;
}

EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
	uint8_t CardMonth;
	uint16_t CardYear;
	uint8_t TermMonth;
	uint16_t TermYear;

	EN_terminalError_t Result = TERMINAL_OK;

	// converting cardExpirationDate data to integer
	CardMonth = convertingToInteger(cardData->cardExpirationDate, cardMonthStartInd, cardMonthEndInd);
	CardYear = convertingToInteger(cardData->cardExpirationDate, cardYearStartInd, cardYearEndInd);

	// converting transactionDate to interge
	TermMonth = convertingToInteger(termData->transactionDate, TransMonthStartInd, TransMonthEndInd);
	TermYear = convertingToInteger(termData->transactionDate, TransYearStartInd, TransYearEndInd);

	CardYear = (TermYear / 100) * 100 + CardYear; // TO convert CardYear from 2 digit to 4 digit  

	if (CardYear > TermYear)
		 Result = TERMINAL_OK;
	else if (CardYear == TermYear)
	{
			if(CardMonth > TermMonth)
				 Result = TERMINAL_OK;
			else
				 Result = EXPIRED_CARD;
	}
	else
		 Result = EXPIRED_CARD;

	return Result;

}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	float gettransAmount;
	EN_terminalError_t Result = TERMINAL_OK;

	printf("please enter the transaction Amount :");
	scanf("%f", &gettransAmount);

	//if(termData == NULL)
	//	Result = INVALID_AMOUNT;
	if (gettransAmount > 0.0)
	{
		termData->transAmount = gettransAmount;
		Result = TERMINAL_OK;
	}
	else
	{
		Result = INVALID_AMOUNT;
	}
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	EN_terminalError_t Result = TERMINAL_OK;

	if (termData->transAmount <= gMaxTransAmount)
		Result = TERMINAL_OK;
	else
		Result = EXCEED_MAX_AMOUNT;

	return Result;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount)
{
	EN_terminalError_t Result = TERMINAL_OK;
	if (termData == NULL)
		Result = INVALID_MAX_AMOUNT;
	else if (gMaxTransAmount <= 0)
		Result = INVALID_MAX_AMOUNT;
	else
		termData->maxTransAmount = gMaxTransAmount;
	return Result;
}		




