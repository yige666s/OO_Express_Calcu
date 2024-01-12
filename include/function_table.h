#ifndef _FUNCTION_TABLE_
#define _FUNCTION_TABLE_

class SymbolTable;
typedef double (*PtrFun)(double);
class FunctionTable{	//保存函数名(symbol_table保存)与函数指针的对应关系
	public:
		FunctionTable(SymbolTable& tbl);
		~FunctionTable();
		void Init(SymbolTable& tbl);
		unsigned int Size() const{return size_;}
		PtrFun GetFunction(unsigned int id) const{ return pFuns_[id];}
	private:
		 PtrFun* pFuns_;	//pFuns_是一个指向指针数组首地址的指针
		 int size_;

};

#endif // _FUNCTION_TABLE_