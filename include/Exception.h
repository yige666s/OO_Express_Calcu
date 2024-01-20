#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <exception>
#include <string>

class Exception : public std::exception{
	public:
	 	explicit Exception(const char* message) : message_(message){}
		virtual ~Exception() noexcept(true){}
		virtual const char* what() const noexcept(true){return message_.c_str();}
	private:
		std::string message_;
};

class SyntaxError : public Exception{
	public:
		explicit SyntaxError(const char* message) : Exception(message){}
		virtual ~SyntaxError() noexcept(true){}
};

#endif //_EXCEPTION_H_