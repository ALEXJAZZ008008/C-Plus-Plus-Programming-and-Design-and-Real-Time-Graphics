#include "list.h"

template<class m_template>

//Constructor
List<m_template>::List() : m_headNode(0), m_numberOfElements(0)
{

}

template<class m_template>

// Destructor
List<m_template>::~List()
{
	ClearList();
}

template<class m_template>

void List<m_template>::ClearList()
{
	while (GetSize())		// Delete the head node until the List is empty
	{
		RemoveNode();
	}
}

template<class m_template>

void List<m_template>::AddNode(m_template item)
{
	if (m_numberOfElements++ > 0)   // Check if the List is currently empty
	{
		new Node<m_template>(item, m_headNode, m_headNode->GetPreviousNode());   // Create new node on the tail
	}
	else
	{
		m_headNode = new Node<m_template>(item);   // Create the first node on the List
	}
}

template<class m_template>

void List<m_template>::AddNode(m_template item, int index)
{
	if (m_numberOfElements++ > 0)   // Check if the List is currently empty
	{
		Node<m_template> *temporaryNode = GetElement(index);

		new Node<m_template>(item, temporaryNode, temporaryNode->GetPreviousNode());
	}
	else
	{
		m_headNode = new Node<m_template>(item);   // Create the first node on the List
	}
}

template<class m_template>

void List<m_template>::RemoveNode()
{
	Node<m_template> *temporaryNode = m_headNode;

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

template<class m_template>

Node<m_template> *List<m_template>::GetElement(int index)
{
	if(index < m_numberOfElements)
	{
		Node<m_template> *temporaryNode = m_headNode;

		for (int n = 0; n < index; n++)
		{
			temporaryNode = temporaryNode->GetNextNode();
		}

		return temporaryNode;
	}

	return nullptr;
}