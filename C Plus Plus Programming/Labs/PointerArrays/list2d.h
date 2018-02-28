#pragma once

#include "list.h"

class List2d
{
private:
	class Node
	{
	private:
		Node *m_nextNode, *m_previousNode;	// Previous and Next Nodes
		List m_item;

	public:
		// Constructor and destructor
		Node(List item);
		Node(List item, Node *nextNode, Node *previousNode);
		~Node();

		// Selectors
		List GetItem() const
		{
			return m_item;
		}

		List *GetItemReference()
		{
			return &m_item;
		}

		Node *GetNextNode()
		{
			return m_nextNode;
		}

		void SetNextNode(Node *node)
		{
			m_nextNode = node;
		}

		Node *GetPreviousNode()
		{
			return m_previousNode;
		}

		void SetPreviousNode(Node *node)
		{
			m_previousNode = node;
		}
	};

	Node *m_headNode;	        // A pointer pointing to the head node in the list
	int m_numberOfElements;		// The current size of the list

public:
	// Constructor and destructors
	List2d();
	~List2d();

	// Selectors
	List GetHead() const
	{
		return m_headNode->GetItem();
	}

	List GetTail() const
	{
		return m_headNode->GetPreviousNode()->GetItem();
	}

	int GetSize() const
	{
		return m_numberOfElements;
	}

	// Modifiers
	void AddNode(List item);		// Add a data item to the tail of the list

	void AddNode(List item, int index);

	void RemoveNode();	        // Remove the item at the head of the list

	void ClearList();			// Remove all items from the list

	Node *GetElement(int index);
};