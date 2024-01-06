#include "symbol_table.h"
#include <algorithm>

unsigned int SymbolTable::Add(const std::string& str){
	dictionary_[str] = curId_;
	return curId_++;
}

unsigned int SymbolTable::Find(const std::string& str) const {
	for(auto it = dictionary_.begin(); it != dictionary_.end(); ++it){
		it = dictionary_.find(str);
		if(it != dictionary_.end())
			return it->second;
		return IDNOTFOUND;
	}
}

void SymbolTable::Clear(){
	dictionary_.clear();
	curId_ = 0;
}

//function object/ functor
//让类对象使用起来像一个函数，通过重载()实现
//STL六大组件:容器+算法+迭代器 适配器+函数对象+内存分配器
class IsEqualId{
	public:
		IsEqualId(unsigned int id) : id_(id){}
		bool operator()(const std::pair<const std::string, unsigned int>& it){
			return it.second == id_;
		}
	private:	
		unsigned int id_;
};

std::string SymbolTable::GetSymbolName(unsigned int id) const {
	auto it = find_if(dictionary_.begin(), dictionary_.end(), IsEqualId(id)); 	/*[id](const std::pair<const std::string,unsigned int>& p){return p.second == id;}*/
	return it->first;
}