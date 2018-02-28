#pragma once

class List
{
private:
	class Node
	{
	private:
		Node *m_nextNode, *m_previousNode;	// Previous and Next Nodes
		int m_item;

	public:
		// Constructor and destructor
		Node(int item);
		Node(int item, Node *nextNode, Node *previousNode);
		~Node();

		// Selectors
		int GetItem() const
		{
			return m_item;
		}

		int *GetItemReference()
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
	List();
	~List();

	// Selectors
	int GetHead() const
	{
		return m_numberOfElements > 0 ? m_headNode->GetItem() : -1;
	}

	int GetTail() const
	{
		return m_numberOfElements > 0 ? m_headNode->GetPreviousNode()->GetItem() : -1;
	}

	int GetSize() const
	{
		return m_numberOfElements;
	}

	// Modifiers
	void AddNode(int item);		// Add a data item to the tail of the list

	void AddNode(int item, int index);

	void RemoveNode();	        // Remove the item at the head of the list

	void ClearList();			// Remove all items from the list

	Node *GetElement(int index);
};