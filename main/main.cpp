#include <iostream>
#include "../PolishLib/Polish.h"

int main()
{
	char* s = "2*(2+2)";
	TPolish P;
	std::cout << P.Calculate(s);

	return 0;
}