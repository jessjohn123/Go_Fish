//#include "Card.h"
#pragma once
template<typename Item>
class Stack
{
private:

	// Can't have a linked list without this guy
	// This is a node for a singly linked list
	struct Node
	{
		Item m_data;	// What we're holding (the "element")
		Node* m_next;	// Pointer to the next one in the list
		
	};

	Node* m_top;		// Points to the most recent node
	int m_currSize;		// Current number of things allocated

public:

	// Def ctor
	// Create an empty list
	//template<typename Item>
	Stack();

	// Dtor
	//template<typename Item>
	~Stack();

	// Get the number of nodes
	//template<typename Item>
	int GetCurrSize() const
	{
		return m_currSize;
	}

	// Add something to the top of the stack
	// In:	_info		The thing to add
	//
	// Return: True, if it was added
	//template<typename Item>
	bool Push(const Item& _info);

	// Remove something from the top of the stack
	// In:	_info		A "blank" Item
	//
	// Out: _info		The Item that was at the top
	// Return: True, if something was removed
	//template<typename Item>
	bool Pop(Item& _info);

	// Empty out the stack for re-use
	//template<typename Item>
	void Clear();

	// Check the top-most thing without removing it
	//template<typename Item>
	const Item* Peek() const;
};


//#include "stdafx.h"


// Def ctor
// Create an empty list
template<typename Item>
Stack<Item>::Stack()
{
	m_top = NULL;
	m_currSize = 0;
}


// Dtor
template<typename Item>
Stack<Item>::~Stack()
{
	Clear();
}


// Add something to the top of the stack
// In:	_info		The thing to add
//
// Return: True, if it was added
template<typename Item>
bool Stack<Item>::Push(const Item& _info)
{
	// Allocate each time we add something
	Node* newTop = new Node;

	// Did we run out of memory?
	if (NULL == newTop)
		return false;

	// Fill out the node
	newTop->m_data = _info;
	// Link us on top of everything else
	newTop->m_next = m_top;

	// Update the top pointer
	m_top = newTop;

	// Success
	++m_currSize;
	return true;
}


// Remove something from the top of the stack
// In:	_info		A "blank" Item
//
// Out: _info		The Item that was at the top
// Return: True, if something was removed
template<typename Item>
bool Stack <Item>::Pop(Item& _info)
{
	// Check to see if the stack is empty first
	if (!m_top)
		return false;

	// Copy over the value
	_info = m_top->m_data;

	// Need a temp pointer to avoid a memory leak
	Node* temp = m_top;
	m_top = m_top->m_next;
	delete temp;
	
	// Success
	--m_currSize;
	return true;
}

// Empty out the stack for re-use
template<typename Item>
void Stack <Item>::Clear()
{
	Node* temp = m_top;

	// Delete all of the nodes
	while (temp)
	{
		m_top = m_top->m_next;
		delete temp;
		temp = m_top;
	}

	// Set us back to 0
	m_currSize = 0;
}

// Check the top-most thing without removing it
template<typename Item>
const Item* Stack<Item>::Peek() const
{
	return (m_top ? &m_top->m_data : NULL);
}