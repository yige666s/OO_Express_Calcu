#include "parser.h"
#include <iostream>
#include <cassert>
#include "scanner.h"
#include "node.h"
#include "Calc.h"

Parser::Parser(Scanner& scanner, Calc& calc) : 
	scanner_(scanner), calc_(calc), tree_(0),status_(STATUS_OK){

}

STATUS Parser::Parse(){
	tree_ = Expr();
	if(!scanner_.IsDone()){
		status_ = STATUS_ERROR;
	}
	return status_;
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
	else if(token ==TOEKN_ASSIGN){
		//Expr := Term = Expr
		scanner_.Accept();
		Node* nodeRight = Expr();
		if(node->IsLvalue()){
			node = new AssignNode(node, nodeRight);
		}else{
			status_ = STATUS_ERROR;
			std::cout<<"Error: lvalue required"<<std::endl;
			// TODO 抛出异常
		}
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
	}else if(token == TOEKN_IDENTIFIER){
		std::string symbol = scanner_.GetSymbol();
		unsigned int id = calc_.FindSymbol(symbol);
		scanner_.Accept();
		if(scanner_.Token() == TOKEN_LPAREN){
			scanner_.Accept();	// accept '('
			node = Expr();
			if(scanner_.Token() == TOKEN_RPAREN){
				scanner_.Accept();	// accpet ')'
				if(id != SymbolTable::IDNOTFOUND && calc_.IsFunction(id)){
					node = new FunctionNode(node, calc_.GetFunction(id));
				}else{
					status_ = STATUS_ERROR;
					std::cout<<"Unknown function"<<"\""<<symbol<<"\""<<std::endl;
				}
			}else{
				status_ = STATUS_ERROR;
				std::cout<<"missing parenthesis"<<std::endl; 
			}
		}else{
			if(id == SymbolTable::IDNOTFOUND){
			id = calc_.AddSymbol(symbol);
			}
			node = new VariableNode(id, calc_.GetStorage());
		}
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