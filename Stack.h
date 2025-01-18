#pragma once
#include "Card.h"
#include<iostream>
using namespace std;

template <class T>
class Stack
{
private:
	class sNode;
	sNode* top;
	int size;
public:
	Stack();
	~Stack()
	{	
		sNode* temp = top;
		while (top != nullptr)
		{
			temp = top;
			top = top->next;
			//delete temp;
		}
	}
	bool isEmpty();
	void pushN(sNode* n);
	void pushC(T* c);
	sNode* popN();
	T* popC();
	T* peekC();

	void print();
	int getSize();
};

template <class T>
class Stack<T>::sNode
{
public:
	T* obj;
	sNode* next;
	sNode(T* o = nullptr, sNode* s = nullptr) :obj(o), next(s) {  }
	~sNode()
	{
		//delete obj;
	}
};

template<class T>
Stack<T>::Stack()
{
	top = nullptr;
	size = 0;
}
template<class T>
bool Stack<T>::isEmpty()
{
	if (top == nullptr)
		return true;
	else
		return false;
}
template<class T>
void Stack<T>::pushN(sNode* n)
{
	if (!isEmpty())
	{
		n->next = top;
		top = n;
	}
	else
	{
		n->next = nullptr;
		top = n;
	}
	size++;
}
template<class T>
void Stack<T>::pushC(T* c)
{
	if (!isEmpty())
	{
		sNode* temp = new sNode(c, top);
		top = temp;
	}
	else
	{
		sNode* temp = new sNode(c, nullptr);
		top = temp;
	}
	size++;
}
template<class T>
typename Stack<T>::sNode* Stack<T>::popN()
{
	if (!isEmpty())
	{
		sNode* temp = top;
		top = top->next;
		size--;
		return temp;
	}
	else
		return nullptr;
}
template<class T>
T* Stack<T>::popC()
{
	if (!isEmpty())
	{
		sNode* temp = top;
		top = top->next;
		T* ret = temp->obj;
		delete temp;
		size--;
		return ret;
	}
	else
		return nullptr;
}

template<class T>
T* Stack<T>::peekC()
{
	if (!isEmpty())
		return top->obj;
	else
		return nullptr;
}
template<class T>
int Stack<T>::getSize()
{
	return size;
}
template<class T>
void Stack<T>::print()
{
	for (sNode* i = top; i != nullptr; i = i->next)
	{
		//i->obj->Card::print();
	}
}
