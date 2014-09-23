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

	for (int i = 0; i < DIGITCOUNT; i++)
	{
		rest = number % m_base;
		m_digits[i] = rest; 
		number /= m_base; 
	}

	/* DEBUG */

	for (int i = 0; i < DIGITCOUNT; i++)
	{
		cout << m_digits[i] << endl;
	}


}

CBigNumber::CBigNumber(string& str) : CBigNumber(*(str.c_str())) { }

CBigNumber& CBigNumber::operator-=(const CBigNumber& rop)
{

}

CBigNumber& CBigNumber::operator+=(const CBigNumber& rop)
{

	if (*this < 0)
	{
		if (*this < rop)
		{
			return (*this -= rop); 
		}



	}

	for (int i = 0; i < DIGITCOUNT; i++)
	{
		m_digits[i] += rop.m_digits[i]; 
	}

	return *this; 
}

bool CBigNumber::operator<(const CBigNumber& rop) const
{
	bool result = false; 
	int posLeft = 0; 
	int posRight = 0; 

	for (int i = 0; i < DIGITCOUNT; i++)
	{
		if (this->m_digits[i] > 0) posLeft = i; 
		if (rop.m_digits[i] > 0) posRight = i; 
	}

	if (posLeft < posRight)
	{
		result = true; 
	}
	else if (posLeft > posRight)
	{
		result = false; 
	}
	else
	{
		if (this->m_digits[posLeft] < rop.m_digits[posRight])
		{
			result = true; 
		}
	}

	return result; 
}

bool CBigNumber::operator>(const CBigNumber& rop) const
{
	return !(*this < rop); 
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
	}
	else
	{
		endOfArray = arr + arrayLength - 1;
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
