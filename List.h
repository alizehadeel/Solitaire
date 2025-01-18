#pragma once
#include "Card.h"

class List
{
private:
	class node;
	class ListIterator;
	node* head;
	node* tail;
	int size;
public:
	List();
	~List();
	void addNode(node* n);
	void addCard(Card* card);
	Card* removeCard();
	node* removeNode();
	node* extractSublist(int n);
	void addSubList(node* start, int s);
	bool isEmpty();
	void print();

	typedef ListIterator Iterator;
	Iterator begin();
	Iterator end();


};

class List::ListIterator
{
	friend class List;
private:
	node* iptr;
public:
	ListIterator(node* ptr = nullptr) :iptr(ptr) {  }
	ListIterator& operator++();
	ListIterator& operator--(int);
	ListIterator operator++(int);
	bool operator==(const ListIterator& obj);
	bool operator!=(const ListIterator& obj);
	Card* getCard();
	node* operator*();
};
class List::node
{
public:
	node* next;
	node* prev;
	Card* card;
	node(Card* c, node* p = nullptr, node* n = nullptr) : card(c), prev(p), next(n) {  }
	~node()
	{
		//delete card;
	}
};