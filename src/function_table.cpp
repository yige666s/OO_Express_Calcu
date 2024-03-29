#include "function_table.h"
#include <iostream>
#include <cmath>
#include <cassert>
#include "symbol_table.h"
struct FunctionEntry{
	PtrFun pFun_;
	char* funName_;
};

FunctionEntry Entrys[] ={
	log, "log",
	exp, "exp",
	sqrt, "sqrt",
	cos, "cos",
	sin, "sin",
	tan, "tan",
	acos, "acos",
	asin, "asin",
	atan, "atan",
	sinh, "sinh",
	cosh, "cosh",
	tanh, "tanh"
};
FunctionTable::FunctionTable(SymbolTable& tbl) :size_(sizeof(Entrys)/sizeof(Entrys[0])){
	Init(tbl);
}

FunctionTable::~FunctionTable(){
	delete[] pFuns_;
}

void FunctionTable::Init(SymbolTable& tbl){
	std::cout<<"function list"<<std::endl;
	pFuns_ = new PtrFun[size_];
	for(unsigned int i = 0; i<size_; ++i){
		pFuns_[i] = Entrys[i].pFun_;
		unsigned int j = tbl.Add(Entrys[i].funName_);
		assert(i == j);
		std::cout<<Entrys[i].funName_<<std::endl;
	}
}
