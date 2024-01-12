#ifndef _CALC_H_
#define _CALC_H_

#include "symbol_table.h"
#include "storage.h"
#include "function_table.h"
#include <string>
class Parser;

class Calc{
	friend class Parser;	//方便parser类访问Calc类
	public:
		Calc(): funtbl_(symtbl_),storage_(symtbl_){}	//先构造symbol_table，再构造storage
	private:	
		Storage& GetStorage() {return storage_;}
		bool IsFunction(unsigned int id) const{return id < funtbl_.Size();}
		PtrFun GetFunction(unsigned int id) const{return funtbl_.GetFunction(id);}
		unsigned int AddSymbol(const std::string& str);
		unsigned int FindSymbol(const std::string& str) const;
		SymbolTable symtbl_;	//这里使用引用，不能使用前向声明，必须显示include
		FunctionTable funtbl_;
		Storage storage_;
};


#endif //_CALC_H_