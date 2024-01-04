#include "node.h"
#include <cmath>
#include <iostream>

double NumberNode::Calc() const{
	return number_;
}

BinaryNode::~BinaryNode(){
	delete left_;
	delete right_;
}

double AddNode::Calc() const{
	return left_->Calc() + right_->Calc();
}

double SubNode::Calc() const{
	return left_->Calc() - right_->Calc();
}

double MutilNode::Calc() const{
	return left_->Calc() * right_->Calc();
}

double DivideNode::Calc() const{
	double divisor = right_->Calc();
	if( divisor != 0){
			return left_->Calc() / right_->Calc();
	}else{
		std::cout<<"Error: Divisor by zero"<<std::endl;
		return HUGE_VAL;
	}
}

double UminsNode::Calc () const{
	return - child_->Calc();
}

UnaryNode::~UnaryNode()
{
	delete child_; 	 
}
