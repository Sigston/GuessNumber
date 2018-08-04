#include "InputValidate.h"
#include <string>
#include <iostream>

void ValidInputChar(char &OutputChar, std::string ErrorMessage)
{
	std::cin >> OutputChar;
	while (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << ErrorMessage;
		std::cin >> OutputChar;
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void ValidInputInt(int &OutputInt, std::string ErrorMessage)
{
	std::cin >> OutputInt;
	while (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << ErrorMessage;
		std::cin >> OutputInt;
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void ValidInputStr(std::string &OutputStr, std::string ErrorMessage)
{
	std::getline(std::cin, OutputStr);
}
