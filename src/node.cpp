#include "node.h"
#include <iostream>
#include <cassert>
#include <cmath>

 double NumberNode::Calc() const{
	return number_;
}

BinaryNode::~BinaryNode(){
	delete left_;
	delete right_;
}

// double AddNode::Calc() const{
// 	return left_->Calc() + right_->Calc();
// }

// double SubNode::Calc() const{
// 	return left_->Calc() - right_->Calc();
// }

// double MutilNode::Calc() const{
// 	return left_->Calc() * right_->Calc();
// }

// double DivideNode::Calc() const{
// 	double divisor = right_->Calc();
// 	if( divisor != 0){
// 			return left_->Calc() / right_->Calc();
// 	}else{
// 		std::cout<<"Error: Divisor by zero"<<std::endl;
// 		return HUGE_VAL;
// 	}
// }

double UminsNode::Calc () const{
	return - child_->Calc();
}

UnaryNode::~UnaryNode()
{
	delete child_; 	 
}

MutilpleNode::~MutilpleNode(){
	for(auto it = childs_.begin(); it != childs_.end(); ++it){
		delete *it;
	}
}

double SumNode::Calc() const{
	double result = 0.0;
	auto childIt = childs_.begin();
	auto positiveIt = positives_.begin();
	for(; childIt != childs_.end(); ++childIt, ++positiveIt){
		double val = (*childIt)->Calc();
		assert(positiveIt != positives_.end());
		if(*positiveIt)
			result += val;
		else	
			result -= val;
	}
	assert(positiveIt == positives_.end());
}

double ProductNode::Calc() const{
	double result = 1.0;
	auto childIt = childs_.begin();
	auto positiveIt = positives_.begin();
	for(; childIt != childs_.end(); ++childIt, ++positiveIt){
		double val = (*childIt)->Calc();
		assert(positiveIt != positives_.end());
		if(*positiveIt)
			result *= val;
		else if(val != 0.0)
			result /= val;
		else{			
			std::cout<<"Error: Divisor by zero"<<std::endl;
			return HUGE_VAL;
		}
	}
	assert(positiveIt == positives_.end());
}