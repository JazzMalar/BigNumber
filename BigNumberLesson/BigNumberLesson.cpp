// BigNumberLesson.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BigNumber.h"
#include <iostream>

//CBigNumber bignumber(12345);


int _tmain(int argc, _TCHAR* argv[])
{

	CBigNumber bignumberSmall(50);
	CBigNumber bignumberBig(100);

	if (bignumberSmall < 10) 
	{
		cout << "Small ist kleiner"; 
	}
	
	return 0;
}