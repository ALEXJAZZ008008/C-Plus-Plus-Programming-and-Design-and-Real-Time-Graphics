#pragma once

#include "node.h"

template<class m_template>

class List
{
private:
	Node<m_template> *m_headNode;	        // A pointer pointing to the head node in the queue
	int m_numberOfElements;		// The current size of the queue

public:
	// Constructor and destructors
	List();
	~List();

	// Selectors
	m_template GetHead() const
	{
		return m_headNode->GetItem();
	}

	m_template GetTail() const
	{
		return m_headNode->GetPreviousNode()->GetItem();
	}

	int GetSize() const
	{
		return m_numberOfElements;
	}

	// Modifiers
	void AddNode(m_template item);		// Add a data item to the tail of the queue

	void AddNode(m_template item, int index);

	void RemoveNode();	        // Remove the item at the head of the queue

	void ClearList();			// Remove all items from the queue

	Node<m_template> *GetElement(int index);
};