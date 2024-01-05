#include "parser.h"
#include <iostream>
#include <cassert>
#include "scanner.h"
#include "node.h"

Parser::Parser(Scanner& scanner) : scanner_(scanner), tree_(0){

}

void Parser::Parse(){
	tree_ = Expr();
}

Node* Parser::Expr(){
	Node* node = Term();
	EToken token = scanner_.Token();
	// if(token == TOKEN_PLUS){
	// 	scanner_.Accept();
	// 	Node* nodeRight = Expr();
	// 	node = new AddNode(node, nodeRight);
	// }else if(token == TOKEN_MINUS){
	// 	scanner_.Accept();
	// 	Node* nodeRight = Expr();
	// 	node = new SubNode(node, nodeRight);
	// }
	if(token == TOKEN_PLUS || TOKEN_MINUS){
		// Expr := Term ( '+' Term | '-' Term )
		MutilpleNode* mutipleNode = new SumNode(node);
		do{
			scanner_.Accept();
			Node* nextNode = Term();
			mutipleNode->AppendChild(nextNode,(token == TOKEN_PLUS));
			token = scanner_.Token();
		}while(token == TOKEN_PLUS || TOKEN_MINUS);
		node = mutipleNode; 
	}

	return node;
}

Node* Parser::Term(){
	Node* node = Factor();
	EToken token = scanner_.Token();
	// if(token == TOKEN_MUTIPLY){
	// 	scanner_.Accept();
	// 	Node* nodeRight = Term();
	// 	node = new MutilNode(node, nodeRight);
	// }else if(token == TOKEN_DIVIDE){
	// 	scanner_.Accept();
	// 	Node* nodeRight = Term();
	// 	node = new DivideNode(node, nodeRight);
	// }
	if(token == TOKEN_MUTIPLY || TOKEN_DIVIDE){
		// Term := Factor ( '*' Factor | '/' Factor )
		MutilpleNode* mutipleNode = new ProductNode(node);
		do{
			scanner_.Accept();
			Node* nextNode = Term();
			mutipleNode->AppendChild(nextNode,(token == TOKEN_PLUS));
			token = scanner_.Token();
		}while(token == TOKEN_MUTIPLY || TOKEN_DIVIDE);
		node = mutipleNode; 
	}
	return node;
}

Node* Parser::Factor(){
	Node* node;
	EToken token =scanner_.Token();
	if(token == TOKEN_LPAREN){
		scanner_.Accept();	// accept '('
		node = Expr();
		if(scanner_.Token() == TOKEN_RPAREN){
			scanner_.Accept();	// accpet ')'
		}else{
			status_ = STATUS_ERROR;
			// TODO:抛出异常
			std::cout<<"missing parenthesis"<<std::endl;
			node = 0;
		}
	}else if (token == TOKEN_NUMBER){
		node = new NumberNode(scanner_.Number());
		scanner_.Accept();
	}else if(token == TOKEN_MINUS){
		scanner_.Accept();  //accept minus
		node = new UminsNode(Factor());
	}else{
		status_ = STATUS_ERROR;
		//TODO:抛出异常
		std::cout<<"Not a valid expression"<<std::endl;
		node = 0;
	}
	return node;
}

double Parser::Calculate() const{
	assert(tree_ != NULL);	
	return tree_->Calc();
}