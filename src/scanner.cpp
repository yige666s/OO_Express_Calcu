#include "scanner.h"
#include <cctype>

Scanner::Scanner(const std::string& buf) : buf_(buf), curPos_(0)
{
	Accept();
}

double Scanner::Number() const
{
	return number_;
}

EToken Scanner::Token() const
{
	return token_;
}

void Scanner::SkipWhite()
{
	while (isspace(buf_[curPos_]))
		++curPos_;
}

void Scanner::Accept()
{
	SkipWhite();
	switch (buf_[curPos_])
	{
	case '+':
		token_ = TOKEN_PLUS;
		++curPos_;
		break;
	case '-':
		token_ = TOKEN_MINUS;
		++curPos_;
		break;
	case '*':
		token_ = TOKEN_MUTIPLY;
		++curPos_;
		break;
	case '/':
		token_ = TOKEN_DIVIDE;
		++curPos_;
		break;
	case '(':
		token_ = TOKEN_LPAREN;
		++curPos_;
		break;
	case ')':
		token_ = TOKEN_RPAREN;
		++curPos_;
		break;
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	case '.':
		token_ = TOKEN_NUMBER;
		char* p;
		number_ = strtod(&buf_[curPos_], &p);
		curPos_ = p - &buf_[0];
		break;
	case '\0': case '\n': case '\r': case EOF:
		token_ = TOKEN_END;
		break;
	default:
		token_ = TOKEN_ERROR;
		break;
	}
}