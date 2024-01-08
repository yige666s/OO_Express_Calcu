#include "Calc.h"

unsigned int Calc::FindSymbol(const std::string& str) const {
	 return symtbl_.Find(str);
}

unsigned int Calc::AddSymbol(const std::string& str){
	return symtbl_.Add(str);
}