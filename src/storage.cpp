#include "storage.h"
#include <cmath>
#include <cassert>
#include "symbol_table.h"

Storage::Storage(SymbolTable& tbl){
	AddConstants(tbl);
}

void Storage::Clear(){
	cells_.clear();
	inits_.clear();
}
bool Storage::IsInit(unsigned int id) const{
	return id < cells_.size() && inits_[id];
}
void Storage::AddConstants(SymbolTable& tbl){
	unsigned int id = tbl.Add("e");
	AddVal(id, exp(1.0));	//符号存在符号表，值存在storage

	id = tbl.Add("pi");
	AddVal(id,2.0*acos(0.0));	//反余弦 pi = 2*acos(0 )
}
double Storage::GetVal(unsigned int id) const{
	assert(id < cells_.size());
	return cells_[id];
}
void Storage::SetVal(unsigned int id, double val){
	assert(id <= cells_.size());
	if(id < cells_.size()){
		cells_[id] = val;
		inits_[id] = true;
	}else if(id == cells_.size()){
		AddVal(id, val);
	}
}
void Storage::AddVal(unsigned int id, double val){
	cells_.resize(id + 1);
	inits_.resize(id + 1);
	cells_[id] = val;
	inits_[id] = true;
}
