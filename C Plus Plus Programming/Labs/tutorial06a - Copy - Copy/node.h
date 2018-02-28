#pragma once

template<class m_template>

class Node
{
private:
	Node<m_template> *m_nextNode, *m_previousNode;	// Previous and Next Nodes
	m_template m_item;

public:
	// Constructor and destructor
	Node(m_template item);
	Node(m_template item, Node<m_template> *nextNode, Node<m_template> *previousNode);
	~Node();

	// Selectors
	m_template GetItem() const
	{
		return m_item;
	}

	m_template *GetItemReference()
	{
		return &m_item;
	}

	Node<m_template> *GetNextNode()
	{
		return m_nextNode;
	}

	void SetNextNode(Node<m_template> *node)
	{
		m_nextNode = node;
	}

	Node<m_template> *GetPreviousNode()
	{
		return m_previousNode;
	}

	void SetPreviousNode(Node<m_template> *node)
	{
		m_previousNode = node;
	}
};