#pragma once
#include "Node.h"
class Stack
{
public:
	Node* top;
	Stack();
	int pop();
	void push(int vertex);
	bool isEmpty() const;
	~Stack();
};


