#include "stdafx.h"
#include "BigNumber.h"
#include <iostream>
#include <string>

using namespace std; 

CBigNumber::CBigNumber(int number)
{
	int rest = 0;
	int prev_rest = 0; 
	int i = 0; 
	int j = 1; 

	if (number < 0) 
	{
		m_positive = false; 
		number *= -1; 
	}

	/*
	for (int i = 0; i < DIGITCOUNT; i++)
	{

		rest = number % (j*m_base);

		m_digits[i] = (rest - prev_rest) / (j);

		prev_rest = number % j; 
		j*=m_base; 
	}
	*/

	unsigned int digitsToConsider = 0; 

	for (int i = 0; i < DIGITCOUNT; i++)
	{

		if (number != 0)
		{
			rest = number % m_base;
			m_digits[i] = rest;
			digitsToConsider++;
			number /= m_base;
		}
		else
		{
			m_digits[i] = 0;
		}


	}

	m_validDigits = digitsToConsider; 

	/* DEBUG */
	/*
	for (int i = 0; i < DIGITCOUNT; i++)
	{
		cout << m_digits[i] << endl;
	}
	*/

}

CBigNumber::CBigNumber(string& str) : CBigNumber(*(str.c_str())) { }

CBigNumber& CBigNumber::operator-=(const CBigNumber& rop)
{
	// ToDo :  implement
	return *this;
}

CBigNumber& CBigNumber::operator*=(const CBigNumber& rop)
{
	const int arrSize = this->m_validDigits+1; 
	CBigNumber* tmpArr = new CBigNumber[arrSize]; 
	CBigNumber* tmpArrOrig = tmpArr; 

	for (int i = 0; i < arrSize; i++)
	{
		*tmpArr = CBigNumber(0); 
		tmpArr++; 
	}

	tmpArr = tmpArrOrig; 

	CBigNumber tmp(0);
	const unsigned int *pDigitsRop = rop.m_digits;
	unsigned int *pDigitsLop = this->m_digits;
	unsigned int *pDigitsTmp = tmp.m_digits;
	unsigned int digitsToConsider = 0;

	digitsToConsider = this->m_validDigits;

	unsigned int runningBase = this->m_base;
	unsigned int newValue = 0;
	unsigned int rest = 0;
	this->m_validDigits = 0; 
	
	for (unsigned int i = 0; i <= digitsToConsider; i++)
	{
		pDigitsTmp = tmp.m_digits + i;
		pDigitsRop = rop.m_digits;
		rest = 0; 
		
		tmp = 0;

		tmp.m_validDigits = rop.m_validDigits + i + 1; 

		for (int j = 0; j <= rop.m_validDigits; j++)
		{		

			newValue = *pDigitsLop * *pDigitsRop + rest;
			if (newValue >= runningBase)
			{
				rest = newValue / runningBase;
				newValue %= runningBase;
			}

			*pDigitsTmp = newValue;
			pDigitsRop++;
			pDigitsTmp++; 

		}

		*tmpArr = tmp; 
		tmpArr++; 

		pDigitsLop++;

	}

	tmpArr = tmpArrOrig; 

	*this = 0; 
	for (int i = 0; i < arrSize; i++)
	{
		*this += *tmpArr;
		tmpArr++; 
	}

	delete [] tmpArrOrig;


	return *this; 

}

CBigNumber CBigNumber::operator*(const CBigNumber& rop) const
{
	CBigNumber tmp(*this); 
	return tmp *= rop; 
}

CBigNumber CBigNumber::operator+(const CBigNumber& rop) const 
{
	CBigNumber temp(*this); 

	return temp += rop; 

	// return temp 
}

CBigNumber& CBigNumber::operator+=(const CBigNumber& rop)
{

	if (this->m_positive != rop.m_positive)
	{
		// ToDo : negative values are going to be fun
		/*
		if (this->m_positive)
		{
			return (*this -= rop); 
		}
		else 
		{
			return (rop -= *this); 
		}
		*/

		// ToDo :  implement

		return *this;

	}

	unsigned int digitsToConsider = 0; 
	if (this->m_validDigits > rop.m_validDigits)
	{
		digitsToConsider = this->m_validDigits; 
	}
	else
	{
		digitsToConsider = rop.m_validDigits;
	}


	this->m_validDigits = 0; 
	unsigned int runningBase = this->m_base; 
	unsigned int *pDigitsLop = m_digits; 
	const unsigned int *pDigitsRop = rop.m_digits; 
	unsigned int newValue = 0; 
	unsigned int rest = 0; 
	for (unsigned int i = 0; i <= digitsToConsider; i++)
	{
		newValue = *pDigitsLop + *pDigitsRop + rest;
		rest = 0; 

		if (newValue >= runningBase)
		{
			rest = 1; 
			newValue -= runningBase; 
		}

		*pDigitsLop = newValue; 
		runningBase *= this->m_base;

		pDigitsLop++; 
		pDigitsRop++; 

		if (newValue > 0)
		{
			this->m_validDigits = i + 1; 
		}

		/*
		//this->m_validDigits++;

		// In case we prepared a position for a new digit
		// but didn't create one, reduce the valid digits again.
		if (i == digitsToConsider && newValue == 0)
		{
			this->m_validDigits--;
		}

		*/

	}

	return *this; 
}

