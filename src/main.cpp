#include <iostream>
#include <string>
#include "scanner.h"
#include "parser.h"

int main(void)
{
	do 
	{
		std::cout<<"> ";
		std::string buf;
		std::getline(std::cin, buf);
		std::cout<<buf<<std::endl;
		Scanner scanner(buf);
		Parser parser(scanner);
		parser.Parse();
		parser.Calculate();
	} while (1);
	return 0;
}