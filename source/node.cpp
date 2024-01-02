#include "node.h"
#include <cmath>

double NumerNode::Calc() const{
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
	static_assert(divisor != 0, "divisor can't be zero");
	return left_->Calc() / right_->Calc();
}

double UminsNode::Calc () const{
	return - child_->Calc();
}

UnaryNode::~UnaryNode()
{
	delete child_; 	 
}