bool CBigNumber::operator<(const CBigNumber& rop) const
{
	bool result = false; 

	if (this->m_validDigits > rop.m_validDigits) 
	{
		result = false; 
	}
	else if (this->m_validDigits < rop.m_validDigits)
	{
		result = true; 
	}
	else
	{
		const unsigned int* pDigitLop = m_digits + m_validDigits - 1;
		const unsigned int* pDigitRop = rop.m_digits + rop.m_validDigits - 1; 

		for (int i = this->m_validDigits-1; i >= 0; i--)
		{
			if (*pDigitLop > *pDigitRop)
			{
				result = false;
			}
			else if (*pDigitLop < *pDigitRop)
			{
				result = true; 
			}
			else
			{
				result = false; 
			}

			pDigitLop--;
			pDigitRop--;
		}
	}

	return result; 
}

bool CBigNumber::operator>(const CBigNumber& rop) const
{

	bool result = false;

	if (this->m_validDigits > rop.m_validDigits)
	{
		result = true;
	}
	else if (this->m_validDigits < rop.m_validDigits)
	{
		result = false;
	}
	else
	{
		const unsigned int* pDigitLop = m_digits + m_validDigits - 1;
		const unsigned int* pDigitRop = rop.m_digits + rop.m_validDigits - 1;

		for (int i = this->m_validDigits - 1; i >= 0; i--)
		{
			if (*pDigitLop > *pDigitRop)
			{
				result = true;
			}
			else if (*pDigitLop < *pDigitRop)
			{
				result = false;
			}
			else
			{
				result = false;
			}

			pDigitLop--;
			pDigitRop--;

		}
	}

	return result;
}

bool CBigNumber::operator==(const CBigNumber& rop) const
{
	bool result = true;

	if ((*this > rop) || (*this < rop))
	{
		result = false;
	}

	return result;
}

CBigNumber::CBigNumber(char* arr)
{

	int j = 0; 

	int arrayLength = strlen(arr); 
	
	switch (*arr)
	{
	case '-' : 
		m_positive = false;
		j = 1; 
		break;
	case '+' : 
		j = 1; 
		break;
	}

	// if the input is too long or too short, just use the 
	// significant numbers.
	// also, if the first symbol was a '-' or a '+' take a number 
	// more into account (we don't want to loose accuracy for the
	// plus / minus sign).
	char* endOfArray;
	if (arrayLength >= (DIGITCOUNT + j))
	{
		endOfArray = arr + (DIGITCOUNT + j) - 1;
		m_validDigits = DIGITCOUNT;
	}
	else
	{
		endOfArray = arr + arrayLength - 1;
		m_validDigits = arrayLength - j; 
	}

	for (int i = DIGITCOUNT-1; i >= 0; i--)
	{
		// if the number is shorter than allowed digits
		// fill the rest with zeroes.
		if (i >= arrayLength-j)
		{
			m_digits[i] = 0; 
		}
		else
		{
			m_digits[i] = (*endOfArray) - 48;
			endOfArray--;
		}
	}

	// DEBUG
	/*
	for (int k = 0; k < DIGITCOUNT; k++)
	{
		cout << m_digits[k] << endl; 
	}
	*/
}

istream& operator>>(std::istream& lop, CBigNumber& rop)
{
	// STRING VERSION
	// DOES NOT WORK! I'd like to call the char* constructor
	// with the string, but that does not work.. hmm..
	/*
	string inputData; 
	lop >> inputData; 

	rop = CBigNumber(inputData);

	return lop; 
	*/
	
	// CHAR ARRAY VERSION 
	char* inputData = new char[CBigNumber::DIGITCOUNT+1];

	std::cout << "Grosse Zahl eingeben :" << endl;
	lop >> inputData; 

	rop = CBigNumber(inputData);

	return lop;
}

ostream& operator<<(std::ostream& lop, const CBigNumber& rop)
{
	std::string out; 

	if (rop.m_positive)
	{
		out += "+"; 
	}
	else 
	{
		out += "-"; 
	}

	for (int i = 0; i < CBigNumber::DIGITCOUNT; i++)
	{
		out = out + std::to_string(rop.m_digits[i]); 
	}


	lop << out << endl;

	return lop; 
}
/*
CBigNumber& operator>>(istream& is, char*& bignumber)
{
	char* chars = new char[CBigNumber::DIGITCOUNT]; 
	return(CBigNumber(chars));
}
*/

CBigNumber::~CBigNumber()
{
}
