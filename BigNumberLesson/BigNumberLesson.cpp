// BigNumberLesson.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BigNumber.h"
#include <iostream>

//CBigNumber bignumber(12345);


int _tmain(int argc, _TCHAR* argv[])
{

	/*
	CBigNumber bignumber; 

	cin >> bignumber; 

	cout << bignumber << endl;;
	*/

	CBigNumber bignumberSmall(1234);
	CBigNumber bignumberBig(100000);

	CBigNumber temp = bignumberBig + bignumberSmall;

	cout << temp << endl;
	
	return 0;
}