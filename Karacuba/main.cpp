#include <iostream>
#include "Longdigit.h"

using namespace std;

void main()
{
	Longdigit a, b, c;
	
	//don`t work with negative numbers
	a = "1685287499328328297814655639278583667919355849391453456921116729";
	b = "7114192848577754587969744626558571536728983167954552999895348492";

	c = a + b;
	c.show();

	//dont`t work if b < a 
	c = b - a;
	c.show();

	c = a * b;
	c.show();

	c.writeToFile("out.txt");

	system("pause");
}