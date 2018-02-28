#include "list.h"

// Creates the first node of the list, and ensures that the list is circular
List::Node::Node(int item) : m_item(item)
{
	m_nextNode = m_previousNode = this;
}

// Creates a new node containing the data item, and inserts it between the previous and next nodes.
List::Node::Node(int item, Node *nextNode, Node *previousNode) : m_nextNode(nextNode), m_previousNode(previousNode), m_item(item)
{
	previousNode->m_nextNode = nextNode->m_previousNode = this;
}

// Deletes the node and links the previous and next nodes
List::Node::~Node()
{
	m_previousNode->m_nextNode = m_nextNode;
	m_nextNode->m_previousNode = m_previousNode;
}

//Constructor
List::List() : m_headNode(0), m_numberOfElements(0)
{

}

// Destructor
List::~List()
{
	
}

void List::ClearList()
{
	while (GetSize())		// Delete the head node until the List is empty
	{
		RemoveNode();
	}
}

void List::AddNode(int item)
{
	if (m_numberOfElements++ > 0)   // Check if the List is currently empty
	{
		new Node(item, m_headNode, m_headNode->GetPreviousNode());   // Create new node on the tail
	}
	else
	{
		m_headNode = new Node(item);   // Create the first node on the List
	}
}

void List::AddNode(int item, int index)
{
	if (m_numberOfElements++ > 0)   // Check if the List is currently empty
	{
		Node *temporaryNode = GetElement(index);

		new Node(item, temporaryNode, temporaryNode->GetPreviousNode());
	}
	else
	{
		m_headNode = new Node(item);   // Create the first node on the List
	}
}

void List::RemoveNode()
{
	Node *temporaryNode = m_headNode;

	if (--m_numberOfElements > 0)  // Check if the List contains one item before removal
	{
		m_headNode = m_headNode->GetNextNode();   // The head of the List moves to the next node
	}
	else
	{
		m_headNode = 0;	// The List is empty
	}

	delete temporaryNode;   // Delete the node
}

List::Node *List::GetElement(int index)
{
	if (index < m_numberOfElements)
	{
		Node *temporaryNode = m_headNode;

		for (int n = 0; n < index; n++)
		{
			temporaryNode = temporaryNode->GetNextNode();
		}

		return temporaryNode;
	}

	return nullptr;
}
