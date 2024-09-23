#include "Helper.h"

#include <conio.h> 

void Helper::getInt(int& num)
{
	char ch = ' ';
	std::string numberStr;

	while (true)
	{
		ch = _getch();
		if (ch >= '0' && ch <= '9')
		{
			numberStr = ch;
			break;
		}
	}

	num = std::stoi(numberStr);
}