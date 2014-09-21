#pragma once

#include <iostream>

using namespace std; 

class CBigNumber
{

public:
	static const int DIGITCOUNT = 5;


	CBigNumber(char*);
	CBigNumber(int);
	~CBigNumber();


	//friend istream& operator>>(istream& a, char*& b);
	friend CBigNumber& operator>>(istream& in, char*& b); 


private:

	int m_digits[DIGITCOUNT];
	int m_validDigits = 3;
	int m_base = 10;
	bool m_positive;
	/*
	CBigNumber(CBigNumber&);
	CBigNumber(char*); 

	CBigNumber();
	
	CBigNumber operator+(const CBigNumber); 
	CBigNumber& operator+=(const CBigNumber) const;

	CBigNumber operator*(const CBigNumber); 
	CBigNumber& operator*=(const CBigNumber) const; 
	*/

};




