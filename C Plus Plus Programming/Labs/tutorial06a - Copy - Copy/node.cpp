#include "node.h"

template<class m_template>

// Creates the first node of the list, and ensures that the list is circular
Node<m_template>::Node(m_template item) : m_item(item)
{
	m_nextNode = m_previousNode = this;
}

template<class m_template>

// Creates a new node containing the data item, and inserts it between the previous and next nodes.
Node<m_template>::Node(m_template item, Node<m_template> *nextNode, Node<m_template> *previousNode) : m_nextNode(nextNode), m_previousNode(previousNode), m_item(item)
{
	previousNode->m_nextNode = nextNode->m_previousNode = this;
}

template<class m_template>

// Deletes the node and links the previous and next nodes
Node<m_template>::~Node()
{
	m_previousNode->m_nextNode = m_nextNode;
	m_nextNode->m_previousNode = m_previousNode;
}