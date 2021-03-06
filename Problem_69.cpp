// Problem_69.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>

int GreatestCommonDivisor(int A, int B)
{
	int Rem = A % B;
	while (Rem > 0)
	{
		A = B;
		B = Rem;
		Rem = A % B;
	}

	return B;
}

int EulerTotientFunction(const int N)
{
	bool* SkipArray = new bool[N];
	memset(SkipArray, 0, N * sizeof(bool));

	int Count = 2;
	for (int A = 2; A <= N-2; ++A)
	{
		if (SkipArray[A] == true)
		{
			continue;
		}

		if (GreatestCommonDivisor(N,A) == 1)
		{
			++Count;
		}
		else
		{
			for (int i=1; i<=N/A-1; ++i)
			{
				SkipArray[i*A] = true;
			}			
		}
	}

	delete[] SkipArray;

	return Count;
}

int EulerTotientFunctionWithSkip(const int N, const double MaxRes)
{
	std::vector<int> SkipArray;

	int Count = 2;
	for (int A = 2; A <= N-2; ++A)
	{
		if (double(N)/double(Count) < MaxRes)
		{
			return Count;
		}

		bool DoSkip = false;
		for (int i=0, VecSize=SkipArray.size(); i<VecSize; ++i)
		{
			if (A % SkipArray[i] == 0)
			{
				DoSkip = true;
				break;
			}
		}

		if (DoSkip)
		{
			continue;
		}

		if (GreatestCommonDivisor(N,A) == 1)
		{
			++Count;
		}
		else
		{
			SkipArray.push_back(A);		
		}
	}

	return Count;
}

bool IsPrime(int val)
{
	for (int i = 2; i <= sqrt((double)val); i++)
	{
		if (val % i == 0)
			return false;
	}
	return true;
}

int main()
{
	double MaxRes = 0.f;
	int Mult = 1;
	int CalcFor = 10000000;
	for (int i=2; i<=sqrt(CalcFor); ++i)
	{
		if (i * Mult >= CalcFor)
		{
			break;
		}

		if (IsPrime(i))
		{
			Mult *= i;

			int EulerTotFun = EulerTotientFunctionWithSkip(Mult, MaxRes);
			const double CurRes = double(Mult)/double(EulerTotFun);
			if (MaxRes < CurRes)
			{
				MaxRes = CurRes;
				std::cout << "EulerTotient(" << Mult << ") = " << EulerTotFun << ", n/fi = " << CurRes << std::endl;
			}		
		}
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
