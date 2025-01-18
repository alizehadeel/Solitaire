//#include<iostream>
//using namespace std;
//
//#include"Stack.h"
//
//template<class T>
//Stack<T>::Stack()
//{
//	top = nullptr;
//	size = 0;
//}
//template<class T>
//bool Stack<T>::isEmpty()
//{
//	if (top == nullptr)
//		return true;
//	else
//		return false;
//}
//template<class T>
//void Stack<T>::push(T* c)
//{
//	if(!isEmpty())
//	{
//		sNode* temp = new sNode(c, top);
//		top = temp;
//	}
//	else
//	{
//		sNode* temp = new sNode(c, nullptr);
//		top = temp;
//	}
//	size++;
//}
//template<class T>
//T* Stack<T>::pop()
//{
//	if (!isEmpty())
//	{
//		sNode* temp = top;
//		top = top->next;
//		T* ret = temp->obj;
//		delete temp;
//		size--;
//		return ret;
//	}
//	else
//		return nullptr;
//}
//template<class T>
//T* Stack<T>::peek()
//{
//	if (!isEmpty())
//		return top->obj;
//	else
//		return nullptr;
//}
//template<class T>
//int Stack<T>::getSize()
//{
//	return size;
//}
//template<class T>
//void Stack<T>::print()
//{
//	for (sNode* i = top; i != nullptr; i=i->next)
//	{
//		//i->obj->Card::print();
//	}
//}
