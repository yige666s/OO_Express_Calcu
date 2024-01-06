#ifndef _STORAGE_H_
#define _STORAGE_H_

#include <vector>
class SymbolTable;
class Storage{
public:
	Storage(SymbolTable& tbl);
	void Clear();
	bool IsInit(unsigned int id) const;
	void AddConstants(SymbolTable& tbl);
	double GetVal(unsigned int id) const;
	void SetVal(unsigned int id, double val);
	void AddVal(unsigned intid, double val);
private:
	std::vector<double> cells_;	//存储常量/变量
	std::vector<bool> inits_;	 //记录初始化情况
};
#endif //_STORAGE_H_