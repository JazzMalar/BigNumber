#pragma once
#ifndef __BIGNUMBER__H
#define __BIGNUMBER_H

#include <iostream>
#include <string>

using namespace std; 

class CBigNumber
{

public:
	static const int DIGITCOUNT = 10000;

	CBigNumber(string&);
	CBigNumber(char*);
	CBigNumber(int i = 0);
	~CBigNumber();

	CBigNumber& operator*=(const CBigNumber&); 
	CBigNumber operator*(const CBigNumber&) const; 
	CBigNumber& operator+=(const CBigNumber&);
	CBigNumber operator+(const CBigNumber&) const;
	CBigNumber& operator-=(const CBigNumber&);
	bool operator>(const CBigNumber&) const; 
	bool operator<(const CBigNumber&) const;
	bool operator==(const CBigNumber&) const;

	friend istream& operator>>(istream& lop, CBigNumber& rop); 
	friend ostream& operator<<(ostream& lop, const CBigNumber& rop); 


	
private:

	unsigned int m_digits[DIGITCOUNT];
	int m_validDigits = 3;
	int m_base = 10;
	bool m_positive;
	
};


#endif

