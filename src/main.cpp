#include <iostream>
#include <string>
#include "scanner.h"
#include "parser.h"

int main(void)
{

	STATUS status = STATUS_OK;
	do 
	{
		std::cout<<"> ";
		std::string buf;
		std::getline(std::cin, buf);
		// std::cout<<buf<<std::endl;
		Scanner scanner(buf);
		Parser parser(scanner);
		parser.Parse();
		std::cout<<parser.Calculate()<<std::endl;
	} while (status != STATUS_QUIT);
	return 0;
}