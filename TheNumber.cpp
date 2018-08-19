// TheNumber.cpp: определяет точку входа для консольного приложения.
//
#include "NUMBER.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string>



int main()
{
	try
	{
		number nn = 1;
		number nnn = 3;
		number n1 = 2.11;
		number n2 = 3.7;

		number n3 = (n1 + n2) / (n1*n2);
		//                n3 += n2;
		n3 = n3 * n1;
		n3 = n3;
		std::cout << std::setprecision(100);
		std::cout << n3.to_double() << std::endl;
		auto nnnn = nn + nnn + n1*n2;
		n1 = n2;
		std::cout << nnnn.to_double() << '\n';

		




	}
	catch (number::exception e)
	{
		std::cerr << e.what() << std::endl;
	}
	system("pause");

	return 0;
}

