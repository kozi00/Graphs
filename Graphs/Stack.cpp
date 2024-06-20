#include "Stack.h"
#include <iostream>


Stack::Stack() {
	top = nullptr;
}
bool Stack::isEmpty() const {
	if (top == NULL) {
		return true;
	}
	else {
		return false;
	}
}
int Stack::pop() {
	if (!Stack::isEmpty()) {
		int token = top->vertex;
		Node* p = top;
		top = top->next;
		delete p;
		return token;
	}
	return 0;
}
void Stack::push(int vertex) {
	Node* node = new Node(vertex);
	node->next = top;
	top = node;
}
Stack::~Stack() {
	while (top != nullptr) {//free memory
		Node* temp = top;
		top = top->next;
		delete temp;
	}
}






