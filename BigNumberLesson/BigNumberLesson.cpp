// BigNumberLesson.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BigNumber.h"
#include "TestBigNumber.h"
#include <iostream>
#include <ctime>

//CBigNumber bignumber(12345);


CBigNumber fact(int factor)
{
	CBigNumber tmp(1);
	for (int i = 1; i <= factor; i++)
	{
		tmp *= i;
	}

	return tmp;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// TEST FRAMEWORK
	CTestBigNumber test; 
	test.TestAll(); 

	/*CBigNumber bnC; 
	cout << "Benoetigte Zeit um 1000! zu berechnen = ";
	long starttime = clock(); //Startzeit

	//Zur Zeitmessung sind mehrere Durchläufe geeigneter
	int loops = 10;
	for (int i = 0; i < loops; i++)
	{
		bnC = fact(1000);
	}

	long endtime = clock(); //Endzeit

	cout << ((double)(endtime - starttime) / ((double)CLOCKS_PER_SEC / 1000)) / loops << "ms" << endl; //Gemittelte Zeit ausgeben

	// cout << "Faktorial von 3 ist " << bnC << endl;
	*/

	return 0;
}