#ifndef _NODE_H_
#define _NODE_H_

class Noncopyable{
protected:
	Noncopyable(){}	//不需要实例化，只是用来继承
	~Noncopyable(){}
private:
	Noncopyable(const Noncopyable&);
	const Noncopyable& operator=(const Noncopyable&);
};

class Node : private Noncopyable{	// Node实现继承Noncopyable，不需要实现Nonecopyable接口
	public:
		virtual double Calc() const= 0;
		virtual ~Node(){}
};

class NumberNode : public Node{
	public:
		NumberNode(double number) : number_(number){}
		double Calc() const;
	private:
		double number_;
};

class BinaryNode : public Node{
	public:
		BinaryNode(Node* left,Node* right) : left_(left),right_(right){}
		~BinaryNode();
	protected:
		Node* const left_;
		Node* const right_;
};

class AddNode : public BinaryNode{
	public:
		AddNode(Node* left,Node* right) : BinaryNode(left,right){}
		double Calc() const;
};

class SubNode : public BinaryNode{
	public:
		SubNode(Node* left,Node* right) : BinaryNode(left,right){}
		double Calc() const;
};

class MutilNode : public BinaryNode{
	public:
		MutilNode(Node* left,Node* right) : BinaryNode(left,right){}
		double Calc() const;
};

class DivideNode : public BinaryNode{
	public:
		DivideNode(Node* left,Node* right) : BinaryNode(left,right){}
		double Calc() const;
};

class UnaryNode : public Node{
public:
	UnaryNode(Node* child) : child_(child){}
	~UnaryNode();
protected:
	Node* const child_;
};

class UminsNode : public UnaryNode{
	public:
		UminsNode(Node* child) : UnaryNode(child){}
		double Calc() const;
};

#endif	//_NODE_H_

