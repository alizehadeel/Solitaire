#include "List.h";
#include<iostream>
using namespace std;

List::List()
	{
		head = new node(nullptr, nullptr, nullptr);
		tail = new node(nullptr, head, nullptr);
		head->next = tail;
		head->prev = nullptr;
		tail->next = nullptr;
		size = 0;
	}
bool List::isEmpty()
	{
		if (head->next == tail)
			return true;
		else
			return false;
	}

void List::print()
{
		node* temp = head->next;
		while (temp != tail)
		{
			temp->card->print();
			cout<< " ";
			temp = temp->next;
		}
}
void List::addNode(node* n)
{
	if (n)
	{
		tail->prev->next = n;
		tail->prev = n;
		size++;
	}
}
void List::addCard(Card* c)
{
	if(c)
	{
		node* temp = new node(c, tail->prev, tail);
		tail->prev->next = temp;
		tail->prev = temp;
		size++;
	}
}
Card* List::removeCard()		
{
	node* temp = tail->prev;
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	size--;
	Card* c = temp->card;
	delete temp;
	return c;
}
List::node* List::removeNode()
{
	node* temp = tail->prev;
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	size--;
	return temp;
}
List::node* List::extractSublist(int n)
{
	node* temp = tail->prev;
	node* endSublist = tail->prev;
	while (n>1 && temp!=head)
	{
		temp = temp->prev;
		n--;
	}
	temp->prev->next = tail;
	tail->prev = temp->prev;
	temp->prev = nullptr;
	endSublist->next = nullptr;
	return temp;

}
void List::addSubList(node* start, int s)
{
	node* temp = tail->prev;
	temp->next = start;
	start->prev = temp;
	while (s > 1)
	{
		start = start->next;
		s--;
	}
	start->next = tail;
	tail->prev = start;

}
//----------Iterator Functions-------------//
List::ListIterator& List::ListIterator::operator++()	//note:scope resoltion was needed before the data type too 
{
	if (iptr)
	{
		if (iptr->next->card == nullptr)
			iptr = nullptr;
		else
			iptr = iptr->next;
	}
	return (*this);
}
List::ListIterator List::ListIterator::operator++(int)
{
	ListIterator temp(iptr);//calling constructor
	//OR ListIterator temp = *this; 
	if (iptr)
	{
		if (iptr->next->next == nullptr)
			iptr = nullptr;
		else
			iptr = iptr->next;
	}
	return temp;
}
bool List::ListIterator::operator==(const ListIterator& obj)
{
	if (iptr == obj.iptr)
		return true;
	return false;
}
bool List::ListIterator::operator!=(const ListIterator& obj)
{
	if (iptr != obj.iptr)
		return true;
	return false;
}
List::node* List::ListIterator::operator*() 
{
	return iptr;
	
}
Card* List::ListIterator::getCard()
{
	if(iptr)
	{
		return iptr->card;
	}
}
List::ListIterator& List::ListIterator::operator--(int) 
{
	if (iptr)
		iptr = iptr->prev;
	return *this;

}
List::Iterator List::begin()	
{
	if (head->next != tail)
	{
		Iterator ite(head->next);
		return ite;
	}
	else
	{
		Iterator ite(nullptr);
		return ite;
	}
}
List::Iterator List::end()		
{
	if (tail->prev != head)
	{
		Iterator ite(tail->prev);
		return ite;
	}
	else
	{
		Iterator ite(nullptr);
		return ite;
	}
}
List::~List()
{
	node* temp = nullptr;
	while (head != nullptr)
	{
		temp = head;
		head=head->next;
		//delete temp;
	}
}
