#include "graphnode.h"

#include <algorithm>

namespace Scenegraph
{
	GraphNode::GraphNode()
	{
	}

	GraphNode::~GraphNode()
	{
		if (getParent())
		{
			getParent()->removeChild(this);
		}

		for (auto child : m_childList)
		{
			child->setParent(nullptr);
		}
	}

	GraphNode::Errors GraphNode::addChild(GraphNode* pChild)
	{
		if (!pChild)
		{
			return Errors::NullArgument;
		}

		if (hasChild(pChild))
		{
			return Errors::ChildExists;
		}

		pChild->setParent(this);
		m_childList.push_back(pChild);

		return Errors::None;
	}

	GraphNode::Errors GraphNode::removeChild(GraphNode* pChild)
	{
		if (!pChild)
		{
			return Errors::NullArgument;
		}

		std::vector<GraphNode*>::iterator elementToRemove;
		Errors error = findChild(pChild, &elementToRemove);
		if (error != Errors::None)
		{
			return error;
		}

		m_childList.erase(elementToRemove);
		pChild->setParent(nullptr);

		return Errors::None;
	}

	bool GraphNode::hasChild(GraphNode* pChild)
	{
		return findChild(pChild, nullptr) == Errors::None;
	}

	GraphNode* GraphNode::getParent() const
	{
		return m_pParent;
	}

	void GraphNode::setParent(GraphNode* pParent)
	{
		// WARNING: only call from add child or remove child
		m_pParent = pParent;
	}

	GraphNode::Errors GraphNode::findChild(GraphNode* pChild, std::vector<GraphNode*>::iterator* pOutIterator)
	{
		if (!pOutIterator)
		{
			return Errors::NullArgument;
		}

		auto result = std::find(m_childList.begin(), m_childList.end(), pChild);
		if (result == m_childList.end())
		{
			return Errors::NotFound;
		}

		if (pOutIterator)
		{
			*pOutIterator = result;
		}
		return Errors::None;
	}
}
