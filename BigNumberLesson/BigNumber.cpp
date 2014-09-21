#include "stdafx.h"
#include "BigNumber.h"
#include <iostream>

using namespace std; 

CBigNumber::CBigNumber(int number)
{
	int rest = 0;
	int prev_rest = 0; 
	int i = 0; 
	int j = 1; 

	for (int i = 0; i < DIGITCOUNT; i++)
	{
		rest = number % (j*m_base);

		if (rest > 0)
		{
			m_digits[i] = (rest - prev_rest) / (j);
		}

		prev_rest = number % j; 
		j*=m_base; 
	}

	for (int i = 0; i < DIGITCOUNT; i++)
	{
		cout << m_digits[i] << endl;
	}



}
/*
istream& operator>>(std::istream& is, CBigNumber& obj)
{
	is << obj
	return is;
}
*/

CBigNumber& operator>>(istream& is, char*& bignumber)
{
	char* chars = new char[CBigNumber::DIGITCOUNT]; 
	return(CBigNumber(chars));
}


CBigNumber::~CBigNumber()
{
}
