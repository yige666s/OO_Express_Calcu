#include <iostream>
#include <string>
#include "parser.h"
#include "scanner.h"

int main(int argc, char const *argv[])
{
	do{
		std::cout<<"> ";
		std::string buf;
		std::getline(std::cin, buf);	//输入字符串放入buf
		std::cout<<buf<<std::endl;

		Scanner scanner(buf);	//扫描buf
		Parser Parser(scanner);	//使用scanner构造parser
		parser.Parse();	//进行解析
		parser.Calculate();	//计算节点
	}
	return 0;
}
