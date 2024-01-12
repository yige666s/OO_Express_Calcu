#ifndef _SCANNER_H_
#define _SCANNER_H_

#include <string>
enum EToken{
	TOKEN_END,
	TOKEN_ERROR,
	TOKEN_NUMBER,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_MUTIPLY,
	TOKEN_DIVIDE,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOEKN_IDENTIFIER,
	TOEKN_ASSIGN
};

class Scanner
{
public:
	Scanner(const std::string& buf);
	void Accept();
	double Number() const;
	bool IsEmpty() const;
	bool IsDone() const;
	std::string GetSymbol() const;
	EToken Token() const;
private:
	void SkipWhite();
	const std::string buf_;
	unsigned int curPos_;
	EToken token_;
	double number_;
	std::string symbol_;
	bool isEmpty_;
};

#endif // _SCANNER_H_